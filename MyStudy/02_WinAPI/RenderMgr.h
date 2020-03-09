#pragma once
#include "Render.h"
#include "Image.h"
#include <map>
#include <set>
#include <list>


class GameCore;
class RenderMgr
{
	friend GameCore;

private:
	static Image* g_BackBuffer; //������ۿ� �̹���

public:
	static HDC BACKDC()
	{
		return g_BackBuffer->GetDC();
	}

public:
	static RenderMgr& Inst()
	{
		static RenderMgr Inst;
		return Inst;
	}

	// ��� Ư�� �о��� ��ü���� ��Ƴ��´ٴ°���
	// ���� �׻� ���ϴ�.
	// �׷��� ������ ������ �ѳ� ������ �Ѵ�.
	// �̳༮�� ����� �Ҽ��� �ִµ�.
	// �ظ��ϸ� �����ϴ� ���� �����ϴ� ����
	// �ڵ带 ¥�°��� ���� ���̴�.
	// ���� �ظ��ϸ� 
	// �ش����� ���ڷ� �׽�Ʈ �غ��°��� �����մϴ�.
	// BackGround�̷��ֵ��� ���ڰ� -10000
	// UI�̷��ֵ��� ���ڰ� 10000
	// ���ø��� ���ؼ� ������� Ŭ������
	// ���� Ư���� �ڷ����ΰ�?
	// std::vector<hrender>
	// std::list<std::list<T>>
	// �׳� ��ġ�´�� ���ϰ� �;��ϰ�
	// �ȵǸ� ���߿� 
	// �������� ���ٲ��ϱ� ���߿� �ؾ���.
	// �ʿ��ϴ�.
	// �� ������� ������ �ؾ� �Ѵ�.

private:
	std::map<int, std::list<JRender*>> renderMap;

	std::map<int, std::list<JRender*>>::iterator renderLoop;
	std::map<int, std::list<JRender*>>::iterator renderEnd;

	std::list<JRender*>::iterator rendererStart;
	std::list<JRender*>::iterator rendererEnd;

	std::set<int> ySort;

private:
	void Init();
	

private:
	friend class Scene;

private:
	void AllRenderClear();

public:
	void PushRender(JRender* _Render);

public:
	void Render();
	void Release();

public:
	RenderMgr();
	~RenderMgr();
};

