#include "MainGame.h"

MainGame::MainGame() {
    _window = nullptr;
    _screenWidth = 1280;
    _screenHeight = 720;
}

MainGame::~MainGame() {
    
}

void MainGame::run() {
    initSystems();
}


void MainGame::initSystems() {
    SDL_Init(SDL_INIT_EVERYTHING); //initialize everything from SDL
    
    _window = SDL_CreateWindow("maoristone", 0,0, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL); 
}