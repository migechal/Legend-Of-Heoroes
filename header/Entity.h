#pragma once
#include <string>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <vector>

class Entity
{
protected:
    SDL_Rect Position;

    std::vector<int> Inventory;
    SDL_Surface *Surface;
    bool Hidden;
    int health;
    int defaultHealth;
    int defaultDamage;
    int Rarity;
    std::string name;

public:
    Entity(int defaultHealth, int defaultDamage, int Rarity, bool Hidden = false);
    int getHealth();
    int getDamage();
    int getRarity();
    int getItem(int index);
    bool getIsHidden();
    std::string getName();

    void giveItem(int itemID);
    void decreaseHealth(int decrease);
    void setDamage(int newDamage);
    void setPosition(int newPosition);
    void printEntity(SDL_Surface *screen);
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
    int Age;

public:
    bool doesSell();
    int getAge();
};

class Player : public Entity
{
public:
    Player(std::string Name);
};