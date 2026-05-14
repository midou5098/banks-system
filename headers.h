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
        void drawswitch(int x,int y,int dir);
        SDL_Renderer* getrender(void){return renderer;}

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
        int current_frame=0,frame_delay=100;
        Uint32 current_time,lframe_time=0;
        SDL_Texture *mbank,*bbank,*cbank,*ar;
        int vit=0;

    public:
        uinter(SDLinit& sdlo);
        void layout(int* mode);
        void handle(SDL_Event& event,int &mode);
        void animate(SDL_Texture* seleanim,int px,int py,int w,int h,int dir);
        void draw(SDL_Texture* tex, int x,int y ,int w,int h);
};
uinter::uinter(SDLinit& sdlo):sdl(sdlo){
    SDL_Renderer* renderer=sdl.getrender();

    SDL_Surface* sb=IMG_Load("assets/bbank.png");
    SDL_Surface* sm=IMG_Load("assets/mbank.png");
    SDL_Surface* sc=IMG_Load("assets/cbank.png");
    SDL_Surface* ars=IMG_Load("assets/arrow.png");

    bbank=SDL_CreateTextureFromSurface(renderer,sb);
    mbank=SDL_CreateTextureFromSurface(renderer,sm);
    cbank=SDL_CreateTextureFromSurface(renderer,sc);
    ar=SDL_CreateTextureFromSurface(renderer,ars);
    
    
    SDL_FreeSurface(sb);
    SDL_FreeSurface(sc);
    SDL_FreeSurface(sm);
    SDL_FreeSurface(ars);
    

}
void uinter::draw(SDL_Texture* tex, int x,int y ,int w,int h){
    SDL_Rect rect={x,y,w,h};
    SDL_RenderCopy(sdl.getrender(),tex,NULL,&rect);
}

void uinter::layout(int* mode){
    if (*mode==0){ //for this time here is the layout : 0 for adding banks , 1 for view/modify , -1 for map , i all add mroe as the project goes on
        
        sdl.drawtext(500,400,"adding banks");
        switch(vit){
            case 0:
                draw(cbank,430,0,400,400);
                break;
            case 1:
                draw(mbank,500,200,150,150);
                break;
            case 2:
                draw(bbank,500,200,150,150);
                break;
        }
        animate(ar,350,165,100,70,-1);
        animate(ar,800,165,100,70,1);










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
void uinter::animate(SDL_Texture* seleanim,int px,int py,int w,int h,int dir){
        int W,H;
        SDL_QueryTexture(seleanim,NULL,NULL,&W,&H);
        int framewidth=W/6;
        int frameheight=H/6;
        SDL_Rect rect;
        rect.w=framewidth;
        rect.h=frameheight;
        int framex=current_frame%6;
        int framey=current_frame/6;
        rect.x=framex*framewidth;
        rect.y=framey*frameheight;
        SDL_Rect dst;
        dst.x=px;
        dst.y=py;
        dst.w=w;
        dst.h=h;
        current_time = SDL_GetTicks();
        if (current_time > lframe_time + frame_delay) {
            current_frame = (current_frame + 1) % 36; 
            lframe_time = current_time;
        }
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        if (dir==0){
            SDL_RenderCopy(sdl.getrender(), seleanim, &rect, &dst);
        }if(dir==1){
            SDL_RenderCopyEx(sdl.getrender(),seleanim,&rect,&dst,0.0,NULL,flip);
        }else{
            SDL_RenderCopy(sdl.getrender(),seleanim,&rect,&dst);

        }

}



#endif 