#include "raylib.h"

using namespace std;

class Projectile{
    public:
        Vector2 pos;
        Vector2 velocity;
        Vector2 _size;
        Vector2 start_pos;
        vector<Texture2D> assets;
        string owner;
        float damage;
        float MaxDistance;
        int AnimationFrame = 0;
        int AnimationCD = 0;
        bool exist = true;

        Projectile(string owner, Texture2D texture, int x, int y, int velocity_x, int velocity_y, float MaxDistance, float damage, vector<Texture2D> assets){
            this->owner = owner;
            this->_size = Vector2{texture.width,texture.height};
            this->pos.x = x;
            this->pos.y = y;
            this->start_pos.x = x;
            this->start_pos.y = y;
            this->velocity.x = velocity_x;
            this->velocity.y = velocity_y;
            this->MaxDistance = MaxDistance;
            this->damage = damage;
            this->assets = assets;
        }

        Rectangle get_rect(){
            return Rectangle{this->pos.x,this->pos.y,this->_size.x,this->_size.y};
        }

        void update(int screenWidth, int screenHeight, string mode, vector<Platform> platforms, auto player1, auto player2){
            this->pos.x += this->velocity.x;
            this->pos.y += this->velocity.y;
            if (sqrt(pow(this->pos.x-this->start_pos.x,2)+pow(this->pos.y-this->start_pos.y,2)) >= this->MaxDistance)
                this->exist = false;
            /*
            for (auto platform: platforms){
                if (CheckCollisionRecs(this->get_rect(),platform.get_rect()))
                    this->exist = false;
            }
            */
            if (CheckCollisionRecs(this->get_rect(),player1.get_rect())){
                if (this->owner != player1.player)
                    this->exist = false;
            }
            if (CheckCollisionRecs(this->get_rect(),player2.get_rect())){
                if (this->owner != player2.player)
                    this->exist = false;
            }
            if (mode != "borderless"){
                if (this->pos.x < 0 || this->pos.x + this->_size.x > screenWidth || this->pos.y < 0 || this->pos.y + this->_size.y > screenHeight)
                    this->exist = false;
            }
        }

        void render(){
            DrawTexture(this->assets[this->AnimationFrame],this->pos.x,this->pos.y,WHITE);
            if (this->AnimationCD <= 0){
                this->AnimationCD = 3;
                this->AnimationFrame++;
                if (this->AnimationFrame >= this->assets.size())
                    this->AnimationFrame = 0;
            }
            else
                this->AnimationCD--;
        }
};
