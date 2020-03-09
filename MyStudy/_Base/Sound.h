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

//���带 ������ִ� ��ü�� �ȴ�.
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

public: // ������� ����
	static bool Init(int _Cnt = 128);
	static void Update();
	static void End();

private:
	static std::map<std::wstring, SoundClip*> m_ClipMap;

	static std::stack<SoundPlayer*> m_SoundPlayerPool;
	static std::set	 <SoundPlayer*>	m_CurPlayer;
	//Ǯ����� �����ְڴ�.
	//Ǯ�� �� �������� 100
	//100���̻��� 
public:
	static SoundClip* SoundLoad(const wchar_t* _Path);
	static SoundClip* SoundLoad(const wchar_t* _Name, const wchar_t* _Path);

	//�̳༮�� �ѹ� ����Ǹ� �˾Ƽ� ó��
	static void SoundPlay(const wchar_t* _Name, int _LoopCnt = 0);

	//���������� ���� �÷��̾��� �����͸� ���
	//����ϰ� �ʹٸ� �̳༮�� ����ؾ� �մϴ�.
	static SoundPlayer* SoundPlayNoneReturn();
	static void AllSoundPlayerStop();

private:
	static SoundClip* FindSound(const wchar_t* _Name);


private:
	Sound() {};
	~Sound() {};
};

