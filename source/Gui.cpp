#include "header/Gui.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "header/Init.h"
#define CHECK_RESULT(fnc)                                                      \
  {                                                                            \
    auto res = fnc;                                                            \
    if (!res) {                                                                \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error("    \
                << SDL_GetError() << ")  err: " << res << " in " << #fnc       \
                << std::endl                                                   \
                << "Maybe ;; export LEGEND_OF_HEROES=`pwd` ;; will fix?"       \
                << std::endl;                                                  \
      exit(-2);                                                                \
    }                                                                          \
  }

Gui::Gui(SDL_Window* window, SDL_Renderer* renderer, Init* init) : window(window), renderer(renderer), init(init), windowDimensions(init->getDisplayMode()){}

void Gui::addText(std::string Text, SDL_Rect position, TTF_Font* font, SDL_Color color, size_t scale){
  CHECK_RESULT(font);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, Text.c_str(), color));
  int texW = 0;
  int texH = 0;
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  SDL_Rect dst = { position.x - scale * texW, position.y - texH, texW * scale, texH * scale };
  SDL_RenderCopy(renderer, texture, NULL, &dst);
}