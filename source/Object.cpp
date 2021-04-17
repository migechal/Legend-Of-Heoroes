#include "header/Object.h"
#include <bits/stdc++.h>

Object::Object(int Rarity, std::string Name) : Rarity(Rarity), Name(Name) {}

std::string Object::getName( ) { return this->Name; }

int Object::getRarity( ) { return this->Rarity; }
