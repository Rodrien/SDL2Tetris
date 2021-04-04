#include "block.h"
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 600
#define COLUMNS 10
#define ROWS 20
#define Y_BLOCK_SIZE SCREEN_HEIGHT/ROWS
#define X_BLOCK_SIZE SCREEN_WIDTH/COLUMNS

class Tetrominoe{
    private:
        int numberBlocks;
        Block* blocks;
    public:
        Tetrominoe();
        ~Tetrominoe();
        void rotate();
        void moveLeft();
        void moveRight();
        void moveUp();
        bool moveDown();
        void draw(SDL_Renderer*);

        int getNumberBlocks();
        Block* getBlocks();
};