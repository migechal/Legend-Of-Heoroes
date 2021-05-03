#include "header/Entity.h"
#include <SDL2/SDL.h>
#include <bits/stdc++.h>

Rarity::Rarity(std::string name, int rarity) : rarity(rarity), name(name) {}

Entity::Entity(int defaultHealth, int defaultDamage, Rarity rarity,
               SDL_Texture *texture, SDL_Rect position, int directionFacing,
               int offset, int amountOfChars, bool hidden)
    : defaultHealth(defaultHealth),
      defaultDamage(defaultDamage),
      damage(defaultDamage),
      rarity(rarity),
      texture(texture),
      position(position),
      directionFacing(directionFacing),
      offset(offset),
      amountOfChars(amountOfChars),
      hidden(hidden),
      health(defaultHealth),
      moving(false),
      animationCounter(0)
{
}

void Entity::toggleMovement() { moving = !moving; }
bool Entity::isMoving() { return moving; }

void Entity::setFrame(int frame)
{
  animationCounter = frame % getAmountOfChars();
}
int          Entity::getHealth() { return health; }
int          Entity::getDamage() { return damage; }
Rarity       Entity::getRarity() { return rarity; }
bool         Entity::getIsHidden() { return hidden; }
std::string  Entity::getName() { return name; }
int          Entity::getOffset() { return offset; }
int          Entity::getAmountOfChars() { return amountOfChars; }
SDL_Texture *Entity::getTexture() { return texture; }

void Entity::decreaseHealth(int decrease) { health -= decrease; }
void Entity::setDamage(int newDamage) { damage = newDamage; }

int *Entity::getEntityTile(int x, int y) { return 0; }

Player::Player(std::string name, int defaultHealth, int defaultDamage,
               Rarity rarity, SDL_Texture *texture, SDL_Rect position,
               int offset, int amountOfChars, bool hidden)
    : Entity(defaultHealth, defaultDamage, rarity, texture, position,
             DirectionFacing::DOWN, offset, amountOfChars, false)
{
  this->name = name;
}
