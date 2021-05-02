#include <bits/stdc++.h>

#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include "header/Entity.h"
#include "header/Game.h"
#include "header/Init.h"
#include "header/Input.h"
#include "header/KeyboardHandler.h"

#define GREEN                                                                  \
  {                                                                            \
    0, 255, 0                                                                  \
  }

#define CHECK_RESULT(fnc)                                                      \
  {                                                                            \
    auto res = fnc;                                                            \
    if (!res) {                                                                \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error("    \
                << SDL_GetError() << ")  err: " << res << " in " << #fnc       \
                << std::endl;                                                  \
      exit(-2);                                                                \
    }                                                                          \
  }

const int tileSize  = 32; // Tile Size from "Tiled"
const int scale     = 4;
const int tileScale = 3;

enum Location { MAINMENU = 0, INGAME = 1, OPTIONS = 2 };

int main(int argc, char** argv)
{
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  CHECK_RESULT(
      !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER));

  // Create Init class
  Init* init = new Init(argv[0], tileSize);

  std::vector<std::string> keyNames{
    init->getSettingsFromJson("settings/config.json", "Buttons", "up"),
    init->getSettingsFromJson("settings/config.json", "Buttons", "down"),
    init->getSettingsFromJson("settings/config.json", "Buttons", "left"),
    init->getSettingsFromJson("settings/config.json", "Buttons", "right")};

  const SDL_Scancode UP    = SDL_GetScancodeFromName(keyNames[0].c_str());
  const SDL_Scancode DOWN  = SDL_GetScancodeFromName(keyNames[1].c_str());
  const SDL_Scancode LEFT  = SDL_GetScancodeFromName(keyNames[2].c_str());
  const SDL_Scancode RIGHT = SDL_GetScancodeFromName(keyNames[3].c_str());

  const int cameraMovementByPixels = std::stoi(init->getSettingsFromJson(
      "settings/config.json", "Game", "CameraMovement"));

  KeyboardHandler keyboard({UP, DOWN, LEFT, RIGHT});

  int windowWidth  = init->getDisplayMode().w;
  int windowHeight = init->getDisplayMode().h;


  // // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(
      SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window* window =
      SDL_CreateWindow("Imeto na egrata", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, window_flags);
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);

  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync

  int oglIdx = -1;
  int nRD    = SDL_GetNumRenderDrivers();
  for (int i = 0; i < nRD; i++) {
    SDL_RendererInfo info;
    if (!SDL_GetRenderDriverInfo(i, &info)) {
      if (!strcmp(info.name, "opengl")) { oglIdx = i; }
    }
  }

  // Initialize OpenGL loader
  CHECK_RESULT(!gl3wInit());

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Load Fonts
  std::string defaultFont = init->getFontLocation("DisposableDroidBB.ttf");
  io.Fonts->AddFontFromFileTTF(defaultFont.c_str(), 30.0f);

  // Our state
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);




  auto renderer = SDL_CreateRenderer(
      window, oglIdx, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_Texture* text = SDL_CreateTextureFromSurface(
      renderer, init->imageLoader("assets/Loading/Loading.jpeg"));


  std::vector<std::vector<std::vector<int>>> csvFileMap{
    init->getCSVvector("assets/Map/Back.csv"),
    init->getCSVvector("assets/Map/Middle.csv"),
    init->getCSVvector("assets/Map/Front.csv")};


  SDL_Surface *t_tiles = init->imageLoader("assets/tiles.png");
  SDL_Texture *tiles   = SDL_CreateTextureFromSurface(renderer, t_tiles);
  SDL_FreeSurface(t_tiles);


  KeyboardHandler handleKeyboard = KeyboardHandler({UP, DOWN, LEFT, RIGHT});

  Game *  game   = nullptr;
  Camera *camera = nullptr;


  game   = new Game(init->getBaseDirectory(), tileSize);
  camera = new Camera(csvFileMap[0], tileSize, init->getDisplayMode());
  int direction = 0;
  // Main loop
  bool done = false;
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) done = true;
      if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE){
          done = true;
          break;
        }
      }
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }




    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    {
      ImGui::Begin("Game Panel"); // Create a window called "Hello, world!"
                                     // and append into it.

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);



    auto         _input        = handleKeyboard.handleInput();
    Command *    command       = std::get<0>(_input);
    SDL_Scancode buttonPressed = std::get<1>(_input);

    if (command != nullptr) {
      command->execute(*camera, cameraMovementByPixels);
    }

    CHECK_RESULT(game->printTiles(csvFileMap, renderer, tiles, camera->getPos(),
                                  tileScale));

    int temp = direction;

    if (buttonPressed == UP) {
      direction = 2;
    } else if (buttonPressed == DOWN) {
      direction = 0;
    } else if (buttonPressed == RIGHT) {
      direction = 3;
    } else if (buttonPressed == LEFT) {
      direction = 1;
    }
    // game->printEntity(player, renderer, direction);

    // SDL_RenderPresent(renderer);


    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

/*
int main(int argc, char **argv)
{
  CHECK_RESULT(!SDL_Init(SDL_INIT_EVERYTHING));

  const char* glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  //TTF_Init();

  // Create Init class
  Init *init = new Init(argv[0], tileSize);

  std::vector<std::string> keyNames{
      init->getSettingsFromJson("settings/config.json", "Buttons", "up"),
      init->getSettingsFromJson("settings/config.json", "Buttons", "down"),
      init->getSettingsFromJson("settings/config.json", "Buttons", "left"),
      init->getSettingsFromJson("settings/config.json", "Buttons", "right")};

  const SDL_Scancode UP    = SDL_GetScancodeFromName(keyNames[0].c_str());
  const SDL_Scancode DOWN  = SDL_GetScancodeFromName(keyNames[1].c_str());
  const SDL_Scancode LEFT  = SDL_GetScancodeFromName(keyNames[2].c_str());
  const SDL_Scancode RIGHT = SDL_GetScancodeFromName(keyNames[3].c_str());

  const int cameraMovementByPixels = std::stoi(init->getSettingsFromJson(
      "settings/config.json", "Game", "CameraMovement"));

  KeyboardHandler keyboard({UP, DOWN, LEFT, RIGHT});

  int windowWidth  = init->getDisplayMode().w;
  int windowHeight = init->getDisplayMode().h;

  SDL_Rect backgroundRect{0, 0, windowWidth, windowHeight};

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_BORDERLESS |
        SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window *window = SDL_CreateWindow(
      "Loading...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      windowWidth / scale, windowHeight / scale,
      window_flags);

  SDL_Rect loadingRect{0, 0, windowWidth / scale, windowHeight / scale};

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface *loading = init->imageLoader("assets/Loading/Loading.jpeg");

  SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, loading),
                 NULL, &loadingRect);
  SDL_RenderPresent(renderer);

  // Loads Needed to be done
  Gui* gui = nullptr;
  TTF_Font* font = init->LoadFont("DisposableDroidBB.ttf", 12);

  KeyboardHandler handleKeyboard = KeyboardHandler({UP, DOWN, LEFT, RIGHT});

  SDL_Surface *background = init->imageLoader("assets/MainMenu/MainMenu.png");
  SDL_SetSurfaceBlendMode(background, SDL_BLENDMODE_NONE);

  SDL_Surface *playerSurface =
      init->imageLoader("assets/Entity/Player/betty.png");

  Rarity garbage("Garbage", 0);
  Rarity uncommon("Uncommon", 1);
  Rarity common("Common", 2);
  Rarity rare("Rare", 3);

  // Destroy Loading Window objects

  SDL_DestroyWindow(window);
  SDL_FreeSurface(loading);


  // Create Main Window and Screen objects
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  window   = SDL_CreateWindow("Legend Of Heros", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                            window_flags | SDL_WINDOW_FULLSCREEN);

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Surface *t_tiles = init->imageLoader("assets/tiles.png");
  SDL_Texture *tiles   = SDL_CreateTextureFromSurface(renderer, t_tiles);
  SDL_FreeSurface(t_tiles);

  //gui = new Gui(window, renderer, init);


  SDL_Log("Created renderer for main window");
  SDL_Event e;

  SDL_Color color{181, 50, 22, 1};
  Button    playButton(windowWidth / 2 - 200, windowHeight / 3 * 2, 400, 150,
                    color);

  bool menuIsRunning = false;
  int  location      = MAINMENU;

  while (menuIsRunning) {
    while (SDL_PollEvent(&e)) {
      ImGui_ImplSDL2_ProcessEvent(&event);

      if (playButton.isClick()) {
        location      = INGAME;
        menuIsRunning = false;
        break;
      }
      switch (e.type) {
      case SDL_QUIT: menuIsRunning = false; break;
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          menuIsRunning = false;
          break;
        }
      }
    }
    SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, background),
                   NULL, &backgroundRect);
    playButton.print(renderer);
    SDL_RenderPresent(renderer);
  }

  location           = INGAME;
  bool gameIsRunning = true;

  std::vector<std::vector<std::vector<int>>> csvFileMap{
      init->getCSVvector("assets/Map/Back.csv"),
      init->getCSVvector("assets/Map/Middle.csv"),
      init->getCSVvector("assets/Map/Front.csv")};

  Game *  game   = nullptr;
  Camera *camera = nullptr;

  if (location == INGAME) {
    game   = new Game(init->getBaseDirectory(), tileSize);
    camera = new Camera(csvFileMap[0], tileSize, init->getDisplayMode());
  }

  bool update    = true;
  int  direction = 0;

  std::string playerName = "player";

  Player *player =
      new Player(playerName, 100, 10, garbage, playerSurface, {0, 0});

  std::cout << "If you don\'t see this it didnt get to line number " << __LINE__
            << " from file " << __FILE__ << std::endl;

  while (gameIsRunning && location == INGAME) {
    Uint64 start = SDL_GetPerformanceCounter();
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT: gameIsRunning = false; break;
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          gameIsRunning = false;
          break;
        }
      }
    }

    auto         _input        = handleKeyboard.handleInput();
    Command *    command       = std::get<0>(_input);
    SDL_Scancode buttonPressed = std::get<1>(_input);

    if (command != nullptr) {
      command->execute(*camera, cameraMovementByPixels);
    }

    CHECK_RESULT(game->printTiles(csvFileMap, renderer, tiles, camera->getPos(),
                                  tileScale));

    int temp = direction;

    if (buttonPressed == UP) {
      direction = 2;
    } else if (buttonPressed == DOWN) {
      direction = 0;
    } else if (buttonPressed == RIGHT) {
      direction = 3;
    } else if (buttonPressed == LEFT) {
      direction = 1;
    }
    game->printEntity(player, renderer, direction);
    Uint64 end = SDL_GetPerformanceCounter();

    float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();

    //gui->addText("Current FPS: " + std::to_string(int(1.0f / elapsed)),
{windowWidth, 0}, font, GREEN, 10);

    SDL_RenderPresent(renderer);

  }
  SDL_DestroyRenderer(renderer);
  SDL_FreeSurface(background);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
*/