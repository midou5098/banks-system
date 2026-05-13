#ifndef HEADERS_H

#include <SDL2/SDL_render.h>
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
        SDLinit(int w,int h);
        ~SDLinit();
        void clear();
        void present();
        void drawtext(int x,int y,const std::string &text);
};
SDLinit::SDLinit(int w,int h){
    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    window=SDL_CreateWindow("fuckass bank",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    font1 =TTF_OpenFont("font.ttf",20);
}
SDLinit::~SDLinit(void){
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
void SDLinit::clear(void){
    SDL_SetRenderDrawColor(renderer,140,210,60,255);
    SDL_RenderClear(renderer);
}
void SDLinit::present(void){
    SDL_RenderPresent(renderer);
}
void SDLinit::drawtext(int x,int y,const std::string &text){
    SDL_Color black = {0,0,0,255};
    SDL_Surface* surf=TTF_RenderText_Solid(font1,text.c_str(),black);
    int tw = surf->w;
    int th = surf->h;
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,surf);
    SDL_Rect rect={x,y,tw,th};
    SDL_RenderCopy(renderer,tex,NULL,&rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}


class uinter{
    private:
        SDLinit& sdl;
    public:
        uinter(SDLinit& sdlo);
        void layout(int* mode);
        void handle(SDL_Event& event,int &mode);
};
uinter::uinter(SDLinit& sdlo):sdl(sdlo){
}
void uinter::layout(int* mode){
    if (*mode==0){ //for this time here is the layout : 0 for adding banks , 1 for view/modify , -1 for map , i all add mroe as the project goes on
        sdl.drawtext(500,300,"adding banks");
    }else if (*mode==1){
        sdl.drawtext(500,300,"viewing bank");
    }else if (*mode==-1){
        sdl.drawtext(500,300,"viewing map");
    }
}
void uinter::handle(SDL_Event& event,int &mode){
    if (event.type==SDL_KEYDOWN){
        SDL_Keycode key=event.key.keysym.sym;
        if (key==SDLK_a){
            mode=0;
        }else if(key==SDLK_v){
            mode=1;
        }else if(key==SDLK_m){
            mode=-1;
        }


    }
    
}



#endif 