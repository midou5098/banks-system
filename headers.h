#ifndef HEADERS_H
#include <sqlite3.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
class bank{
    public:
        std::string name;
        int inter;
        int type;
        int manager;
        int clients;
        int funds;
        int x,y;

};
class clients{
    public:
        std::string name;
        int score;
        std::string bank;
        int age;
        int pin;
};




class database{
    private:
        sqlite3* db;
    public:
    int opening(int choice);
    bool search(std::string name); 
    bool remove(bank nb);
    int modify(bank nb);
    int add(bank nb);
};


int database::add(bank nb){
    sqlite3_stmt* stmt;
    const char* sql;
            sql = "INSERT INTO banks (name, type, manager, interest, funds, clients, x, y) VALUES (? , ?, ? , ?, ?, ?, ?, ?);";
            sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
            sqlite3_bind_text(stmt,1,nb.name.c_str(),-1,SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, nb.y);
            sqlite3_bind_int(stmt, 3, nb.manager);
            sqlite3_bind_int(stmt, 4, nb.inter);
            sqlite3_bind_int(stmt, 5, nb.funds);
            sqlite3_bind_int(stmt, 6, nb.clients);
            sqlite3_bind_int(stmt, 7, nb.x);
            sqlite3_bind_int(stmt, 8, nb.y);
            if(sqlite3_step(stmt)!=SQLITE_DONE){
                return -1;
            }return (int)sqlite3_last_insert_rowid(db);

    return true;
}













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
        void line(int x1,int y1,int x2,int y2);
        void drawbut(int x,int y,int w,int h,int r,int g,int b,const int type);
        void drawtext(int x,int y,const std::string &text);
        SDL_Renderer* getrender(void){return renderer;}
        void drawtextarea(int x,int y,int w,int h);

};
void SDLinit::line(int x1,int y1,int x2,int y2){

    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
}
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
    SDL_SetRenderDrawColor(renderer,128, 54, 7,255);
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
std::vector<SDL_Texture*> tips;
class uinter{
    private:
        SDLinit& sdl;
        database& db;
        int current_frame=0,frame_delay=75,manag=0,focus=-1,res;
        Uint32 current_time,lframe_time=0;
        SDL_Texture *mbank,*bbank,*cbank,*ar,*nbutton,*cat,*jew,*somal,*adolf,*kirk,*star,*map;
        int vit=0,j;
        std::string name,inter,s1,s2,s3,s4,mes;
        bank newb;

    public:
        
        void layout(int* mode);
        void handle(SDL_Event& event,int &mode);
        void animate(SDL_Texture* seleanim,int px,int py,int w,int h,int dir);
        void draw(SDL_Texture* tex, int x,int y ,int w,int h);
        bool checkms(int msx,int msy,int x,int y,int w,int h);
        
        void shuffle(void){j=rand()%5;};
        uinter(SDLinit& sdlo,database& dbo);
    };
uinter::uinter(SDLinit& sdlo,database& dbo):sdl(sdlo),db(dbo){
    
    shuffle();

    SDL_Renderer* renderer=sdl.getrender();

    SDL_Surface* sb=IMG_Load("assets/bbank.png");
    SDL_Surface* sm=IMG_Load("assets/mbank.png");
    SDL_Surface* sc=IMG_Load("assets/cbank.png");
    SDL_Surface* ars=IMG_Load("assets/arrow.png");
    SDL_Surface* nbs=IMG_Load("assets/nbutton.png");
    SDL_Surface* cats=IMG_Load("assets/cat.png");
    SDL_Surface* jews=IMG_Load("assets/jew.png");
    SDL_Surface* ads=IMG_Load("assets/adolf.png");
    SDL_Surface* soms=IMG_Load("assets/somalian.png");
    SDL_Surface* kirks=IMG_Load("assets/kirk.png");
    SDL_Surface* stars=IMG_Load("assets/star.png");
    SDL_Surface* maps=IMG_Load("assets/map.png");

    for (int i = 1; i <= 5; i++) {
        std::ostringstream s ;
        s <<"assets/tip"<< i  << ".png";
        SDL_Surface* surface = IMG_Load(s.str().c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        tips.push_back(texture);
        SDL_FreeSurface(surface);
    }









    bbank=SDL_CreateTextureFromSurface(renderer,sb);
    mbank=SDL_CreateTextureFromSurface(renderer,sm);
    cbank=SDL_CreateTextureFromSurface(renderer,sc);
    ar=SDL_CreateTextureFromSurface(renderer,ars);
    nbutton=SDL_CreateTextureFromSurface(renderer,nbs);
    cat=SDL_CreateTextureFromSurface(renderer,cats);
    jew=SDL_CreateTextureFromSurface(renderer,jews);
    adolf=SDL_CreateTextureFromSurface(renderer,ads);
    somal=SDL_CreateTextureFromSurface(renderer,soms);
    kirk=SDL_CreateTextureFromSurface(renderer,kirks);
    star=SDL_CreateTextureFromSurface(renderer,stars);
    map=SDL_CreateTextureFromSurface(renderer,maps);
    
    
    SDL_FreeSurface(sb);
    SDL_FreeSurface(sc);
    SDL_FreeSurface(sm);
    SDL_FreeSurface(ars);
    SDL_FreeSurface(nbs);
    SDL_FreeSurface(cats);
    SDL_FreeSurface(ads);
    SDL_FreeSurface(jews);
    SDL_FreeSurface(soms);
    SDL_FreeSurface(kirks);
    SDL_FreeSurface(stars);
    SDL_FreeSurface(maps);
    

}
void uinter::draw(SDL_Texture* tex, int x,int y ,int w,int h){
    SDL_Rect rect={x,y,w,h};
    SDL_RenderCopy(sdl.getrender(),tex,NULL,&rect);
}

void uinter::layout(int* mode){
    if (*mode==1){ //for this time here is the layout : 0 for adding banks , 1 for view/modify , -1 for map , i all add mroe as the project goes on
        res=abs(vit%3);
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
        draw(tips[j],600,0,700,500);
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











    }else if (*mode==11){
        sdl.drawtext(530,100,"choose the manager :");
        SDL_SetRenderDrawColor(sdl.getrender(),0,0,0,255);
        sdl.line(320,150,320,600);
        sdl.line(640,150,640,600);
        sdl.line(960,150,960,600);
        draw(jew,20,150,300,200);
        draw(kirk,340,150,300,200);
        draw(adolf,660,150,300,200);
        draw(somal,990,150,300,200);
        sdl.drawtext(100,370,"name : shlomo");
        sdl.drawtext(95,420,"origin :   obvious...");
        sdl.drawtext(75,470,"pros :  +bank relations");
        sdl.drawtext(95,520,"cons :  -reputaion");

        sdl.drawtext(420,370,"name : kirk");
        sdl.drawtext(400,420,"origin :   america");
        sdl.drawtext(420,470,"pros :  +funds");
        sdl.drawtext(415,520,"cons :  -clients");

        sdl.drawtext(740,370,"name : adolf");
        sdl.drawtext(720,420,"origin :  germany");
        sdl.drawtext(730,470,"pros :  +reputaion");
        sdl.drawtext(705,520,"cons :  -banks relations");

        sdl.drawtext(1060,370,"name : captain");
        sdl.drawtext(1060,420,"origin :  somal");
        sdl.drawtext(1056,470,"pros :  +security");
        sdl.drawtext(1045,520,"cons :  -reputation");
        draw(nbutton,440,475,400,400);
        int xs;
        switch(manag){
            case 1 :
                xs=150;
                break;
            case 2:
                xs=450;
                break;
            case 3:
                xs=840-50;
                break;
            case 4:
                xs=1160-50;
                break;
        }
        if(manag!=0){
            animate(star,xs,560,60,60,-1);
        }
    }else if (*mode==12){
        SDL_Rect mapr={0,0,1280,720};
        SDL_RenderCopy(sdl.getrender(),map,NULL,&mapr);
    
    
    
    
    
    }else if (*mode==2){
        sdl.drawtext(500,300,"viewing bank");
    }else if (*mode==-1){
        sdl.drawtext(500,300,"viewing map");
    }
}
void uinter::handle(SDL_Event& event,int &mode){
    if (event.type==SDL_KEYDOWN){
        SDL_Keycode key=event.key.keysym.sym;
        if (key==SDLK_a){
            mode=1;
            shuffle();
        }else if(key==SDLK_v){
            mode=2;
            shuffle();
        }else if(key==SDLK_m){
            mode=-1;
            shuffle();
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
            switch(mode){
                case 1:
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
                            mode=11;
                            newb.clients=std::stoi(s4.c_str());
                            newb.inter=std::stoi(s2.c_str());
                            newb.funds=std::stoi(s3.c_str());
                            newb.name=s1;
                        }
                    }else{
                        focus=-1;
                    }break;
                case 11:
                    if(checkms(msx,msy,0,150,320,450)){
                        manag=1;
                    }else if(checkms(msx,msy,320,150,320,450)){
                        manag=2;
                    }else if(checkms(msx,msy,640,150,320,450)){
                        manag=3;
                    }else if(checkms(msx,msy,960,150,320,450)){
                        manag=4;
                    }else if (checkms(msx,msy,440,475,400,400)){
                        if (manag==-1){
                            mes="bruh twin choose a damn manager";
                        }else {
                            newb.manager=manag;
                            newb.type=res;
                            mode=12;
                        }
                    }
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