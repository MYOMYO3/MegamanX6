#pragma once
#include "ObjBase.h"
#include <list>
#include <GEOMETRY.h>
//시간 
//컨트롤
//오브젝트
//렌더
//충돌

//상속구조의 단점 : 필요하지않은 멤버를 자식이 갖게된다.
//					이를 극복할수있는 방법은 위임을 사용하면된다.

class Actor;
class SceneMgr;
class RenderMgr;
class Scene : public ObjBase
{
public:
	friend RenderMgr;
	friend SceneMgr;
	friend Actor;

private:
	bool loading;

public:
	bool IsLoading()
	{
		return loading;  
	}

private:
	// 외부에서 사용 할 수있는 인터페이스는 이거하나.
	// 남들이 이걸 실행할수 있으면 안된다.
	void Progress();

private:
	virtual void SceneUpdate();	//가장 먼저 이녀석이 업데이트 된다.

public:
	void Update();
	void Render();
	void Collision();
	void Release();

public:
	bool MgrLoading(); //

private:
	virtual bool Loading();

#pragma region Actor

private:
	std::list<Actor*>::iterator Loop;
	std::list<Actor*>::iterator End;
	std::list<Actor*> actorList;

	void PushActor(Actor* _Actor);
#pragma endregion
public:
	Pos cameraPos;


private:
	void ChangeScene();

	virtual void DebugRender();
	void ActorDebugRender();


protected:
	Scene();
	virtual ~Scene() = 0;
};

