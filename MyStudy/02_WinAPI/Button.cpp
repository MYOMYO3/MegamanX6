#include "stdafx.h"
#include "Button.h"
#include <window.h>
#include <JTIME.h>
#include "GAMECORE.h"
#include "Bullet.h"
#include <JTIME.h>
#include <Input.h>
//#include "Render.h"
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"



bool Button::Init()
{
	render = CreateRender<AniRender>(100);
	render->SubPivotMode(PIVOT::CENTER);

	render->CreateAnimation(L"Start", L"StartBtn.bmp", 0,0, false, 0.1f);
	render->CreateAnimation(L"DoingStart", L"StartBtn.bmp", 0, 1, true, 0.1f);
	
	render->CreateAnimation(L"Option", L"OptionBtn.bmp", 0, 0, false, 0.1f);
	render->CreateAnimation(L"DoingOption", L"OptionBtn.bmp", 0, 1, true, 0.1f);

	render->CreateAnimation(L"Exit", L"ExitBtn.bmp", 0, 0, false, 0.1f);
	render->CreateAnimation(L"DoingExit", L"ExitBtn.bmp", 0, 1, true, 0.1f);

	render->PlayAnimation(L"Start");

	render->DebugOff();



	return true;
}

void Button::Update()
{


}

void Button::StartButtonOn()
{
	render->PlayAnimation(L"DoingStart");
}

void Button::StartButtonOff()
{
	render->PlayAnimation(L"Start");
}

void Button::OptionButtonOn()
{
	render->PlayAnimation(L"DoingOption");
}

void Button::OptionButtonOff()
{
	render->PlayAnimation(L"Option");
}

void Button::ExitButtonOn()
{
	render->PlayAnimation(L"DoingExit");
}

void Button::ExitButtonOff()
{
	render->PlayAnimation(L"Exit");
}



void Button::SetButtonName(const wchar_t* _ButtonName)
{
	render->PlayAnimation(_ButtonName);
}



Button::Button() : selectMenu(0), isButton(false)
{
}


Button::~Button()
{
}
