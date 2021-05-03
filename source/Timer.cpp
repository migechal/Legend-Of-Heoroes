#include "header/Timer.h"
#include <SDL2/SDL.h>

Timer *Timer::minstance = NULL;

Timer *Timer::getInstance(){
	if(minstance == NULL){
		minstance = new Timer();
	}
	return minstance;
}

void Timer::release(){
	delete minstance;
	minstance = NULL;
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

void Timer::update(){
	mElapsed = SDL_GetTicks() - mStart;
	mDelta = mElapsed * 0.001f;
}