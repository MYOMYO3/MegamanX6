#pragma once
#include "ObjBase.h"
#include <list>
#include <GEOMETRY.h>
//�ð� 
//��Ʈ��
//������Ʈ
//����
//�浹

//��ӱ����� ���� : �ʿ��������� ����� �ڽ��� ���Եȴ�.
//					�̸� �غ��Ҽ��ִ� ����� ������ ����ϸ�ȴ�.

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
	// �ܺο��� ��� �� ���ִ� �������̽��� �̰��ϳ�.
	// ������ �̰� �����Ҽ� ������ �ȵȴ�.
	void Progress();

private:
	virtual void SceneUpdate();	//���� ���� �̳༮�� ������Ʈ �ȴ�.

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

