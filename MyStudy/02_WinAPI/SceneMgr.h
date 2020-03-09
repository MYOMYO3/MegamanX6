#pragma once
#include <map>
#include <assert.h>

//���� �Ѱ��� �ν��Ͻ��� �������ϴ� �������� = �̱�������
//���� : �˰��� ��������
//������ ������ Ŀ�������� ���������� �������� ���������� ��ƴ�


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
	//static HSceneMgr* PSingleObj; ȣ���Լ� ������ ���� �ּҸ� �Ҿ���� �ٱ����� ���־��Ѵ�.
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

	// ���� � ���� �ε����ΰ��� �˷��ִ� ����
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

