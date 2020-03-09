#pragma once
#include "Scene.h"




class TitleScene : public Scene
{
private:
	int armorCheatKey;
	int selectMenu;



public :
	//void SceneUpdate()	override;
	bool Loading()		override;

	void SceneUpdate() override;
	void DebugRender()	override;


public:
	TitleScene();
	~TitleScene();
};

