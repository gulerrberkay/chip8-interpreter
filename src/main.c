#include <stdio.h>
#include <stdlib.h>
#include "../include/chip8-core.h"
#include "../include/newlib.h"
#include <SDL2/SDL.h>


int main(){

    //set_graphs();
    //set_inputs();

    //SDL_Init(SDL_INIT_VIDEO);

    initialize_chip();
    load_rom();
    emulate_cycle();



    return 0;
}