#pragma once
#include <string>
enum Rarity {
  COMMON    = 0,
  UNCOMMON  = 1,
  RARE      = 2,
  SUPERRARE = 3,
  LEGENDARY = 4,
  GODLY     = 5
};

class Object {
  int         Rarity;
  std::string Name;

public:
  Object(int Rarity, std::string Name);
  std::string getName( );
  int         getRarity( );
};