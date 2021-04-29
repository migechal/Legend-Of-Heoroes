#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <string>
#include <vector>
struct Rarity {
  Rarity(std::string name, int rarity);
  std::string name;
  int         rarity;
};
class Entity {
protected:
  SDL_Rect Position;

  std::vector<int> Inventory;
  SDL_Surface *    Surface;
  Rarity           rarity;
  bool             Hidden;
  int              health;
  int              defaultHealth;
  int              defaultDamage;
  int              damage;
  int              AnimationCounter;
  std::string      name;

public:
  enum DirectionFacing { DOWN = 0, LEFT = 1, UP = 2, RIGHT = 3 };
  Entity(int defaultHealth, int defaultDamage, Rarity rarity,
         SDL_Surface *Surface, SDL_Rect Position, bool Hidden = false);
  int         getHealth( );
  int         getDamage( );
  Rarity      getRarity( );
  int         getItem(int index);
  bool        getIsHidden( );
  std::string getName( );

  void giveItem(int itemID);
  void decreaseHealth(int decrease);
  void setDamage(int newDamage);
  void setPosition(SDL_Rect newPosition);
  int *getEntityTile(int x, int y);
};
class Ememy : public Entity {
  std::string currentTarget;

public:
  std::string getCurrentTarget( );

  void setCurrentTarget(std::string EntityName);
};

class Neutral : public Entity {
  bool Attacked;

public:
  bool isAttacked( );
};

class Good : public Entity {
  bool Sell;
  int  Age;

public:
  bool doesSell( );
  int  getAge( );
};

class Player : public Entity {
public:
  Player(std::string Name, int defaultHealth, int defaultDamage, Rarity rarity,
         SDL_Surface *Surface, SDL_Rect Position, bool Hidden = false);
};
