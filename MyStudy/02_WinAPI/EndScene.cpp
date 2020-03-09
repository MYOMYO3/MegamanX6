#include "stdafx.h"
#include "EndScene.h"
#include "GAMECORE.h"
//#include "SceneMgr.h"
#include "EndingVideo.h"
#include "Asset.h"
#include "Actor.h"


EndingVideo* video = nullptr;

EndScene::EndScene()
{
}


EndScene::~EndScene()
{
}

bool EndScene::Loading()
{
	video = Actor::CreateActor<EndingVideo>();

	return true;
}

void EndScene::DebugRender()
{

}
