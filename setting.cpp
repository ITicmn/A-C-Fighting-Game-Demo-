#include <bits/stdc++.h>

#include "raylib.h"
#include "structure.h"
#include "class.h"

using namespace std;

auto setting(map<string,Texture2D> assets){
    map<string,array<int,4>> menu_set = {
    {"return",{0,0,230,107}}
    };
    Vector2 MousePosition;
    Font font = LoadFont("assets/alagard.png");
    bool run = true;
    while (run && !WindowShouldClose()){
        MousePosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (CheckCollisionPointRec(MousePosition,Rectangle{(float)menu_set["return"][0],(float)menu_set["return"][1],(float)menu_set["return"][2],(float)menu_set["return"][3]}))
                return "menu";
        }
        BeginDrawing();
            for (auto texture: menu_set)
                DrawTexture(assets[texture.first],texture.second[0],texture.second[1], WHITE);
            if (CheckCollisionPointRec(MousePosition,Rectangle{(float)menu_set["return"][0],(float)menu_set["return"][1],(float)menu_set["return"][2],(float)menu_set["return"][3]}))
                DrawTexture(assets["return_shader"],0,0, WHITE);
            ClearBackground(WHITE);
        EndDrawing();
    }
    return "menu";
}

