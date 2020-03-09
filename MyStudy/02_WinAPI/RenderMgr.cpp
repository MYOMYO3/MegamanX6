#include "stdafx.h"
#include "RenderMgr.h"
#include <Windows.h>
#include "GAMECORE.h"
#include "Image.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CollisionMgr.h"


Image* RenderMgr::g_BackBuffer = nullptr;

RenderMgr::RenderMgr()
{

}


RenderMgr::~RenderMgr()
{
	delete g_BackBuffer;
}

void RenderMgr::Init()
{
	g_BackBuffer = new Image();
	g_BackBuffer->Create(GameCore::MainWindow().GetWindowSize());
}


void RenderMgr::AllRenderClear()
{
	renderLoop = renderMap.begin();
	renderEnd  = renderMap.end();

	for (; renderLoop != renderEnd; ++renderLoop)
	{
		renderLoop->second.clear();
	}
}


void RenderMgr::PushRender(JRender* _Render)
{
	std::map<int, std::list<JRender*>>::iterator renderGroupIter = renderMap.find(_Render->GetOrder());

	if (renderMap.end() == renderGroupIter)
	{
		renderMap.insert(std::map<int, std::list<JRender*>>::value_type(_Render->GetOrder(), std::list<JRender*>()));
		renderGroupIter = renderMap.find(_Render->GetOrder());
	}

	renderGroupIter->second.push_back(_Render);
}


void RenderMgr::Render()
{
	Rectangle(RenderMgr::BACKDC(), 0, 0, 1280, 800);

	//first = int, second = 렌더의 리스트
	renderLoop = renderMap.begin();
	renderEnd  = renderMap.end();

	for (; renderLoop != renderEnd; ++renderLoop)
	{
		//렌더의 리스트
		rendererStart = renderLoop->second.begin();
		rendererEnd  = renderLoop->second.end();

		for (; rendererStart != rendererEnd; ++rendererStart)
		{
			if (false == (*rendererStart)->IsActive())
			{
				continue;
			}
			(*rendererStart)->Render();
		}
	}


	
	if (nullptr != SceneMgr::Inst().GetCurScene())
	{		
		CollisionMgr::Inst().DebugRender();
		SceneMgr::Inst().GetCurScene()->ActorDebugRender();
		SceneMgr::Inst().GetCurScene()->DebugRender();
	}

	BitBlt(GameCore::MainWindow().GetHDC(),
		0, 0, 
		GameCore::MainWindow().GetWindowSize().IX(),
		GameCore::MainWindow().GetWindowSize().IY(), 
		RenderMgr::BACKDC(), 
		0, 0, 
		SRCCOPY);
}

void RenderMgr::Release()
{
	
	renderLoop = renderMap.begin();
	renderEnd = renderMap.end();

	for (; renderLoop != renderEnd; ++renderLoop)
	{
		rendererStart = renderLoop->second.begin();
		rendererEnd = renderLoop->second.end();

		for (; rendererStart != rendererEnd; )
		{
			if (false == (*rendererStart)->IsDeath())
			{
				++rendererStart;
				continue;
			}
			rendererStart = renderLoop->second.erase(rendererStart);
		}
	}
}