//
//  main.c
//  Chip-8 Emulator
//
//  Created by Aaron Halbert on 7/17/15.
//  Copyright (c) 2015 Aaron Halbert. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "opcodes.h"

int main(int argc, const char * argv[]) {
	
	System chip8;			// Declare a system struct
	
	reset(&chip8);			// Initialize the system
	load_rom(&chip8);		// Load the game ROM file
	
	for(;;) {
		emulate_cycle(&chip8);
		
		draw_screen(&chip8);
		
		store_keypad(&chip8);
	}
	
	
	
	
	return 0;
}

void reset(System * chip8) {
	
	unsigned char fontSet[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
	
	int i = 0;
	
	for (i = 0; i <= 4095; i++) {
		chip8->memory[i] = 0;
	}
	
	for (i = 0; i <= 15; i++) {
		chip8->V[i] = 0;
	}
		
	chip8->I = 0;

	chip8->pc = 0x200;		// Start reading code at position 512
	
	for (i = 0; i <= 2047; i++) {
		chip8->gfx[i] = 0;
	}
	
	chip8->opcode = 0;
	chip8->delayTimer = 0;
	chip8->soundTimer = 0;
	
	for (i = 0; i <= 15; i++) {
		chip8->stack[i] = 0;
	}
	
	chip8->sp = 0;
	
	for (i = 0; i <= 15; i++) {
		chip8->key[i] = 0;
	}
	
	chip8->drawFlag = 0;
	
	for (i = 0; i <= 79; i++) {	// Load fontset starting at 0x0
		chip8->memory[i] = fontSet[i];
	}
}

void load_rom(System * chip8) {
	FILE *fp;
	unsigned long lengthOfFile;
	
	fp = fopen("/Users/aaronhalbert/Google Drive/Nand2Tetris/Xcode/Chip-8 Emulator/c8games/15PUZZLE", "r");
	fseek(fp, 0, SEEK_END);		// Set stream position to EOF
	lengthOfFile = ftell(fp);	// Get current position of stream
	printf("file size in bytes = %lu\n", lengthOfFile);
	fseek(fp, 0, SEEK_SET);		// Set stream position to EOF
	fread(&chip8->memory[0x200], 1, lengthOfFile, fp);	// Read 1-byte chunks into chip8->memory[] starting at 0x200
	printf("First byte of program: %x\n", chip8->memory[512]);
	printf("Second byte of pogram: %x\n", chip8->memory[513]);
	printf("...\n");
	printf("Next to last byte: %x\n", chip8->memory[512+lengthOfFile-2]);
	printf("Last byte: %x\n", chip8->memory[512+lengthOfFile-1]);
	fclose(fp);
}

void emulate_cycle(System * chip8) {
	// First, fetch the opcode
	// Each opcode is 2 bytes, so read first half, shift, and OR with second
	chip8->opcode = ((chip8->memory[chip8->pc]) << 8) | (chip8->memory[chip8->pc+1]);
	
	// Second, decode and execute the opcode
	switch((chip8->opcode) & 0xF000) {	// look only at first 4 bits
		case 0x0000:
			switch(chip8->opcode) {
				case 0x00E0:
					opcode_00E0(chip8);
					printf("00E0 executed, pc = %x\n", chip8->pc);
					break;
				case 0x00EE:
					// return from subroutine
					break;
				default:
					// call RCA 1802 program at address NNN
					// only relevant when running on old machine
					// ignored by this emulator
					opcode_0NNN(chip8);
					break;
			}
			break;
		case 0x2000:
			opcode_2NNN(chip8);
			printf("2NNN executed, pc = %x\n", chip8->pc);
			for (int i = 0; i <= 15; i++) {
				printf("stack[%d] = %x\n", i, chip8->stack[i]);
			}
			break;
		case 0x3000:
			opcode_3XNN(chip8);
			printf("3XNN executed, pc = %x\n", chip8->pc);
			printf("v12 = %x\n", chip8->V[12]);
			break;
		case 0x4000:
			opcode_4XNN(chip8);
			printf("4XNN executed, pc = %x\n", chip8->pc);
			break;
		case 0x6000:
			opcode_6XNN(chip8);
			printf("6XNN executed, pc = %x\n", chip8->pc);
			printf("v1 is %x\n", chip8->V[1]);
			printf("v2 is %x\n", chip8->V[2]);
			printf("v3 is %x\n", chip8->V[3]);
			break;
		case 0xA000:
			opcode_ANNN(chip8);
			printf("ANNN executed, pc = %x\n", chip8->pc);
			printf("I = %x\n", chip8->I);
			break;
		case 0xF000:
			switch((chip8->opcode) & 0x00FF) {
				case 0x0007:
					
					break;
				case 0x000A:
					
					break;
				case 0x0015:
					
					break;
				case 0x0018:
					
					break;
				case 0x001E:
					
					break;
				case 0x0029:
					
					break;
				case 0x0033:
					
					break;
				case 0x0055:
					opcode_FX55(chip8);
					printf("FX55 executed, pc = %x\n", chip8->pc);
					break;
				case 0x0065:
					
					break;
			}
			break;
		default:
			printf("exiting, next opcode was %x\n", chip8->opcode);
			exit(0);
	}
}

void draw_screen(System * chip8) {

}

void store_keypad(System * chip8) {

}


