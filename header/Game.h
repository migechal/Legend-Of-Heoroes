#pragma once
#include "header/Entity.h"
#include "header/Init.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <map>
#include <string>
#include <vector>
class Game
{
  std::vector<int> hitboxes;
  int              tileSize;
  std::string      baseDir;
  int              roundDown(int &num, int toSize);
  int              cordinateToTile(int x, int y, std::string tileLocation);
  int              pixelToTile(int pixel);
  int              placeHolder;

public:
  Game(std::string baseDirectoryLocation, int tileSize);
  enum Positions { UP = 0, DOWN = 1, RIGHT = 2, LEFT = 3 };
  bool checkHitbox(int x, int y, std::vector<std::string> tileLocation);
  void printEntity(Entity *entity, SDL_Renderer *renderer);
  int  printTiles(std::vector<std::vector<std::vector<int>>> csv,
                  SDL_Renderer *renderer, SDL_Texture *tiles, SDL_Rect position,
                  int tileScale);
};

class Camera
{
  SDL_Rect                      cameraPosition = {0, 0, 0, 0};
  int                           tileSize;
  SDL_Rect                      levelSize;
  SDL_DisplayMode               Display;
  std::vector<std::vector<int>> currentLevel;

public:
  Camera(std::vector<std::vector<int>> currentLevel, int tileSize,
         SDL_DisplayMode Display);
  void     move(SDL_Rect loc);
  SDL_Rect getPos();
};
