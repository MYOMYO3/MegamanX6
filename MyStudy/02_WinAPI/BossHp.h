#pragma once
#include "UI.h"

class AniRender;
class BossHp :
	public UI
{
public:
	static BossHp* m_inst;

private:
	AniRender* render;

	int bossHP;

public:
	bool Init()		override;
	void Update()	override;

public:
	BossHp();
	~BossHp();
};

