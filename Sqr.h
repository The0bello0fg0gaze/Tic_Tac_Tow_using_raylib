#include "raylib.h"
#ifndef Playale_Square
#define Playale_Square
class Sqr{
    public:
    int recy = 0, recx = 0, status = 0;
    Rectangle Rec{recx,recy,50,50};
    void setRec(int type){
    if(type == 1){Rec = {recx, recy, 50, 50};}
    else if(type == 2){Rec = {recx, recy, 0, 0};}
    }
};
#endif