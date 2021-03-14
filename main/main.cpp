#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <map>
#include <string_view>
#include "header/Init.h"
#include "header/Player.h"
#include "header/Menu.h"
#include "header/Game.h"
#include "header/KeyboardHandler.h"
#include "header/Input.h"
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
const int scale = 4;
const int tileScale = 3;

enum Location
{
    MAINMENU = 0,
    INGAME = 1,
    OPTIONS = 2
};

int main(int argc, char **argv)
{

    SDL_Init(SDL_INIT_EVERYTHING);

    Init *init = new Init(argv[0], tileSize); //Create Init class

    std::vector<std::string> keyNames{
        init->getSettingsFromJson("settings/config.json", "Buttons", "up"),
        init->getSettingsFromJson("settings/config.json", "Buttons", "down"),
        init->getSettingsFromJson("settings/config.json", "Buttons", "left"),
        init->getSettingsFromJson("settings/config.json", "Buttons", "right")};
    const SDL_Scancode UP = SDL_GetScancodeFromName(keyNames[0].c_str());
    const SDL_Scancode DOWN = SDL_GetScancodeFromName(keyNames[1].c_str());
    const SDL_Scancode LEFT = SDL_GetScancodeFromName(keyNames[2].c_str());
    const SDL_Scancode RIGHT = SDL_GetScancodeFromName(keyNames[3].c_str());
    const int cameraMovementByPixels = std::stoi(init->getSettingsFromJson("settings/config.json", "Game", "CameraMovement"));

    Game *game = new Game(init->getBaseDirectory(), tileSize);

    KeyboardHandler keyboard({UP, DOWN, LEFT, RIGHT});

    int windowWidth = init->getDisplayMode().w;
    int windowHeight = init->getDisplayMode().h;

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

    tiles = init->imageLoader("assets/tiles.png");
    loading = init->imageLoader("assets/Loading/Loading.jpeg");
    window = SDL_CreateWindow("Loading...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth / scale, windowHeight / scale, SDL_WINDOW_BORDERLESS); //Create loading window object
    screen = SDL_GetWindowSurface(window);
    SDL_Rect loadingRect{0, 0, windowWidth / scale, windowHeight / scale};
    SDL_BlitScaled(loading, NULL, screen, &loadingRect);
    SDL_UpdateWindowSurface(window);
    //Loads Needed to be done
    SDL_Delay(200);
    background = init->imageLoader("assets/MainMenu/MainMenu.png");

    //Destroy Loading Window objects
    SDL_DestroyWindow(window);
    SDL_FreeSurface(loading);

    //Create Main Window and Screen objects
    window = SDL_CreateWindow("Legend Of Heros", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_FULLSCREEN); //Create window object
    screen = SDL_GetWindowSurface(window);

    SDL_Event e;
    SDL_Color color{181, 50, 22, 1};
    Button playButton(windowWidth / 2 - 200, windowHeight / 3 * 2, 400, 150, color);

    bool menuIsRunning = false;
    static int location = MAINMENU;

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

    location = INGAME;
    bool gameIsRunning = true;
    std::vector<std::vector<int>> csvFileMap[3]{
        init->getCSVvector("assets/Map/Back.csv"),
        init->getCSVvector("assets/Map/Middle.csv"),
        init->getCSVvector("assets/Map/Front.csv"),
    };
    if (gameIsRunning)
    {
        CHECK_RESULT(game->printTiles({csvFileMap[0], csvFileMap[1], csvFileMap[2]}, screen, tiles, Camera::getCamera()->getPos(), tileScale));
    }
    while (gameIsRunning && location == INGAME)
    {
        Uint64 start = SDL_GetPerformanceCounter();

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
        bool update = false;
        if (Keyboard::getInstance().isPressed(UP))
        {
            Camera::getCamera()->move({0, -cameraMovementByPixels});
            update = true;
        }
        if (Keyboard::getInstance().isPressed(DOWN))
        {
            Camera::getCamera()->move({0, cameraMovementByPixels});
            update = true;
        }
        if (Keyboard::getInstance().isPressed(LEFT))
        {
            Camera::getCamera()->move({-cameraMovementByPixels, 0});
            update = true;
        }
        if (Keyboard::getInstance().isPressed(RIGHT))
        {
            Camera::getCamera()->move({cameraMovementByPixels, 0});
            update = true;
        }
        if (update)
        {
            CHECK_RESULT(game->printTiles({csvFileMap[0], csvFileMap[1], csvFileMap[2]}, screen, tiles, Camera::getCamera()->getPos(), tileScale));
        }

        SDL_UpdateWindowSurface(window);
        Uint64 end = SDL_GetPerformanceCounter();

        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        std::cout << "Current FPS: " << std::to_string(1.0f / elapsed) << std::endl;
    }
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
