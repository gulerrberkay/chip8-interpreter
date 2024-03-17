#include "../include/opcodes.h"
#include <string.h>

extern unsigned short opcode;
extern unsigned char memory[MEMORY_SIZE];
extern unsigned char V[REGS_NUM];
extern unsigned short I;
extern unsigned short pc;
extern unsigned char screen[SCREEN_SIZE];
extern unsigned short stack[STACK_SIZE];
extern unsigned short sp;
extern unsigned char key[KEYPAD_NUM];

// Function pointers for decode stage.
static void cpuNULL() 
{
	// Do Nothing
}

static void display_clear() 
{
	 memset(screen, 0x00, sizeof(screen));
}

static void (*Chip8_OPCODE_0[16])() = 
{
	display_clear, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
    cpuNULL      , cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
};

static void OPCODE_0(){
    Chip8_OPCODE_0[(opcode&0x000F)]();
}

static void OPCODE_1() 
{
	// Do Nothing
}

static void OPCODE_2() 
{
	// Do Nothing
}

static void OPCODE_3() 
{
	// Do Nothing
}

static void OPCODE_4() 
{
	// Do Nothing
}

static void OPCODE_5() 
{
	// Do Nothing
}

static void OPCODE_6() 
{
	// Do Nothing
}

static void OPCODE_7() 
{
	// Do Nothing
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
	// Do Nothing
}

static void OPCODE_B() 
{
	// Do Nothing
}

static void OPCODE_C() 
{
	// Do Nothing
}

static void OPCODE_D() 
{
	// Do Nothing
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
