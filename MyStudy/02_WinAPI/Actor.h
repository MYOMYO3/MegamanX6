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
	//��ü�� ������ �ְ� �ƴϴ�.
	//���� �Ҵ��س��� �༮�� �ظ��ϸ� �� ����� ���� �ȴ�.
	//�Ҹ��� Ŭ����
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



	//1�����
	static std::list<Actor*>::iterator Loop;
	static std::list<Actor*>::iterator End;
	//�� ���ο��� ������ ������� �Ѵ�.
	static std::list<Actor*> allActorList;

	static std::map<std::wstring, Actor*> findActor;
	//ã�� �ÿ����� �ִ�.
	//�Ѱ��� ������ �ִ�.
	//���� ������ �ʰ� �ٸ� ������Ʈ�� �� ���������ϴ�.

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

		// MgrLoading�� ���Ǵ� ������ m_CreateScene nullptr�� �ƴϹǷ� ��������� ��������
		// ũ������Ʈ ������ �־��ָ� �ȴ�.
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
	std::set<std::wstring> sceneSet; // �ּ��ޱ� ��������ϴ��� �Ͼ�������ʱ�
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

		//����ڵ�
		//��û���� �߿��ϴ�
		//����ڵ忡 �Ǽ��� �ְ� �Ǹ� ���� ġ������ ������ �߻���Ű�� ������
		//�� ���ü� �ִ� ��츦 �� �����ؼ� ��� �����س��� �Ѵ�.
		//�����
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
	// ���漱�� ���⿡ �ص� �ȴ�.
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


	// �÷��̾ ����ϴ� �Լ��ε� �� ���Ͱ� ������ �ֳ���?????
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
	//������ �߿��ϴ�
	//���� ���������� �ݸ����̴�
	//virtual void Collision();
	virtual void Update();
	//virtual void Render(); RenderŬ�������� ���������õȰ� �����ߴ�.
	


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
	//�ڽĵ鿡�� �����δ��� �ٿ��ְ�
	//�׷��鼭 �� �ڽ��� �����ɼ� ���� ����� ���ؼ�

	virtual ~Actor() /*= 0*/;
};

