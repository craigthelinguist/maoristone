
#ifndef MAINGAME_H
#define MAINGAME_H

#include "Modules.h"
#include "Socket.h"
#include LIBRARY(SDL.h)
#include <string>

class MainGame {

public:
    MainGame(int screenWidth, int screenHeight);
    ~MainGame();

    void init();

    void run();

    void initSystems();

    void Close();

    void drawCard();
    void drawText();

    void pollEvents(SDL_Event event);

    /* Networking related functions */
    bool InitializeSockets();
    void ShutdownSockets();
    void CreateSocket();
    void SendPacket(const char data[], const int len);
    void ReceivePacket();

private:
    SDL_Window* _window;
    SDL_Surface* _surface;
    SDL_Renderer* _renderer;
    int _screenWidth;
    int _screenHeight;

    SDL_Texture* _cardTexture;
    std::string ASSETS = "assets/cards/";
    std::string FONTS = "assets/fonts/";

    /* Networking */
    int port = 30001;
    int sendToPort = 30000;
    bool sending = false;
    const char data[256] = "ITSUPGOGOGO";

    Socket sock;
};

#endif
