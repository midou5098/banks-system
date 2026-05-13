#ifndef HEADERS_H
#define HEADERS_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class SDLinit{
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        TTF_Font* font1;
    public:
        SDLinit(void);
        ~SDLinit(void);
};
SDLinit::SDLinit(void){
    
}


