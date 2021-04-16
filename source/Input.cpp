#include <string>
#include <SDL2/SDL.h>
#include <vector>
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


bool Keyboard::isPressed(std::vector<SDL_Scancode> buttons)
{
    getInput();
    for(SDL_Scancode i : buttons){
        if(!state[i]){
            return false;
        }
    }
    return true;
}
