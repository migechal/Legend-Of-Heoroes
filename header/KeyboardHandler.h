#pragma once
#include <string>
#include <vector>
#include <SDL2/SDL_scancode.h>
class Command
{

public:
    virtual ~Command(){};
    virtual void execute(int amount) = 0;
};

class Up : public Command
{
public:
    void execute(int amount);
};

class Down : public Command
{
public:
    void execute(int amount);
};

class Left : public Command
{
public:
    void execute(int amount);
};

class Right : public Command
{
public:
    void execute(int amount);
};
class KeyboardHandler
{
    Command *buttonUp;
    Command *buttonDown;
    Command *buttonLeft;
    Command *buttonRight;
    std::vector<SDL_Scancode> keys;

public:
    KeyboardHandler(std::vector<SDL_Scancode> keys);
    Command *handleInput();
};