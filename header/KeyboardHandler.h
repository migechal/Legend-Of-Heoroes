#pragma once
#include "header/Game.h"
#include <SDL2/SDL.h>
#include <string>
#include <tuple>
#include <vector>
class Command
{

public:
  virtual ~Command(){};
  virtual void execute(Camera &camera, float amount) = 0;
};

class Up : public Command
{
public:
  void execute(Camera &camera, float amount);
};

class Down : public Command
{
public:
  void execute(Camera &camera, float amount);
};

class Left : public Command
{
public:
  void execute(Camera &camera, float amount);
};

class Right : public Command
{
public:
  void execute(Camera &camera, float amount);
};

class UpRight : public Command
{
public:
  void execute(Camera &camera, float amount);
};

class DownRight : public Command
{
public:
  void execute(Camera &camera, float amount);
};

class UpLeft : public Command
{
public:
  void execute(Camera &camera, float amount);
};

class DownLeft : public Command
{
public:
  void execute(Camera &camera, float amount);
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
  std::pair<Command *, SDL_Scancode> handleInput();
  bool                               isSprint();
  bool                               isSneak();
};
