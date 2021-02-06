#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <map>
class Init{
    const int tileSize = 32;
    std::string baseDirectoryLocation;
    std::fstream& gotoLine(std::fstream& file, size_t num);
    int getSettingsFromJson(std::string path, std::string tree, std::string child);
    std::string GetResourcePath(std::string applicationPath);
public:
    Init(std::string dir, int tileSize);
    SDL_Surface *imageLoader(std::string file);
    std::map<int, int> getCSVRow(std::string CSVFile, int row);
    SDL_DisplayMode getDisplayMode();
    std::string getBaseDirectory();
};
