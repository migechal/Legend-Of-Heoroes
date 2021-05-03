#pragma once

class Timer{
	static Timer* instance;

	unsigned int mStart, mElapsed;

	float mDelta, mScale;

	Timer();
	~Timer();

public:
	static Timer* getInstance();

	static void release();

	void reset();

	float getDeltaTime();

        int getElapsedTime();

	void timeScale(float f);

	float getScale();

	void update();
};