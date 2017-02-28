#include "Modules.h"
#include LIBRARY(SDL.h)
#include LIBRARY(SDL_ttf.h)
#include <string>

class Text {
public:
  Text(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);

  void display(int x, int y, SDL_Renderer* renderer) const;

  static SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
private:
  SDL_Texture* _textTexture = nullptr;
  mutable SDL_Rect _textRect;

};
