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

/** Imports. **/
#include <iostream>
#include LIBRARY(SDL\SDL.h)
#include "MainGame.h"

int main(int argc, char** argv) {
    MainGame mainGame;
    mainGame.run();
    
    std::cout << "ITSUPGOGOOG!!";
    system("pause");

    return 0;
}
