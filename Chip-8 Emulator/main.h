//
//  Header.h
//  Chip-8 Emulator
//
//  Created by Aaron Halbert on 7/23/15.
//  Copyright (c) 2015 Aaron Halbert. All rights reserved.
//

#ifndef Chip_8_Emulator_main_h
#define Chip_8_Emulator_main_h

struct system {
    unsigned char memory[4096];		// 4K RAM = 4,096 bytes
    unsigned char V[16];			// 16 8-bit data registers, V0 - VF
    unsigned short I;				// One 16-bit address register, I
    unsigned short pc;				// Program counter - why 0xFFF max?
    unsigned char gfx[64 * 32];		// 64x32 1-bit b&w screen
    unsigned short opcode;			// Stores the current 2-byte opcode
    unsigned char delayTimer;		// When set > 0 counts to 0 at 60Hz
    unsigned char soundTimer;		// When set > 0 counts to 0 at 60Hz
    unsigned short stack[16];		// To remember addresses
    unsigned char sp;				// Stack pointer, why a short?
    unsigned char key[16];			// Keypad state, array for multi?
    unsigned char drawFlag;
};

typedef struct system System;

void emulate_cycle(System *);
void draw_screen(System *);
void store_keypad(System *);
void load_rom(System *);
void reset(System *);

#endif


