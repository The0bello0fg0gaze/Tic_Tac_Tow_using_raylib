#include <cmath>
#include <iostream>
#include "raylib.h"
#include "Sqr.h"
int gap = 50;
const int screenWidth = 800;//Window parramiter 
const int screenHeight = 450;//Window parramiter 
int player = 1;
const int row=1,column=9;
bool wincondition=false;

int checkwin(Sqr Block[row][column]){
    for(int x=0; x<row; x++){
        if(
        (Block[x][0].status+Block[x][1].status+Block[x][2].status == -3) ||
        (Block[x][0].status+Block[x][4].status+Block[x][8].status == -3) ||
        (Block[x][0].status+Block[x][3].status+Block[x][6].status == -3) ||
        (Block[x][1].status+Block[x][4].status+Block[x][7].status == -3) ||
        (Block[x][2].status+Block[x][4].status+Block[x][6].status == -3) ||
        (Block[x][2].status+Block[x][5].status+Block[x][8].status == -3) ||
        (Block[x][3].status+Block[x][4].status+Block[x][5].status == -3) ||
        (Block[x][6].status+Block[x][7].status+Block[x][8].status == -3)
        ){ return -1; }
        else if(
        (Block[x][0].status+Block[x][1].status+Block[x][2].status == 3) ||
        (Block[x][0].status+Block[x][4].status+Block[x][8].status == 3) ||
        (Block[x][0].status+Block[x][3].status+Block[x][6].status == 3) ||
        (Block[x][1].status+Block[x][4].status+Block[x][7].status == 3) ||
        (Block[x][2].status+Block[x][4].status+Block[x][6].status == 3) ||
        (Block[x][2].status+Block[x][5].status+Block[x][8].status == 3) ||
        (Block[x][3].status+Block[x][4].status+Block[x][5].status == 3) ||
        (Block[x][6].status+Block[x][7].status+Block[x][8].status == 3)
        ){return 1;}
    }
    return 0;
}
    
Sqr Block[row][column]; //need to be 9 X 10 for super tic tac tow

int main(){
    InitWindow(screenWidth, screenHeight, "PvP_GAME");
    SetTargetFPS(60);
    Texture2D P1 = LoadTexture("player1.png");
    Texture2D P2 = LoadTexture("player2.png");
    
    for(int x=0; x<row; x++){
        for(int y=0; y<column; y++){
            Block[x][y].recy=(gap*(y%3))-50;
            Block[x][y].recx=(gap*(floor(y/3)))-50;
            Block[x][y].setRec(1);
        }
    }
    
    Camera2D camera = { 0 };
    camera.target = (Vector2){gap,gap};
    camera.offset = (Vector2){screenWidth/2.0f,screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    while (!WindowShouldClose()){
        ClearBackground(RAYWHITE);
        BeginDrawing();
        BeginMode2D(camera);
        for (int x=0; x<2; x++){
            DrawLine(-gap,x*gap,gap*2,x*gap,BLACK);
        }
        for (int x=0; x<2; x++){
            DrawLine(x*gap,-gap,x*gap,gap*2,BLACK);
        }
        
        for(int x=0; x<row; x++){
            for(int y=0; y<column; y++){
                Rectangle transform = Block[x][y].Rec;
                transform.x = (transform.x)+(screenWidth/2.0f)-gap;
                transform.y = (transform.y)+(screenHeight/2.0f)-gap;
                if ((CheckCollisionPointRec(GetMousePosition(), transform)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)&& 
                (Block[x][y].status == 0)&&(!wincondition)){
                    Block[x][y].status = player;
                    player = 0-(player);
                }
                if(Block[x][y].status == -1){
                    DrawTexture(P1, Block[x][y].recx, Block[x][y].recy, WHITE);
                }else if(Block[x][y].status == 1){
                    DrawTexture(P2, Block[x][y].recx, Block[x][y].recy, WHITE);
                }else if(wincondition){
                    if(0-player == 1){
                         DrawText("PLAYER 1 WON", -50, -70, 20.0f, BLACK);
                    }
                    else if(0-player == -1){
                        DrawText("PLAYER 2 WON", -50, -70, 20.0f, BLACK);
                    }
                        
                    
                }
            }
        }
        EndMode2D();
        EndDrawing();
        if(checkwin(Block)==-1){
            wincondition = true;
        }else if(checkwin(Block)== 1){
            wincondition = true;
        }
    }
    UnloadTexture(P1);
    UnloadTexture(P2);
    CloseWindow();
    return 0;
}