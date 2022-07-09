#include "GameTimer.h"

GameTimer::GameTimer()
	: mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec); // ���� Ÿ�̸��� ���ļ�(�ʴ� count)�� ����
	mSecondsPerCount = 1.0 / (double)countsPerSec; // count�� ��
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
	// ���� Ÿ�̸Ӱ� �ߴ� �����̸� �ߴܵ� �ķκ��� �帥 �ð��� ������� ���ƾ� �Ѵ�.
	// ���� ������ �Ͻ� ������ ���� �ִٸ� �� �ð��� ��ü �ð��� ���Խ�Ű�� ���ƾ� �Ѵ�.
	// �̸� ���� mStopTime���� �Ͻ����� �ð��� ����.
	//             ������ �Ͻ����� �ð�
	//              | <-----------> |
	// ---*---------*---------------*------*------------*-----> �ð�
	// mBaseTime                        mStopTime     mCurrTime
	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime)
			- mBaseTime) * mSecondsPerCount);
	}

	// �ð��� mCurrTime - mBastTime���� �Ͻ� ������ �ð��� ���ԵǾ� �ִ�.
	// �̸� ��ü �ð��� ���Խ�Ű�� �� �ǹǷ�, �� �ð��� mCurrTime���� ���Ѵ�.
	//              |<---�Ͻ����� �ð�--->|
	// ---*---------*---------------------*------------*-----> �ð�
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

	if (mStopped) // �ߴܵ� ���¿��� Ÿ�̸� �簳�ϴ� ��Ȳ
	{
		// �Ͻ����� �ð��� ������Ŵ
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
	// 1. �̹� �������� �ð��� ����
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime); // count ������ ���� �ð� ����
	mCurrTime = currTime;

	// 2. �� �ð��� ���� �������� �ð��� ���̸� ���� => �� ������ ����
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	// 3. ���� ������ �غ�
	mPrevTime = mCurrTime;

	// 4. ������ ���� �ʰ� ��
	// (���μ����� ���� ���� ���ų� �ٸ� ���μ����� ��Ű�� ��� mDeltaTime�� ������ �� �� ����)
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}

}
