#pragma once
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL_rect.h>
#include "header/Init.h"
#include <SDL2/SDL_surface.h>
class Game
{
    std::vector<int> hitboxes;
    int tileSize;
    std::string baseDir;
    int roundDown(int &num, int toSize);
    int cordinateToTile(int x, int y, std::string tileLocation);

public:
    Game(std::string baseDirectoryLocation, int tileSize);
    static Game *getInstance(std::string baseDirectoryLocation);
    bool checkHitbox(int x, int y, std::vector<std::string> tileLocation);
    int printTiles(std::vector<std::vector<std::vector<int>>> csv, SDL_Surface *screen, SDL_Surface *tiles, SDL_Rect position, int tileScale);
};

class Camera
{
    static SDL_Rect cameraPosition;

public:
    static Camera *getCamera();
    void move(SDL_Rect loc);
    SDL_Rect getPos();
};