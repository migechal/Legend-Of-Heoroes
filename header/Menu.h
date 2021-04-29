#pragma once
#include <SDL2/SDL.h>
class Button {
  int       x, y, w, h, mouseX, mouseY;
  SDL_Color color;
  int       update( );
  void      changeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void      updateMouse( );
  int       mouseClick( );

public:
  Button(int x, int y, int w, int h, SDL_Color color);
  void print(SDL_Renderer* renderer);
  bool isClick( );
};