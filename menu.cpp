#include <bits/stdc++.h>

#include "raylib.h"
#include "structure.h"
#include "class.h"

using namespace std;

string menu(map<string,Texture2D> assets){
    map<string,array<int,4>> menu_set = {
    {"top_left_button",{29,201,835,329}},
    {"bottom_left_button",{29,550,835,329}},
    {"top_right_button",{1054,201,835,329}},
    {"bottom_right_button",{1054,550,835,329}},
    {"middle",{736,213,449,653}}
    };
    Vector2 MousePosition;
    Font font = LoadFont("assets/alagard.png");
    bool run = true;
    while (run && !WindowShouldClose()){
        MousePosition = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            for (auto button: menu_set){
                if (CheckCollisionPointRec(MousePosition,Rectangle{(float)button.second[0],(float)button.second[1],(float)button.second[2],(float)button.second[3]})){
                    if (button.first == "top_left_button")
                        return "1v1";//1 v 1
                    else if (button.first == "bottom_left_button")
                        return "setting";//setting
                    else if (button.first == "bottom_right_button")
                        return "quit";//quit
                    else if (button.first == "top_right_button")
                        return "setting";//2 v 2
                }
            }
        }
        //Drawing////////////////////////////////////////////////
        BeginDrawing();
            DrawTexture(assets["menu_button_right"],menu_set["top_left_button"][0],menu_set["top_left_button"][1], WHITE);
            DrawTexture(assets["menu_button_left"],menu_set["bottom_left_button"][0],menu_set["bottom_left_button"][1], WHITE);
            DrawTexture(assets["menu_button_right"],menu_set["bottom_right_button"][0],menu_set["bottom_right_button"][1], WHITE);
            DrawTexture(assets["menu_button_left"],menu_set["top_right_button"][0],menu_set["top_right_button"][1], WHITE);
            DrawTexture(assets["menu_middle"],menu_set["middle"][0],menu_set["middle"][1], WHITE);
            DrawTextEx(font,"1 vs 1",Vector2{menu_set["top_left_button"][0]+265,menu_set["top_left_button"][1]+135},90,2,BLACK);
            DrawTextEx(font,"2 vs 2",Vector2{menu_set["top_right_button"][0]+305,menu_set["top_right_button"][1]+135},90,2,BLACK);
            DrawTextEx(font,"Setting",Vector2{menu_set["bottom_left_button"][0]+265,menu_set["bottom_left_button"][1]+135},90,2,BLACK);
            DrawTextEx(font,"Quit",Vector2{menu_set["bottom_right_button"][0]+305,menu_set["bottom_right_button"][1]+135},90,2,BLACK);
            for (auto button: menu_set){
                if (CheckCollisionPointRec(MousePosition,Rectangle{(float)button.second[0],(float)button.second[1],(float)button.second[2],(float)button.second[3]})){
                    if (button.first == "top_left_button")
                        DrawTexture(assets["menu_button_right_shader"],menu_set["top_left_button"][0],menu_set["top_left_button"][1], WHITE);
                    else if (button.first == "bottom_left_button")
                        DrawTexture(assets["menu_button_left_shader"],menu_set["bottom_left_button"][0],menu_set["bottom_left_button"][1], WHITE);
                    else if (button.first == "bottom_right_button")
                        DrawTexture(assets["menu_button_right_shader"],menu_set["bottom_right_button"][0],menu_set["bottom_right_button"][1], WHITE);
                    else if (button.first == "top_right_button")
                        DrawTexture(assets["menu_button_left_shader"],menu_set["top_right_button"][0],menu_set["top_right_button"][1], WHITE);
                }
            }
            ClearBackground(WHITE);
        EndDrawing();
        /////////////////////////////////////////////////////////
    }
    return "a";
}
