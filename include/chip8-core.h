#ifndef CHIP8_CORE_H
#define CHIP8_CORE_H

#include "opcodes.h"

void initialize_chip();
void load_rom();
void emulate_cycle();
void update_keypad();

#endif
