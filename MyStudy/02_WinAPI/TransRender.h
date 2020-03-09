#pragma once
#include <..\_Base\ColorRGB.h>

#include "Render.h"

class Sprite;
class TransRender : public JRender
{
private:
	Sprite* sprite;
	ColorRGB transRender;
	int index;

public:
	Sprite* GetSprite()
	{
		return sprite;
	}

public:
	void Sprite(const wchar_t* _Name, int _Index);
	void Render() override;
	void SpriteSizeOn();

public:
	TransRender();
	~TransRender();
};

