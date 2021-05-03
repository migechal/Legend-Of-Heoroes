#pragma once

class Timer{
	static Timer* minstance;

	unsigned int mStart, mElapsed;

	float mDelta, mScale;

	Timer();
	~Timer();

public:
	static Timer* getInstance();

	static void release();

	void reset();

	float getDeltaTime();

	void timeScale(float f);

	float getScale();

	void update();
};