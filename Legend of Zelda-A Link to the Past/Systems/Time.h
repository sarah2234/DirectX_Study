#pragma once

class Time
{
public:
	Time();
	~Time();

	void Update();

	float Running();
	float Elapsed();

private:
	__int64 tick;
	__int64 start;

	__int64 elapsed;
	__int64 last;
};