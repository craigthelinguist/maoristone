
#ifndef MAINGAME_H
#define MAINGAME_H

#include "Modules.h"
#include LIBRARY(SDL.h)


class MainGame {

public:
    MainGame(int screenWidth, int screenHeight);
    ~MainGame();

    void init();

    void run();

    void initSystems();

private:
    SDL_Window* _window;
    SDL_Surface* _surface;
    int _screenWidth;
    int _screenHeight;
};

#endif
