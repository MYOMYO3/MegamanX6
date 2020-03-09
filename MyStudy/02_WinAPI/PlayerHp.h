#pragma once
#include "UI.h"

class AniRender;
class PlayerHp :
	public UI
{
private:
	AniRender* render;
	
	int playerHP;

public:
	bool Init()		override;
	void Update()	override;
public:
	PlayerHp();
	~PlayerHp();
};

