//
//  opcodes.c
//  Chip-8 Emulator
//
//  Created by Aaron Halbert on 7/23/15.
//  Copyright (c) 2015 Aaron Halbert. All rights reserved.
//

#include "opcodes.h"
#include "main.h"

void opcode_0NNN(System * chip8) { // Calls RCA 1802 program at address NNN.
	// Ignored by modern interpreters
	chip8->pc += 2;
}

void opcode_00E0(System * chip8) { // Clears the screen. Done.
	for (int i = 0; i <= 2047; i++) {
		chip8->gfx[i] = 0;
	}
	chip8->pc += 2;
}

void opcode_00EE(System * chip8) { // Returns from a subroutine.

}

void opcode_1NNN(System * chip8) { // Jumps to address NNN.

}

void opcode_2NNN(System * chip8) { // Calls subroutine at NNN.
	// don't increment pc since jumping to subroutine
	// Are you sure? Would not want to pop back to the 2nnn opcode again..
	// need to make sure this is right...
	chip8->stack[chip8->sp] = chip8->pc;
	chip8->sp++;
	chip8->pc = chip8->opcode & 0x0FFF;
}

void opcode_3XNN(System * chip8) { // Skips the next instruction if VX equals NN.
	if (chip8->V[(chip8->opcode & 0x0F00) >> 8] == (chip8->opcode & 0x00FF)) {
		chip8->pc += 4;
	}
	else {
		chip8->pc += 2; // increment pc normally
	}
}

void opcode_4XNN(System * chip8) { // Skips the next instruction if VX doesn't equal NN. Done.
	if (chip8->V[(chip8->opcode & 0x0F00) >> 8] != (chip8->opcode & 0x00FF)) {
		chip8->pc += 4;
	}
	else {
		chip8->pc += 2; // increment pc normally
	}
}

void opcode_5XY0(System * chip8) { // Skips the next instruction if VX equals VY.

}

void opcode_6XNN(System * chip8) { // Sets VX to NN. Done.
	chip8->V[(chip8->opcode & 0x0F00) >> 8] = chip8->opcode & 0x00FF;
	chip8->pc += 2;
}

void opcode_7XNN(System * chip8) { // Adds NN to VX.

}

void opcode_8XY0(System * chip8) { // Sets VX to the value of VY.

}

void opcode_8XY1(System * chip8) { // Sets VX to VX or VY.

}

void opcode_8XY2(System * chip8) { // Sets VX to VX and VY.

}

void opcode_8XY3(System * chip8) { // Sets VX to VX xor VY.


}

void opcode_8XY4(System * chip8) { // Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.

}

void opcode_8XY5(System * chip8) { // VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

}

void opcode_8XY6(System * chip8) { // Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.[2]

}

void opcode_8XY7(System * chip8) { // Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

}

void opcode_8XYE(System * chip8) { // Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.[2]

}

void opcode_9XY0(System * chip8) { // Skips the next instruction if VX doesn't equal VY.

}

void opcode_ANNN(System * chip8) { // Sets I to the address NNN. Done.
	chip8->I = (chip8->opcode & 0x0FFF);
	chip8->pc += 2;
}

void opcode_BNNN(System * chip8) { // Jumps to the address NNN plus V0.

}

void opcode_CXNN(System * chip8) { // Sets VX to a random number, masked by NN.

}

void opcode_DXYN(System * chip8) { // Sprites stored in memory at location in index register (I), maximum 8bits wide. Wraps around the screen. If when drawn, clears a pixel, register VF is set to 1 otherwise it is zero. All drawing is XOR drawing (i.e. it toggles the screen pixels)

}

void opcode_EX9E(System * chip8) { // Skips the next instruction if the key stored in VX is pressed.

}

void opcode_EXA1(System * chip8) { // Skips the next instruction if the key stored in VX isn't pressed.

}

void opcode_FX07(System * chip8) { // Sets VX to the value of the delay timer.

}

void opcode_FX0A(System * chip8) { // A key press is awaited, and then stored in VX.

}

void opcode_FX15(System * chip8) { // Sets the delay timer to VX.

}

void opcode_FX18(System * chip8) { // Sets the sound timer to VX.

}

void opcode_FX1E(System * chip8) { // Adds VX to I.[3]

}

void opcode_FX29(System * chip8) { // Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.

}

void opcode_FX33(System * chip8) { // Stores the Binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)

}

void opcode_FX55(System * chip8) { // Stores V0 to VX in memory starting at address I. Done.
	for(int i = 0; i <= ((chip8->opcode & 0x0F00) >> 8); i++) {
		chip8->memory[(chip8->I) + i] = chip8->V[i];
	}
	chip8->pc += 2;
}

void opcode_FX65(System * chip8) { // Fills V0 to VX with values from memory starting at address I.[4]

}