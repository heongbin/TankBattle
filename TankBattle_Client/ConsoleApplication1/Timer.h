#pragma once

#include <ctime>

class Timer
{
public:
	Timer(float timeout = 1.0f);
	~Timer();

	void Init();
	float GetTime() const;
	float GetTimeout() const;
	void Update();
	void SetTimeout(float timeout);
	bool Timeout();

private:
	float mOldTime;
	float mCurTime;
	float mDeltaTime;
	float mAccumulatedTime;
	float mStartTime;
	float mTimeout;
};

