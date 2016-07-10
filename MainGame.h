/** A mechanism for cleaner imports. **/

#include "Modules.h"
#include LIBRARY(SDL.h)


class MainGame {
    
public:
    MainGame();
    ~MainGame();
    
    void run();
    
    void initSystems();
    
private:
    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
};