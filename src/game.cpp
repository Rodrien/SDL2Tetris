#include <iostream>
#include "../include/game.h"

Game::Game(){
    maxFPS = 60;
    running = false;
    score = lastFrame = fps = frameCount = 0;
    current = NULL;

    for(int i = 0; i < COLUMNS; i++){ //empty grid
        for(int j = 0; j < ROWS; j++){
            blocks[i][j].setColor(255,255,255);
        }
    }
}

Game::~Game(){}

void Game::start(){
    running = true;
    fullScreen = false;
    score = lastFrame = fps = frameCount = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error empezando SDL: %s\n", SDL_GetError());
    }
    if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH,SCREEN_HEIGHT,0,&window,&renderer) != 0) std::cout << "Error al crear ventana\n";
    SDL_SetWindowTitle(window,"Kike Tetris");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");
}

void Game::stop(){
    running = false;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::growScore(int x){
    score = score + x;
}

int Game::getScore(){
    return score;
}

bool Game::isRunning(){
    return running;
}

SDL_Renderer* Game::getRenderer(){
    return renderer;
}
    
SDL_Window* Game::getWindow(){
    return window;
}

void Game::setLastFrame(int x){
    lastFrame = x;
}

void Game::setLastTime(int x){
    lastTime = x;
}

void Game::setFPS(int x){
    fps = x;
}

void Game::setFrameCount(int x){
    frameCount = x;
}

int Game::getLastFrame(){
    return lastFrame;
}

int Game::getLastTime(){
    return lastTime;
}

int Game::getFPS(){
    return fps;
}

int Game::getFrameCount(){
    return frameCount;
}

void Game::addTetrominoe(){
    current = new Tetrominoe();
}

Tetrominoe* Game::getCurrent(){
    return current;
}

void Game::input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){ //si apreto la cruz roja de la ventana
        if(e.type == SDL_QUIT) running = false;
    }
    const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
    if(keyStates[SDL_SCANCODE_ESCAPE]) running = false; //si apreto la tecla de escape
    if(keyStates[SDL_SCANCODE_F]) fullScreen = !fullScreen; //si apreto la tecla F
    if(keyStates[SDL_SCANCODE_LEFT]){
        current->moveLeft();
    }
    if(keyStates[SDL_SCANCODE_RIGHT]){
        current->moveRight();
    }
    //if(keyStates[SDL_SCANCODE_DOWN]){
    //    current->moveDown();
    //}
    if(keyStates[SDL_SCANCODE_UP]){
        current->moveUp();
    }
}

void Game::draw(){
    //draw background
    SDL_SetRenderDrawColor(renderer,255,255,255,255); //black
    SDL_Rect background;
    background.x = background.y = 0;
    background.w = SCREEN_WIDTH;
    background.h = SCREEN_HEIGHT;
    SDL_RenderFillRect(renderer,&background);
    //SDL_RenderPresent(renderer);

    //draw blocks
    for(int i = 0; i < COLUMNS; i++){ 
        for(int j = 0; j < ROWS; j++){
            int* rgb = blocks[i][j].getColor();
            SDL_SetRenderDrawColor(renderer,rgb[0],rgb[1],rgb[2],255);
            SDL_Rect square;
            square.x = i*X_BLOCK_SIZE;
            square.y = j*Y_BLOCK_SIZE;
            square.w = X_BLOCK_SIZE;
            square.h = Y_BLOCK_SIZE;
            SDL_RenderFillRect(renderer,&square); 
        }
    }

    //draw current tetrominoe
    current->draw(renderer);

    //draw lines
    SDL_SetRenderDrawColor(renderer,0,0,0,255); //white
    int i = 0;
    while(i <= SCREEN_WIDTH){
        SDL_RenderDrawLine(renderer,i,0,i,SCREEN_HEIGHT);
        //SDL_RenderPresent(renderer);
        i = i+ X_BLOCK_SIZE;
    }

    i = 0;
    while(i <= SCREEN_HEIGHT){
        SDL_RenderDrawLine(renderer,0,i,SCREEN_WIDTH,i);
        //SDL_RenderPresent(renderer);
        i = i+ Y_BLOCK_SIZE;
    }

    SDL_RenderPresent(renderer); //push everything to screen
    
    //use this to control fps limit
    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS < (1000/maxFPS)){
        SDL_Delay((1000/maxFPS)-timerFPS);
    }
    //---------------------
}

bool Game::lowerCurrent(){ //colision con los colores 
    Block* squares = current->getBlocks();
    int cantidadBloques = current->getNumberBlocks();

    for(int i = 0; i< cantidadBloques; i++){
        int* rgb = blocks[squares[i].getX()][squares[i].getY()+1].getColor();
        if(rgb[0]!=255 || rgb[1]!=255 || rgb[2]!=255){ //collision with other blocks
            return false;
        }
    }
    return true;
}

void Game::update(){
    if(fullScreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullScreen) SDL_SetWindowFullscreen(window, 0);
    //hacer la colision con los demas colores aca y si se puede ahi hago moveDown()
    bool cont =  this->lowerCurrent(); //implementar esto para hacer el chequeo de colision con los colores
    bool newCurrent = false; //or use cont
    if(cont){
        newCurrent = current->moveDown();
    }
    if(newCurrent || !cont){ //add current to grid and creante nes current
        Block* squares = current->getBlocks();
        for(int i = 0; i< current->getNumberBlocks();i++){
            int* rgb = squares[i].getColor();
            blocks[squares[i].getX()][squares[i].getY()].setColor(rgb[0],rgb[1],rgb[2]);
        }
        current->~Tetrominoe();
        current = NULL;
    }
}