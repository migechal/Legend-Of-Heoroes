#include "header/Player.h"
#include <string>
#include <iostream>
#include <SDL2/SDL_rect.h>
#define CHECK_RESULT(fnc)                                                         \
    {                                                                             \
        auto res = fnc;                                                           \
        if (!res)                                                                 \
        {                                                                         \
            std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                      << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                      << std::endl;                                               \
            exit(-2);                                                             \
        }                                                                         \
    }
#include <SDL2/SDL_rect.h>

Player::Player(std::string Name):
    Name(Name){}

int Player::getHealth(){
    return this->Health;
}
std::string Player::getName(){
    return this->Name;
}
SDL_Rect Player::getPosition(){
    return this->Position;
}
void Player::decreaseHealth(int decrease=10){
    this->Health -= decrease;
    return;
}
void Player::setPosition(SDL_Rect newPos){
    this->Position = newPos;
}
void Player::printPlayer(SDL_Surface* screen){
    CHECK_RESULT(SDL_BlitSurface(this->surface, NULL, screen, &this->Position));
}