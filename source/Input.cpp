#include <string>
#include <SDL2/SDL.h>
#include "header/Input.h"
Keyboard &Keyboard::getInstance()
{
    static Keyboard instance;
    return instance;
}

void Keyboard::getInput()
{
    state = SDL_GetKeyboardState(NULL);
}

bool Keyboard::isPressed(SDL_Scancode button)
{
    getInput();
    return state[button];
}
