#pragma once
#include <Windows.h>

class GameTimer
{
public:
	GameTimer();

	float GameTime() const; // 초 단위
	float DeltaTime() const; // 초 단위
	float TotalTime() const; // Reset이 호출된 이후 흐른 시간에서 일시 정지된 시간을 제외한 시간 리턴
	
	void Reset(); // 메세지 루프 이전에 호출해야 함
	void Start(); // 타이머 시작/재개 시 호출해야 함
	void Stop(); // 일시정지 시 호출해야 함
	void Tick(); // 매 프레임마다 호출해야 함

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime; // Reset이 호출될 때 현재 시간으로 초기화
	__int64 mPausedTime; // 타이머가 일시 정지된 동안 계속해서 누적됨
	__int64 mStopTime; // 타이머가 중단된 시점의 시간
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};
