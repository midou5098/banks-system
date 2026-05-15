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


class bank{
    std::string name;
    int inter;
    int manager;
    int clients;
    int funds;
};














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
        void drawbut(int x,int y,int w,int h,int r,int g,int b,const int type);
        void drawtext(int x,int y,const std::string &text);
        SDL_Renderer* getrender(void){return renderer;}
        void drawtextarea(int x,int y,int w,int h);

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
    SDL_SetRenderDrawColor(renderer,246, 154, 44,255);
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
void SDLinit::drawtextarea(int x,int y,int w,int h){
    
    SDL_Rect rect4={x,y,w,h};
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&rect4);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer,&rect4);
    
}

class uinter{
    private:
        SDLinit& sdl;
        bank newb;
        int current_frame=0,frame_delay=50,manag,focus=-1;
        Uint32 current_time,lframe_time=0;
        SDL_Texture *mbank,*bbank,*cbank,*ar,*nbutton,*cat;
        int vit=0;
        std::string name,inter,s1,s2,s3,s4,mes;

    public:
        uinter(SDLinit& sdlo);
        void layout(int* mode);
        void handle(SDL_Event& event,int &mode);
        void animate(SDL_Texture* seleanim,int px,int py,int w,int h,int dir);
        void draw(SDL_Texture* tex, int x,int y ,int w,int h);
        bool checkms(int msx,int msy,int x,int y,int w,int h);
};
uinter::uinter(SDLinit& sdlo):sdl(sdlo){
    SDL_Renderer* renderer=sdl.getrender();

    SDL_Surface* sb=IMG_Load("assets/bbank.png");
    SDL_Surface* sm=IMG_Load("assets/mbank.png");
    SDL_Surface* sc=IMG_Load("assets/cbank.png");
    SDL_Surface* ars=IMG_Load("assets/arrow.png");
    SDL_Surface* nbs=IMG_Load("assets/nbutton.png");
    SDL_Surface* cats=IMG_Load("assets/cat.png");


    bbank=SDL_CreateTextureFromSurface(renderer,sb);
    mbank=SDL_CreateTextureFromSurface(renderer,sm);
    cbank=SDL_CreateTextureFromSurface(renderer,sc);
    ar=SDL_CreateTextureFromSurface(renderer,ars);
    nbutton=SDL_CreateTextureFromSurface(renderer,nbs);
    cat=SDL_CreateTextureFromSurface(renderer,cats);
    
    
    SDL_FreeSurface(sb);
    SDL_FreeSurface(sc);
    SDL_FreeSurface(sm);
    SDL_FreeSurface(ars);
    SDL_FreeSurface(nbs);
    SDL_FreeSurface(cats);
    

}
void uinter::draw(SDL_Texture* tex, int x,int y ,int w,int h){
    SDL_Rect rect={x,y,w,h};
    SDL_RenderCopy(sdl.getrender(),tex,NULL,&rect);
}

void uinter::layout(int* mode){
    if (*mode==0){ //for this time here is the layout : 0 for adding banks , 1 for view/modify , -1 for map , i all add mroe as the project goes on
        int res=abs(vit%3);
        sdl.drawtextarea(180,340,300,30);
        sdl.drawtext(100,345,"name :");
        if(!s1.empty()){sdl.drawtext(185,345,s1.c_str());}
        sdl.drawtextarea(180,390,100,30);
        sdl.drawtext(30,395,"interest rate :");
        if(!s2.empty()){sdl.drawtext(185,395,s2.c_str());}
        sdl.drawtextarea(180,440,100,30);
        sdl.drawtext(100,445,"funds :");
        if(!s3.empty()){sdl.drawtext(185,445,s3.c_str());}
        sdl.drawtextarea(180,490,100,30);
        sdl.drawtext(100,495,"clients :");
        if(!s4.empty()){sdl.drawtext(185,495,s4.c_str());}
        draw(nbutton,440,475,400,400);
        if(!mes.empty()){sdl.drawtext(1000,100,mes.c_str());}
        animate(cat,1080,560,200,200,0);

        switch(res){
            case 0:
                draw(cbank,80,-60,400,400);
                sdl.drawtext(215,270,"country bank");
                break;
            case 1:
                draw(mbank,80,-60,400,400);
                sdl.drawtext(130,270,"modern bank");
                break;
            case 2:
                draw(bbank,80,-60,400,400);
                sdl.drawtext(140,270,"billionaires bank");
                break;
        }
        animate(ar,0,165,100,70,-1);
        animate(ar,450,165,100,70,1);











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
        if(focus!=-1){
            if (key>=32 && key<=126) {  
                    char c=(char)key;
                    if(focus==0 && s1.length()<20) s1+=c;

                    else if(focus==1 && s2.length()<20) s2+=c;
                    else if(focus==2 && s3.length()<10) s3+=c;
                    else if(focus==3 && s3.length()<10) s4+=c;}
                    
        }
//aint gon lie , miss u , but gawd dayum u dunno how much i m disgusted by you , the thought of u became a reason to vomit , not even hate or guilt , pure disgust .
    }else if (event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button==SDL_BUTTON_LEFT){
            int msx=event.button.x,msy=event.button.y;
            if (checkms(msx,msy,0,165,100,70)){
                vit-=1;
            }else if(checkms(msx,msy,450,165,100,70)){
                vit+=1;
            }else if (checkms(msx,msy,180,340,300,30)){
                focus=0;
            }else if (checkms(msx,msy,180,390,100,30)){
                focus=1;                
            }else if (checkms(msx,msy,180,440,100,30)){
                focus=2;
            }else if (checkms(msx,msy,180,490,100,30)){
                focus=3;
            }else if (checkms(msx,msy,440,475,400,400)){
                if (s1.empty() || s2.empty() || s3.empty() || s4.empty()){
                    mes="nigga fill all the fields bruh";
                }else{
                    mode=-1;
                }
            }else{
                focus=-1;
            }
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
bool uinter::checkms(int msx,int msy,int x,int y,int w,int h){
    if (msx<x+w && msx>x && msy<y+h && msy>y){
        return true;
    }
    return false;
}

#endif 