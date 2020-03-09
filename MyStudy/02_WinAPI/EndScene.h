#pragma once
#include "Scene.h"
class EndScene : public Scene
{
private:
	bool Loading() override;

public:
	void DebugRender() override;

	

public:
	EndScene();
	~EndScene();
};

