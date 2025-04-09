#include <bits/stdc++.h>

#include "raylib.h"
#include "structure.h"
#include "class.h"

using namespace std;

const string characters[2][7] = {{"Steve","","","","","",""},{"","","","","","",""}}, maps[1][4] = {{"map1","map2","map3","map4"}};

pair<map<string,string>,string> one_character_map_choosing(map<string,Texture2D> assets){
    map<string,string> choice = {
        {"player_1",""},
        {"player_2",""},
        {"map",""}
    };
    pair<map<string,string>,string> result={choice,"menu"};
    map<string,array<int,4>> menu_set = {
    {"return",{0,0,230,107}},
    {"player1_card",{0,852,746,229}},
    {"player2_card",{1174,852,746,229}}
    };
    int player1_pos[2] = {0,0}, player2_pos[2] = {0,0}, map_pos[2] = {0,0};
    bool player1_selected = false, player2_selected = false, map_selected = false;
    string state = "character";
    Vector2 MousePosition;
    Font font = LoadFont("assets/alagard.png");
    bool run = true;
    while (run && !WindowShouldClose()){
        MousePosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (CheckCollisionPointRec(MousePosition,Rectangle{(float)menu_set["return"][0],(float)menu_set["return"][1],(float)menu_set["return"][2],(float)menu_set["return"][3]}))
                return result;
        }
        if (state=="character"){
            if (!player1_selected){
                if (IsKeyPressed(KEY_W))
                    player1_pos[1] = max(0,player1_pos[1]-1);
                if (IsKeyPressed(KEY_S))
                    player1_pos[1] = min(1,player1_pos[1]+1);
                if (IsKeyPressed(KEY_A))
                    player1_pos[0] = max(0,player1_pos[0]-1);
                if (IsKeyPressed(KEY_D))
                    player1_pos[0] = min(6,player1_pos[0]+1);
                if (IsKeyPressed(KEY_H)){
                    choice["player_1"] = characters[player1_pos[1]][player1_pos[0]];
                    player1_selected = true;
                }
            }
            else{
                if (IsKeyPressed(KEY_J)){
                    choice["player_1"] = "";
                    player1_selected = false;
                }
            }
            if (!player2_selected){
                if (IsKeyPressed(KEY_UP))
                    player2_pos[1] = max(0,player2_pos[1]-1);
                if (IsKeyPressed(KEY_DOWN))
                    player2_pos[1] = min(1,player2_pos[1]+1);
                if (IsKeyPressed(KEY_LEFT))
                    player2_pos[0] = max(0,player2_pos[0]-1);
                if (IsKeyPressed(KEY_RIGHT))
                    player2_pos[0] = min(6,player2_pos[0]+1);
                if (IsKeyPressed(KEY_KP_4)){
                    choice["player_2"] = characters[player2_pos[1]][player2_pos[0]];
                    player2_selected = true;
                }
            }
            else{
                if (IsKeyPressed(KEY_KP_5)){
                    choice["player_2"] = "";
                    player2_selected = false;
                }
            }
            //Drawing////////////////////////////////////////////////
            BeginDrawing();
                for (auto texture: menu_set)
                    DrawTexture(assets[texture.first],texture.second[0],texture.second[1], WHITE);
                if (CheckCollisionPointRec(MousePosition,Rectangle{(float)menu_set["return"][0],(float)menu_set["return"][1],(float)menu_set["return"][2],(float)menu_set["return"][3]}))
                    DrawTexture(assets["return_shader"],0,0, WHITE);
                DrawTexture(assets["characters"],671,148, WHITE);
                DrawTextEx(font,"Player 1",Vector2{menu_set["player1_card"][0]+125,menu_set["player1_card"][1]+55},60,2,BLACK);
                DrawTextEx(font,"Player 2",Vector2{menu_set["player2_card"][0]+395,menu_set["player2_card"][1]+55},60,2,BLACK);
                if (player1_selected)
                    DrawTexture(assets["player1_selected"],671+84*player1_pos[0],148+84*player1_pos[1], WHITE);
                else
                    DrawTexture(assets["player1_pickbox"],671+84*player1_pos[0],148+84*player1_pos[1], WHITE);
                if (player2_selected)
                    DrawTexture(assets["player2_selected"],671+84*player2_pos[0],148+84*player2_pos[1], WHITE);
                else
                    DrawTexture(assets["player2_pickbox"],671+84*player2_pos[0],148+84*player2_pos[1], WHITE);
                ClearBackground(WHITE);
            EndDrawing();
            /////////////////////////////////////////////////////////
            if (player1_selected && player2_selected)
                state = "map";
        }
        else if (state == "map"){
            if (IsKeyPressed(KEY_J) || IsKeyPressed(KEY_KP_5)){
                player1_selected = false;
                player2_selected = false;
                map_selected = false;
                state = "character";
            }
            if (!map_selected){
                if (IsKeyPressed(KEY_W))
                    map_pos[1] = max(0,map_pos[1]-1);
                if (IsKeyPressed(KEY_S))
                    map_pos[1] = min(0,map_pos[1]+1);
                if (IsKeyPressed(KEY_A))
                    map_pos[0] = max(0,map_pos[0]-1);
                if (IsKeyPressed(KEY_D))
                    map_pos[0] = min(3,map_pos[0]+1);
                if (IsKeyPressed(KEY_H)){
                    choice["map"] = maps[map_pos[1]][map_pos[0]];
                    map_selected = true;
                }
                if (IsKeyPressed(KEY_UP))
                    map_pos[1] = max(0,map_pos[1]-1);
                if (IsKeyPressed(KEY_DOWN))
                    map_pos[1] = min(0,map_pos[1]+1);
                if (IsKeyPressed(KEY_LEFT))
                    map_pos[0] = max(0,map_pos[0]-1);
                if (IsKeyPressed(KEY_RIGHT))
                    map_pos[0] = min(3,map_pos[0]+1);
                if (IsKeyPressed(KEY_KP_4)){
                    choice["map"] = maps[map_pos[1]][map_pos[0]];
                    map_selected = true;
                }
            }
            //Drawing////////////////////////////////////////////////

                for (auto texture: menu_set)
                    DrawTexture(assets[texture.first],texture.second[0],texture.second[1], WHITE);
                if (CheckCollisionPointRec(MousePosition,Rectangle{(float)menu_set["return"][0],(float)menu_set["return"][1],(float)menu_set["return"][2],(float)menu_set["return"][3]}))
                    DrawTexture(assets["return_shader"],0,0, WHITE);
                DrawTexture(assets["maps"],671,148, WHITE);
                DrawTextEx(font,"Player 1",Vector2{menu_set["player1_card"][0]+125,menu_set["player1_card"][1]+55},60,2,BLACK);
                DrawTextEx(font,"Player 2",Vector2{menu_set["player2_card"][0]+395,menu_set["player2_card"][1]+55},60,2,BLACK);
                if (map_selected)
                    DrawTexture(assets["map_selected"],671+84*map_pos[0],148+84*map_pos[1], WHITE);
                else
                    DrawTexture(assets["map_pickbox"],671+84*map_pos[0],148+84*map_pos[1], WHITE);
                ClearBackground(WHITE);
            EndDrawing();
            /////////////////////////////////////////////////////////
            if (map_selected)
                break;
        }
    }
    result = {choice,"1v1 battle"};
    ClearBackground(WHITE);
    BeginDrawing();
    DrawTextEx(font,"LOADING...",Vector2{600,450},180,2,BLACK);
    EndDrawing();
    return result;
}

pair<map<string,string>,string> two_character_map_choosing(map<string,Texture2D> assets){
    map<string,string> choice = {
        {"player_1",""},
        {"player_2",""},
        {"map",""}
    };
    pair<map<string,string>,string> result={choice,"menu"};
    map<string,array<int,4>> menu_set = {
    {"return",{0,0,230,107}}
    };
    int player1_pos[2] = {0,0}, player2_pos[2] = {0,0}, map_pos[2] = {0,0};
    bool player1_selected = false, player2_selected = false, map_selected = false;
    string state = "character";
    Vector2 MousePosition;
    Font font = LoadFont("assets/alagard.png");
    bool run = true;
    while (run && !WindowShouldClose()){
        MousePosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (CheckCollisionPointRec(MousePosition,Rectangle{(float)menu_set["return"][0],(float)menu_set["return"][1],(float)menu_set["return"][2],(float)menu_set["return"][3]}))
                return result;
        }
        //Drawing////////////////////////////////////////////////
        BeginDrawing();
            for (auto texture: menu_set)
                DrawTexture(assets[texture.first],texture.second[0],texture.second[1], WHITE);
            if (CheckCollisionPointRec(MousePosition,Rectangle{(float)menu_set["return"][0],(float)menu_set["return"][1],(float)menu_set["return"][2],(float)menu_set["return"][3]}))
                DrawTexture(assets["return_shader"],0,0, WHITE);
            ClearBackground(WHITE);
        EndDrawing();
        /////////////////////////////////////////////////////////
    }
    result = {choice,"2v2 battle"};
    return result;
}
