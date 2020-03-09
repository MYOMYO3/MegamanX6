#include "stdafx.h"
#include "Axe.h"
#include "AniRender.h"


Axe::Axe()  :startAni(false), isEndAni(false)
{
	selectAni = 0;
}


Axe::~Axe()
{
}


bool Axe::Init()
{
	aniRender = CreateRender<AniRender>();
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"R_Start", L"X_Basic01.bmp", 0, 17, false, 0.1f);
	aniRender->CreateAnimation(L"R_Idle", L"X_Basic01.bmp", 18, 21, true, 0.1f);
	aniRender->CreateAnimation(L"R_Run", L"X_Basic01.bmp", 51, 62, true, 0.05f);
	aniRender->CreateAnimation(L"R_Gotohome", L"X_Basic01.bmp", 190, 199, false, 0.1f); //애니메이션 순서가 깨져있음 참고


	aniRender->PlayAnimation(L"R_Start");		

	return true;
}

void Axe::Update()
{
	if (startAni == false)
	{
		if (aniRender->GetCurAni()->aniEnd == true)
		{
			if (isEndAni == false)
			{
				aniRender->PlayAnimation(L"R_Idle");

				startAni = true;
			}

			
		}
	}

	if (selectAni == 0)
	{
		aniRender->PlayAnimation(L"R_Idle");
	}

	if (selectAni == 1)
	{
		aniRender->PlayAnimation(L"R_Run");
	}

	if (selectAni == 2)
	{
		if (isEndAni == false)
		{
			aniRender->PlayAnimation(L"R_Gotohome");
		}
		isEndAni = true;
	}



}