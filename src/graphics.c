#include "../include/graphics.h"

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int SCALE = 15;
SDL_Rect srcR, destR;


void render(SDL_Renderer* renderer)
{
    for (int i = 0; i < SCREEN_SIZE; i++)
    {
        int Vx = (i % SCREEN_WIDTH);
        int Vy = (i / SCREEN_WIDTH);
  /*
        if((i%64)!=0){
            printf("%d",screen[i]);
        }
        else{
            printf("\n");
            printf("%d",screen[i]);
             
        }
  */      
        if (screen[i] == 1)
        {
            SDL_RenderDrawPoint(renderer, Vx, Vy);
        }
    }
}

void update_screen(SDL_Renderer* renderer)
{
    render(renderer);
    SDL_RenderPresent(renderer);
}

int init_screen()
{
    if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    
    window = SDL_CreateWindow( "CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                                SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, SDL_WINDOW_SHOWN );
    if(window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer)
    {
        SDL_RenderSetScale(renderer,SCALE,SCALE);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black color
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    }

    return 0;
};

void deinit_screen()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}