#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include "header/Init.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <iostream>
#include <zip.h>
#include <minizip/mztools.h>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

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

Init::Init(std::string dir, int tileSize) : tileSize(tileSize)
{
    baseDirectoryLocation = GetResourcePath(dir);
    std::cout << baseDirectoryLocation << std::endl;
}

int Init::getSettingsFromJson(std::string path, std::string tree, std::string child)
{
    std::string pathSettings = path + "settings/config.json";
    std::cout << "Settings from " << pathSettings << std::endl;
    int num;
    namespace pt = boost::property_tree;
    pt::ptree loadPtreeRoot;
    pt::read_json(pathSettings, loadPtreeRoot);
    pt::ptree temp;
    pt::ptree tsize;
    std::string type;
    //! Get child of file
    temp = loadPtreeRoot.get_child(tree);
    tsize = temp.get_child(child);
    num = tsize.get_value<int>();
    return num;
}

std::string Init::GetResourcePath(std::string applicationPath)
{
    if (!getenv("LEGEND_OF_HEROES"))
    {
        std::cout << "Failed to get variable" << std::endl;
    }
    auto envResourcePath = getenv("LEGEND_OF_HEROES");
    std::cout << "envResourcePath:  " << (envResourcePath ? envResourcePath : "NULL")
              << std::endl;
    if (envResourcePath != NULL)
    {
        applicationPath.assign(envResourcePath);
        if (applicationPath.back() != '/')
        {
            applicationPath += "/";
        }
        return applicationPath;
    }
    else
    {
        while (applicationPath.back() != '/')
        {
            applicationPath.pop_back();
        }
    }
    return applicationPath + "";
}

std::string Init::getBaseDirectory()
{
    return this->baseDirectoryLocation;
}

std::fstream &Init::gotoLine(std::fstream &file, size_t num)
{
    file.seekg(std::ios::beg);
    for (size_t i = 0; i < num - 1; ++i)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return file;
}

std::map<int, int> Init::getCSVRow(std::string CSVFile, int row)
{
    std::map<int, int> location;
    std::string line;
    auto temp = CSVFile;
    CSVFile = baseDirectoryLocation + temp;
    std::fstream file(CSVFile);
    //
    this->gotoLine(file, row);
    file >> line;
    int pos = 0;
    for (size_t i = 0; i < line.length(); ++i)
    {
        int currentNum = 0;
        for (; line[pos] != ','; ++pos)
        {
            if (line[pos] != '-')
            {
                currentNum += line[pos] * 10 * i;
            }
        }
        if (currentNum != 0)
        {
            for (int column = 0; column < 2016; column += tileSize)
            {
                if (tileSize * currentNum < 1024)
                {
                    location[column, currentNum * tileSize];
                }
            }
        }
        ++pos;
    }
    //
    return location;
}

SDL_Surface *Init::imageLoader(std::string file)
{

    SDL_Log(file.c_str());
    std::string temp = file;
    std::cout << baseDirectoryLocation << std::endl;
    SDL_Log(baseDirectoryLocation.c_str());
    file = baseDirectoryLocation;
    file.append(temp.c_str());

    SDL_Surface *bp = IMG_Load(file.c_str());
    SDL_Log(file.c_str());
    CHECK_RESULT(bp);
    return bp;
}

SDL_DisplayMode Init::getDisplayMode()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    return DM;
}
