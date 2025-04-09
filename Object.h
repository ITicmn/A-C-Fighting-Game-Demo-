#ifndef OBJECT_H
#define OBJECT_H

#include "structure.h"

using namespace std;

class Object{
    public:
        Vector2 pos;
        Vector2 _size;
        string name;
        string status;
        string type;
        int AnimationFrame=0;

        Object(string name, float position[2], float size[2], string type){
            this->name = name;
            pos.x = position[0];
            pos.y = position[1];
            _size.x = size[0];
            _size.y = size[1];
        }

        Rectangle get_rect(){
            Rectangle rect = {this->pos.x,this->pos.y,this->_size.x,this->_size.y};
            return rect;
        }

        void update(int screenWidth, int screenHeight){
        }

        void render(){
        }
};

#endif // OBJECT_H
