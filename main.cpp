#include <iostream>
using namespace std;

#include "include/game.h"

//#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

int main(){
    Game* gameInstance = new Game();
    gameInstance->start();
    while(gameInstance->isRunning()){
        gameInstance->setLastFrame(SDL_GetTicks());
        if(gameInstance->getLastFrame()>=(gameInstance->getLastTime()+1000)){ //controla FPS
            gameInstance->setLastTime(gameInstance->getLastFrame());
            gameInstance->setFPS(gameInstance->getFrameCount());
            gameInstance->setFrameCount(0);
        }
        if(gameInstance->getCurrent() == NULL){
            gameInstance->addTetrominoe(); 
        }
        gameInstance->draw();
        gameInstance->update();
        gameInstance->input();
    }
    gameInstance->~Game();
    return 0;
}