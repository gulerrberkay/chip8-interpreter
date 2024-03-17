#ifndef GRAPHCIS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "opcodes.h"

extern unsigned char screen[SCREEN_SIZE];

//Screen dimension constants
const int SCREEN_WIDTH = 32;
const int SCREEN_HEIGHT = 64;

SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Surface* customSurface;


// Function to create SDL surface from array
static SDL_Surface* createSurfaceFromArray(unsigned char* pixels, int width, int height) {
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 8, 0 ,0, 0, 0, 0);
    if (!surface) {
        SDL_Log("Unable to create surface: %s", SDL_GetError());
    }
    return surface;
}

void update_screen(){

}

extern int setup_graphics(){
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return -1;
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            // Create SDL surface from array
            SDL_Surface* customSurface = createSurfaceFromArray(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            if (!customSurface)
            {
                printf( "customSurface could not initialize! SDL_Error: %s\n", SDL_GetError() );
                return -1;
            } 
            
            // Blit the custom surface to the window surface
            SDL_BlitSurface(customSurface, NULL, screenSurface, NULL);           
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }
    
    return 0;
};

void deinit_screen(){
    // Deinit safely.
    SDL_FreeSurface(customSurface);
    SDL_DestroyWindow( window );
    SDL_Quit();
}

#endif
