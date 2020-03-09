#pragma once
#include <string>
#include <vector>
#include <map>
#include <assert.h>

//bool m_Up;
//bool m_UpAway; // �̳༮�� true
//bool m_Down;
//bool m_Press;

//���ȴ� �ȴ��ȴ�.
//���������� ġ��

//������ ����
// bool ���� �Ѽ��� ���ȴ�. 1�����ӵ��� true�� �Ǵ� ����//down
// bool ��� ������ �ִ�. ���������� ������ �ִ�		//press

//�ڽ��� �ʿ��� �͸� �����
//bool �ȴ����ִ�. -> ���������� ������ �ִ�. // upAway
//bool ������ -> 1�����Ӹ� ����				  // up

//bool�� ���ϵȴ�.
// ����Ű�� �����ϰ� 'A' + 'B'

// if(ture == HINPU::GetUpAway(L"Fire"))
// if(ture == HINPU::GetPress(L"Fire"))
// if(ture == HINPU::GetUp(L"Fire"))
// if(ture == HINPU::GetDown(L"Fire"))
// �Ѿ� ��� �ڵ� ���



class Input
{
#pragma region DesInerClass
private:
	class Destructor
	{
	public:
		~Destructor()
		{
			Input::InputEnd();
		}
	};
	static Destructor destoructor;
	friend Destructor;
#pragma endregion
private:
	class Key
	{
	private: 
		friend Input;

	public:
		std::vector<int> keyArray;

		bool up;		
		bool down;
		bool press;
		bool notPress; //notPressed // upAway
		

	public:
		bool IsKeyCheck(); // Űüũ�ϴ� ����
		void Update();	   // Űüũ�ϴ±���

	private:
		Key();
		~Key();
	};

private:
	static std::map<std::wstring, Key*> allKeyMap;
	static std::map<std::wstring, Key*>::iterator keyStart;
	static std::map<std::wstring, Key*>::iterator keyEnd;

	static void InputEnd();

private:
	static Key* FindKey(const wchar_t* _Name);

public:
	static void Update();

public:
	static Key* newKey;

	template<typename ...Rest>
	static void CreateKey(const wchar_t* _Name, Rest ..._Arg)
	{
		newKey = FindKey(_Name);

		if (nullptr != newKey)
		{
			assert(false);
		}

		newKey = new Key();

		newKey->keyArray.reserve(sizeof...(_Arg));
		PushKey(_Arg...);

		allKeyMap.insert(std::map<std::wstring, Key*>::value_type(_Name, newKey));
	}

	template<typename ...Rest>
	static void PushKey(int _Key, Rest ..._Arg)
	{
		newKey->keyArray.push_back(_Key);
		PushKey(_Arg...);
	}


	static void PushKey()
	{
		//
	}

public:
	static bool Up(const wchar_t* _Name);
	static bool Down(const wchar_t* _Name);
	static bool Press(const wchar_t* _Name);
	static bool NotPress(const wchar_t* _Name);

public:
	Input();
	~Input();
};

