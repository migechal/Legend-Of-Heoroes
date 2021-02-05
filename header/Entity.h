#pragma once
#include <string>
#include <SDL2/SDL_rect.h>
#include <vector>

class Entity{
protected:
    SDL_Rect Position;
    
    std::vector<int> Inventory;

    bool Hidden;

    int defaultHealth;
    int defaultDamage;
    int Rarity;
public:
    Entity(int defaultHealth, int defaultDamage, int Rarity, bool Hidden = false);
    int getHealth();
    int getDamage();
    int getRarity();
    int getItem(int index);
    bool getIsHidden();

    void giveItem(int itemID);
    void decreaseHealth(int decrease);
    void setDamage(int newDamage);
    void setPosition(int newPosition); 
};
class Ememy : Entity{
    std::string currentTarget;
public:
    std::string getCurrentTarget();

    void setCurrentTarget(std::string EntityName);
};

class Neutral : Entity{
    bool Attacked;
public:
    bool isAttacked();
};

class Good : Entity{
    bool Sell;
    int Age;
public:
    bool doesSell();
    int getAge();
};