#include "stdafx.h"
#include "Actor.h"
#include "GAMECORE.h"

std::list<Actor*>::iterator		Actor::Loop;
std::list<Actor*>::iterator		Actor::End;
std::list<Actor*>				Actor::allActorList = std::list<Actor*>();
std::map <std::wstring, Actor*> Actor::findActor;

Actor::Destructor Actor::Destroyer;


void Actor::ReleaseActor()
{
	Loop = allActorList.begin();
	End = allActorList.end();

	for (; Loop != End;)
	{
		if (false == (*Loop)->IsDeath())
		{
			++Loop;
			continue;
		}

		delete (*Loop);
		Loop = allActorList.erase(Loop);
	}
}

void Actor::PassOverActor(Scene* _Scene)
{
	Loop = allActorList.begin();
	End = allActorList .end();

	for (; Loop != End; ++Loop)
	{
		if (true == (*Loop)->CheckOverScene(_Scene))
		{
			(*Loop)->AllRenderRePush();
			(*Loop)->AllColRePush();

			_Scene->PushActor((*Loop));
		}
	}
}

void Actor::ActorEnd()
{
	Loop = allActorList.begin();
	End  = allActorList.end();

	for (; Loop != End; ++Loop)
	{
		delete (*Loop);
	}
}

Actor::Actor()
{
}


Actor::~Actor()
{
	std::list<JRender*>::iterator RenderLoop = renderList.begin();
	std::list<JRender*>::iterator RenderEnd = renderList.end();


	for (; RenderLoop != RenderEnd; ++RenderLoop)
	{
		if (nullptr != (*RenderLoop))
		{
			delete (*RenderLoop);
			(*RenderLoop) = nullptr;
		}
	}

	std::list<Collision*>::iterator ColLoop = colList.begin();
	std::list<Collision*>::iterator ColEnd = colList.end();


	for (; ColLoop != ColEnd; ++ColLoop)
	{
		if (nullptr != (*ColLoop))
		{
			delete (*ColLoop);
			(*ColLoop) = nullptr;
		}
	}


}

bool Actor::Init()
{


	return true;
}


//void Actor::Collision()
//{
//
//}

void Actor::Update()
{

}

//void Actor::Render()
//{
//	//Ellipse(GAMECORE::MainWindow().GetHDC(), )
//}

void Actor::AllRenderRePush()
{
	renderStart = renderList.begin();
	renderEnd = renderList.end();

	for (; renderStart != renderEnd; ++renderStart)
	{
		(*renderStart)->PushRenderMgr();
	}
}

void Actor::AllColRePush()
{
	ColStart = colList.begin();
	ColEnd = colList.end();

	for (; ColStart != ColEnd; ++ColStart)
	{
		(*ColStart)->PushColMgr();
	}
}

void Actor::DebugRender()
{

}

