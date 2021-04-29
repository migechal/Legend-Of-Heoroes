#include "header/Entity.h"
#include <bits/stdc++.h>
Rarity::Rarity(std::string name, int rarity) : rarity(rarity), name(name) {}

Entity::Entity(int defaultHealth, int defaultDamage, Rarity rarity,
               SDL_Surface *Surface, SDL_Rect Position, bool Hidden)
    : defaultHealth(defaultHealth),
      defaultDamage(defaultDamage),
      damage(defaultDamage),
      health(defaultHealth),
      rarity(rarity),
      Surface(Surface),
      Position(Position),
      Hidden(Hidden),
      AnimationCounter(0) {}
int         Entity::getHealth( ) { return health; }
int         Entity::getDamage( ) { return damage; }
Rarity      Entity::getRarity( ) { return rarity; }
bool        Entity::getIsHidden( ) { return Hidden; }
std::string Entity::getName( ) { return name; }

void Entity::decreaseHealth(int decrease) { health -= decrease; }
void Entity::setDamage(int newDamage) { damage = newDamage; }
void Entity::setPosition(SDL_Rect newPosition) { Position = newPosition; }

int *Entity::getEntityTile(int x, int y) { return 0; }

Player::Player(std::string Name, int defaultHealth, int defaultDamage,
               Rarity rairty, SDL_Surface *Surface, SDL_Rect Position,
               bool Hidden)
    : Entity(defaultHealth, defaultDamage, rarity, Surface, Position, false) {
  this->name = Name;
}
