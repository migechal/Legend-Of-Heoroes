#include "header/Game.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>

Game::Game(int tileSize, SDL_Surface *tiles) : tileSize(tileSize), tiles(tiles) {}

void Game::printTiles(std::vector<std::vector<int>> csv, SDL_Surface *screen)
{
    if (csv.empty())
    {
        SDL_Log("Couldn't load CSV file");
    }
    for (size_t row = 0; row < csv.size(); ++row)
    {
        for (size_t col = 0; col < csv[row].size(); ++col)
        {
            int orig = csv[row][col];
            SDL_Rect position{static_cast<int>(tileSize * row), static_cast<int>(tileSize * col), tileSize, tileSize};

            SDL_Rect cut{0, 0, tileSize, tileSize};
            if (savedTiles.count(csv[row][col]) > 0)
            {
                cut = savedTiles.find(csv[row][col])->second;
                std::cout << csv[row][col] << std::endl;
                SDL_BlitScaled(tiles, &cut, screen, &position);
            }
            else
            {
                if (csv[row][col] != -1)
                {
                    int vecNum = csv[row][col];
                    for (; (vecNum * tileSize) > 1024; cut.y += 32)
                    {
                        vecNum -= 1024;
                        std::cout << vecNum << std::endl;
                    }
                    cut.x = abs(vecNum);
                    SDL_BlitScaled(tiles, &cut, screen, &position);
                }
                savedTiles[orig] = cut;
            }
        }
    }
}