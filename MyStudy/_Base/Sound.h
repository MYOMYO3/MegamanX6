#pragma once

#include <fmod.hpp>
#include <map>
#include <stack>
#include <set>

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "\\X32\\fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "\\X32\\fmod_vc.lib")
#endif // DEBUG
///
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "\\X64\\fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "\\X64\\fmod_vc.lib")
#endif // DEBUG
#endif // DEBUG

class Sound;	
class SoundPlayer;
class SoundClip
{
public:
	friend Sound;
	friend SoundPlayer;

private:
	FMOD::Sound* m_pSound;

	unsigned int SoundLen()
	{
		unsigned int Value = -1;
		m_pSound->getLength(&Value, FMOD_TIMEUNIT_MS);

		return Value;
	}

private:
	SoundClip();
	~SoundClip();
};

//사운드를 재생해주는 주체가 된다.
class Sound;
class SoundPlayer
{
private:
	friend Sound;

private:
	SoundClip* m_SoundClip;
	FMOD::Channel* m_pChannel;

	bool m_Rental;

public:
	bool GetRental()
	{
		return m_Rental;
	}

public:
	bool ReturnPool();
	bool Play(const wchar_t* _SoundName, int _LoopCnt);
	void Stop();

private:
	SoundPlayer() : m_Rental(false) {};
	~SoundPlayer() {};
};


class Sound
{
public:
	friend SoundPlayer;

private:
	static FMOD::System* m_pMainSoundSystem;

public: // 동시재생 개수
	static bool Init(int _Cnt = 128);
	static void Update();
	static void End();

private:
	static std::map<std::wstring, SoundClip*> m_ClipMap;

	static std::stack<SoundPlayer*> m_SoundPlayerPool;
	static std::set	 <SoundPlayer*>	m_CurPlayer;
	//풀방식을 보여주겠다.
	//풀은 다 만들어놓고 100
	//100개이상을 
public:
	static SoundClip* SoundLoad(const wchar_t* _Path);
	static SoundClip* SoundLoad(const wchar_t* _Name, const wchar_t* _Path);

	//이녀석은 한번 재생되면 알아서 처리
	static void SoundPlay(const wchar_t* _Name, int _LoopCnt = 0);

	//여러번들이 사운드 플레이어의 포인터를 들고서
	//사용하고 싶다면 이녀석을 사용해야 합니다.
	static SoundPlayer* SoundPlayNoneReturn();
	static void AllSoundPlayerStop();

private:
	static SoundClip* FindSound(const wchar_t* _Name);


private:
	Sound() {};
	~Sound() {};
};

