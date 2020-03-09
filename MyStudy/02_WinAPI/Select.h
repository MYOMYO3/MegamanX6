#pragma once
#include "Scene.h"

class TransRender;
class AniRender;
class Select : public Scene
{
private:
	float changeSceneTime;
	bool isChangeScene;

public:
	bool Loading() override;

	void SceneUpdate() override;
	void DebugRender() override;

public:
	Select();
	~Select();
};

