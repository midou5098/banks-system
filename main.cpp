#include "headers.h"





int main(void){
    int mode=-1;
    SDLinit sdl(1280,720);
    uinter uic(sdl);
    bool running =true;
    SDL_Event event;
    while (running){
        while(SDL_PollEvent(&event)){
            if (event.type==SDL_QUIT){
                running=false;
                
            }
            uic.handle(event, mode);}
        sdl.clear();
        uic.layout(&mode);

        sdl.present();

        }
        sdl.~SDLinit();
    }
    


