#pragma once
#include "Image.h"
#include "Sprite.h"

// 맵과 일단 하나도 사용법은 하나도 다르지 않다.
// 내부가 다르다.
// 일단 트리구조가 아니다.
// 배열로 되어있다.
// 그런데 어떻게 맵이에요????
// 차이점 1 해쉬사용
// 차이점 2 이터레이터로 돌렸을때 정렬이 안된다.
// 맵이 아니다.
// 해쉬를 사용하는 자료구조 입니다.
// 탐색을 맵보다도 더 빠르게 하기 위해서 만들어 졌다.
// 속력을 체크하는데 빅O(오)표기법이라는 것이 있는데.
// 해쉬라고 하는 방식을 사용하는데.
// 해쉬함수 
// template<typename T>
// __int64 Hash(T& _KeyValue);
// 해쉬의 단점 
// "Player.bmp" 로 바꿔버린다. 1252
// "Monster.bmp" 1252 나왔다. 
// 배열을 한번에 1252만들어 놓는다.
// 속력이 1이다.
// 최악의 경우에도 n회만 걸리고
// 다른경우에는 항상 n보다 더 빠르다.
// 참고로 맵은 Log(n)
// 이미지는 절대로 같은 이름의 이미지를 사용할수 없다.
#include <unordered_map>

class Image;
class Asset
{
	class Destructor
	{
	public:
		~Destructor()
		{
			Asset::End();
		}
	};
	static Destructor DES;
	friend Destructor;

private:
	static void End();

#pragma region IMAGE
private:
	static std::unordered_map<std::wstring, Image*> ImageMap;

public:
	static Image* FIndBitImage(const wchar_t* _Name);
	static Image* LoadBitImage(const wchar_t* _Path);
	static Image* LoadBitImage(const wchar_t* _Name, const wchar_t* _Path);

#pragma endregion
///////////////////////////////////////////////////////////////////////////
#pragma region SPRITE
private:
	static std::unordered_map<std::wstring, Sprite*> spriteMap;

public:
	static Sprite* FIndSprite(const wchar_t* _Name);
	static Sprite* CreateSprite(const wchar_t* _ImageName, int _X, int _Y, bool _Reverse = false);
	static Sprite* CreateSprite(const wchar_t* _ImageName, const wchar_t* _SpriteName, int _X, int _Y, bool _Reverse = false);
#pragma endregion


private:
	Asset() {};
	~Asset() {};
};

