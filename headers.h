#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
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
#include <tinyfiledialogs.h> // tinyfiledialogs was interrupting the sdl while i get the file which caused crashes and freezes sos i switched to nfd
#include <nfd/nfd.h>


class bank{
    public:
        std::string name;
        int inter;
        int type;
        int manager;
        int clients;
        int funds;
        double x,y;

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
    int opening(void);
    bank search(std::string name);
    bool remove(bank nb);
    int modify(bank nb);
    int add(bank nb);
};

int database::opening(void){
        
    

    nfdu8char_t *outPath;
    nfdu8filteritem_t filters[1] = { { "Source code", "db" }};
    nfdopendialogu8args_t args;
    args.filterList   = filters;
    args.filterCount  = 1;
    args.defaultPath  = nullptr;
    args.parentWindow = {0};
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outPath);
    }
    if(sqlite3_open(outPath,&db)!=SQLITE_OK) return 1; 
        int res = sqlite3_exec(db, "SELECT count(*) FROM sqlite_master;", nullptr, nullptr, nullptr);
        if (res!=SQLITE_OK){
            sqlite3_close(db);
            db = nullptr;
            return 0;
        }
        return 1;}
int database::add(bank nb){
    sqlite3_stmt* stmt;
    const char* sql;
            sql = "INSERT INTO banks (name, type, interest, funds, clients, manager, x, y) VALUES (? , ?, ? , ?, ?, ?, ?, ?);";
            sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
            sqlite3_bind_text(stmt,1,nb.name.c_str(),-1,SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, nb.type);
            sqlite3_bind_int(stmt, 3, nb.inter);
            sqlite3_bind_int(stmt, 4, nb.funds);
            sqlite3_bind_int(stmt, 5, nb.clients);
            sqlite3_bind_int(stmt, 6, nb.manager);
            sqlite3_bind_double(stmt, 7, nb.x);
            sqlite3_bind_double(stmt, 8, nb.y);
            int result = sqlite3_step(stmt);
            sqlite3_finalize(stmt); 
            if (result != SQLITE_DONE) {
                return -1;
            }
    return true;
}

bank database::search(std::string name){

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
        void animatepop();

};
void SDLinit::line(int x1,int y1,int x2,int y2){

    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
}
SDLinit::SDLinit(int w,int h){
    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
    TTF_Init();
    NFD_Init();
    IMG_Init(IMG_INIT_PNG);
    window=SDL_CreateWindow("fuckass bank",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    font1 =TTF_OpenFont("font.ttf",20);
}
SDLinit::~SDLinit(void){
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    NFD_Quit();
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
        int current_frame=0,frame_delay=75,manag=-1,focus=-1,res,nx,ny,wy=740,no=0,state=-1;
        Uint32 current_time,lframe_time=0,timer,ltimer=0;;
        SDL_Texture *mbank,*bbank,*cbank,*ar,*nbutton,*cat,*jew,*somal,*adolf,*kirk,*star,*map11,*map12,*map13,*map21,*map22,*map23,*map31,*map32,*map33,*ab,*sbu,*dbu,*lb,*nb,*wind,*load;
        int vit=0,j,worldx=-1280,worldy=-720,vx=0,vy=0,dragsx,dragsy,lsx,lsy;
        std::string name,inter,s1,s2,s3,s4,mes;
        SDL_Texture* mapst[9];
        SDL_Rect rect[9],windr;
        bank newb;
        bool isdrg=false,fs=false,popped=false,down=false,up=true;

    public:
        
        void layout(int* mode);
        void handle(SDL_Event& event,int &mode);
        void animate(SDL_Texture* seleanim,int px,int py,int w,int h,int dir);
        void renderit(int x,int y,int cased);
        void viewport(void);
        void draw(SDL_Texture* tex, int x,int y ,int w,int h);
        bool checkms(int msx,int msy,int x,int y,int w,int h);
        void window(void);
        void animatepop(void);
        
        void shuffle(void){j=rand()%5;};
        uinter(SDLinit& sdlo,database& dbo);
    };



void uinter::viewport(void){
    for(int i=0;i<9;i++){
        SDL_RenderCopy(sdl.getrender(),mapst[i],NULL,&rect[i]);
    }
 
}

void uinter::window(void){
    if(popped==true){
            animatepop();
    }
    if(wy<=-70){
        popped=false;
        up=false;
    }else if (wy>=760){
        popped=false;
        wy=740;
        state=-1;
        up=false;
        down=false;
    }

}







void uinter::animatepop(void){
    windr={-110,wy,1500,1000};
    
    timer=SDL_GetTicks();
    if(timer>ltimer+4  ){
        if(up==true && wy>-70){
            wy-=10;
            ltimer=timer;
            if(no+2<230){
                no+=2;
            }
        }else if (down==true && wy<760){
            wy+=10;
            ltimer=timer;
            if(no-2>0){
                no-=2;
            }
        }
    }

    
    
    
    

}






















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
    SDL_Surface* abs=IMG_Load("assets/buttons/addbnk.png");
    SDL_Surface* sbs=IMG_Load("assets/buttons/searchbnk.png");
    SDL_Surface* dbs=IMG_Load("assets/buttons/delbnk.png");
    SDL_Surface* ns=IMG_Load("assets/buttons/news.png");
    SDL_Surface* lbs=IMG_Load("assets/buttons/lockbnk.png");
    SDL_Surface* loa=IMG_Load("assets/buttons/load.png");
    SDL_Surface* win=IMG_Load("assets/ui/window.png");
    
    

    SDL_Surface* maps1=IMG_Load("assets/map/maptl.png");
    SDL_Surface* maps2=IMG_Load("assets/map/mapml.png");
    SDL_Surface* maps3=IMG_Load("assets/map/mapbl.png");
    SDL_Surface* maps4=IMG_Load("assets/map/mapmm.png");
    SDL_Surface* maps5=IMG_Load("assets/map/maptm.png");
    SDL_Surface* maps6=IMG_Load("assets/map/mapbm.png");
    SDL_Surface* maps7=IMG_Load("assets/map/maptr.png");
    SDL_Surface* maps8=IMG_Load("assets/map/mapmr.png");
    SDL_Surface* maps9=IMG_Load("assets/map/mapbr.png");





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
    ab=SDL_CreateTextureFromSurface(renderer,abs);
    sbu=SDL_CreateTextureFromSurface(renderer,sbs);
    dbu=SDL_CreateTextureFromSurface(renderer,dbs);
    lb=SDL_CreateTextureFromSurface(renderer,lbs);
    nb=SDL_CreateTextureFromSurface(renderer,ns);
    load=SDL_CreateTextureFromSurface(renderer,loa);
    wind=SDL_CreateTextureFromSurface(renderer,win);
    
    mapst[0]=SDL_CreateTextureFromSurface(renderer,maps1);
    mapst[1]=SDL_CreateTextureFromSurface(renderer,maps2);
    mapst[2]=SDL_CreateTextureFromSurface(renderer,maps3);
    mapst[3]=SDL_CreateTextureFromSurface(renderer,maps4);
    mapst[4]=SDL_CreateTextureFromSurface(renderer,maps5);
    mapst[5]=SDL_CreateTextureFromSurface(renderer,maps6);
    mapst[6]=SDL_CreateTextureFromSurface(renderer,maps7);
    mapst[7]=SDL_CreateTextureFromSurface(renderer,maps8);
    mapst[8]=SDL_CreateTextureFromSurface(renderer,maps9);
    
    
    
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
    SDL_FreeSurface(sbs);
    SDL_FreeSurface(abs);
    SDL_FreeSurface(dbs);
    SDL_FreeSurface(lbs);
    SDL_FreeSurface(ns);
    SDL_FreeSurface(win);
    SDL_FreeSurface(loa);
    

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
        sdl.drawtext(720,420,"origin :   germany");
        sdl.drawtext(730,470,"pros :  +reputaion");
        sdl.drawtext(705,520,"cons :  -banks relations");

        sdl.drawtext(1060,370,"name : captain");
        sdl.drawtext(1060,420,"origin :   somal");
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
    }else if (*mode==-1){
        if(!fs){
            rect[0]={worldx,worldy,1280,720};
            rect[1]={worldx,worldy+720,1280,720};
            rect[2]={worldx,worldy+1440,1280,720};

            rect[3]={worldx+1280,worldy,1280,720};
            rect[4]={worldx+1280,worldy+720,1280,720};
            rect[5]={worldx+1280,worldy+1440,1280,720};

            rect[6]={worldx+2480,worldy,1280,720};
            rect[7]={worldx+2480,worldy+720,1280,720};
            rect[8]={worldx+2480,worldy+1440,1280,720};
            viewport();
        }else{
            rect[0]={0,0,426,240};
            rect[1]={426,0,426,240};
            rect[2]={852,0,428,240};

            rect[3]={0,240,426,240};
            rect[4]={426,240,426,240};
            rect[5]={852,240,428,240};

            rect[6]={0,480,426,240};
            rect[7]={426,480,426,240};
            rect[8]={852,480,428,240};
            viewport();
        }
        SDL_Rect rec1={990,-105,350,300};
        SDL_Rect rec2={760,-105,350,300};
        SDL_Rect rec3={530,-105,350,300};
        SDL_Rect rec4={300,-105,350,300};
        SDL_Rect rec5={-25,560,200,200};
        SDL_Renderer* renderer=sdl.getrender();
        SDL_RenderCopy(renderer,ab,NULL,&rec1);
        SDL_RenderCopy(renderer,sbu,NULL,&rec2);
        SDL_RenderCopy(renderer,dbu,NULL,&rec3);
        SDL_RenderCopy(renderer,lb,NULL,&rec4);
        
        SDL_RenderCopy(renderer,nb,NULL,&rec5);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer,0,0,0,no);
        SDL_Rect fsr={0,0,1280,720};
        SDL_RenderFillRect(renderer,&fsr);
        window();
        SDL_RenderCopy(sdl.getrender(),wind,NULL,&windr);
        //SDL_Rect test={0,570,170,150};
        //SDL_SetRenderDrawColor(renderer,0,0,0,255);
        //SDL_RenderFillRect(renderer,&test);
        
        

        
    }else if (*mode==2){
        sdl.drawtext(500,300,"viewing bank");
        if(!mes.empty()){
            sdl.drawtext(300,690,mes.c_str());
        }
    }else if(*mode==12){
        rect[0]={160,90,320,180};
        rect[1]={480,90,320,180};
        rect[2]={800,90,320,180};

        rect[3]={160,270,320,180};
        rect[4]={480,270,320,180};
        rect[5]={800,270,320,180};

        rect[6]={160,450,320,180};
        rect[7]={480,450,320,180};
        rect[8]={800,450,320,180};
        viewport();
        draw(nbutton,440,475,400,400);
    }else if (*mode==13){
        sdl.drawtext(500,50,"<=FINAL REVIEW=>");
        SDL_SetRenderDrawColor(sdl.getrender(),0,0,0,255);
        sdl.line(426,100,426,600);
        sdl.line(854,100,854,600);

        switch(res){
            case 0:
                draw(cbank,20,20,400,400);
                sdl.drawtext(215,340,"country bank");
                break;
            case 1:
                draw(mbank,20,20,400,400);
                sdl.drawtext(130,340,"modern bank");
                break;
            case 2:
                draw(bbank,20,-30,400,400);
                sdl.drawtext(140,300,"billionaires bank");
                break;
        }

        switch(manag){
            case 1:
                draw(jew,450,100,400,200);
                sdl.drawtext(556,325," manager :   jew");
                sdl.drawtext(570,370,"name : shlomo");
                sdl.drawtext(565,420,"origin :   obvious...");
                sdl.drawtext(545,470,"pros :  +bank relations");
                sdl.drawtext(565,520,"cons :  -reputaion");
                break;
            case 2:
                draw(kirk,450,100,400,200);
                sdl.drawtext(556,325," manager :   fraud");
                sdl.drawtext(570,370,"name : kirk");
                sdl.drawtext(565,420,"origin :   america");
                sdl.drawtext(545,470,"pros :  +funds");
                sdl.drawtext(565,520,"cons :  -clinets");
                break;
            case 3:
                draw(adolf,450,100,400,200);
                sdl.drawtext(556,325," manager :  hero");
                sdl.drawtext(570,370,"name : adolf");
                sdl.drawtext(565,420,"origin :   germany");
                sdl.drawtext(545,470,"pros :  +reputation");
                sdl.drawtext(565,520,"cons :  -banks relations");
                break;
            case 4:
                draw(somal,450,100,400,200);
                sdl.drawtext(556,325," manager :   boss");
                sdl.drawtext(570,370,"name : captain");
                sdl.drawtext(565,420,"origin :   somal");
                sdl.drawtext(545,470,"pros :  +security");
                sdl.drawtext(565,520,"cons :  -reputaion");
        }
        rect[0]={890,120,120,80};
        rect[1]={1010,120,120,80};
        rect[2]={1130,120,120,80};

        rect[3]={890,180,120,80};
        rect[4]={1010,180,120,80};
        rect[5]={1130,180,120,80};

        rect[6]={890,260,120,80};
        rect[7]={1010,260,120,80};
        rect[8]={1130,260,120,80};
        viewport();
        s1="niggs.co";
        s2="20";
        s3="30";
        s4="545";
        sdl.drawtext(120,385,"name :         "+s1);
        sdl.drawtext(50,420,"interest rate :         "+s2+"%");
        sdl.drawtext(120,455,"funds :        "+s3+"billions");
        sdl.drawtext(120,490,"clients :      "+s4);
        sdl.drawtext(900,400,"coords : "+std::to_string(newb.x)+" , "+std::to_string(newb.y));
        sdl.drawtext(900,450,"location:   god knows where ....");
        if (isdrg){
            std::cout<<"dragging";
        }




        draw(nbutton,440,475,400,400);
    }else if(*mode==-2){
        sdl.drawtext(400,200,"press f to import a db ! ");
    }
}
void uinter::handle(SDL_Event& event,int &mode){
    if (event.type==SDL_KEYDOWN){
        SDL_Keycode key=event.key.keysym.sym;
        switch(mode){
            case 1:
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
                break;
            case -2:
                if(key==SDLK_f){
                    if(db.opening()==1){
                    mode=-1;
                }else{
                    mes="wrong db mf...";
                }
                }
                break;
            case -1:
                if(key==SDLK_f){
                    fs=!fs;
                }else if (key==SDLK_a){
                    mode=1;
                }else if(key==SDLK_ESCAPE){
                    if(state==1 && !down){
                        popped=true;
                        down=true;
                        up=false;
                        
                        
                    }
                }
                if(fs==false){
                    if(key==SDLK_RIGHT){
                        if ( worldx-40>=-2480){
                            worldx-=40;
                        }
                    }else if(key==SDLK_LEFT){
                        if (worldx+40<=0){
                            worldx+=40;
                        }
                    }else if(key==SDLK_UP){
                        if (worldy+40<=0){
                            worldy+=40;
                        }
                    }else if(key==SDLK_DOWN){
                        if (worldy-40>=-1440){
                            worldy-=40;
                        }
                    }
                }
                break;

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
                    break;
                case -1:
                    if (fs==false){
                        isdrg=true;
                        dragsx=event.button.x;
                        dragsy=event.button.y;
                        lsx=event.button.x;
                        lsy=event.button.y;
                    }
                    //thhe new pages : 20 search bank , 21 delete bank,22 lock bank(the boss) , 23 news, nah hold on , why overcomplicate it and add separate layouts ? i ll add a floating window for the search and the delete and the news ,and only add a layout for lock
                    if(checkms(msx,msy,1060,0,350,60)){
                        mode=1;
                    }else if(checkms(msx,msy,830,0,210,60)){
                        if (state==-1){
                            popped=true;
                            up=true;
                            down=false;
                            state=1;
                        }
                    }else if(checkms(msx,msy,600,0,210,60)){
                        mode=21;
                    }else if(checkms(msx,msy,370,0,210,60)){
                        mode=22;
                    }else if(checkms(msx,msy,0,570,170,150)){
                        mode=23;
                    }

                    break;
                case 12:{
                    if (checkms(msx,msy,160,90,1120,630)){
                        newb.x=((msx-320.0)/1120.0)*1280;
                        newb.y=((msy-180.0)/630.0)*720;
                        std::cout<<newb.x<<newb.y;
                        mode=13;
                    }

                    break;}
                case 13:
                    if (checkms(msx,msy,440,475,400,400)){
                        if(db.add(newb)!=1){
                            mes="bank addded";
                        }else{
                            mes="u fucked up twin";
                        }
                        mode=-1;
                    }
                    break;

                
                    


                    
            
        
        }
    }
    }else if (event.type==SDL_MOUSEMOTION){
        if(fs==false){
            if(isdrg){
                int drgdx=event.motion.x-lsx;
                int drgdy=event.motion.y-lsy;
                if ( worldx+drgdx*0.6f>=-2480 && worldx+drgdx*0.6f<=0){
                        worldx+=drgdx*0.6f;}
                if (worldy+drgdy*0.6f<=0 && worldy+drgdy*0.6f>=-1440){
                        worldy+=drgdy*0.6f;
                    }
                lsx = event.motion.x;  
                lsy = event.motion.y; 
        }

        }
    }else if (event.type==SDL_MOUSEBUTTONUP){
        if (mode==-1){
            isdrg=false;
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