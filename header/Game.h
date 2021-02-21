#pragma once
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
class Game
{
    static std::vector<int> hitboxes;

    static std::string baseDir;
    int roundDown(int &num, int toSize);
    int cordinateToTile(int x, int y, int tileSize, std::string tileLocation);

public:
    static Game *getInstance(std::string baseDirectoryLocation);
    bool checkHitbox(int x, int y, int tileSize, std::vector<std::string> tileLocation);
    int printTiles(std::vector<std::vector<std::vector<int>>> csv, SDL_Surface *screen, int tileSize, SDL_Surface *tiles, SDL_Rect position);
};

class Camera
{
    static SDL_Rect cameraPosition;

public:
    static Camera *camera();
    void move(SDL_Rect loc);
    SDL_Rect getPos();
};