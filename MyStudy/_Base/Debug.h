#pragma once
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>


class Debug
{
private:
	bool active;
	
public:
	static Debug& Inst()
	{
		static Debug debug;
		return debug;
	}

public:
	inline void On()
	{
		active = true;
	}
	
	inline void Off()
	{
		active = false;
	}

	bool GetActive()
	{
		return active;
	}

public:
	static void LeakCheck();

	
public:
	static void Update();
	static void Render();
	static void PrintText(HDC _DC, int _X, int _Y, const std::wstring _Str);


private:
	Debug() { active = true; }
	~Debug() {}
};