#pragma once
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

class Init
{
    const int tileSize = 32;
    std::string baseDirectoryLocation;
    std::fstream &gotoLine(std::fstream &file, size_t num);
    std::string GetResourcePath(std::string applicationPath);
    bool exists(std::string file);

public:
    Init(std::string dir, int tileSize);

    std::string getSettingsFromJson(std::string path, std::string tree, std::string child);
    SDL_Surface *imageLoader(std::string file);
    std::vector<std::vector<int>> getCSVvector(std::string CSVFile);
    std::string getFontLocation(std::string fontName);
    SDL_DisplayMode getDisplayMode();
    std::string getBaseDirectory();
};
