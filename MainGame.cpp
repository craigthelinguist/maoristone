#include "MainGame.h"
#include LIBRARY(SDL.h)
#include LIBRARY(SDL_image.h)
#include LIBRARY(SDL_ttf.h)
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include "Socket.h"
#include "Address.h"
#include "Text.h"

MainGame::MainGame(int screenWidth, int screenHeight) {
    _window = nullptr;
    _surface = nullptr;
    _renderer = nullptr;
    _cardTexture = nullptr;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
}

MainGame::~MainGame() {

}

void MainGame::init() {

    // Initialise SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf(stderr, "SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
      fprintf(stderr, "SDL_image could not initialise! SDL_Error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1) {
      fprintf(stderr, "SDL_TTF could not initialise! SDL_Error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }

    // Construct the window.
    _window = SDL_CreateWindow("maoristone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			       _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

    // Construct the surface.
    _surface = SDL_GetWindowSurface(_window);

    // Construct the renderer
    // might want to use SDL_RENDERER_PRESENTVSYNC because SDL_RENDERER_ACCELERATED might be too much
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    //SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 0xFF, 0xFF, 0xFF));
    //SDL_UpdateWindowSurface(_window);


    /*
    SDL_Init(SDL_INIT_EVERYTHING); //initialize everything from SDL

    _window = SDL_CreateWindow("maoristone", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    */
}

void MainGame::drawText() {
  std::string text = FONTS + "arial.ttf";
  Text t(_renderer, text, 14, "asdf", {255, 0, 0, 255});

  t.display(20, 20, _renderer);

}

void MainGame::drawCard() {
  // SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255); // sets color
  // SDL_RenderClear(_renderer); // gets color on renderer

  std::string card_chilldwin_jedi = ASSETS + "chillwind_jedi.png";
  auto surface = IMG_Load(card_chilldwin_jedi.c_str());
  if (!surface) {
    std::cerr << "failed creating surface\n";
  }

  _cardTexture = SDL_CreateTextureFromSurface(_renderer, surface);
  if (!_cardTexture) {
    std::cerr << "failed creating texture\n";
  }

  SDL_Rect rect;
  rect.w = 186;
  rect.h = 255;
  rect.x = _screenWidth/2;
  rect.y = _screenHeight/2;

  // if texture has loaded, draw it, else draw default (coloured rect)
  if (_cardTexture) {
    SDL_RenderCopy(_renderer, _cardTexture, nullptr, &rect);
  }
  else {
    SDL_SetRenderDrawColor(_renderer, 100, 0, 200, 255); // sets color
    SDL_RenderFillRect(_renderer, &rect);
  }

  SDL_FreeSurface(surface);
}

bool MainGame::InitializeSockets() {
  #if PLATFORM == PLATFORM_WINDOWS
  WSADATA WsaData;
  return WSAStartup (MAKEWORD(2,2), &WsaData) == NO_ERROR;
  #else
  return true;
  #endif
}

void MainGame::ShutdownSockets() {
  #if PLATFORM == PLATFORM_WINDOWS
  WSACleanup();
  #endif
}

void MainGame::CreateSocket() {
  if (!sock.Open(port)) {
    printf("Opening socket failed\n");
  }
}

void MainGame::SendPacket(const char data[], const int len) {
  sock.Send(Address(127,0,0,1, sendToPort), data, len);
}

void MainGame::ReceivePacket() {
  while(true) {
    Address sender;
    unsigned char buffer[256];
    int bytes_read = sock.Receive(sender, buffer, sizeof(buffer));

    if (bytes_read <= 0) {
      continue;
    }

    const char* packet_data = (const char*) buffer;
    printf("%d: %s\n", bytes_read, packet_data);
  }
}

void MainGame::pollEvents(SDL_Event event) {
  if (event.type == SDL_KEYDOWN) { // if key was pressed
    if (event.key.keysym.sym == SDLK_a) { // if the 'a' key was pressed
      drawCard();
      drawText();
    }
  }
  else if (event.type == SDL_MOUSEMOTION) { // if mouse was moved
    // motion.x
    // motion.y
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN) { // if mouse was pressed
    // process mouse down
  }
  else if (event.type == SDL_MOUSEBUTTONUP) { // if mouse was released
    // process mouse up
  }
}


// Main Game Loop
void MainGame::run() {
  SDL_Event event;
  bool run = true;

  InitializeSockets();
  CreateSocket();

  const char connect[256] = "connect";
  SendPacket(connect, sizeof(data));

  while (run) {

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) { // if closed
        run = false;
      }
    }

    // process the inputs from the user
    pollEvents(event);

    SDL_RenderPresent(_renderer); // puts whatever is on renderer on screen
  }

  Close();
}

void MainGame::Close() {
  SDL_DestroyWindow(_window);
  SDL_FreeSurface(_surface);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyTexture(_cardTexture);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
