#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <string>
#include <vector>
class Player
{
    std::string Name;
    int Health = 100;
    SDL_Rect Position;
    SDL_Surface *surface;
    std::vector<int> Inventory;

public:
    Player(std::string Name);
    std::string getName();
    int getHealth();
    SDL_Rect getPosition();
    void printPlayer(SDL_Surface *screen);
    void decreaseHealth(int decrease);
    void setPosition(SDL_Rect newPos);
    std::vector<std::vector<int>> getPlayerTile(int x, int y);
};