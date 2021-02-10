#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <map>
#include <string_view>
#include "header/Init.h"
#include "header/Player.h"
#include "header/Menu.h"
#define CHECK_RESULT(fnc)                                                         \
    {                                                                             \
        auto res = fnc;                                                           \
        if (!res)                                                                 \
        {                                                                         \
            std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                      << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                      << std::endl;                                               \
            exit(-2);                                                             \
        }                                                                         \
    }

const int tileSize = 32; // Tile Size from "Tiled"

enum Location
{
    MAINMENU = 0,
    INGAME = 1,
    OPTIONS = 2
};

int main(int argc, char **argv)
{

    SDL_Init(SDL_INIT_EVERYTHING);

    Init init(argv[0], tileSize); //Create Init class

    int windowWidth = init.getDisplayMode().w;
    int windowHeight = init.getDisplayMode().h;

    SDL_Rect backgroundRect;

    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.h = windowHeight;
    backgroundRect.w = windowWidth;

    SDL_Surface *loading = nullptr;
    SDL_Surface *tiles = nullptr;
    SDL_Surface *background = nullptr;
    SDL_Surface *screen = nullptr;
    SDL_Window *window = nullptr;
    SDL_SetSurfaceBlendMode(background, SDL_BLENDMODE_NONE);

    tiles = init.imageLoader("assets/tiles.png");
    loading = init.imageLoader("assets/Loading/Loading.jpeg");
    const int scale = 4;
    window = SDL_CreateWindow("Loading...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth / scale, windowHeight / scale, SDL_WINDOW_BORDERLESS); //Create loading window object
    screen = SDL_GetWindowSurface(window);
    SDL_Rect loadingRect{0, 0, windowWidth / scale, windowHeight / scale};
    SDL_BlitScaled(loading, NULL, screen, &loadingRect);
    SDL_UpdateWindowSurface(window);
    //Loads Needed to be done

    // background = SDL_ConvertSurface(init.imageLoader("assets/Map/Map.jpeg"), screen->format, 0); //Create background which will be used to clear the screen as well
    SDL_Delay(200);
    background = init.imageLoader("assets/MainMenu/MainMenu.png");

    SDL_DestroyWindow(window);
    SDL_FreeSurface(loading);
    window = SDL_CreateWindow("Legend Of Heros", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_FULLSCREEN); //Create window object
    screen = SDL_GetWindowSurface(window);

    bool menuIsRunning = false;
    std::string name = "mik";
    static int location = MAINMENU;

    SDL_Event e;
    SDL_Color color{181, 50, 22, 1};
    Button playButton(windowWidth / 2 - 200, windowHeight / 3 * 2, 400, 150, color);

    while (menuIsRunning)
    {
        while (SDL_PollEvent(&e))
        {
            if (playButton.isClick())
            {
                location = INGAME;
                menuIsRunning = false;
                break;
            }
            switch (e.type)
            {
            case SDL_QUIT:
                menuIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    menuIsRunning = false;
                    break;
                }
            }
        }
        SDL_BlitScaled(background, NULL, screen, &backgroundRect);
        playButton.print(screen);
        SDL_UpdateWindowSurface(window);
    }

    // Player *player = new Player(name);
    location = INGAME;
    bool gameIsRunning = true;
    std::map<int, SDL_Rect> savedTiles;
    while (gameIsRunning && location == INGAME)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    gameIsRunning = false;
                    break;
                }
            }
        }
        std::vector<std::vector<int>> vec = init.getCSVvector("assets/Map/Back.csv");
        if (vec.empty())
        {
            SDL_Log("Couldn't load CSV file");
            return -1;
        }
        for (size_t row = 0; row < vec.size(); ++row)
        {
            for (size_t col = 0; col < vec[row].size(); ++col)
            {
                SDL_Rect position{static_cast<int>(tileSize * row), static_cast<int>(tileSize * col), tileSize, tileSize};

                SDL_Rect cut{0, 0, tileSize, tileSize};
                if (savedTiles.find(vec[row][col]) == savedTiles.end())
                {
                    cut = savedTiles.find(vec[row][col])->second;
                }
                else
                {
                    int orig = vec[row][col];
                    if (vec[row][col] != -1)
                    {

                        for (; (vec[row][col] * tileSize) > 1024; ++cut.y)
                        {
                            vec[row][col] -= 1024;
                            std::cout << vec[row][col] << std::endl;
                        }
                        cut.x = abs(vec[row][col]);
                        SDL_BlitScaled(tiles, &cut, screen, &position);
                    }
                    savedTiles[orig] = cut;
                }
            }
        }
        SDL_UpdateWindowSurface(window);
    }
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
