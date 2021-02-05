#include <string>
#include <SDL2/SDL.h>
#include "header/Input.h"
Input *Input::getInstance(){
    if (!instance)
    instance = new Input;
    return instance;
}

void Input::getInput(){
	this->state = SDL_GetKeyboardState(NULL);

}

bool Input::isPressed(std::string button){
	this->getInput();
	return this->keyboard[button];
}
