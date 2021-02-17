#pragma once
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
class Game
{
    int tileSize;
    SDL_Surface *tiles;

public:
    Game(int tileSize, SDL_Surface *tiles);
    void printTiles(std::vector<std::vector<std::vector<int>>> csv, SDL_Surface *screen);
};