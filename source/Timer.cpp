#include "header/Timer.h"
#include <SDL2/SDL.h>

Timer *Timer::instance = NULL;

Timer *Timer::getInstance(){
	if(instance == NULL){
		instance = new Timer();
	}
	return instance;
}

void Timer::release(){
	delete instance;
	instance = NULL;
}

Timer::Timer(){
	reset();
	mScale = 1.0f;
}
Timer::~Timer(){

}

void Timer::reset(){
	mStart = SDL_GetTicks();
	mElapsed = 0;
	mDelta = 0.0f;
}

float Timer::getDeltaTime(){
	return mDelta;
}

void Timer::timeScale(float f){
	mScale = f;
}

float Timer::getScale(){
	return mScale;
}

int Timer::getElapsedTime(){
  return mElapsed;
}

void Timer::update(){
	mElapsed = SDL_GetTicks() - mStart;
	mDelta = mElapsed * 0.001f;
}