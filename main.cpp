#include <bits/stdc++.h>

const int screenWidth = 1920;
const int screenHeight = 1080;

#include "raylib.h"
#include "class.h"
#include "Object.h"
#include "map_data.h"
#include "character_data.h"
#include "map_initialize.cpp"
#include "Projectile.cpp"
#include "character_initialize.cpp"
#include "structure.h"
#include "setting.cpp"
#include "menu.cpp"
#include "choosing.cpp"
#include "level.cpp"
#include "arena.cpp"

using namespace std;

const string ASSET_PATH = "assets/";

int main(){

    InitWindow(screenWidth,screenHeight,"Game");

    SetTargetFPS(60);

    map<string,Texture2D> assets = {
    {"menu_background",LoadTexture("assets/menu_background.png")},
    {"menu_button_left",LoadTexture("assets/menu_button_left.png")},
    {"menu_button_left_shader",LoadTexture("assets/menu_button_left_shader.png")},
    {"menu_button_right",LoadTexture("assets/menu_button_right.png")},
    {"menu_button_right_shader",LoadTexture("assets/menu_button_right_shader.png")},
    {"menu_middle",LoadTexture("assets/menu_middle.png")},
    {"return",LoadTexture("assets/return.png")},
    {"return_shader",LoadTexture("assets/return_shader.png")},
    {"characters",LoadTexture("assets/characters.png")},
    {"maps",LoadTexture("assets/maps.png")},
    {"player1_card",LoadTexture("assets/player1_card.png")},
    {"player2_card",LoadTexture("assets/player2_card.png")},
    {"player1_pickbox",LoadTexture("assets/player1_pickbox.png")},
    {"player2_pickbox",LoadTexture("assets/player2_pickbox.png")},
    {"player1_selected",LoadTexture("assets/player1_selected.png")},
    {"player2_selected",LoadTexture("assets/player2_selected.png")},
    {"map_pickbox",LoadTexture("assets/map_pickbox.png")},
    {"map_selected",LoadTexture("assets/map_selected.png")},
    {"arena_player_card",LoadTexture("assets/arena_player_card.png")}
    };

    string destination = "menu";

    map<string,string> battle_setting;

    while (!WindowShouldClose()){
        if (destination == "menu")
            destination = menu(assets);
        else if (destination == "1v1"){
            auto result = one_character_map_choosing(assets);
            battle_setting = result.first;
            destination = result.second;
        }
        else if (destination == "1v1 battle")
            destination = arena(assets,battle_setting);
        else if (destination == "2v2"){
            auto result = two_character_map_choosing(assets);
            battle_setting = result.first;
            destination = result.second;
        }
        else if (destination == "setting")
            destination = setting(assets);
        else if (destination == "quit")
            break;
    }
    for (auto texture : assets)
        UnloadTexture(texture.second);
    CloseWindow();
    return 0;
}

