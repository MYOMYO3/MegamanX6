#include "stdafx.h"
#include "Map.h"
#include <window.h>
#include <JTIME.h>
#include "GAMECORE.h"
#include "Bullet.h"
#include <JTIME.h>
#include <Input.h>
//#include "Render.h"
#include <Debug.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"


Map* Map::m_inst = nullptr;


Map::Map()
{
}


Map::~Map()
{
}

bool Map::Init()
{


	render = CreateRender<TransRender>(-100);
	render->SubPivotMode(PIVOT::LT);


	pixelRender = CreateRender<TransRender>(-120);
	pixelRender->SubPivotMode(PIVOT::LT);

	debugRender = CreateRender<TransRender>(-80);
	debugRender->SubPivotMode(PIVOT::LT);

	render->Sprite(L"Map.bmp", 0);
	pixelRender->Sprite(L"PixelMap.bmp", 0);
	debugRender->Sprite(L"PixelMap.bmp", 0);
	
	return true;
}

void Map::Update()
{

}

void Map::DebugRender()
{
	if (Debug::Inst().GetActive() == true)
	{
		debugRender->On();
	}
	else
	{
		
		debugRender->Off();
	}
}


