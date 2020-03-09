#pragma once
#include "Actor.h"

class JRender;
class TransRender;
class AniRender;
class BGImage :	public Actor
{
private:
	TransRender* render;

	

	BGImage* m_inst2;




public:	
	static BGImage* m_inst;

	static BGImage* Inst()
	{		
		return m_inst;
	}

	BGImage* GetBGImage()
	{
		return m_inst2;
	}
	bool isBossRoom;

public:
	bool Init() override;
	void Update() override;

public:
	BGImage();
	~BGImage();
};

