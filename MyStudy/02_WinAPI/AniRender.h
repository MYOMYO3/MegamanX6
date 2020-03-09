#pragma once
#include "Render.h"
#include <map>
#include "Sprite.h"



class AniRender :public JRender
{
	//애니메이션이란 필요한게? 스프라이트
	//같은 스프라이트안에서만 가능하게 제한을건다.

private:

	class Animation
	{
	public:
		Sprite*		sprite;
		bool		over;
		bool		loop;
		int			startIndex;
		int			endIndex;
		int			curIndex;
		float		aniTime;
		float		curTime;
		bool		aniEnd;

		//bool		isDebug;
	
		

	public:
		void ResetAnimation(int _PrevIndex = -1)
		{
			if (_PrevIndex == -1)
			{
				curIndex = startIndex;				
			}

			curTime = aniTime;
			aniEnd	= false;
		}


		
	public:
		Animation() : sprite(nullptr), over(false), loop(false), curIndex(0), aniEnd(false) {}
		~Animation() {}
	};

private:
	bool isDebug;
	bool isAfterImage;
	bool isBoss;

public:
	int BossCloneDis;

public:
	void DebugOn()
	{
		isDebug = true;
	}

	void DebugOff()
	{
		isDebug = false;
	}

	void AfterImageOn()
	{
		isAfterImage = true;
	}

	void AfterImageOff()
	{
		isAfterImage = false;
	}

	void BossDashOn()
	{
		isBoss = true;
	}

	void BossDashOff()
	{
		isBoss = false;
	}
private:
	bool		aniPause;
public:
	void PauseOn()
	{
		aniPause = true;
	}
	void PauseOff()
	{
		aniPause = false;
	}

private:


	std::map<std::wstring, Animation*> aniMap;
	
	Animation*	curAni;
	Animation*	particleAni;

	int			transRender; // 마젠타

private:
	Animation* FindAnimation(const wchar_t* _AniName);

public:
	Animation* GetCurAni()
	{
		return curAni;
	}
	Animation* GetParitcleAni()
	{
		return particleAni;
	}

public:
	bool IsAni			(const wchar_t* _AniName);
	void PlayAnimation	(const wchar_t* _AniName, bool _IndexCheck = false);
	void PlayAnimation	(const wchar_t* _AniName, const wchar_t* _Particle);
	void CreateAnimation(const wchar_t* _AniName, const wchar_t* _SpriteName, int _StartIdx, int _EndIdx, float _AniTimebool,	bool _Loop);
	void CreateAnimation(const wchar_t* _AniName, const wchar_t* _SpriteName, int _StartIdx, int _EndIdx, bool	_Loop,			float _AniTime);

	void Render() override;

public:
	AniRender();
	~AniRender();
};

