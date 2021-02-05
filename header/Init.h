#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <vector>
class Init{
    const int tileSize = 32;
    std::fstream& gotoLine(std::fstream& file, unsigned int num);
class Init{
    int getSettingsFromJson(std::string path, std::string tree, std::string child);
    std::string GetResourcePath(std::string applicationPath);
    std::string baseDirectoryLocation;
public:
    Init(std::string baseDirectoryLocation, int tileSize);
    SDL_Surface *imageLoader(std::string file);
    std::vector<SDL_Surface*> getCSVRow(std::string CSVFile, int row);
    Init(std::string baseDirectoryLocation);
    SDL_Surface *BMPloader(std::string file);

    SDL_DisplayMode getDisplayMode();
};