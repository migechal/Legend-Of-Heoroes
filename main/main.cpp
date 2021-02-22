#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <map>
#include <string_view>
#include "header/Init.h"
#include "header/Player.h"
#include "header/Menu.h"
#include "header/Game.h"
#include "header/KeyboardHandler.h"
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

    std::vector<std::string> keyNames{
        init.getSettingsFromJson("settings/config.json", "Buttons", "up"),
        init.getSettingsFromJson("settings/config.json", "Buttons", "down"),
        init.getSettingsFromJson("settings/config.json", "Buttons", "left"),
        init.getSettingsFromJson("settings/config.json", "Buttons", "right")};
    const SDL_Scancode UP = SDL_GetScancodeFromName(keyNames[0].c_str());
    const SDL_Scancode DOWN = SDL_GetScancodeFromName(keyNames[1].c_str());
    const SDL_Scancode LEFT = SDL_GetScancodeFromName(keyNames[2].c_str());
    const SDL_Scancode RIGHT = SDL_GetScancodeFromName(keyNames[3].c_str());
    const int cameraMovementByPixels = std::stoi(init.getSettingsFromJson("settings/config.json", "Game", "CameraMovement"));

    KeyboardHandler keyboard({UP, DOWN, LEFT, RIGHT});

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

        Command *keyboardCommand = keyboard.handleInput();
        if (keyboardCommand != nullptr)
        {
            keyboardCommand->execute(cameraMovementByPixels);
        }

        CHECK_RESULT(Game::getInstance(init.getBaseDirectory())->printTiles({init.getCSVvector("assets/Map/Back.csv"), init.getCSVvector("assets/Map/Middle.csv"), init.getCSVvector("assets/Map/Front.csv")}, screen, tileSize, tiles, Camera::camera()->getPos()));

        SDL_UpdateWindowSurface(window);
    }
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
