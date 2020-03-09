#pragma once
#include <GEOMETRY.h>
#include "ObjBase.h"
#include <set>
#include "SceneMgr.h"
#include "Scene.h"
#include "Render.h"
#include "Collision.h"



class Actor : public ObjBase
{
private:
	//객체가 감싸진 애가 아니다.
	//남이 할당해높은 녀석은 왠만하면 이 방법을 쓰면 된다.
	//소멸자 클래스
#pragma region STATIC
	class Destructor
	{
	public:
		~Destructor()
		{
			Actor::ActorEnd();
		}
	};
	static Destructor Destroyer;
	friend Destructor;



	//1번방식
	static std::list<Actor*>::iterator Loop;
	static std::list<Actor*>::iterator End;
	//이 내부에서 완전히 지워줘야 한다.
	static std::list<Actor*> allActorList;

	static std::map<std::wstring, Actor*> findActor;
	//찾기 시워질수 있다.
	//한가지 장점이 있다.
	//씬을 가리지 않고 다른 오브젝트를 다 조절가능하다.

public:
	static void ReleaseActor();
	static void PassOverActor(Scene* _Scene);

public:
	static void ActorEnd();


public:
	//typedef Actor T;
	template<typename T>
	static T* CreateActor(const wchar_t* _Name = L"", bool _IsFind = false)
	{
		T* newActor = new T();
		newActor->Name(_Name);

		allActorList.push_back(newActor);

		// MgrLoading이 사용되는 동안은 m_CreateScene nullptr이 아니므로 만들어지는 순간에는
		// 크리에이트 씬에만 넣어주면 된다.
		if (nullptr != SceneMgr::Inst().createScene)
		{
			newActor->sceneSet.insert(SceneMgr::Inst().createScene->Name());
			SceneMgr::Inst().createScene->PushActor(newActor);
		}
		else if (nullptr != SceneMgr::Inst().curScene)
		{
			newActor->sceneSet.insert(SceneMgr::Inst().curScene->Name());
			SceneMgr::Inst().curScene->PushActor(newActor);
		}

		if (true == _IsFind)
		{
			findActor.insert(std::map<std::wstring, Actor*>::value_type(_Name, newActor));
		}

		newActor->Init();

		return newActor;
	}
#pragma endregion

	
#pragma region SCENE
	friend Scene;
private:
	std::set<std::wstring> sceneSet; // 주석달기 무슨기능하는지 일어버리지않기
	bool CheckOverScene(Scene* _Scene)
	{
		if (nullptr == _Scene)
		{
			assert(false);
		}

		return CheckOverScene(_Scene->Name());
	}
	bool CheckOverScene(const std::wstring& _Name)
	{
		return CheckOverScene(_Name.c_str());
	}
	bool CheckOverScene(const wchar_t* _Name)
	{
		return sceneSet.end() != sceneSet.find(_Name);
	}

public:
	template <typename ...Rest>
	void PossibleOverScene(const wchar_t* _Name, Rest ..._Arg)
	{
		int tRestSize = sizeof...(_Arg);

		//방어코드
		//엄청나게 중요하다
		//방어코드에 실수가 있게 되면 보통 치명적인 오류를 발생시키기 떄문에
		//꼭 나올수 있는 경우를 잘 예상해서 모두 예방해놔야 한다.
		//디버깅
		if (false == CheckOverScene(_Name))
		{
			sceneSet.insert(_Name);
		}

		PossibleOverScene(_Arg...);
	}
	void PossibleOverScene()
	{
		int a = 0;
	}
#pragma endregion	
public:
	// 전방선언 여기에 해도 된다.
	// class HRenderer;
	// class HUIRenderer;
	// class HAniRenderer;
	// std::list<HRenderer*>();


	// class HCollision;
	// class HRectCol : HCollision;
	// class HCircleCol : HCollision;
	// std::list<HCollision*>();


protected:
	int hp;
	int att;

public:
	void Damaged(int _Att)
	{
		hp -= _Att;
	}

	int GetAtt()
	{
		return att;
	}

	
protected:
	Pos pos;

#pragma region DEBUG POS
	Pos rPos;
	Pos lPos;
	Pos tPos;
#pragma endregion

protected:
		enum CHECKDIR
		{
			CHECKLEFT,
			CHECKRIGHT,
			CHECKTOP,
			CHECKBOTTOM,
			CHECKUNDERGROUND,
			CHECKLT,
			CHECKRT,
			CHECKLB,
			CHECKRB,
			CHECKMAX
		};

protected:
	Pos CHECKPOS[CHECKMAX];
	Pos CHECKPOSSUB[CHECKMAX];

	Pos GetCheckPos(CHECKDIR _eDir)
	{
		return pos + CHECKPOS[_eDir];
	}

public:
	void SetPos(Pos _Pos)
	{
		pos = _Pos;

		//DebugPos
		CalDebugPos(pos);
	}

	Pos GetPos()
	{
		return pos;
	}
	Pos GetRPos()
	{
		return rPos;
	}
	Pos GetLPos()
	{
		return lPos;
	}
	Pos GetTPos()
	{
		return tPos;
	}


	// 플레이어만 사용하는 함수인데 왜 액터가 가지고 있나요?????
	void CalDebugPos(Pos _Pos)
	{
		rPos = { _Pos.x + 20.0f, _Pos.y - 20.0f };
		lPos = { _Pos.x - 20.0f, _Pos.y - 20.0f };
		tPos = { _Pos.x ,		 _Pos.y - 50.0f };
	}

	void Move(const Pos& _Pos)
	{
		pos += _Pos;
	}

private://start
	virtual bool Init();

public://loop
	//순서가 중요하다
	//보통 렌더다음이 콜리전이다
	//virtual void Collision();
	virtual void Update();
	//virtual void Render(); Render클래스에게 렌더에관련된걸 위임했다.
	


	/////////////////////////////////////Render
#pragma region RENDER

private:
	std::list<JRender*> renderList;
	std::list<JRender*>::iterator renderStart;
	std::list<JRender*>::iterator renderEnd;
	
private:
	void AllRenderRePush();

public:
	template<typename T>
	T* CreateRender(int _Order = 0)
	{
		T* newRender = new T();
		newRender->Init(_Order, this);
		renderList.push_back(newRender);

		return newRender;
	}

#pragma endregion

#pragma region COLLISION

private:	
	std::list<Collision*>::iterator ColStart;
	std::list<Collision*>::iterator ColEnd;
	std::list<Collision*> colList;

public:
	template<typename T>
	T* CreateCol(const wchar_t* _GroupName = L"Default", Size _Size = {10, 10})
	{
		T* newCol = new T();
		newCol->Init(_GroupName, this, _Size);
		colList.push_back(newCol);

		return newCol;
	}

private:
	void AllColRePush();

public:
	virtual void ColEnter(Collision* _This, Collision* _Other) { }
	virtual void ColStay (Collision* _This, Collision* _Other) { }
	virtual void ColExit (Collision* _This, Collision* _Other) { }

#pragma endregion

public:
	virtual void DebugRender();


protected:
	Actor();
	//자식들에게 구현부담은 줄여주고
	//그러면서 나 자신은 생성될수 없게 만들기 위해서

	virtual ~Actor() /*= 0*/;
};

