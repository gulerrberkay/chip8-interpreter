#include "../include/libs.h"


extern unsigned char V[REGS_NUM];
SDL_Window* window;
SDL_Surface* windowSurface;
SDL_Surface* customSurface;
SDL_Renderer* renderer;
SDL_Texture* customTexture;

int main(){
    DEBUG_PRINT("Debugging is enabled.\n");

    SDL_Event Event;

    initialize_chip();
    load_rom();
    init_screen();
    //set_inputs();

    
    

    int i = 25;
    while(1){
        SDL_PollEvent(&Event);
        if( Event.type == SDL_QUIT ) return 0;
        emulate_cycle();

        update_screen(renderer, customTexture);

        if((V[0xF])==1)
            update_screen(renderer, customTexture);


        update_keypad();

        i--;
    }
    


    deinit_screen();
    return 0;
}