#include "GameTimer.h"

GameTimer::GameTimer()
	: mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec); // 성능 타이머의 주파수(초당 count)를 얻음
	mSecondsPerCount = 1.0 / (double)countsPerSec; // count당 초
}

float GameTimer::GameTime() const
{
	return 0.0f;
}

float GameTimer::DeltaTime() const
{
	return (float)mDeltaTime;
}

float GameTimer::TotalTime() const
{
	// 현재 타이머가 중단 상태이면 중단된 후로부터 흐른 시간은 계산하지 말아야 한다.
	// 또한 이전에 일시 정지된 적이 있다면 그 시간도 전체 시간에 포함시키지 말아야 한다.
	// 이를 위해 mStopTime에서 일시정지 시간을 뺀다.
	//             이전의 일시정지 시간
	//              | <-----------> |
	// ---*---------*---------------*------*------------*-----> 시간
	// mBaseTime                        mStopTime     mCurrTime
	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime)
			- mBaseTime) * mSecondsPerCount);
	}

	// 시간차 mCurrTime - mBastTime에는 일시 정지된 시간이 포함되어 있다.
	// 이를 전체 시간에 포함시키면 안 되므로, 그 시간을 mCurrTime에서 제한다.
	//              |<---일시정지 시간--->|
	// ---*---------*---------------------*------------*-----> 시간
	// mBaseTime  mStopTime            startTime   mCurrTime
	else
	{
		return (float)(((mCurrTime - mPausedTime) -
			mBaseTime) * mSecondsPerCount);
	}
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (mStopped) // 중단된 상태에서 타이머 재개하는 상황
	{
		// 일시정지 시간을 누적시킴
		mPausedTime += (startTime - mStopTime);
		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mStopTime = currTime;
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}
	// 1. 이번 프레임의 시간을 얻음
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime); // count 단위로 현재 시간 구함
	mCurrTime = currTime;

	// 2. 이 시간과 이전 프레임의 시간의 차이를 구함 => 초 단위로 구함
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	// 3. 다음 프레임 준비
	mPrevTime = mCurrTime;

	// 4. 음수가 되지 않게 함
	// (프로세서가 절전 모드로 들어가거나 다른 프로세서와 엉키는 경우 mDeltaTime이 음수가 될 수 있음)
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}

}
