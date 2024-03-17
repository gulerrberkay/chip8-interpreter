#include "../include/opcodes.h"
#include <string.h>
#include <stdio.h>

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
	// Do Nothing
	DEBUG_PRINT("Decoded opcode3 .\n");

}

static void OPCODE_4() 
{
	// Do Nothing
	DEBUG_PRINT("Decoded opcode4 .\n");

}

static void OPCODE_5() 
{
	// Do Nothing
	DEBUG_PRINT("Decoded opcode3 .\n");

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

static void OPCODE_8() 
{
	// Do Nothing
}

static void OPCODE_9() 
{
	// Do Nothing
}

static void OPCODE_A() 
{
	// Sets I to the address NNN - ANNN
	I = opcode & 0x0FFF;
	DEBUG_PRINT("Decoded opcodeA = ANNN .\n");
}

static void OPCODE_B() 
{
	// Do Nothing
}

static void OPCODE_C() 
{
	// Do Nothing
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
	for(int col = 0 ; col < height ; col++){
		pixel = memory[I + col];
		DEBUG_PRINT("Drawing col=%02X, pixel=%02X, on Vx=%02X, Vy=%02X.\n",col,pixel,Vx,Vy);
		screen[Vx + Vy*32] ^= pixel;

		if((screen[Vx + Vy*32] & pixel) != 0){
			V[0xF] = 1;
		}
	}

}

static void OPCODE_E() 
{
	// Do Nothing
}

static void OPCODE_F() 
{
	// Do Nothing
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
