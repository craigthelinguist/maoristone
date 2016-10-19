#include "MainGame.h"

MainGame::MainGame(int screenWidth, int screenHeight) {
    _window = nullptr;
    _surface = nullptr;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

}

MainGame::~MainGame() {

}

void MainGame::init() {

    // Construct the window.
    _window = SDL_CreateWindow("maoristone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			       _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

    // Construct the surface.
    _surface = SDL_GetWindowSurface(_window);
    SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(_window);
    SDL_Delay(600);

    // 1280 x 720

    /*
    SDL_Init(SDL_INIT_EVERYTHING); //initialize everything from SDL

    _window = SDL_CreateWindow("maoristone", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    */
}


void MainGame::run() {
}
