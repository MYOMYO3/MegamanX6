#pragma once

#pragma region HTIME단위
//단위

//1초에 RUN을
//deltatime
//컴퓨터의 프레임사이 간격을
//현실시간으로 변경한 시간
//
//A컴퓨터는 20 (20 * deltatime()) = 1;
//B컴퓨터는 10 (10 * deltatime()) = 1;
//
//컴퓨터는 cpu에 물리적으로
//항상 정확히 1초마다 정확히 같은 수를 정확히 똒같이 반복적으로 새고있다.
//1초에 100번을 센다
//ConstTime = 100;
//
//ConstTime = 1초에 얼마나 셀수있는 함수()
//startTime = 시간이 얼마나()
//prevTime = 시간이 얼마나()

// Start = 누적시간얼마니() 50;
//  50    -  0    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;

// Start = 누적시간얼마니() 100;
//  100    -  50    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;

// Start = 누적시간얼마니() 150;
//  150    -  100    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;
#pragma endregion
//http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735

#include <Windows.h>

class Time
{
	class Timer
	{
	public:
		friend Time;

	private:
		LARGE_INTEGER frequency;
		LARGE_INTEGER prevTime;
		LARGE_INTEGER curTime;

		double dDeltaTime;
		float  deltaTime;

	public:
		float Update();
		void  Reset();

	private:
		Timer();
		~Timer();
	};

private:
	//여러분들에게 프로파일링을 보여주려고 한다.
	// 게임 루프의 시간을 재는 용도/
	static Timer mainTimer;

public:
	//간단함 함수라 헤더안에 정의
	//linline 함수에 대해서 알아보자
	static float DeltaTime()
	{
		return mainTimer.deltaTime;
	}

public:
	static void Update();
	static void Reset();
	static UINT getFPS();

private:
	Time() {};
	~Time() {};
};

