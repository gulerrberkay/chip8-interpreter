#ifndef GRAPHCIS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "opcodes.h"

extern unsigned char screen[SCREEN_SIZE];


extern SDL_Window* window;
extern SDL_Renderer* renderer;

void update_screen(SDL_Renderer* renderer);
int init_screen();
void deinit_screen();

#endif
