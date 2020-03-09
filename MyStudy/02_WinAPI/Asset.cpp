#include "stdafx.h"
#include "Asset.h"
#include <Path.h>
#include <assert.h>

std::unordered_map<std::wstring, Image*> Asset::ImageMap;
std::unordered_map<std::wstring, Sprite*> Asset::spriteMap;

Asset::Destructor Asset::DES;//소멸자클래스는 항상 제일밑에 해제는 조립의 역순


void Asset::End()
{
	//IMAGE
	std::unordered_map<std::wstring, Image*>::iterator startIter = ImageMap.begin();
	std::unordered_map<std::wstring, Image*>::iterator endIter  = ImageMap.end();

	for (; startIter != endIter; ++startIter)
	{
		if (nullptr == startIter->second)
		{
			continue;
		}

		delete startIter->second;
		startIter->second = nullptr;
	}

	//SPRITE
	std::unordered_map<std::wstring, Sprite*>::iterator startSIter = spriteMap.begin();
	std::unordered_map<std::wstring, Sprite*>::iterator endSIter = spriteMap.end();

	for (; startSIter != endSIter; ++startSIter)
	{
		if (nullptr == startSIter->second)
		{
			continue;
		}

		delete startSIter->second;
		startSIter->second = nullptr;
	}

}
#pragma region IMAGE

Image* Asset::FIndBitImage(const wchar_t* _Name)
{
	std::unordered_map<std::wstring, Image*>::iterator findIter = ImageMap.find(_Name);

	if (findIter == ImageMap.end())
	{
		//assert(false);
		return nullptr;
	}

	return findIter->second;
}

Image* Asset::LoadBitImage(const wchar_t* _Path)
{
	std::wstring key = Path::ExtractFileName(_Path);

	return LoadBitImage(key.c_str(), _Path);
}

Image* Asset::LoadBitImage(const wchar_t* _Name, const wchar_t* _Path)
{
	Image* newLoadImage = FIndBitImage(_Name);

	if (nullptr != newLoadImage)
	{
		assert(false);
		return nullptr;
	}

	newLoadImage = new Image();

	if (false == newLoadImage->Load(_Path))
	{
		assert(false);
		delete newLoadImage;

		return nullptr;
	}

	ImageMap.insert(std::unordered_map<std::wstring, Image*>::value_type(_Name, newLoadImage));

	return newLoadImage;
}
#pragma endregion

#pragma region SPRITE

Sprite* Asset::FIndSprite(const wchar_t* _Name)
{
	std::unordered_map<std::wstring, Sprite*>::iterator findSpriteIter = spriteMap.find(_Name);

	if (findSpriteIter == spriteMap.end())
	{
		return nullptr;
	}

	return findSpriteIter->second;
}

Sprite* Asset::CreateSprite(const wchar_t* _ImageName, int _X, int _Y, bool _Reverse)
{
	return CreateSprite(_ImageName, _ImageName, _X, _Y, _Reverse);
}

Sprite* Asset::CreateSprite(const wchar_t* _ImageName, const wchar_t* _SpriteName, int _X, int _Y, bool _Reverse)
{
	Image* findImg = FIndBitImage(_ImageName);

	if (nullptr == findImg)
	{
		assert(false);
	}

	Sprite* findSprite = FIndSprite(_SpriteName);

	if (nullptr != findSprite)
	{
		assert(false);
	}

	findSprite = new Sprite(findImg);

	findSprite->Cut(_X, _Y, _Reverse);

	spriteMap.insert(std::unordered_map<std::wstring, Sprite*>::value_type(_SpriteName, findSprite));
	return findSprite;


}

#pragma endregion


