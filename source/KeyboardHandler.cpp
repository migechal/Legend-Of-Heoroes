#include <string>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>
#include <map>
#include "header/KeyboardHandler.h"
#include "header/Input.h"
#include "header/Game.h"

void Up::execute(int move)
{
    Camera::camera()->move({0, -move});
}

void Down::execute(int move)
{
    Camera::camera()->move({0, move});
}

void Left::execute(int move)
{
    Camera::camera()->move({-move, 0});
}

void Right::execute(int move)
{
    Camera::camera()->move({move, 0});
}

KeyboardHandler::KeyboardHandler(std::vector<SDL_Scancode> keys) : keys(keys) {}

/**
 * @brief Up, Down, Left, Right
 */
Command *KeyboardHandler::handleInput()
{
    if (Keyboard::getInstance().isPressed(keys[0]))
        return buttonUp;
    else if (Keyboard::getInstance().isPressed(keys[1]))
        return buttonDown;
    else if (Keyboard::getInstance().isPressed(keys[2]))
        return buttonLeft;
    else if (Keyboard::getInstance().isPressed(keys[3]))
        return buttonRight;
    return nullptr;
};