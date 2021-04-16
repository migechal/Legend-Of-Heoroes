#pragma once
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "header/Game.h"
class Command
{

public:
    virtual ~Command(){};
    virtual void execute(Camera &camera, int amount) = 0;
};

class Up : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class Down : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class Left : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class Right : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class UpRight : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class DownRight : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class UpLeft : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class DownLeft : public Command
{
public:
    void execute(Camera &camera, int amount);
};

class KeyboardHandler
{
    Command *buttonUp;
    Command *buttonDown;

    Command *buttonLeft;
    Command *buttonRight;
    
    Command *buttonUpLeft;
    Command *buttonUpRight;
    
    Command *buttonDownLeft;
    Command *buttonDownRight;
    
    std::vector<SDL_Scancode> keys;

public:
    KeyboardHandler(std::vector<SDL_Scancode> keys);
    Command *handleInput();
};
