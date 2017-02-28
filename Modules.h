
#ifndef MODULES_H
#define MODULES_H

    #define QUOTEME(X) QUOTEME_1(X)
    #define QUOTEME_1(X) #X

    #ifdef _LINUX
	#define LIBRARY(M) QUOTEME(SDL2/M)
    #elif defined(_WINDOWS)
	#define LIBRARY(M) QUOTEME(lib\windows\SDL\M)

  // you may need to add one for linux - this is for when we are including SDL inside server directory
  #define LIBRARY2(M) QUOTEME(..\lib\windows\SDL\M)
    #else
	#error Error resolving import paths; your operating system is unknown.
    #endif

#endif
