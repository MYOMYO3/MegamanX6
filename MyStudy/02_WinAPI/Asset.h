#pragma once
#include "Image.h"
#include "Sprite.h"

// �ʰ� �ϴ� �ϳ��� ������ �ϳ��� �ٸ��� �ʴ�.
// ���ΰ� �ٸ���.
// �ϴ� Ʈ�������� �ƴϴ�.
// �迭�� �Ǿ��ִ�.
// �׷��� ��� ���̿���????
// ������ 1 �ؽ����
// ������ 2 ���ͷ����ͷ� �������� ������ �ȵȴ�.
// ���� �ƴϴ�.
// �ؽ��� ����ϴ� �ڷᱸ�� �Դϴ�.
// Ž���� �ʺ��ٵ� �� ������ �ϱ� ���ؼ� ����� ����.
// �ӷ��� üũ�ϴµ� ��O(��)ǥ����̶�� ���� �ִµ�.
// �ؽ���� �ϴ� ����� ����ϴµ�.
// �ؽ��Լ� 
// template<typename T>
// __int64 Hash(T& _KeyValue);
// �ؽ��� ���� 
// "Player.bmp" �� �ٲ������. 1252
// "Monster.bmp" 1252 ���Դ�. 
// �迭�� �ѹ��� 1252����� ���´�.
// �ӷ��� 1�̴�.
// �־��� ��쿡�� nȸ�� �ɸ���
// �ٸ���쿡�� �׻� n���� �� ������.
// ����� ���� Log(n)
// �̹����� ����� ���� �̸��� �̹����� ����Ҽ� ����.
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

