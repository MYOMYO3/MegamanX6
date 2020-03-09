#pragma once

#pragma region HTIME����
//����

//1�ʿ� RUN��
//deltatime
//��ǻ���� �����ӻ��� ������
//���ǽð����� ������ �ð�
//
//A��ǻ�ʹ� 20 (20 * deltatime()) = 1;
//B��ǻ�ʹ� 10 (10 * deltatime()) = 1;
//
//��ǻ�ʹ� cpu�� ����������
//�׻� ��Ȯ�� 1�ʸ��� ��Ȯ�� ���� ���� ��Ȯ�� �Q���� �ݺ������� �����ִ�.
//1�ʿ� 100���� ����
//ConstTime = 100;
//
//ConstTime = 1�ʿ� �󸶳� �����ִ� �Լ�()
//startTime = �ð��� �󸶳�()
//prevTime = �ð��� �󸶳�()

// Start = �����ð��󸶴�() 50;
//  50    -  0    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;

// Start = �����ð��󸶴�() 100;
//  100    -  50    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;

// Start = �����ð��󸶴�() 150;
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
	//�����е鿡�� �������ϸ��� �����ַ��� �Ѵ�.
	// ���� ������ �ð��� ��� �뵵/
	static Timer mainTimer;

public:
	//������ �Լ��� ����ȿ� ����
	//linline �Լ��� ���ؼ� �˾ƺ���
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

