#include "../include/opcodes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Take a look at https://en.wikipedia.org/wiki/CHIP-8  -Opcode table section.

extern unsigned short opcode;
extern unsigned char memory[MEMORY_SIZE];
extern unsigned char V[REGS_NUM];
extern unsigned short I;
extern unsigned short pc;
extern unsigned char screen[SCREEN_SIZE];
extern unsigned short stack[STACK_SIZE];
extern unsigned short sp;
extern unsigned char key[KEYPAD_NUM];
extern unsigned char chip8_fontset;
extern unsigned char delay_timer;
extern unsigned char sound_timer;

static void cpuNULL() 
{
	// Do Nothing
	DEBUG_PRINT("Unknown opcode [0x0000]: 0x%X\n", opcode);
}

static void display_clear() 
{
	DEBUG_PRINT("Decoded opcode0 = 00E0 - Display clear.\n");
	memset(screen, 0x00, sizeof(screen)); // 00E0
}
static void return_sub() 
{
	// Returns from a subroutine - 00EE
	DEBUG_PRINT("Decoded opcode0 = 00EE - Return from subroutine.\n");
	pc = stack[sp];
	--sp;
}
static void (*Chip8_OPCODE_0[16])() = 
{
	display_clear, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL   , cpuNULL,
    cpuNULL      , cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, return_sub, cpuNULL,
};

static void OPCODE_0(){
    Chip8_OPCODE_0[(opcode&0x000F)]();
}

static void OPCODE_1() 
{
	// Jumps to address NNN - 1NNN
	pc = opcode & 0x0FFF;
	DEBUG_PRINT("Decoded opcode1 = 1NNN - Jumps to address %04X.\n",pc);
}

static void OPCODE_2() 
{
	// Calls subroutine at NNN - 2NNN
	stack[sp] = pc;
	++sp;
	pc = opcode & 0x0FFF;
	DEBUG_PRINT("Decoded opcode2 = 2NNN - Calls subroutine at %04X.\n",pc);

}

static void OPCODE_3() 
{
	// Skips the next instruction if VX equals NN 	
	if ( V[(opcode & 0x0F00)>>8] == (opcode & 0x00FF) )
		pc += 2;
	DEBUG_PRINT("Decoded opcode3 .\n");
}

static void OPCODE_4() 
{
	// Skips the next instruction if VX does not equal NN 
	if ( V[(opcode & 0x0F00)>>8] != (opcode & 0x00FF) )
		pc += 2;
	DEBUG_PRINT("Decoded opcode4 .\n");
}

static void OPCODE_5() 
{
	// Skips the next instruction if VX equals VY	
	if ( V[(opcode & 0x0F00)>>8] == V[(opcode & 0x00F0)>>4] )
		pc += 2;
	DEBUG_PRINT("Decoded opcode5 .\n");
}

static void OPCODE_6() 
{
	// Sets VX to NN - 6XNN
	V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
	DEBUG_PRINT("Decoded opcode6 = 6XNN .\n");
}

static void OPCODE_7() 
{
	// Adds NN to VX (carry flag is not changed) - 7XNN
	V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
	DEBUG_PRINT("Decoded opcode7 = 7XNN .\n");
}

static void op_8XY0()
{
	V[(opcode & 0x0F00)>>8] = V[(opcode & 0x00F0)>>4];
}

static void op_8XY1()
{
	V[(opcode & 0x0F00)>>8] |= V[(opcode & 0x00F0)>>4];
}

static void op_8XY2()
{
	V[(opcode & 0x0F00)>>8] &= V[(opcode & 0x00F0)>>4];
}

static void op_8XY3()
{
	V[(opcode & 0x0F00)>>8] ^= V[(opcode & 0x00F0)>>4];
}

static void op_8XY4()
{
	V[(opcode & 0x0F00)>>8] += V[(opcode & 0x00F0)>>4];
}

static void op_8XY5()
{
	if( V[(opcode & 0x0F00)>>8] >= V[(opcode & 0x00F0)>>4]){
		V[0xF] = 1;
	}
	else{
		V[0xF] = 0;
	}
	V[(opcode & 0x0F00)>>8] -= V[(opcode & 0x00F0)>>4];
}

static void op_8XY6()
{
	V[0xF] = V[(opcode & 0x0F00)>>8] && 0x1;
	V[(opcode & 0x0F00)>>8] = V[(opcode & 0x0F00)>>8] >> 1;
}

static void op_8XY7()
{
	if( V[(opcode & 0x00F0)>>4] >= V[(opcode & 0x0F00)>>8]){
		V[0xF] = 1;
	}
	else{
		V[0xF] = 0;
	}
	V[(opcode & 0x0F00)>>8] = V[(opcode & 0x00F0)>>4] - V[(opcode & 0x0F00)>>8];
}

static void op_8XYE()
{
	V[0xF] = (V[(opcode & 0x0F00)>>8] && 0x80) >> 7;
	V[(opcode & 0x0F00)>>8] = V[(opcode & 0x0F00)>>8] << 1;
}

static void (*Chip8_OPCODE_8[16])() = 
{
	op_8XY0, op_8XY1, op_8XY2, op_8XY3, op_8XY4, op_8XY5, op_8XY6, op_8XY7,
    cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, op_8XYE, cpuNULL,
};

static void OPCODE_8() 
{
	Chip8_OPCODE_8[(opcode&0x000F)]();
}

static void OPCODE_9() 
{
	if ( V[(opcode & 0x0F00)>>8] != V[(opcode & 0x00F0)>>4] )
		pc += 2;
		}

static void OPCODE_A() 
{
	// Sets I to the address NNN - ANNN
	I = opcode & 0x0FFF;
	DEBUG_PRINT("Decoded opcodeA = ANNN .\n");
}

static void OPCODE_B() 
{
	pc = V[0] + (opcode & 0x0FFF);
}

static void OPCODE_C() 
{
	srand(time(NULL)); // random seed every time.
	 V[(opcode & 0x0F00)>>8] = (rand() % 256) & (opcode & 0x00FF);
}

static void OPCODE_D() // DXYN
{
	// Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of
	// N pixels.
	unsigned char Vx = V[(opcode & 0x0F00) >> 8];
	unsigned char Vy = V[(opcode & 0x00F0) >> 4];
	unsigned char height = (opcode & 0x000F);
	unsigned char pixel;
	DEBUG_PRINT("Decoded opcodeD = DXYN .\n");


	V[0xF] = 0;
	for(int col = 0 ; col < height ; col++)
	{
		pixel = memory[I + col]; // 0xAF
		DEBUG_PRINT("Drawing col=%02X, pixel=%02X, on Vx=%02X, Vy=%02X.\n",col,pixel,Vx,Vy);
		for(int row = 0; row < 8; row++)
		{
			int bitMask = 0x80 >> row;
			if((screen[Vx + row + 64*(Vy+col)] & ((bitMask & pixel) >> (7-row))) == 1)
			{
				V[0xF] = 1;
			}
			screen[Vx + row + 64*(Vy+col)] ^= (bitMask & pixel) >> (7-row);
		}


	}

}

static void op_EXA1() //keyop
{

}

static void op_EX9E() //keyop
{
	
}

static void (*Chip8_OPCODE_E[16])() = 
{
	cpuNULL, op_EXA1, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
    cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, op_EX9E, cpuNULL,
};

static void OPCODE_E() 
{
	Chip8_OPCODE_E[(opcode&0x000F)]();
}

static void op_FX33() // TODO
{
	
}

//================================================================================================

static void op_FX15()
{
	delay_timer = V[(opcode & 0x0F00)>>8];
}

static void op_FX55()
{
	for(int k = 0; k < 16; k++){
		memory[I+k] = V[0x0 + k];
	}
}

static void op_FX65()
{
	for(int k = 0; k < 16; k++){
		V[0x0 + k] = memory[I+k];
	}
}

static void (*Chip8_FXX5[16])() = 
{
	cpuNULL, op_FX15, cpuNULL, cpuNULL, cpuNULL, op_FX55, op_FX65, cpuNULL,
    cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
};

// Big notation for additional decoding. OP_
static void OP_FXX5() 
{
	Chip8_FXX5[(opcode&0x00F0) >> 4]();
}
//================================================================================================

static void op_FX07()
{
	V[(opcode & 0x0F00)>>8] = delay_timer;
}

static void op_FX18()
{
	sound_timer = V[(opcode & 0x0F00)>>8];
}

static void op_FX29() // TODO
{
	I = 5*((opcode & 0x0F00)>>8); 
}

static void op_FX0A() //keyop
{
	
}

static void op_FX1E()
{
	I += V[(opcode & 0x0F00)>>8];
}

static void (*Chip8_OPCODE_F[16])() = 
{
	cpuNULL, cpuNULL, cpuNULL, op_FX33, cpuNULL, OP_FXX5, cpuNULL, op_FX07,
    op_FX18, op_FX29, op_FX0A, cpuNULL, cpuNULL, cpuNULL, op_FX1E, cpuNULL,
};

static void OPCODE_F() 
{
	Chip8_OPCODE_F[(opcode&0x000F)]();
}

static void (*Chip8Table[16])() = 
{
	OPCODE_0,
    OPCODE_1,
    OPCODE_2,
    OPCODE_3,
    OPCODE_4,
    OPCODE_5,
    OPCODE_6,
    OPCODE_7, 
    OPCODE_8,
    OPCODE_9,
    OPCODE_A,
    OPCODE_B,
    OPCODE_C,
    OPCODE_D,
    OPCODE_E,
    OPCODE_F,
};

/* External Functions*/
void decode_opcode(int a)
{
	Chip8Table[a]();
}
