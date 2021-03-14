#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "header/Game.h"
#include "header/Init.h"
SDL_Rect Camera::cameraPosition = {0, 0, 0, 0};

Game::Game(std::string baseDirectoryLocation, int tileSize) : tileSize(tileSize), baseDir(baseDirectoryLocation) {}
int Game::roundDown(int &num, int toSize)
{
    for (; num % 32 != 0; --num)
    {
        // DO NOTHING
    }
    return num;
}
int Game::cordinateToTile(int x, int y, std::string tileLocation)
{
    Init *csvGet = new Init(baseDir, tileSize);
    roundDown(x, tileSize);
    roundDown(y, tileSize);
    x /= tileSize; //Get the location of the tile
    y /= tileSize; //Get the location of the tile
    return csvGet->getCSVvector(tileLocation)[x][y];
}

bool Game::checkHitbox(int x, int y, std::vector<std::string> tileLocation)
{
    for (size_t i = 0; i < tileLocation.size(); ++i)
    {
        int temp = cordinateToTile(x, y, tileLocation[i]);
        if (temp >= 0 && std::binary_search(hitboxes.begin(), hitboxes.end(), temp))
        {
            return false;
        };
    }
    return true;
}
int Game::printTiles(std::vector<std::vector<std::vector<int>>> csv, SDL_Surface *screen, SDL_Surface *tiles, SDL_Rect position, int tileScale)
{
    if (position.x < 0 || position.y < 0)
    {
        std::cout << "Error!! Camera position is out of bounds." << std::endl;
        return 0;
    }
    Init *get = new Init("n", 0);

    int cutTilesX = std::floor(position.x / tileSize);
    int cutTilesY = std::floor(position.y / tileSize);
    int cutPosX = position.x % tileSize;
    int cutPosY = position.y % tileSize;
    /* 
    / Remember, start from back to front.
    */
    int windowWidth = get->getDisplayMode().w;
    int windowHeight = get->getDisplayMode().h;

    for (size_t i = 0; i < csv.size(); ++i)
    {

        if (csv.empty())
        {
            SDL_Log("Couldn't load CSV file");
        }

        int destTileSize = tileSize * tileScale;
        int srcTileSize = tileSize;

        size_t rowPlacement = 0;
        for (size_t row = Camera::getCamera()->getPos().x / tileSize; row < windowWidth / tileSize + Camera::getCamera()->getPos().x; ++row && ++rowPlacement)
        {
            size_t colPlacement = 0;
            for (size_t col = Camera::getCamera()->getPos().y / tileSize; col < windowHeight / tileSize + Camera::getCamera()->getPos().y; ++col && ++colPlacement)
            {
                SDL_Rect dist{destTileSize * colPlacement + cutTilesX - Camera::getCamera()->getPos().x, destTileSize * rowPlacement - cutTilesY - Camera::getCamera()->getPos().y, destTileSize, destTileSize};

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

Camera *Camera::getCamera()
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
    if (cameraPosition.x + loc.x < 0 || cameraPosition.y + loc.y < 0)
    {
        return;
    }
    cameraPosition.x += loc.x;
    cameraPosition.y += loc.y;
}
SDL_Rect Camera::getPos()
{
    // std::cout << cameraPosition.x << " " << cameraPosition.y << std::endl;
    return cameraPosition;
}