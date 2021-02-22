#include <string>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>
#include <map>
#include "header/KeyboardHandler.h"
#include "header/Input.h"
#include "header/Game.h"

void Up::execute(int move)
{
    printf("move = %d\n", move);
    Camera::camera()->move({0, -move});
    printf("up called");
}

void Down::execute(int move)
{
    printf("move = %d\n", move);
    Camera::camera()->move({0, move});
    printf("down called");
}

void Left::execute(int move)
{
    printf("move = %d\n", move);
    Camera::camera()->move({-move, 0});
    printf("left called");
}

void Right::execute(int move)
{
    printf("move = %d\n", move);
    Camera::camera()->move({move, 0});
    printf("right called");
}

KeyboardHandler::KeyboardHandler(std::vector<SDL_Scancode> keys) : keys(keys)
{
    printf("keys size = %ld\n", keys.size());
}

/**
 * @brief Up, Down, Left, Right
 */
Command *KeyboardHandler::handleInput()
{
    if (Keyboard::getInstance().isPressed(keys[0]))
        return buttonUp;
    if (Keyboard::getInstance().isPressed(keys[1]))
        return buttonDown;
    if (Keyboard::getInstance().isPressed(keys[2]))
        return buttonLeft;
    if (Keyboard::getInstance().isPressed(keys[3]))
        return buttonRight;
    return nullptr;
};