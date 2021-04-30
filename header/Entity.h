#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
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
  SDL_Rect position;

  std::vector<int> inventory;
  SDL_Surface *    surface;
  Rarity           rarity;
  bool             hidden;
  int              health;
  int              defaultHealth;
  int              defaultDamage;
  int              damage;
  int              animationCounter;
  std::string      name;

public:
  enum DirectionFacing { DOWN = 0, LEFT = 1, UP = 2, RIGHT = 3 };
  Entity(int defaultHealth, int defaultDamage, Rarity rarity,
         SDL_Surface *surface, SDL_Rect position, bool hidden = false);
  int         getHealth();
  int         getDamage();
  Rarity      getRarity();
  int         getItem(int index);
  bool        getIsHidden();
  std::string getName();

  void giveItem(int itemID);
  void decreaseHealth(int decrease);
  void setDamage(int newDamage);
  void setPosition(SDL_Rect newposition);
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
         SDL_Surface *surface, SDL_Rect position, bool hidden = false);
};
