#include <stdio.h>
/*
        System's memory map
----------------------------------
0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
0x200-0xFFF - Program ROM and work RAM
----------------------------------

*/

//Chip 8 font set. Each number or character is 4 pixels wide and 5 pixel high
unsigned char chip8_fontset[80] =
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

// 35 opcodes, 2 bytes
unsigned short opcode;

// 4K memory
unsigned char memory[4096];

// CPU regs-8 bits: V0-VE
unsigned char V[16];

// Index register, program counter
unsigned short I;
unsigned short pc;

// 2048 pixels (64 x 32) - B&W screen
unsigned char gfx[64 * 32];

// Timer regs - Counts 60 Hz
unsigned char delay_timer;
unsigned char sound_timer;

// Stack pointer: 16 levels
unsigned short stack[16];
unsigned short sp;

// Keypad
unsigned char key[16];

/*
// Function pointers for decode stage.
void (*Chip8Table[17])();
void (*Chip8Arithmetic[16])();

void (*Chip8Table[17]) = 
{
	cpuNULL      , cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, 
	cpuARITHMETIC, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
	cpuNULL
};

void (*Chip8Arithmetic[16]) = 
{
	cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL,
	cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL, cpuNULL
};
*/
void update_timer()
{
        // Update timers
    if(delay_timer > 0)
    --delay_timer;

    if(sound_timer > 0)
    {
    if(sound_timer == 1)
        printf("BEEP!\n");
    --sound_timer;
    } 
}


void cpuNULL() 
{
	// Do Nothing
}

void cpuARITHMETIC(){
	//Chip8Arithmetic[(opcode&0x000F)]();
}


/* Internal Functions */
void fetch()
{
	opcode =  memory[pc] << 8 | memory[pc+1];
	pc += 2;
}

void execute()
{
   // Chip8Table[(opcode&0xF000)>>12]();
}


/* External Functions */
void emulate_cycle()
{
    fetch();
    
    execute();  

  // Update timers

  update_timers();
}

void load_rom()
{
    // pointer demo to FILE
    FILE* demo;
    int display;
 
    // Creates a file "demo_file"
    // with file access as read mode
    demo = fopen("/home/berkay/git/chip8/roms/BLINKY", "rb");

    for(int i = 0; ;i++){
        // reading file
        display = fgetc(demo);
 
        // end of file indicator
        if (feof(demo))
            break;
 
        memory[i + 512] = display;

        // displaying every characters
        printf("%02X\n", display);

    }
    fclose(demo);
}

void initialize_chip()
{
    pc     = 0x200;  // Program counter starts at 0x200
    opcode = 0;      // Reset current opcode	
    I      = 0;      // Reset index register
    sp     = 0;      // Reset stack pointer

    // Clear display	
    // Clear stack
    // Clear registers V0-VF
    // Clear memory

    // Load fontset
    for(int i = 0; i < 80; ++i)
        memory[i] = chip8_fontset[i];	

    printf("Chip-8 is initialized. \n");
}
