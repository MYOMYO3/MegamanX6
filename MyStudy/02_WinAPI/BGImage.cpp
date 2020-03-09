#include "stdafx.h"
#include "BGImage.h"
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
#include "Player.h"

BGImage* BGImage::m_inst = nullptr;


bool BGImage::Init()
{
	render = CreateRender<TransRender>(-110);

	render->SubPivotMode(PIVOT::LT);

	render->Sprite(L"BG_image.bmp", 0);
	//SetPos({ 3417.0f, 922.0f });
	//SetPos({ 3400.0f, 1000.0f });
	//SetPos({ 0.0f, 0.0f});

	//1280 * 0.5f, 800 *0.5f 640,200
	//SetPos({ 3417.0f, 922.0f });
	//pos.x = Player::Inst()->GetPos().x ;
	//pos.y = Player::Inst()->GetPos().y ;
	return true;
}

void BGImage::Update()
{
	if (isBossRoom == true)
	{
		pos.x += 3.0f * Time::DeltaTime();
	}


	//pos.x = Player::Inst()->GetPos().x * 0.94f;

	//if (Player::Inst()->GetGroundCheck() == false)
	//{

	//}
	//pos.y = Player::Inst()->GetPos().y * 0.8f;

	
}


BGImage::BGImage()
{
	isBossRoom = false;
}


BGImage::~BGImage()
{
}
