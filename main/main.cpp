#include <bits/stdc++.h>

#include "../imgui/GL/gl3w.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_sdl.h"

#include "../header/Init.h"
#include "../header/KeyboardHandler.h"
#include "../header/Entity.h"
#include "../header/Game.h"
#include "../header/Init.h"
#include "../header/Input.h"
#include "../header/KeyboardHandler.h"
#include "../header/Timer.h"

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

const int tileSize = 32; // Tile Size from "Tiled"
const int scale    = 4;
const int tickTime = 50;

enum Location { MAINMENU = 0, INGAME = 1, OPTIONS = 2 };

int main(int argc, char** argv)
{
  // GL 3.0 + GLSL 130
  // return 0;
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
      init->getSettingsFromJson("settings/config.json", "Buttons", "right"),
      init->getSettingsFromJson("settings/config.json", "Buttons", "sprint"),
      init->getSettingsFromJson("settings/config.json", "Buttons", "sneak"),
  };

  const SDL_Scancode UP     = SDL_GetScancodeFromName(keyNames[0].c_str());
  const SDL_Scancode DOWN   = SDL_GetScancodeFromName(keyNames[1].c_str());
  const SDL_Scancode LEFT   = SDL_GetScancodeFromName(keyNames[2].c_str());
  const SDL_Scancode RIGHT  = SDL_GetScancodeFromName(keyNames[3].c_str());
  const SDL_Scancode SPRINT = SDL_GetScancodeFromName(keyNames[4].c_str());
  const SDL_Scancode SNEAK  = SDL_GetScancodeFromName(keyNames[5].c_str());

  const int cameraMovementByPixels = std::stoi(init->getSettingsFromJson(
      "settings/config.json", "Game", "CameraMovement"));

  KeyboardHandler keyboard({UP, DOWN, LEFT, RIGHT, SPRINT, SNEAK});

  int windowWidth  = init->getDisplayMode().w;
  int windowHeight = init->getDisplayMode().h;

  // // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  auto window_flags = (SDL_WindowFlags)(
      SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window* window = SDL_CreateWindow(
      "Imeto na egrata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      windowWidth, windowHeight, window_flags);
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

  SDL_Surface* t_tiles = init->imageLoader("assets/tiles.png");
  SDL_Texture* tiles   = SDL_CreateTextureFromSurface(renderer, t_tiles);
  SDL_FreeSurface(t_tiles);

  Rarity garbage("Garbage", 0);
  Rarity uncommon("Uncommon", 1);
  Rarity common("Common", 2);
  Rarity rare("Rare", 3);

  Game*       game       = nullptr;
  Camera*     camera     = nullptr;
  Entity*     player     = nullptr;
  Timer*      tickTimer  = nullptr;
  std::string playerName = "player";

  player = new Player(
      playerName, 100, 10, garbage,
      SDL_CreateTextureFromSurface(
          renderer, init->imageLoader("assets/Entity/Player/betty.png")),
      {500, 500}, 48, 4);

  game      = new Game(init->getBaseDirectory(), tileSize);
  camera    = new Camera(csvFileMap[0], tileSize, init->getDisplayMode());
  tickTimer = Timer::getInstance();

  // Main loop
  bool done = false;
  tickTimer->reset();

  while (!done) {
    tickTimer->update();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) done = true;
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
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
                  1000.0f / ImGui::GetIO().Framerate,
                  ImGui::GetIO().Framerate);
      ImGui::End();
    }
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    auto         _input        = keyboard.handleInput();
    Command*     command       = std::get<0>(_input);
    SDL_Scancode buttonPressed = std::get<1>(_input);

    if (command != nullptr) {
      int speed = cameraMovementByPixels;
      if (keyboard.isSprint()) { speed *= 2; }
      if (keyboard.isSneak()) { speed *= 0.8; }
      command->execute(*camera, speed);
      if (!player->isMoving()) { player->toggleMovement(); }
    } else {
      if (player->isMoving()) {
        player->toggleMovement();
        player->animationCounter = 0;
      }
    }

    int temp = player->directionFacing;

    if (buttonPressed == UP) {
      player->directionFacing = 2;
    } else if (buttonPressed == DOWN) {
      player->directionFacing = 0;
    } else if (buttonPressed == RIGHT) {
      player->directionFacing = 3;
    } else if (buttonPressed == LEFT) {
      player->directionFacing = 1;
    }
    CHECK_RESULT(
        game->printTiles(csvFileMap, renderer, tiles, camera->getPos(), scale));

    game->printEntity(player, renderer, 5);

    if (tickTimer->getElapsedTime() >= tickTime) {

      if (player->isMoving()) { player->increaseAnimationCounter(); }
      tickTimer->reset();
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
  }

  // Cleanup
  tickTimer->release();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}