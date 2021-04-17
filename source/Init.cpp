#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include "header/Init.h"
#include <SDL2/SDL_image.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#define CHECK_RESULT(fnc)                                                      \
  {                                                                            \
    auto res = fnc;                                                            \
    if (!res) {                                                                \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error("    \
                << SDL_GetError( ) << ")  err: " << res << " in " << #fnc      \
                << std::endl                                                   \
                << "Maybe ;; export LEGEND_OF_HEROES=`pwd` ;; will fix?"       \
                << std::endl;                                                  \
      exit(-2);                                                                \
    }                                                                          \
  }

Init::Init(std::string dir, int tileSize) : tileSize(tileSize) {
  baseDirectoryLocation = GetResourcePath(dir);

  CHECK_RESULT(!exists("settings/exists"));
}
bool Init::exists(std::string file) {
  std::fstream f((baseDirectoryLocation + file).c_str( ));
  return f.fail( );
}
std::string Init::getSettingsFromJson(std::string path, std::string tree,
                                      std::string child) {
  std::cout << baseDirectoryLocation << std::endl;
  std::string pathSettings = baseDirectoryLocation + path;
  std::cout << "Settings from " << pathSettings << std::endl;
  std::string value;
  namespace pt = boost::property_tree;
  pt::ptree loadPtreeRoot;
  pt::read_json(pathSettings, loadPtreeRoot);
  pt::ptree   temp;
  pt::ptree   tsize;
  std::string type;
  //! Get child of file
  temp  = loadPtreeRoot.get_child(tree);
  tsize = temp.get_child(child);
  value = tsize.get_value<std::string>( );
  return value;
}

std::string Init::GetResourcePath(std::string applicationPath) {
  if (!getenv("LEGEND_OF_HEROES")) {
    std::cout << "Failed to get variable" << std::endl;
  }
  auto envResourcePath = getenv("LEGEND_OF_HEROES");

  if (envResourcePath != NULL) {
    applicationPath.assign(envResourcePath);
    if (applicationPath.back( ) != '/') { applicationPath += "/"; }
    return applicationPath;
  } else {
    while (applicationPath.back( ) != '/') { applicationPath.pop_back( ); }
  }
  return applicationPath + "";
}

std::string Init::getBaseDirectory( ) { return this->baseDirectoryLocation; }

std::fstream &Init::gotoLine(std::fstream &file, size_t num) {
  file.seekg(std::ios::beg);
  for (size_t i = 0; i < num - 1; ++i) {
    file.ignore(std::numeric_limits<std::streamsize>::max( ), '\n');
  }
  return file;
}

std::vector<std::vector<int>> Init::getCSVvector(std::string CSVFile) {
  std::vector<std::vector<int>> content;
  std::string                   line;
  auto                          temp = CSVFile;
  CSVFile                            = baseDirectoryLocation + temp;
  std::fstream file(CSVFile);

  while (getline(file, line)) {
    std::vector<int> lineContent;
    for (size_t i = 0; i < line.length( ); ++i) {
      int  currentNum = 0;
      bool sign       = true;
      for (; isdigit(line[i]) || line[i] == '-'; ++i) {
        if (line[i] == '-') {
          sign = false;
        } else {
          currentNum *= 10;
          currentNum += line[i] - '0';
        }
      }
      lineContent.push_back(sign ? currentNum : -currentNum);
    }
    content.push_back(lineContent);
  }

  return content;
}

SDL_Surface *Init::imageLoader(std::string file) {

  SDL_Log(file.c_str( ));
  std::string temp = file;
  std::cout << baseDirectoryLocation << std::endl;
  SDL_Log(baseDirectoryLocation.c_str( ));
  file = baseDirectoryLocation;
  file.append(temp.c_str( ));

  SDL_Surface *bp = IMG_Load(file.c_str( ));
  SDL_Log(file.c_str( ));
  CHECK_RESULT(bp);
  return bp;
}

SDL_DisplayMode Init::getDisplayMode( ) {
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  return DM;
}
