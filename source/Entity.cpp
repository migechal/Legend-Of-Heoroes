#include "header/Entity.h"
#include <bits/stdc++.h>

Rarity::Rarity(std::string name, int rarity) : rarity(rarity), name(name) {}

Entity::Entity(int defaultHealth, int defaultDamage, Rarity rarity,
               SDL_Surface *surface, SDL_Rect position, bool hidden)
    : defaultHealth(defaultHealth),
      defaultDamage(defaultDamage),
      damage(defaultDamage),
      health(defaultHealth),
      rarity(rarity),
      surface(surface),
      position(position),
      hidden(hidden),
      animationCounter(0)
{
}

int         Entity::getHealth() { return health; }
int         Entity::getDamage() { return damage; }
Rarity      Entity::getRarity() { return rarity; }
bool        Entity::getIsHidden() { return hidden; }
std::string Entity::getName() { return name; }

void Entity::decreaseHealth(int decrease) { health -= decrease; }
void Entity::setDamage(int newDamage) { damage = newDamage; }
void Entity::setPosition(SDL_Rect newPosition) { position = newPosition; }

int *Entity::getEntityTile(int x, int y) { return 0; }

Player::Player(std::string name, int defaultHealth, int defaultDamage,
               Rarity rarity, SDL_Surface *surface, SDL_Rect position,
               bool hidden)
    : Entity(defaultHealth, defaultDamage, rarity, surface, position, false)
{
  this->name = name;
}
