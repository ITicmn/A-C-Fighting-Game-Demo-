#include "raylib.h"
#include "character_data.h"

using namespace std;

class Steve{
    public:
        Vector2 pos = Vector2{0,0};
        Vector2 velocity = Vector2{0,0};
        Vector2 _size;
        Rectangle DamageBox = Rectangle{0,0,0,0};//rect on character texture
        float health = 1200;
        float maxhealth = 1200;
        map<string,float> damage;
        map<string,map<string,vector<Texture2D>>> assets;
        map<string,bool> movement = {
            {"left",false},
            {"right",false},
            {"up",false},
            {"down",false}
        };
        string player;
        string name = "Steve";
        string status = "inAir";
        string action = "Stand";
        string facing = "right";
        int AnimationFrame = 0;
        int AnimationCD = 0;
        int DefaultAnimationCD = 4;
        int ActionCD = 0;
        int ActionFrame = 0;
        int JumpChance = 3;
        bool Vulnerable = true;
        bool Attacking = false;
        bool Controllable = true;
        bool IsPressingJump = false;

        Steve(Texture2D texture, int x, int y, map<string,map<string,vector<Texture2D>>> assets, map<string,float> damage){
            this->_size = Vector2{texture.width,texture.height};
            this->pos.x = x;
            this->pos.y = y;
            this->assets = assets;
            this->damage = damage;
        }

        Rectangle get_rect(){
            return Rectangle{this->pos.x, this->pos.y, this->_size.x, this->_size.y};
        }

        Rectangle get_HitBox(){
            return Rectangle{this->pos.x, this->pos.y, this->_size.x, this->_size.y};
        }

        Rectangle get_DamageBox(){
            return Rectangle{this->pos.x + this->DamageBox.x, this->pos.y + this->DamageBox.y, this->DamageBox.width, this->DamageBox.width};
        }

        void update(int screenWidth, int screenHeight, string mode, vector<Platform> platforms, vector<Projectile>* projectiles){
            if (this->Controllable){
                auto movement = this->movement;
                if (movement["up"] == false && this->IsPressingJump == true){
                        this->IsPressingJump = false;
                }
                ///////////////////////////////////
                if (this->status == "inAir"){
                    if (movement["up"] == true && this->IsPressingJump == false && this->JumpChance > 0){
                        this->IsPressingJump = true;
                        this->velocity.y = movement["up"]*-30 + (9-this->JumpChance);
                        this->JumpChance--;
                    }
                }
                else if (this->status == "onWall")
                    this->velocity.y = 3;
                else if (this->status == "onGround"){
                    this->velocity.y += movement["up"]*-30;
                    if (this->velocity.y < 0){
                        this->IsPressingJump = true;
                        this->JumpChance--;
                        this->status = "inAir";
                    }
                }
                this->velocity.y = min((float)25,this->velocity.y+1+movement["down"]*3);
                this->pos.y = this->pos.y + this->velocity.y;
                ///////////////////////////////////
                bool floor = false;
                for (auto platform: platforms){
                    if (CheckCollisionRecs(this->get_rect(),platform.get_rect())){
                        if (velocity.y > 0){
                            this->pos.y = platform.pos.y - this->_size.y;
                            this->velocity.y = 0;
                            this->IsPressingJump = false;
                            this->JumpChance = 3;
                            this->status = "onGround";
                            floor = true;
                        }
                        else if (velocity.y < 0){
                            this->pos.y = platform.pos.y + platform._size.y;
                            this->velocity.y = 0;
                        }
                    }
                }
                ///////////////////////////////////
                if (mode != "borderless"){
                    if (!floor && this->pos.y + this->_size.y < screenHeight){
                        this->status = "inAir";
                    }
                    if (this->pos.y < 0){
                        this->pos.y = 0;
                        this->velocity.y = 0;
                    }
                    else if (this->pos.y + this->_size.y > screenHeight){
                        this->pos.y = screenHeight - this->_size.y;
                        this->velocity.y = 0;
                        this->IsPressingJump = false;
                        this->JumpChance = 3;
                        this->status = "onGround";
                    }
                }
                else{
                    if (!floor){
                        this->status = "inAir";
                    }
                }
                ///////////////////////////////////
                this->velocity.x = (movement["left"]*-1+movement["right"]*1) * 7;
                this->pos.x = this->pos.x + this->velocity.x;
                if (this->velocity.x > 0)
                    this->facing = "right";
                else if (this->velocity.x < 0)
                    this->facing = "left";
                ///////////////////////////////////
                for (auto platform: platforms){
                    if (CheckCollisionRecs(this->get_rect(),platform.get_rect())){
                        if (velocity.x > 0){
                            this->pos.x = platform.pos.x - this->_size.x;
                            this->velocity.x = 0;
                        }
                        else if (velocity.x < 0){
                            this->pos.x = platform.pos.x + platform._size.x;
                            this->velocity.x = 0;
                        }
                    }
                }
                ///////////////////////////////////
                if (mode != "borderless"){
                    if (this->pos.x < 0)
                        this->pos.x = 0;
                    else if (this->pos.x + this->_size.x > screenWidth)
                        this->pos.x = screenWidth - this->_size.x;
                }
                ///////////////////////////////////
                if (this->status == "onGround"){
                    if (this->velocity.x == 0)
                        this->action = "Stand";
                    else
                        this->action = "Walk";
                }
                else if (this->status == "inAir"){
                    if (this->velocity.y <= 0)
                        this->action = "Jump";
                    else if (this->velocity.y > 0)
                        this->action = "Drop";
                }
            }
            else{
                for (auto platform: platforms){
                    if (CheckCollisionRecs(this->get_rect(),platform.get_rect())){
                        if (velocity.y > 0){
                            this->pos.y = platform.pos.y - this->_size.y;
                            this->velocity.y = 0;
                        }
                        else if (velocity.y < 0){
                            this->pos.y = platform.pos.y + platform._size.y;
                            this->velocity.y = 0;
                        }
                    }
                }
                ///////////////////////////////////
                if (mode != "borderless"){
                    if (this->pos.y + this->_size.y < screenHeight){
                        this->status = "inAir";
                    }
                    if (this->pos.y < 0){
                        this->pos.y = 0;
                        this->velocity.y = 0;
                    }
                    else if (this->pos.y + this->_size.y > screenHeight){
                        this->pos.y = screenHeight - this->_size.y;
                        this->velocity.y = 0;
                    }
                }
            }
            this->act_update(projectiles);
        }

        auto act(string action){//Action Initialize
            this->action = action;
            if (this->action == "Dash"){
                this->Controllable = false;
                this->Vulnerable = false;
                this->velocity.x = this->velocity.x * 3;
            }
            else if (this->action == "Damaged"){
                this->Controllable = false;
                this->Vulnerable = false;
            }
            else if (this->action == "Light Attack Stand"){
                this->AnimationFrame = 0;
                this->Controllable = false;
                this->ActionFrame = 16;
            }
            else if (this->action == "Light Attack Forward"){
                this->AnimationFrame = 0;
                this->velocity.x *= 1.7;
                this->Controllable = false;
                this->ActionFrame = 16;
            }
            else if (this->action == "Light Attack Downward"){
                this->AnimationFrame = 0;
                this->Controllable = false;
                this->ActionFrame = 16;
            }
            else if (this->action == "Heavy Attack Stand"){
                this->AnimationFrame = 0;
                this->DefaultAnimationCD = 3;
                this->Controllable = false;
                this->ActionFrame = 30;
            }
            else if (this->action == "Heavy Attack Forward"){
                this->AnimationFrame = 0;
                this->DefaultAnimationCD = 3;
                this->Controllable = false;
                this->ActionFrame = 30;
            }
            else if (this->action == "Heavy Attack Downward"){
                this->AnimationFrame = 0;
                this->DefaultAnimationCD = 3;
                this->Controllable = false;
                this->ActionFrame = 27;
            }
            else if (this->action == "Air Attack Upward"){
                this->AnimationFrame = 0;
                this->Controllable = false;
                this->Attacking = true;
                this->ActionFrame = 16;
            }
            else if (this->action == "Air Attack Downward"){
                this->AnimationFrame = 0;
                this->pos.y += 42;
                this->Controllable = false;
                this->ActionFrame = 20;
            }
            else
                this->action = "Stand";
        }

        void act_update(vector<Projectile>* projectiles){
            if (this->action == "Dash"){
                this->pos.x += this->velocity.x;
                if (this->velocity.x >= 0){
                    this->velocity.x--;
                    if (this->velocity.x <= 0){
                        this->ActionCD = 5;
                        this->Controllable = true;
                        this->Vulnerable = true;
                    }
                }
                else if (this->velocity.x <= 0){
                    this->velocity.x++;
                    if (this->velocity.x >= 0){
                        this->ActionCD = 5;
                        this->Controllable = true;
                        this->Vulnerable = true;
                    }
                }
            }
            else if (this->action == "Jump"){}
            else if (this->action == "Drop"){}
            else if (this->action == "Damaged"){
                this->pos.x += this->velocity.x;
                this->pos.y += this->velocity.y;
                if (this->velocity.x >= 0){
                    this->velocity.x -= 1;
                    if (this->velocity.x <= 0){
                        this->Controllable = true;
                        this->Vulnerable = true;
                    }
                }
                else if (this->velocity.x <= 0){
                    this->velocity.x += 1;
                    if (this->velocity.x >= 0){
                        this->Controllable = true;
                        this->Vulnerable = true;
                    }
                }
                if (this->velocity.y > 0){
                    this->velocity.y = max(1.0f,this->velocity.y-1);
                }
                else if (this->velocity.y < 0){
                    this->velocity.y = min(-1.0f,this->velocity.y+1);
                }
            }
            else if (this->action == "Light Attack Stand"){
                this->ActionFrame--;
                if (ActionFrame == 12){
                    this->Attacking = true;
                    if (this->facing == "right")
                        this->DamageBox = Rectangle{72,28,52,39};
                    else if (this->facing == "left")
                        this->DamageBox = Rectangle{-22,28,52,39};
                }
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->Attacking = false;
                    this->DamageBox = Rectangle{0,0,0,0};
                    this->ActionCD = 15;
                }
            }
            else if (this->action == "Light Attack Forward"){
                this->ActionFrame--;
                if (this->ActionFrame == 12){
                    this->Attacking = true;
                    if (this->facing == "right")
                        this->DamageBox = Rectangle{72,28,52,39};
                    else if (this->facing == "left")
                        this->DamageBox = Rectangle{-22,28,52,39};
                }
                this->pos.x += this->velocity.x;
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->Attacking = false;
                    this->DamageBox = Rectangle{0,0,0,0};
                    this->ActionCD = 15;
                }
            }
            else if (this->action == "Light Attack Downward"){
                this->ActionFrame--;
                if (this->ActionFrame == 8){
                    this->Attacking = true;
                    if (this->facing == "right")
                        this->DamageBox = Rectangle{93,127,41,29};
                    else if (this->facing == "left")
                        this->DamageBox = Rectangle{0,127,41,29};
                }
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->Attacking = false;
                    this->DamageBox = Rectangle{0,0,0,0};
                    this->ActionCD = 20;
                }
            }
            else if (this->action == "Heavy Attack Stand"){
                this->ActionFrame--;
                if (this->ActionFrame == 18){
                    this->Attacking = true;
                    if (this->facing == "right")
                        this->DamageBox = Rectangle{67,40,72,29};
                    else if (this->facing == "left")
                        this->DamageBox = Rectangle{-32,40,72,29};
                }
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->Attacking = false;
                    this->DamageBox = Rectangle{0,0,0,0};
                    this->ActionCD = 35;
                    this->DefaultAnimationCD = 4;
                }
            }
            else if (this->action == "Heavy Attack Forward"){
                this->ActionFrame--;
                if (this->ActionFrame == 21)
                    this->velocity.x *= 2.9;
                if (this->ActionFrame == 18){
                    this->Attacking = true;
                    if (this->facing == "right")
                        this->DamageBox = Rectangle{67,40,72,29};
                    else if (this->facing == "left")
                        this->DamageBox = Rectangle{-32,40,72,29};
                }
                if (this->ActionFrame <= 18){
                    this->pos.x += this->velocity.x;
                }
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->Attacking = false;
                    this->DamageBox = Rectangle{0,0,0,0};
                    this->ActionCD = 35;
                    this->DefaultAnimationCD = 4;
                }
            }
            else if (this->action == "Heavy Attack Downward"){
                this->ActionFrame--;
                if (this->ActionFrame == 21)
                    this->pos.y -= 16;
                else if (this->ActionFrame == 18)
                    this->pos.y += 8;
                else if (this->ActionFrame == 15)
                    this->pos.y += 14;
                else if (this->ActionFrame == 12)
                    this->pos.y += 17;
                else if (this->ActionFrame == 9){
                    this->pos.y += 8;
                    if (this->facing == "right"){
                        Projectile projectile(this->player,this->assets["Projectile"][this->facing][0],this->pos.x+this->_size.x,this->pos.y+this->_size.y/4+4,12,0,500,this->damage["Projectile"],this->assets["Projectile"][this->facing]);
                        projectiles->push_back(projectile);
                    }
                    else{
                        Projectile projectile(this->player,this->assets["Projectile"][this->facing][0],this->pos.x,this->pos.y+this->_size.y/4+4,-12,0,500,this->damage["Projectile"],this->assets["Projectile"][this->facing]);
                        projectiles->push_back(projectile);
                    }
                }
                else if (this->ActionFrame == 6)
                    this->pos.y -= 4;
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->ActionCD = 35;
                    this->DefaultAnimationCD = 4;
                }
            }
            else if (this->action == "Air Attack Upward"){
                this->ActionFrame--;
                if (this->ActionFrame == 12)
                    this->velocity.y = -18;
                if (this->ActionFrame == 8)
                    this->pos.y -= 74;
                if (this->ActionFrame == 4)
                    this->pos.y -= 3;
                if (this->ActionFrame < 8){
                    this->pos.y += this->velocity.y;
                }
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->Attacking = false;
                    this->ActionCD = 25;
                }
            }
            else if (this->action == "Air Attack Downward"){
                this->ActionFrame--;
                if (this->ActionFrame == 16){
                    this->velocity.y = 32;
                    this->pos.y += 5;
                }
                if (this->ActionFrame == 12)
                    this->pos.y += 8;
                if (this->ActionFrame == 8){
                    this->pos.y -= 23;
                    this->DamageBox = Rectangle{70,109,110,16};
                    this->Attacking = true;
                }
                if (this->ActionFrame < 8){
                    this->pos.y += this->velocity.y;
                }
                if (this->ActionFrame <= 0){
                    this->Controllable = true;
                    this->Attacking = false;
                    this->DamageBox = Rectangle{0,0,0,0};
                    this->ActionCD = 25;
                }
            }
        }

        void CalculateDamage(vector<Projectile> projectiles, auto* players){
            if (CheckCollisionRecs(this->get_HitBox(),players->get_DamageBox()) && players->Attacking){
                this->act("Damaged");
                this->health -= players->damage[players->action];
                if (players->action == "Air Attack Upward"){}
                else if (players->action == "Air Attack Downward"){
                    players->ActionFrame = 0;
                }
            }
            for (auto projectile: projectiles){
                if (CheckCollisionRecs(this->get_HitBox(),projectile.get_rect()) && projectile.owner != this->player){
                    this->act("Damaged");
                    this->health -= projectile.damage;
                }
            }
        }

        void CalculateKnockback(vector<Projectile> projectiles, auto* players){
            if (CheckCollisionRecs(this->get_HitBox(),players->get_DamageBox()) && players->Attacking){
                if (players->action != "Air Attack Upward" && players->action != "Air Attack Downward"){
                    if (players->facing == "right"){
                        this->velocity.x = max(12.0f,22 * (1-this->health / this->maxhealth));
                    }
                    else if (players->facing == "left"){
                        this->velocity.x = min(-12.0f,-22 * (1-this->health / this->maxhealth));
                    }
                }
                else if (players->action == "Air Attack Upward")
                    this->velocity.y = -5;
                else if (players->action == "Air Attack Downward")
                    this->velocity.y = 5;
            }
            for (auto projectile: projectiles){
                if (CheckCollisionRecs(this->get_HitBox(),projectile.get_rect()) && projectile.owner != this->player){
                    if (projectile.velocity.x > 0){
                        this->velocity.x = 12;
                        this->velocity.y = 0;
                    }
                    else if (projectile.velocity.x < 0){
                        this->velocity.x = -12;
                        this->velocity.y = 0;
                    }
                    if (projectile.velocity.y > 0){
                        this->velocity.x = 0;
                        this->velocity.y = 5;
                    }
                    else if (projectile.velocity.y < 0){
                        this->velocity.x = 0;
                        this->velocity.y = -5;
                    }
                }
            }
        }

        void render(){
            DrawTexture(this->assets[this->action][this->facing][this->AnimationFrame],this->pos.x,this->pos.y,WHITE);
            if (this->AnimationCD <= 0){
                this->AnimationCD = DefaultAnimationCD;
                this->AnimationFrame++;
                if (this->AnimationFrame >= this->assets[this->action][this->facing].size())
                    this->AnimationFrame = 0;
            }
            else
                this->AnimationCD--;
        }
};
/*
class Swordsman{
    public:
        Vector2 pos = Vector2{0,0};
        Vector2 velocity = Vector2{0,0};
        Vector2 _size;
        Rectangle HitBox;
        map<string,vector<Texture2D>> assets;
        map<string,bool> movement = {
            {"left",false},
            {"right",false},
            {"up",false},
            {"down",false}
        };
        string name = "Swordsman";
        string status = "inAir";
        string action = "Stand";
        int AnimationFrame = 0;
        int AnimationCD = 0;
        int JumpChance = 3;
        bool IsPressingJump = false;

        Swordsman(Texture2D texture, int x, int y, map<string,vector<Texture2D>> assets){
            this->_size = Vector2{texture.width,texture.height};
            this->pos.x = x;
            this->pos.y = y;
            this->assets = assets;
        }

        Rectangle get_rect(){
            return Rectangle{this->pos.x,this->pos.y,this->_size.x,this->_size.y};
        }

        void update(int screenWidth, int screenHeight, string mode, vector<Platform> platforms){
            auto movement = this->movement;
            if (movement["up"] == false && this->IsPressingJump == true){
                    this->IsPressingJump = false;
            }
            this->velocity.x = (movement["left"]*-1+movement["right"]*1) * 7;
            this->pos.x = this->pos.x + this->velocity.x;
            if (mode != "borderless"){
                if (this->pos.x < 0)
                    this->pos.x = 0;
                else if (this->pos.x + this->_size.x > screenWidth)
                    this->pos.x = screenWidth - this->_size.x;
            }

            if (this->status == "inAir"){
                this->velocity.y = min((float)25,this->velocity.y+1);
                if (movement["up"] == true && this->IsPressingJump == false && this->JumpChance > 0){
                    this->IsPressingJump == true;
                    this->velocity.y = movement["up"]*-30 + (12-this->JumpChance);
                    this->JumpChance--;
                }
            }
            else if (this->status == "onWall")
                this->velocity.y = 3;
            else if (this->status == "onGround"){
                this->velocity.y = movement["up"]*-30;
                if (this->velocity.y < 0){
                    this->IsPressingJump = true;
                    this->JumpChance--;
                    this->status = "inAir";
                }
            }
            this->pos.y = this->pos.y + this->velocity.y;
            if (mode != "borderless"){
                if (this->pos.y < 0){
                    this->pos.y = 0;
                    this->velocity.y = 0;
                }
                else if (this->pos.y + this->_size.y > screenHeight){
                    this->pos.y = screenHeight - this->_size.y;
                    this->velocity.y = 0;
                    bool IsPressingJump = false;
                    this->JumpChance = 3;
                    this->status = "onGround";
                }
            }
            this->HitBox = get_rect();
        }

        void act(){
        }

        void render(){
            DrawTexture(this->assets[this->action][this->AnimationFrame],this->pos.x,this->pos.y,WHITE);
            if (this->AnimationCD <= 0){
                this->AnimationCD = 4;
                this->AnimationFrame++;
                if (this->AnimationFrame >= assets[this->action].size())
                    this->AnimationFrame = 0;
            }
            else
                this->AnimationCD--;
        }
};
*/
auto Load_Character(string character_name){
    map<string,map<string,vector<Texture2D>>> assets;
    map<string,map<string,string>> character_assets = character_assets_data[character_name];
    map<string,float> character_damage = character_damage_data[character_name];
    FilePathList path_list;
    for (auto act: character_assets){
        for (auto facing: act.second){
            path_list = LoadDirectoryFiles(facing.second.c_str());
            for (int i=0;i<path_list.capacity;i++){
                assets[act.first][facing.first].push_back(LoadTexture(path_list.paths[i]));
            }
        }
    }
    if (character_name == "Steve"){
        Steve character(assets["Walk"]["right"][0],0,0,assets,character_damage);
        return character;
    }/*
    else if (character_name == "Swordsman"){
        Swordsman character(assets["Stand"][0],0,0,assets,character_damage);
        return character;
    }*/
}

void Unload_Character(auto character){
    map<string,map<string,vector<Texture2D>>> assets = character.assets;
    for (auto act: assets){
        for (auto facing: act.second){
            for (auto texture: facing.second)
                UnloadTexture(texture);
        }
    }
}
