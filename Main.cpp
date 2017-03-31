
/** Imports. **/
#include "Modules.h"
#include <iostream>
#include "MainGame.h"
#include LIBRARY(SDL.h)
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

int main(int argc, char* argv[]) {

    std::cin.get();
    return 0;

}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

  // display console - use this for debugging
  AllocConsole();
  freopen("CONIN$", "r",stdin);
  freopen("CONOUT$", "w",stdout);
  freopen("CONOUT$", "w",stderr);

    // Set up the game.
    MainGame game(1280, 720);
    game.init();
    game.run();

    return 0;
}
