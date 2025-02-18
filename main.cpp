#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#include "raylib.h"
#include "Sqr.h"
float gap = 50.f;
const int screenWidth = 800;//Window parramiter 
const int screenHeight = 450;//Window parramiter 
int player = 1;
const int row=1,column=9;
bool wincondition=false;


void EndScreen(bool *wincondition, vector<vector<Sqr>> &Block){
    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0,0,0,80});
    DrawText("PRESS ENTER TO  TRY AGAIN", 100, 300, 40.0f, BLACK);
    if (IsKeyPressed(KEY_ENTER)){
        for(int x=0; x<row; x++){
            for(int y=0; y<column; y++){
                Block[x][y].status = 0;
                *wincondition = false;
                }
            }
        }
}

int checkwin(vector<vector<Sqr>> Block){
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
        for(int x=0; x<row; x++){
            for(int y=0; y<column; y++){
                if(Block[x][y].status == 0){
                    return 2;
                }
            }
        }
    }
    return 0;
}

vector<float> Min(vector<vector<float>>result){
    int min = result[0][0];
    int pos = 0;
    for(int x=0; x<(int)(result.size()); x++){
            if(result[x][0] < min){
                min = result[x][0];
                pos = x;
            }
        }
    
    return result[pos];
}

vector<float> Max(vector<vector<float>> result){
    int max = result[0][0];
    int pos = 0;
    for(int x=0; x<(int)(result.size()); x++){
            if(result[x][0] > max){
                max = result[x][0];
                pos = x;
            }
        }
    
    return result[pos];
}

vector<float> AI(int player, vector<vector<Sqr>> Block, float Layer){
    vector<vector<float>> result;
    int win = checkwin(Block);
    if (win != 2) { 
        return {((float)win / Layer), -1, -1};
    }
    for(int x=0; x<row; x++){
        for(int y=0; y<column; y++){
            if(Block[x][y].status==0){
                Block[x][y].status = player;
                win = checkwin(Block);
                if(win==2){
                    vector<float> temp = AI(-(player),Block,Layer+1);
                    temp[1] = x;
                    temp[2] = y;
                    result.push_back(temp);
                }
                else{ return {win*Layer,(float)x,(float)y}; }//wtf is ging on with the layer here why is it working if i multiply but not if i divide plzz help goooooodoododododododododddod??????!?!?!?!?!?!?1?/1?1
                Block[x][y].status = 0;
            }
        }
    }
    if(player == -1){
        return Min(result);
    }else if(player == 1){
        return Max(result);
    }else{
    return {0,0,0};}
}

void WinCondition(bool *wincondition, vector<vector<Sqr>> &Block){
    if(checkwin(Block)==-1){
            *wincondition = true;
            DrawText("CIRCLE WON", 260, 80, 40.0f, BLACK);
            EndScreen(wincondition, Block);
        }else if(checkwin(Block)== 1){
            *wincondition = true;
            DrawText("CROSS WON", 260, 80, 40.0f, BLACK);
            EndScreen(wincondition, Block);
        }else if(checkwin(Block)== 0){
            *wincondition = true;
            DrawText("GAME DRAW", 260, 80, 40.f, BLACK);
            EndScreen(wincondition, Block);
        }
}
    
vector<vector<Sqr>> Block(row, vector<Sqr>(column)); //need to be 9 X 10 for super tic tac tow

int main(){ //INT MAIN -------------------------------------------------------------->>
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
                    player = -(player);
                }
                if(Block[x][y].status == -1){
                    DrawTexture(P1, Block[x][y].recx, Block[x][y].recy, WHITE);
                }else if(Block[x][y].status == 1){
                    DrawTexture(P2, Block[x][y].recx, Block[x][y].recy, WHITE);
                }
            }
        }
        if((player == 1)&& (checkwin(Block)== 2)){
        vector<float> temp = AI(player, Block, 1);
        Block[temp[1]][temp[2]].status = player;
        player = -(player);}
        EndMode2D();
        EndDrawing();
        WinCondition(&wincondition, Block);
    }
    UnloadTexture(P1);
    UnloadTexture(P2);
    CloseWindow();
    return 0;
}