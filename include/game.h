#include <SDL2/SDL.h>
#include "tetrominoe.h"

/* //imported from tetrominoe.h
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 800
#define COLUMNS 10
#define ROWS 20
#define Y_BLOCK_SIZE SCREEN_HEIGHT/ROWS
#define X_BLOCK_SIZE SCREEN_WIDTH/COLUMNS
*/

class Game{
    private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool running, fullScreen;
    int lastFrame, fps, frameCount, lastTime;
    int score;
    Block blocks[COLUMNS][ROWS];
    Tetrominoe* current; //pieza actual
    int maxFPS;

    public:
    Game();
    ~Game();
    void start();
    void stop();
    void growScore(int x);
    int getScore();
    bool isRunning();
    bool lowerCurrent();
    void clearRow(); //para cuando toca limpiar la fila

    void setLastFrame(int);
    void setLastTime(int);
    void setFPS(int);
    void setFrameCount(int);
    int getLastFrame();
    int getLastTime();
    int getFPS();
    int getFrameCount();

    void addTetrominoe();
    Tetrominoe* getCurrent();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();

    void input();
    void draw();
    void update();
};