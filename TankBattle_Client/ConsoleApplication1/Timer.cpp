#include "Timer.h"

Timer::Timer(float timeout)
{
	mOldTime = 0;
	mCurTime = 0;
	mDeltaTime = 0.0f;
	mAccumulatedTime = 0.0f;
	mStartTime = (float)clock();
	mTimeout = timeout;
}
Timer::~Timer()
{

}
void Timer::Init()
{
	mOldTime = 0;
	mCurTime = 0;
	mDeltaTime = 0.0f;
	mAccumulatedTime = 0.0f;
	mStartTime = (float)clock();
}

float Timer::GetTime() const
{
	return mAccumulatedTime;
}
float Timer::GetTimeout() const
{
	return mTimeout;
}
void Timer::SetTimeout(float timeout)
{
	mTimeout = timeout;
}
void Timer::Update()
{
	mCurTime = (float)clock() - mStartTime;
	mDeltaTime = static_cast<float>(mCurTime - mOldTime) / 1000.0f;
	mOldTime = mCurTime;
	mAccumulatedTime += mDeltaTime;
}
bool Timer::Timeout()
{
	if (mAccumulatedTime >= mTimeout)
	{
		mAccumulatedTime = 0.0f;
		return true;
	}
	else
		return false;

}
