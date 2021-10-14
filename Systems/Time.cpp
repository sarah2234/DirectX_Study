#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&tick);
	QueryPerformanceCounter((LARGE_INTEGER *)&start);

	last = 0;
}

Time::~Time()
{

}

void Time::Update()
{
	__int64 current;
	QueryPerformanceCounter((LARGE_INTEGER *)&current);

	elapsed = current - last;
	last = current;
}

float Time::Running()
{
	__int64 current;
	QueryPerformanceCounter((LARGE_INTEGER *)&current);

	return (float)((double)(current - start) / tick);
}

float Time::Elapsed()
{
	return (float)elapsed / tick;
}
