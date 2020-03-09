#include "JTIME.h"


#pragma region TIME::TIMER

Time::Timer::Timer() : deltaTime(0.0f)
{
	Reset();
}

Time::Timer::~Timer()
{

}

float Time::Timer::Update()
{
	QueryPerformanceCounter(&curTime);

	dDeltaTime = ((double)curTime.QuadPart - (double)prevTime.QuadPart) / (double)frequency.QuadPart;
	deltaTime = (float)dDeltaTime;
	prevTime = curTime;


	return deltaTime;
}

void Time::Timer::Reset()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&prevTime);
	QueryPerformanceCounter(&curTime);
}

#pragma endregion

//================================//

#pragma region TIME
Time::Timer Time::mainTimer;

void Time::Update()
{
	mainTimer.Update();
}

void Time::Reset()
{
	mainTimer.Reset();
}

UINT Time::getFPS()
{
	return (UINT)(1.0f / mainTimer.deltaTime);
}

#pragma endregion




