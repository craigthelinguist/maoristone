
/** A mechanism for cleaner imports. **/
#define QUOTEME(X) QUOTEME_1(X)
#define QUOTEME_1(X) #X

#ifdef _LINUX
    #define LIBRARY(M) QUOTEME(lib/linux/M)
#elif defined(_WINDOWS)
    #define LIBRARY(M) QUOTEME(lib\windows\M)
#else
    #error Error resolving import paths; your operating system is unknown.
#endif

#include LIBRARY(SDL\SDL.h)

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