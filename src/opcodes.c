#include "../include/opcodes.h"

extern unsigned short opcode;

// Function pointers for decode stage.
static void cpuNULL() 
{
	// Do Nothing
}

static void (*Chip8Arithmetic[16])() = 
{
	cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
	cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL
};

static void cpuARITHMETIC(){
    Chip8Arithmetic[(opcode&0x000F)]();
}

static void (*Chip8Table[17])() = 
{
	cpuNULL      , cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, 
	cpuARITHMETIC, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
	cpuNULL
};

/* External Functions*/
void decode_opcode(int a)
{
	Chip8Table[a]();
}
