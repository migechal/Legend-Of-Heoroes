#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "header/Game.h"
#include "header/Init.h"
std::string Game::baseDir = "";
std::vector<int> Game::hitboxes = {};
SDL_Rect Camera::cameraPosition = {};

Game *Game::getInstance(std::string baseDirectoryLocation)
{
    baseDir = baseDirectoryLocation;
    static Game *instance = nullptr;
    if (instance == nullptr)
    {
        instance = new Game;
    }
    return instance;
}
int Game::roundDown(int &num, int toSize)
{
    for (; num % 32 != 0; --num)
    {
        // DO NOTHING
    }
    return num;
}
int Game::cordinateToTile(int x, int y, int tileSize, std::string tileLocation)
{
    Init *csvGet = new Init(baseDir, tileSize);
    roundDown(x, tileSize);
    roundDown(y, tileSize);
    x /= tileSize; //Get the location of the tile
    y /= tileSize; //Get the location of the tile
    return csvGet->getCSVvector(tileLocation)[x][y];
}

bool Game::checkHitbox(int x, int y, int tileSize, std::vector<std::string> tileLocation)
{
    for (size_t i = 0; i < tileLocation.size(); ++i)
    {
        int temp = cordinateToTile(x, y, tileSize, tileLocation[i]);
        if (temp >= 0 && std::binary_search(hitboxes.begin(), hitboxes.end(), temp))
        {
            return false;
        };
    }
    return true;
}
int Game::printTiles(std::vector<std::vector<std::vector<int>>> csv, SDL_Surface *screen, int tileSize, SDL_Surface *tiles, SDL_Rect position)
{
    if (position.x < 0 || position.y < 0)
    {
        std::cout << "Error!! Camera position is out of bounds." << std::endl;
        return 0;
    }
    /* 
    / Remember, start from back to front.
    */
    for (size_t i = 0; i < csv.size(); ++i)
    {

        if (csv.empty())
        {
            SDL_Log("Couldn't load CSV file");
        }
        int destTileSize = tileSize * 2;
        int srcTileSize = tileSize;
        for (size_t row = position.y; row < csv[i].size(); ++row)
        {
            for (size_t col = position.x; col < csv[i][row].size(); ++col)
            {
                SDL_Rect dist{static_cast<int>(destTileSize * col) - position.x * 64, static_cast<int>(destTileSize * row) - position.y * 64, destTileSize, destTileSize};

                if (csv[i][row][col] != -1)
                {
                    SDL_Rect src{(csv[i][row][col] % 32) * srcTileSize, (csv[i][row][col] / 32) * srcTileSize, srcTileSize, srcTileSize};
                    SDL_BlitScaled(tiles, &src, screen, &dist);
                }
            }
        }
    }
    return 1;
}

Camera *Camera::camera()
{
    static Camera *instance = nullptr;
    if (instance == nullptr)
    {
        instance = new Camera;
    }
    return instance;
}

void Camera::move(SDL_Rect loc)
{
    cameraPosition = loc;
}
SDL_Rect Camera::getPos()
{
    return cameraPosition;
}