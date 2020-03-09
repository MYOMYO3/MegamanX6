#pragma once
#include "Actor.h"
#include <string.h>

class JRender;
class TransRender;
class AniRender;
class ImageRender;
class Button : public Actor
{
private:
	AniRender* render;

	int selectMenu;

	bool isButton;
	
public:
	void SetMenu(const int _Data)
	{
		selectMenu = _Data;
	}

public:
	void StartButtonOn();
	void StartButtonOff();

	void OptionButtonOn();
	void OptionButtonOff();

	void ExitButtonOn();
	void ExitButtonOff();

public:
	void SetButtonName(const wchar_t* _ButtonName);
	

public:
	bool Init()		override;
	void Update()	override; 

public:
	Button();
	~Button();
};

