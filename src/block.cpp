#include "../include/block.h"

Block::Block(){
    state = false;
}

Block::Block(int insertedX,int insertedY,int insertedR,int insertedG,int insertedB){
    x = insertedX;
    y = insertedY;
    r = insertedR;
    g = insertedG;
    b = insertedB;
    state = true;
}

void Block::setColor(int insertedR,int insertedG,int insertedB){
    r = insertedR;
    g = insertedG;
    b = insertedB;
}

void Block::setPosition(int insertedX,int insertedY){
    x = insertedX;
    y = insertedY;
}

void Block::setState(bool s){
    state = s;
}

int* Block::getColor(){ //remember to implement delete
    int* rgb = new int[3];
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    return rgb;
}

void Block::rotate(){

}

void Block::moveLeft(){
    x = x - 1;
}

void Block::moveRight(){
    x = x + 1;
}

void Block::moveUp(){
    y = y - 1;
}

void Block::moveDown(){
    y = y + 1;
}

int Block::getX(){
    return x;
}

int Block::getY(){
    return y;
}

Block::~Block(){
    //nothing
}