#include "stdafx.h"
#include "Zero.h"
#include "AniRender.h"

Zero::Zero() :startAni(false)
{
}


Zero::~Zero()
{
}



bool Zero::Init()
{
	aniRender = CreateRender<AniRender>();
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"R_Start", L"Zero.bmp", 0, 13, false, 0.1f);
	aniRender->CreateAnimation(L"R_Idle", L"Zero.bmp", 14, 18, true, 0.1f);
	aniRender->CreateAnimation(L"R_Run", L"Zero.bmp", 19, 32, true, 0.05f);
	aniRender->CreateAnimation(L"R_Gotohome", L"Zero.bmp", 33, 46, false, 0.1f); //애니메이션 순서가 깨져있음 참고


	aniRender->PlayAnimation(L"R_Start");

	return true;
}

void Zero::Update()
{
	if (startAni == false)
	{
		if (aniRender->GetCurAni()->aniEnd == true)
		{
			aniRender->PlayAnimation(L"R_Idle");

			startAni = true;
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
		aniRender->PlayAnimation(L"R_Gotohome");
	}


}