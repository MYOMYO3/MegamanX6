#pragma once
#include <map>
#include <list>
#include "Collision.h"


class Scene;
class Collision;
class CollisionMgr
{
private:
	friend Scene;
	friend Collision;

public:
	static CollisionMgr& Inst()
	{
		static CollisionMgr inst;
		return inst;
	}

private:
	class LinkData
	{
	public: 
		std::wstring leftName;
		std::wstring rightName;
	};

public:
	std::map<std::wstring, std::list<Collision*>>::iterator colMapStart;
	std::map<std::wstring, std::list<Collision*>>::iterator colMapEnd;
	std::map<std::wstring, std::list<Collision*>> collisionMap;
	
	std::list<Collision*>::iterator ColStart;
	std::list<Collision*>::iterator ColEnd;

	//////////////////////////////////////////////////////////
	std::map<std::wstring, LinkData>::iterator LinkStart ;
	std::map<std::wstring, LinkData>::iterator LinkEnd ;
	std::map<std::wstring, LinkData> linkMap;

	///////////////////////////////////////////////////////////
	   
	std::map<std::wstring, std::list<Collision*>>::iterator LeftGroup;
	std::map<std::wstring, std::list<Collision*>>::iterator RightGroup;

	std::list<Collision*> ::iterator LeftStart;
	std::list<Collision*> ::iterator LeftEnd;

	std::list<Collision*> ::iterator RightStart;
	std::list<Collision*> ::iterator RightEnd;


public:
	void AllColClear();

private:
	void GroupCol(const wchar_t* _Left, const wchar_t* _Right);
	void GroupCol(const wchar_t* _This);

private:
	void PushCol(Collision* _Col);
	void Coll();

public:
	bool IsLink	(const wchar_t* _Left, const wchar_t* _Right);
	void Link	(const wchar_t* _Left, const wchar_t* _Right);

	void Release();
	void DebugRender();

public:
	CollisionMgr();
	~CollisionMgr();
};

