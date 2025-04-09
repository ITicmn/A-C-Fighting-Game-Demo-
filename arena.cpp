#include <bits/stdc++.h>

#include "raylib.h"
#include "structure.h"
#include "class.h"

using namespace std;

auto arena(map<string,Texture2D> assets, map<string,string> battle_setting){
    Vector2 MousePosition;
    Font font = LoadFont("assets/alagard.png");
    Texture2D Background;
    vector<Platform> Platforms;
    auto result = Load_Map(battle_setting["map"]);
    Background = result.first;
    Platforms = result.second;
    string arena_mode = "borderless";
    auto player1 = Load_Character(battle_setting["player_1"]);
    player1.player = "player1";
    auto player2 = Load_Character(battle_setting["player_2"]);
    player2.player = "player2";
    player2.facing = "left";
    vector<Projectile> projectiles;
    player1.pos.x = 300;
    player2.pos.x = 1500;
    bool run = true;
    while (run && !WindowShouldClose()){
        MousePosition = GetMousePosition();
        //Player1 Movement////////////////////////////////////////////////
        if (IsKeyDown(KEY_W)){
            player1.movement["up"] = true;
        }
        if (IsKeyDown(KEY_A)){
            player1.movement["left"] = true;
        }
        if (IsKeyDown(KEY_S)){
            player1.movement["down"] = true;
        }
        if (IsKeyDown(KEY_D)){
            player1.movement["right"] = true;
        }
        if (IsKeyUp(KEY_W)){
            player1.movement["up"] = false;
        }
        if (IsKeyUp(KEY_A)){
            player1.movement["left"] = false;
        }
        if (IsKeyUp(KEY_S)){
            player1.movement["down"] = false;
        }
        if (IsKeyUp(KEY_D)){
            player1.movement["right"] = false;
        }
        if (player1.ActionCD <= 0 && player1.Controllable == true){
            if (IsKeyDown(KEY_H)){
                if (player1.status == "inAir"){
                    if (player1.movement["down"] == true)
                        player1.act("Air Attack Downward");
                    else if (player1.movement["up"] == true)
                        player1.act("Air Attack Upward");
                    else
                        player1.act("Air Attack");
                }
                else if (player1.status == "onGround"){
                    if (player1.movement["down"] == true)
                        player1.act("Light Attack Downward");
                    else if (player1.movement["left"] == true && player1.movement["right"] == true || player1.movement["left"] == false && player1.movement["right"] == false)
                        player1.act("Light Attack Stand");
                    else if (player1.movement["left"] == true || player1.movement["right"] == true)
                        player1.act("Light Attack Forward");
                }
            }
            if (IsKeyDown(KEY_J)){
                if (player1.status == "inAir"){
                    if (player1.movement["down"] == true)
                        player1.act("Air Attack Downward");
                    else if (player1.movement["up"] == true)
                        player1.act("Air Attack Upward");
                    else
                        player1.act("Air Attack");
                }
                else if (player1.status == "onGround"){
                    if (player1.movement["down"] == true)
                        player1.act("Heavy Attack Downward");
                    else if (player1.movement["left"] == true && player1.movement["right"] == true || player1.movement["left"] == false && player1.movement["right"] == false)
                        player1.act("Heavy Attack Stand");
                    else if (player1.movement["left"] == true || player1.movement["right"] == true)
                        player1.act("Heavy Attack Forward");
                }
            }
            if (IsKeyDown(KEY_K))
                if (player1.status == "onGround")
                    player1.act("Dash");
        }
        else
            player1.ActionCD--;
        player1.update(screenWidth,screenHeight,arena_mode,Platforms,&projectiles);
        //Player2 Movement////////////////////////////////////////////////
        if (IsKeyDown(KEY_UP)){
            player2.movement["up"] = true;
        }
        if (IsKeyDown(KEY_LEFT)){
            player2.movement["left"] = true;
        }
        if (IsKeyDown(KEY_DOWN)){
            player2.movement["down"] = true;
        }
        if (IsKeyDown(KEY_RIGHT)){
            player2.movement["right"] = true;
        }
        if (IsKeyUp(KEY_UP)){
            player2.movement["up"] = false;
        }
        if (IsKeyUp(KEY_LEFT)){
            player2.movement["left"] = false;
        }
        if (IsKeyUp(KEY_DOWN)){
            player2.movement["down"] = false;
        }
        if (IsKeyUp(KEY_RIGHT)){
            player2.movement["right"] = false;
        }
        if (player2.ActionCD <= 0 && player2.Controllable == true){
            if (IsKeyDown(KEY_KP_4)){
                if (player2.status == "inAir"){
                    if (player2.movement["down"] == true)
                        player2.act("Air Attack Downward");
                    else if (player2.movement["up"] == true)
                        player2.act("Air Attack Upward");
                    else
                        player2.act("Air Attack");
                }
                else if (player2.status == "onGround"){
                    if (player2.movement["down"] == true)
                        player2.act("Light Attack Downward");
                    else if (player2.movement["left"] == true && player2.movement["right"] == true || player2.movement["left"] == false && player2.movement["right"] == false)
                        player2.act("Light Attack Stand");
                    else if (player2.movement["left"] == true || player2.movement["right"] == true)
                        player2.act("Light Attack Forward");
                }
            }
            if (IsKeyDown(KEY_KP_5)){
                if (player2.status == "inAir"){
                    if (player2.movement["down"] == true)
                        player2.act("Air Attack Downward");
                    else if (player2.movement["up"] == true)
                        player2.act("Air Attack Upward");
                    else
                        player2.act("Air Attack");
                }
                else if (player2.status == "onGround"){
                    if (player2.movement["down"] == true)
                        player2.act("Heavy Attack Downward");
                    else if (player2.movement["left"] == true && player2.movement["right"] == true || player2.movement["left"] == false && player2.movement["right"] == false)
                        player2.act("Heavy Attack Stand");
                    else if (player2.movement["left"] == true || player2.movement["right"] == true)
                        player2.act("Heavy Attack Forward");
                }
            }
            if (IsKeyDown(KEY_KP_6))
                if (player2.status == "onGround")
                    player2.act("Dash");
        }
        else
            player2.ActionCD--;
        player2.update(screenWidth,screenHeight,arena_mode,Platforms,&projectiles);
        //Interactions////////////////////////////////////////////////
        if (player1.Vulnerable){
            player1.CalculateDamage(projectiles, &player2);
            player1.CalculateKnockback(projectiles, &player2);
        }
        if (player2.Vulnerable){
            player2.CalculateDamage(projectiles, &player1);
            player2.CalculateKnockback(projectiles, &player1);
        }
        //Projectile Delete////////////////////////////////////////////////
        for (int i=0;i<projectiles.size();i++){
            if (!projectiles[i].exist)
                projectiles.erase(projectiles.begin()+i);
        }
        //Projectile Movement////////////////////////////////////////////////
        for (int i=0;i<projectiles.size();i++){
            projectiles[i].update(screenWidth,screenHeight,arena_mode,Platforms,player1,player2);
        }
        //Drawing////////////////////////////////////////////////
        BeginDrawing();
            DrawTexture(Background,0,0,WHITE);
            for (auto platform: Platforms){
                platform.render();
            }
            player1.render();
            player2.render();
            for (int i=0;i<projectiles.size();i++){
                if (projectiles[i].exist)
                    projectiles[i].render();
            }
            /////////////////////////////////////////////////////
            DrawTexture(assets["arena_player_card"],607,884,WHITE);
            DrawTextEx(font,"Player 1",Vector2{647,1015},20,2,BLACK);
            DrawTextEx(font,to_string((int)(player1.health/player1.maxhealth*100)).c_str(),Vector2{737,1005},50,2,BLACK);
            DrawTexture(assets["arena_player_card"],1165,884,WHITE);
            DrawTextEx(font,"Player 2",Vector2{1205,1015},20,2,BLACK);
            DrawTextEx(font,to_string((int)(player2.health/player2.maxhealth*100)).c_str(),Vector2{1295,1005},50,2,BLACK);
            ClearBackground(WHITE);
        EndDrawing();
        /////////////////////////////////////////////////////////
        if (player1.pos.y >= 1500){
            player1.health -= 100;
            player1.pos.x = 300;
            player1.pos.y = 0;
        }
        if (player2.pos.y >= 1500){
            player2.health -= 100;
            player2.pos.x = 1500;
            player2.pos.y = 0;
        }
        if (player1.health <= 0 || player2.health <= 0)
            run = false;
    }
    Unload_Character(player1);
    Unload_Character(player2);
    Unload_Map(Background,Platforms);
    return "menu";
}


