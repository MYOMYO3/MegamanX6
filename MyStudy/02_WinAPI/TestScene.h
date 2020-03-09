#pragma once
#include "Scene.h"




class Sprite;
class TransRender;
class TestScene : public Scene
{
private:
	int overSaveCheck;

private:
	int monsterType;
	//TransRender* render;
	Sprite* monsterSprite;	//몬스터 종류 출력용 이미지

	const wchar_t monsterImgName[20][256] =
	{
		L"Bat.bmp",
		L"Worm.bmp",
		L"L_Mettool.bmp",	
		L"D1000.bmp",
		L"LSubBoss.bmp",
		L"LBoss.bmp",
	};

public:
	bool Loading() override;
	void DebugRender() override;
	void SceneUpdate() override;

public:
	TestScene();
	~TestScene();
};

