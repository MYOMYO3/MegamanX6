#include "stdafx.h"
#include "Bullet.h"
#include <JTIME.h>
#include "GAMECORE.h"
#include "CirclCol.h"



Bullet::Bullet() //: deathTime(300.0f)
{
	//size = { 50.0f, 50.0f };
}


Bullet::~Bullet()
{
}

bool Bullet::Init()
{
	//Collision* bullet = CreateCol<CircleCol>(L"PBULLET", {30, 30});

	return true;
}


void Bullet::Update()
{
	//int a = 0;
	//deathTime -= Time::DeltaTime();

	//if (0 >= deathTime)
	//{
		//Die();
	//}

	//pos.x += 100.0f * Time::DeltaTime();

}

void Bullet::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}

void Bullet::ColStay(Collision* _This, Collision* _Other)
{
	int a = 0;
}

void Bullet::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}