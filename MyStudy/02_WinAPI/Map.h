#pragma once
#include "Actor.h"



class JRender;
class TransRender;
class AniRender;
class Map : public Actor
{
public:
	static Map* m_inst;


public:
	static Map* Inst()
	{
		
		return m_inst;
	}


private:
	TransRender* render;
	TransRender* pixelRender;
	TransRender* debugRender;


public:
	TransRender* GetRender()
	{
		return render;
	}

	TransRender* GetPixelRender()
	{
		return pixelRender;
	}

public:
	bool Init()   override;
	void Update() override;

	void DebugRender() override;


public:
	Map();
	~Map();
};

