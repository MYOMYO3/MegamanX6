#include "stdafx.h"
#include "Scene.h"
#include "Actor.h"
#include <assert.h>
#include "RenderMgr.h"
#include "CollisionMgr.h"

Scene::Scene() : loading(false)
{
}


Scene::~Scene()
{
}

void Scene::Progress()
{
	/*this override*/
	SceneUpdate();
	Update();
	Render();
	DebugRender();
	Collision();

	Release();
	Actor::ReleaseActor();
}

void Scene::SceneUpdate()	//가장 먼저 이녀석이 업데이트 된다
{

}

bool Scene::MgrLoading()
{
	SceneMgr::Inst().createScene = this;
	bool check = /*this->*/Loading(); // Loading함수 가상함수
	SceneMgr::Inst().createScene = nullptr;

	if (false == check)
	{
		assert(false);
	}
	loading = true;

	return check;
}


bool Scene::Loading() //부모클래스의 로딩이 호출될일이 있나????
{
	return true;
}

void Scene::Update()
{
	Loop	= actorList.begin();
	End		= actorList.end();

	for (; Loop != End; ++Loop)
	{
		if (false == (*Loop)->IsActive())
		{
			continue;
		}

		(*Loop)->Update();
	}
}

void Scene::Render()
{
	RenderMgr::Inst().Render();
}

void Scene::Collision()
{
	CollisionMgr::Inst().Coll();
}

void Scene::Release()
{
	CollisionMgr::Inst().Release();
	RenderMgr::Inst().Release();

	Loop	= actorList.begin();
	End		= actorList.end();

	for (; Loop != End;)
	{
		if (false == (*Loop)->IsDeath())
		{
			++Loop;
			continue;
		}

		Loop = actorList.erase(Loop);
	}
}


void Scene::DebugRender()
{

}

void Scene::ActorDebugRender()
{
	Loop	= actorList.begin();
	End		= actorList.end();

	for (; Loop != End; ++Loop)
	{
		(*Loop)->DebugRender();
	}
}


void Scene::ChangeScene()
{
	RenderMgr::Inst().AllRenderClear();
	CollisionMgr::Inst().AllColClear();

	actorList.clear();

	Actor::PassOverActor(this);
}

void Scene::PushActor(Actor* _Actor)
{
	if (nullptr == _Actor)
	{
		assert(false);
	}

	actorList.push_back(_Actor);
}






