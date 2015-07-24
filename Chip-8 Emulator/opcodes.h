//
//  opcodes.h
//  Chip-8 Emulator
//
//  Created by Aaron Halbert on 7/23/15.
//  Copyright (c) 2015 Aaron Halbert. All rights reserved.
//

#ifndef __Chip_8_Emulator__opcodes__
#define __Chip_8_Emulator__opcodes__

#include <stdio.h>
#include "main.h"

void opcode_0NNN(System *);
void opcode_00E0(System *);
void opcode_00EE(System *);
void opcode_1NNN(System *);
void opcode_2NNN(System *);
void opcode_3XNN(System *);
void opcode_4XNN(System *);
void opcode_5XY0(System *);
void opcode_6XNN(System *);
void opcode_7XNN(System *);
void opcode_8XY0(System *);
void opcode_8XY1(System *);
void opcode_8XY2(System *);
void opcode_8XY3(System *);
void opcode_8XY4(System *);
void opcode_8XY5(System *);
void opcode_8XY6(System *);
void opcode_8XY7(System *);
void opcode_8XYE(System *);
void opcode_9XY0(System *);
void opcode_ANNN(System *);
void opcode_BNNN(System *);
void opcode_CXNN(System *);
void opcode_DXYN(System *);
void opcode_EX9E(System *);
void opcode_EXA1(System *);
void opcode_FX07(System *);
void opcode_FX0A(System *);
void opcode_FX15(System *);
void opcode_FX18(System *);
void opcode_FX1E(System *);
void opcode_FX29(System *);
void opcode_FX33(System *);
void opcode_FX55(System *);
void opcode_FX65(System *);

#endif /* defined(__Chip_8_Emulator__opcodes__) */

