#pragma once
#include <map>
#include <assert.h>

//오직 한개의 인스턴스만 갖도록하는 생성패턴 = 싱글턴패턴
//단점 : 알고보니 전역변수
//게임의 구조가 커짐에따라서 전역변수가 많아지니 유지보수가 어렵다


class Scene;
class GameCore;
class SceneMgr
{
public:
	friend GameCore;
	friend Scene;
	//friend bool Scene::MgrLoading();
	
	//value type singleton
	static SceneMgr& Inst()
	{
		static SceneMgr singleObj;
		return singleObj;
	}

	//pointer type singleton
	//static HSceneMgr* PSingleObj; 호출함수 안으로 들어가면 주소를 잃어버려 바깥으로 뺴둬야한다.
	//static HSceneMgr* PInst()
	//{
	//	if (nullptr == PSingleObj)
	//	{
	//		PSingleObj = new HSceneMgr();
	//	}
	//	return PSingleObj;
	//}
	//static void Destroy() {
	//	if (nullptr != PSingleObj)
	//	{
	//		delete PSingleObj;
	//		PSingleObj = nullptr;
	//	}
	//}

	std::map<std::wstring, Scene*> scene_Map;

	Scene* nextScene;
	Scene* curScene;

	// 현재 어떤 씬이 로딩중인가를 알려주는 변수
	Scene* createScene;

private:
	void Progress();

public:
	Scene* GetCurScene()
	{
		return curScene;
	}

public:
	Scene* FindScene(const wchar_t* _Name);

	template<typename T>
	bool CreateScene(const wchar_t* _Name, bool _IsLoading = true)
	{
		Scene* pFindScene = FindScene(_Name);

		if (nullptr != pFindScene)
		{
			assert(false);
		}

		Scene* pNewScene = new T(); //template Scene
		pNewScene->Name(_Name);
		if (true == _IsLoading)
		{
			//createScene = pNewScene; 
			pNewScene->MgrLoading();
		}

		scene_Map.insert(std::map<std::wstring, Scene*>::value_type(_Name, pNewScene));
		return pFindScene;
	}
	
	bool ChangeScene(const wchar_t* _Name);

public:
	SceneMgr();
	~SceneMgr();
};

