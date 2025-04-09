#include <bits/stdc++.h>

#include "raylib.h"
#include "structure.h"
#include "class.h"

using namespace std;

string level(map<string,Texture2D> assets){
    bool run = true;
    while (run && !WindowShouldClose()){
        if (IsKeyPressed(KEY_ESCAPE))
            setting(assets);
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    return "a";
}
