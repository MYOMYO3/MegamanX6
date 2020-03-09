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
	static Image* g_BackBuffer; //더블버퍼용 이미지

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

	// 어느 특정 분야의 객체들을 모아놓는다는것은
	// 보통 항상 편하다.
	// 그래도 삭제의 권한은 한놈만 가지게 한다.
	// 이녀석이 지우게 할수도 있는데.
	// 왠만하면 생성하는 놈이 삭제하는 것이
	// 코드를 짜는것이 편할 것이다.
	// 저는 왠만하면 
	// 극단적인 숫자로 테스트 해보는것을 좋아합니다.
	// BackGround이런애들은 숫자가 -10000
	// UI이런애들은 숫자가 10000
	// 템플릿을 통해서 만들어진 클래스는
	// 무슨 특별한 자료형인가?
	// std::vector<hrender>
	// std::list<std::list<T>>
	// 그냥 닥치는대로 다하고 싶어하고
	// 안되면 나중에 
	// 선생님이 해줄꺼니까 나중에 해야지.
	// 필요하다.
	// 그 순서대로 정렬을 해야 한다.

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

