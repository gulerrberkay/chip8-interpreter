#ifndef GRAPHCIS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "opcodes.h"

extern unsigned char screen[SCREEN_SIZE];


extern SDL_Window* window;
extern SDL_Surface* windowSurface;
extern SDL_Surface* customSurface;
extern SDL_Renderer* renderer;
extern SDL_Texture* customTexture;

void update_screen(SDL_Renderer* renderer, SDL_Texture* customTexture);
int init_screen();
void deinit_screen();

#endif
