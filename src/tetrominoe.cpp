#include "../include/tetrominoe.h"

Tetrominoe::Tetrominoe(){
    //case with 7 switches
    srand(time(0));

    //get random colors
    int randomR = rand() % 256;
    int randomG = rand() % 256;
    int randomB = rand() % 256;

    int selec = 0;//rand() % 7;
    switch (selec){
    case 0: //square
        blocks = new Block[4];
        numberBlocks = 4;
        for(int i = 0; i< 4;i++){
            blocks[i].setColor(randomR,randomG,randomB);
        }
        blocks[0].setPosition(4,0);
        blocks[1].setPosition(5,0);
        blocks[2].setPosition(4,-1);
        blocks[3].setPosition(5,-1);
        break;
    case 1: //inverted T
        blocks = new Block[4];
        numberBlocks = 4;
        for(int i = 0; i< 4;i++){
            blocks[i].setColor(randomR,randomG,randomB);
        }
        break;
    case 2: //line
        blocks = new Block[4];
        numberBlocks = 4;
        for(int i = 0; i< 4;i++){
            blocks[i].setColor(randomR,randomG,randomB);
        }
        break;
    case 3: //L left
        blocks = new Block[5];
        numberBlocks = 5;
        for(int i = 0; i< 5;i++){
            blocks[i].setColor(randomR,randomG,randomB);
        }
        break;
    case 4: //L right
        blocks = new Block[5];
        numberBlocks = 5;
        for(int i = 0; i< 5;i++){
            blocks[i].setColor(randomR,randomG,randomB);
        }
        break;
    case 5: //snake left
        blocks = new Block[4];
        numberBlocks = 4;
        for(int i = 0; i< 5;i++){
            blocks[i].setColor(randomR,randomG,randomB);
        }
        break;
    case 6: //snake right
        blocks = new Block[4];
        numberBlocks = 4;
        for(int i = 0; i< 4;i++){
            blocks[i].setColor(randomR,randomG,randomB);
        }
        break;
    default:
        break;
    }
}
 
void Tetrominoe::moveLeft(){ 
    bool move = true;
    for(int i = 0; i< numberBlocks; i++){
        if(blocks[i].getX() - 1 < 0){ //collision
            move = false;
        }
    }
    if(move){
        for(int i = 0; i< numberBlocks; i++){
            blocks[i].moveLeft();
        }
    }
}

void Tetrominoe::moveRight(){
    bool move = true;
    for(int i = 0; i< numberBlocks; i++){
        if(blocks[i].getX() + 1 >= COLUMNS){ //collision
            move = false;
        }
    }
    if(move){
        for(int i = 0; i< numberBlocks; i++){
            blocks[i].moveRight();
        }
    }
}

bool Tetrominoe::moveDown(){
    bool move = true;
    for(int i = 0; i< numberBlocks; i++){
        if(blocks[i].getY() + 1 >= ROWS){ //bottom collision
            move = false;
        }
    }
    if(move){
        for(int i = 0; i< numberBlocks; i++){
            blocks[i].moveDown();
        }
        return false;
    }
    else{ 
        return true;
    }
}

void Tetrominoe::moveUp(){ //for deebuging
    for(int i = 0; i< numberBlocks; i++){
        blocks[i].moveUp();
    }
}

int Tetrominoe::getNumberBlocks(){
    return numberBlocks;
}

Block* Tetrominoe::getBlocks(){
    return blocks;
}

void Tetrominoe::draw(SDL_Renderer* renderer){
    //hacer esto y luego el tema de las coliciones
    int counter = this->getNumberBlocks();
    Block* blocks = this->getBlocks();
    for(int i = 0; i<counter;i++){
        int* rgb = blocks[i].getColor();
        SDL_SetRenderDrawColor(renderer,rgb[0],rgb[1],rgb[2],255);
        SDL_Rect square;
        square.x = blocks[i].getX()*X_BLOCK_SIZE;
        square.y = blocks[i].getY()*Y_BLOCK_SIZE;
        square.w = X_BLOCK_SIZE;
        square.h = Y_BLOCK_SIZE;
        SDL_RenderFillRect(renderer,&square);
    }
    //SDL_RenderPresent(renderer);
}

Tetrominoe::~Tetrominoe(){
    for(int i = 0; i<numberBlocks;i++){
        blocks[i].~Block();
    }
}
