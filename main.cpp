#include "headers.h"





int main(void){
    SDLinit sdl(1280,720);
    bool running =true;
    SDL_Event event;
    while (running){
        while(SDL_PollEvent(&event)){
        if (event.type==SDL_QUIT){
            running=false;

        }
        sdl.clear();
        sdl.present();

        }
    }
    sdl.~SDLinit();

}

