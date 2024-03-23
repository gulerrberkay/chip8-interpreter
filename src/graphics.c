#include "../include/graphics.h"

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int SCALE = 8;
SDL_Rect srcR, destR;

static SDL_Surface* createSurfaceFromArray(void* pixels, int width, int height) {
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 8, 8 ,0, 0, 0, 1);
    //SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(SDL_SWSURFACE, width, height, 1, SDL_PIXELFORMAT_INDEX1MSB);
    //SDL_Color colors[2] = {{0, 255, 0, 255}, {255, 0, 0, 255}};
    //SDL_SetPaletteColors(surface->format->palette, colors, 0, 2);

    if (!surface) {
        SDL_Log("Unable to create surface: %s", SDL_GetError());
    }
    return surface;
}

void render(SDL_Renderer* renderer){
    SDL_Surface* customSurface = createSurfaceFromArray(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
    customTexture = SDL_CreateTextureFromSurface(renderer, customSurface);
    SDL_FreeSurface(customSurface);
}

void update_screen(SDL_Renderer* renderer, SDL_Texture* customTexture){
    destR.h = 64;
    destR.w = 64;
    render(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, customTexture, NULL, &destR);
    SDL_RenderPresent(renderer);
}

int init_screen(){

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    
    window = SDL_CreateWindow( "CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    SDL_Surface* customSurface = createSurfaceFromArray(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
    customTexture = SDL_CreateTextureFromSurface(renderer, customSurface);
    SDL_FreeSurface(customSurface);

    if (!customSurface)
    {
        printf( "customSurface could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    } 
    
    return 0;
};

void deinit_screen(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit();
}