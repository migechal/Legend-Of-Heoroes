#include "header/Entity.h"
#include <bits/stdc++.h>

Entity::Entity(int defaultHealth, int defaultDamage, int Rarity, bool Hidden) {}
int         Entity::getHealth( ) { return health; }
int         Entity::getDamage( ) { return damage; }
int         Entity::getRarity( ) { return Rarity; }
bool        Entity::getIsHidden( ) { return Hidden; }
std::string Entity::getName( ) { return name; }

void Entity::decreaseHealth(int decrease) { health -= decrease; }
void Entity::setDamage(int newDamage) { damage = newDamage; }
void Entity::setPosition(SDL_Rect newPosition) { Position = newPosition; }
void Entity::printEntity(SDL_Surface *screen) {}
int *Entity::getEntityTile(int x, int y) { return 0; }