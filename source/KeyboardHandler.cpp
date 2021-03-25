#include <string>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>
#include <vector>
#include "header/KeyboardHandler.h"
#include "header/Input.h"
#include "header/Game.h"

void Up::execute(Camera &camera, int amount)
{
    printf("move = %d\n", amount);
    camera.move({0, -amount});
    printf("up called");
}

void Down::execute(Camera &camera, int amount)
{
    printf("amount = %d\n", amount);
    camera.move({0, amount});
    printf("down called");
}

void Left::execute(Camera &camera, int amount)
{
    printf("amount = %d\n", amount);
    camera.move({-amount, 0});
    printf("left called");
}

void Right::execute(Camera &camera, int amount)
{
    printf("amount = %d\n", amount);
    camera.move({amount, 0});
    printf("right called");
}

KeyboardHandler::KeyboardHandler(std::vector<SDL_Scancode> keys) : keys(keys)
{
    printf("keys size = %ld\n", keys.size());

    buttonUp = new Up();
    buttonDown = new Down();
    buttonLeft = new Left();
    buttonRight = new Right();
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
