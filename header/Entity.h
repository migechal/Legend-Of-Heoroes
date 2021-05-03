#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>

struct Rarity {
  Rarity(std::string name, int rarity);

  int rarity;

  std::string name;
};

class Entity
{
protected:
  std::vector<int> inventory;
  SDL_Texture *    texture;
  Rarity           rarity;
  bool             hidden;
  int              health;
  int              defaultHealth;
  int              defaultDamage;
  int              damage;
  int              offset;
  int              amountOfChars;
  std::string      name;

public:
  enum DirectionFacing { DOWN = 0, LEFT = 1, UP = 2, RIGHT = 3 };
  Entity(int defaultHealth, int defaultDamage, Rarity rarity,
         SDL_Texture *texture, SDL_Rect position, int directionFacing,
         int offset, int amountOfChars, bool hidden = false);

  SDL_Rect     position;
  int          animationCounter;
  int          directionFacing;
  int          getHealth();
  int          getDamage();
  Rarity       getRarity();
  int          getItem(int index);
  bool         getIsHidden();
  int          getOffset();
  int          getAmountOfChars();
  std::string  getName();
  SDL_Texture *getTexture();

  void giveItem(int itemID);
  void decreaseHealth(int decrease);
  void setDamage(int newDamage);
  int *getEntityTile(int x, int y);
};
class Ememy : public Entity
{
  std::string currentTarget;

public:
  std::string getCurrentTarget();

  void setCurrentTarget(std::string EntityName);
};

class Neutral : public Entity
{
  bool Attacked;

public:
  bool isAttacked();
};

class Good : public Entity
{
  bool Sell;
  int  Age;

public:
  bool doesSell();
  int  getAge();
};

class Player : public Entity
{
public:
  Player(std::string name, int defaultHealth, int defaultDamage, Rarity rarity,
         SDL_Texture *texture, SDL_Rect position, int offset, int amountOfChars,
         bool hidden = false);
};
