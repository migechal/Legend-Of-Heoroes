#include "header/Menu.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#define CHECK_RESULT(fnc)                                                      \
  {                                                                            \
    auto res = fnc;                                                            \
    if (!res) {                                                                \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error("    \
                << SDL_GetError( ) << ")  err: " << res << " in " << #fnc      \
                << std::endl;                                                  \
      exit(-2);                                                                \
    }                                                                          \
  }
enum Click { NOCLICK = 0, CLICKED = 1 };

Button::Button(int x, int y, int w, int h, SDL_Color color)
    : x(x), y(y), w(w), h(h), color(color) {}

void Button::updateMouse( ) { SDL_GetMouseState(&this->mouseX, &this->mouseY); }
int  Button::mouseClick( ) {
  SDL_Event e;
  if (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_MOUSEBUTTONDOWN: return CLICKED; break;
    }
  }
  return NOCLICK;
}
void Button::changeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  this->color.r = r;
  this->color.g = g;
  this->color.b = b;
  this->color.a = a;
}

int Button::update( ) {
  this->updateMouse( );
  static int interval = 0;
  if ((this->mouseX >= x && this->mouseX <= x + w) &&
      (this->mouseY >= y && this->mouseY <= y + h)) {
    // for(Uint8 i = 0; color.a < 190; i++ && ++interval){
    //     this->changeColor(color.r, color.g, color.b, color.a += i);
    // }
    return (this->mouseClick( ) == CLICKED) ? CLICKED : NOCLICK;
  }
  color.a -= interval;
}

void Button::print(SDL_Renderer* renderer) {
  this->update( );
  std::cout << (Uint32)color.r << " " << (Uint32)color.g << " "
            << (Uint32)color.b << " " << (Uint32)color.a << std::endl;
  SDL_Surface* button = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

  SDL_FillRect(button, NULL,
               SDL_MapRGBA(button->format, color.r, color.g, color.b, color.a));

  CHECK_RESULT(button);
  SDL_Rect pos{this->x, this->y, this->w, this->h};
  SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, button), NULL,
                 &pos);
  std::cout << "in print" << std::endl;
  SDL_FreeSurface(button);
}

bool Button::isClick( ) {
  if (this->update( ) == CLICKED) { return true; }
  return false;
}