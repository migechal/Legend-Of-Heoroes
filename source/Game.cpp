#include "header/Game.h"
#include "header/Init.h"
#include <SDL2/SDL.h>
#include <bits/stdc++.h>

Game::Game(std::string baseDirectoryLocation, int tileSize)
    : tileSize(tileSize), baseDir(baseDirectoryLocation) {}
int Game::roundDown(int &num, int toSize) {
  for (; num % tileSize != 0; --num) {
    // DO NOTHING
  }
  return num;
}
int Game::cordinateToTile(int x, int y, std::string tileLocation) {
  Init *csvGet = new Init(baseDir, tileSize);
  roundDown(x, tileSize);
  roundDown(y, tileSize);
  x /= tileSize; // Get the location of the tile
  y /= tileSize; // Get the location of the tile
  return csvGet->getCSVvector(tileLocation)[x][y];
}

bool Game::checkHitbox(int x, int y, std::vector<std::string> tileLocation) {
  for (size_t i = 0; i < tileLocation.size( ); ++i) {
    int temp = cordinateToTile(x, y, tileLocation[i]);
    if (temp >= 0 &&
        std::binary_search(hitboxes.begin( ), hitboxes.end( ), temp)) {
      return false;
    };
  }
  return true;
}
int Game::pixelToTile(int pixel) { return (pixel >= 0) ? pixel / tileSize : 0; }
int Game::printTiles(std::vector<std::vector<std::vector<int>>> csv,
                     SDL_Surface *screen, SDL_Surface *tiles, SDL_Rect position,
                     int tileScale) {
  if (position.x < 0 || position.y < 0) {
    std::cout << "Error!! Camera position is out of bounds." << std::endl;
    return 0;
  }
  Init *get = new Init("n", 0);

  int cutTilesX = position.x % tileSize - position.x;
  int cutTilesY = position.y % tileSize - position.y;
  /*
  / Remember, start from back to front.
  */
  int windowWidth  = get->getDisplayMode( ).w;
  int windowHeight = get->getDisplayMode( ).h;

  if (csv.empty( )) { SDL_Log("Couldn't load CSV file"); }

  int destTileSize = tileSize * tileScale;
  int srcTileSize  = tileSize;
  for (size_t i = 0; i < csv.size( ); ++i) {
    for (size_t row = pixelToTile(position.y - tileSize), rowPlacement = 0;
         row < csv[i].size( ) - pixelToTile(windowHeight + tileSize);
         ++row && ++rowPlacement) {
      for (size_t col = pixelToTile(position.x - tileSize), colPlacement = 0;
           col < csv[i][row].size( ) - pixelToTile(windowWidth + tileSize);
           ++col, ++colPlacement) {
        SDL_Rect dist{
            static_cast<int>(destTileSize * col) - position.x * tileSize / 2,
            static_cast<int>(destTileSize * row) - position.y * tileSize / 2,
            destTileSize, destTileSize};
        if (csv[i][row][col] != -1) {
          SDL_Rect src{(csv[i][row][col] % tileSize) * srcTileSize,
                       (csv[i][row][col] / tileSize) * srcTileSize, srcTileSize,
                       srcTileSize};
          SDL_BlitScaled(tiles, &src, screen, &dist);
        }
      }
    }
  }
  return 1;
}

void printPlayer(SDL_Surface *player, SDL_Surface *screen, SDL_Rect position,
                 int facing) {}

Camera::Camera(std::vector<std::vector<int>> currentLevel, int tileSize,
               SDL_DisplayMode Display)
    : currentLevel(currentLevel), tileSize(tileSize), Display(Display) {
  levelSize.w = currentLevel.size( );
  levelSize.h = currentLevel[0].size( );
}

void Camera::move(SDL_Rect loc) {
  if (cameraPosition.x + loc.x < 0 || cameraPosition.y + loc.y < 0 ||
      cameraPosition.x + loc.x >
          (currentLevel.size( ) * tileSize) - Display.w ||
      cameraPosition.y + loc.y >
          (currentLevel[0].size( ) * tileSize) - Display.h) {
    return;
  }
  cameraPosition.x += loc.x;
  cameraPosition.y += loc.y;
}
SDL_Rect Camera::getPos( ) {
  std::cout << cameraPosition.x << " " << cameraPosition.y << std::endl;
  return cameraPosition;
}
