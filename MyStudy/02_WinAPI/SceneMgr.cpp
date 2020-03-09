#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"

SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
	std::map<std::wstring, Scene*>::iterator Loop = scene_Map.begin();
	std::map<std::wstring, Scene*>::iterator End  = scene_Map.end();

	for (; Loop != End; ++Loop)
	{
		if (nullptr != Loop->second)
		{
			delete Loop->second;
			Loop->second = nullptr;
		}
	}
}


void SceneMgr::Progress()
{
	// scene�� ������ �ƿ� ������ü�� ����ȵǰ� ���� ���� ���̴�.

	if (nullptr != nextScene) 
	{
		curScene = nextScene;				// �ؽ�Ʈ���� ���������
		if (false == curScene->IsLoading()) 
		{
			curScene->MgrLoading();
		}
		
		curScene->ChangeScene();
		
		nextScene = nullptr;
	}


	if (nullptr != curScene)
	{
		curScene->Progress();
	}
	else
	{
		assert(false);
	}


}


Scene* SceneMgr::FindScene(const wchar_t* _Name)
{
	std::map<std::wstring, Scene*>::iterator FindIter = scene_Map.find(_Name);

	if (scene_Map.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

bool SceneMgr::ChangeScene(const wchar_t* _Name)
{
	nextScene = FindScene(_Name);
	if (nullptr == nextScene)
	{
		assert(false);
	}

	return true;
}