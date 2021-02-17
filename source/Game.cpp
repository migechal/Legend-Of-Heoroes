#include "header/Game.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>

Game::Game(int tileSize, SDL_Surface *tiles) : tileSize(tileSize), tiles(tiles) {}

void Game::printTiles(std::vector<std::vector<std::vector<int>>> csv, SDL_Surface *screen)
{
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
        for (size_t row = 0; row < csv[i].size(); ++row)
        {
            for (size_t col = 0; col < csv[i][row].size(); ++col)
            {
                SDL_Rect dist{static_cast<int>(destTileSize * col), static_cast<int>(destTileSize * row), destTileSize, destTileSize};

                if (csv[i][row][col] != -1)
                {
                    SDL_Rect src{(csv[i][row][col] % 32) * srcTileSize, (csv[i][row][col] / 32) * srcTileSize, srcTileSize, srcTileSize};
                    SDL_BlitScaled(tiles, &src, screen, &dist);
                }
            }
        }
    }
}