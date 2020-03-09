#include "stdafx.h"
#include "DeadParticle.h"
#include "AniRender.h"
#include <JTIME.h>
#include <Well512.h>

#define m_PI 3.141592



DeadParticle::DeadParticle() : deathTime( 5.0f)
{
	Well512Random::Init();

	dPos = {Well512Random::GetFloatValue(-1.00f, 1.00f), Well512Random::GetFloatValue(-1.00f, 1.00f) };
}


DeadParticle::~DeadParticle()
{
}

bool DeadParticle::Init()
{
	

	render = CreateRender<AniRender>(120);
	render->SubPivotMode(PIVOT::CENTER);

	render->CreateAnimation(L"CircleBombAll", L"DeadEffect.bmp", 0, 11, true, 0.08f);
	//render->CreateAnimation(L"CircleBomb", L"PlayerBigBullet.bmp", 7, 10, true, 0.05f);
	
	render->PlayAnimation(L"CircleBombAll");
	render->RenderSize({60.0f  , 60.0f });

	
	return true;
}



void DeadParticle::Update()
{
	pos += (dPos)* 100.0F * Time::DeltaTime();

	deathTime -= Time::DeltaTime();

	if (deathTime < 0.0f)
	{
		Die();
	}
}
