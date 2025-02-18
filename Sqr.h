#include "raylib.h"
#ifndef Playale_Square
#define Playale_Square
class Sqr{
    public:
    float recy = 0.f, recx = 0.f, status = 0.f;
    Rectangle Rec{recx,recy,50,50};
    void setRec(int type){
    if(type == 1){Rec = {recx, recy, 50, 50};}
    else if(type == 2){Rec = {recx, recy, 0, 0};}
    }
};
class algo{
    public:
    
};
#endif