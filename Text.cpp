#include "Text.h"
#include <iostream>
#include "MainGame.h"

Text::Text(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color) {
  _textTexture = loadFont(renderer, font_path, font_size, message_text, color);
  SDL_QueryTexture(_textTexture, nullptr, nullptr, &_textRect.w, &_textRect.h);
}

void Text::display(int x, int y, SDL_Renderer* renderer) const {
  _textRect.x = x;
  _textRect.y = y;

  SDL_RenderCopy(renderer, _textTexture, nullptr, &_textRect);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color) {
  TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
  if (!font) {
    std::cerr << "failed loading font\n";
  }

  auto textSurface = TTF_RenderText_Solid(font, message_text.c_str(), color);
  if (!textSurface) {
    std::cerr << "failed creating text surface\n";
  }

  auto textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  if (!textTexture) {
    std::cerr << "failed creating text texture\n";
  }

  SDL_FreeSurface(textSurface);
  return textTexture;
}
