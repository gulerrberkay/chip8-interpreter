#ifndef OPCODES_H
#define OPCODES_H

#define DEBUG 3

#if defined(DEBUG) && DEBUG > 0
 #define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
 #define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

#define SCREEN_SIZE 2048
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define KEYPAD_NUM 16
#define REGS_NUM 16

/* External Functions*/
void decode_opcode(int a);

#endif