#include "raylib.h"
#include "map_data.h"

using namespace std;

class Platform{
    public:
        Vector2 pos;
        Vector2 _size;
        Texture2D asset;
        string name;
        string status;
        int AnimationFrame=0;
        bool Climbable;
        bool Dropable;
        bool Movable;

        Platform(Texture2D texture, int x, int y, bool Climable, bool Dropable, bool Movable){
            this->asset = texture;
            this->pos.x = x;
            this->pos.y = y;
            this->_size = Vector2{texture.width,texture.height};
            this->Climbable = Climable;
            this->Dropable = Dropable;
            this->Movable = Movable;
        }

        Rectangle get_rect(){
            return Rectangle{this->pos.x,this->pos.y,this->_size.x,this->_size.y};;
        }

        void update(int screenWidth, int screenHeight){
            if (this->Movable){}
        }

        void render(){
            DrawTexture(this->asset,this->pos.x,this->pos.y,WHITE);
        }
};

auto Load_Map(string map_name){
    pair<Texture2D,vector<Platform>> result;
    Texture2D Background;
    vector<Platform> Platforms;
    map<string,string> map_assets = map_assets_data[map_name];
    Background = LoadTexture(map_assets["Background"].c_str());
    for (auto obj: map_data[map_name]){
        if (obj.first != "Background"){
            Platforms.push_back(Platform(LoadTexture(map_assets[obj.first].c_str()),obj.second[0],obj.second[1],obj.second[2],obj.second[3],obj.second[4]));
        }
    }
    result = {Background,Platforms};
    return result;
}

void Unload_Map(Texture2D background, vector<Platform> platforms){
    UnloadTexture(background);
    for (auto platform: platforms)
        UnloadTexture(platform.asset);
}

