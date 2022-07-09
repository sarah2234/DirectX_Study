#pragma once
#include <Windows.h>

class GameTimer
{
public:
	GameTimer();

	float GameTime() const; // �� ����
	float DeltaTime() const; // �� ����
	float TotalTime() const; // Reset�� ȣ��� ���� �帥 �ð����� �Ͻ� ������ �ð��� ������ �ð� ����
	
	void Reset(); // �޼��� ���� ������ ȣ���ؾ� ��
	void Start(); // Ÿ�̸� ����/�簳 �� ȣ���ؾ� ��
	void Stop(); // �Ͻ����� �� ȣ���ؾ� ��
	void Tick(); // �� �����Ӹ��� ȣ���ؾ� ��

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime; // Reset�� ȣ��� �� ���� �ð����� �ʱ�ȭ
	__int64 mPausedTime; // Ÿ�̸Ӱ� �Ͻ� ������ ���� ����ؼ� ������
	__int64 mStopTime; // Ÿ�̸Ӱ� �ߴܵ� ������ �ð�
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};
