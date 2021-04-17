#include "header/Input.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
Keyboard &Keyboard::getInstance( ) {
  static Keyboard instance;
  return instance;
}

void Keyboard::getInput( ) { state = SDL_GetKeyboardState(NULL); }

bool Keyboard::isPressed(std::vector<SDL_Scancode> buttons) {
  getInput( );
  for (SDL_Scancode i : buttons) {
    if (!state[i]) { return false; }
  }
  return true;
}
