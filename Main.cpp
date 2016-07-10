
/** Imports. **/
#include "Modules.h"
#include <iostream>
#include "MainGame.h"
#include LIBRARY(SDL.h)


int main(int argc, char* argv[]) {
    
    // Initialise SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	fprintf(stderr, "SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
	exit(EXIT_FAILURE);
    }
    
    // Set up the game.
    MainGame game(1280, 720);
    game.init();
    
    return 0;
    
}
