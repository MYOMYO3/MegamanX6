#include "Sound.h"
#include "Path.h"
#include "JTemplate.h"

#include <string>
#include <assert.h>

#include <atlstr.h>


FMOD_RESULT __stdcall SoundPlayerCallBack
					(	FMOD_CHANNELCONTROL *channelcontrol,
						FMOD_CHANNELCONTROL_TYPE controltype,
						FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
						void *commanddata1,
						void *commanddata2	)
{
	switch (controltype)
	{
	case FMOD_CHANNELCONTROL_CHANNEL:
	
		switch (callbacktype)
		{
		case FMOD_CHANNELCONTROL_CALLBACK_END:
		{
			FMOD::Channel* pPointer = ((FMOD::Channel*)channelcontrol);

			void* pSoundPlayer = nullptr;
			pPointer->getUserData(&pSoundPlayer);

			if (nullptr == pSoundPlayer)
			{
				assert(false);
			}

			SoundPlayer* CallPlayer = (SoundPlayer*)pSoundPlayer;

			if (true == CallPlayer->GetRental())
			{
				return FMOD_OK;
			}

			CallPlayer->ReturnPool();

			return FMOD_OK;
		}
		case FMOD_CHANNELCONTROL_CALLBACK_VIRTUALVOICE:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_SYNCPOINT:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_OCCLUSION:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_MAX:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_FORCEINT:
			break;
		default:
			break;
		}
		break;
	case FMOD_CHANNELCONTROL_CHANNELGROUP:
		break;
	case FMOD_CHANNELCONTROL_MAX:
		break;
	case FMOD_CHANNELCONTROL_FORCEINT:
		break;
	default:
		break;
	}
	return FMOD_OK;
}


#pragma region SOUNDCLIP
SoundClip::SoundClip()
{
}

SoundClip::~SoundClip()
{
	m_pSound->release();
	m_pSound = nullptr;
}

#pragma endregion

#pragma region SOUNDPLAYER

bool SoundPlayer::ReturnPool()
{
	if (Sound::m_CurPlayer.end() != Sound::m_CurPlayer.find(this))
	{
		Sound::m_CurPlayer.erase(this);
	}

	Sound::m_SoundPlayerPool.push(this);

	return true;
}

bool SoundPlayer::Play(const wchar_t* _SoundName, int _LoopCnt)
{
	SoundClip* findClip = Sound::FindSound(_SoundName);
	if (nullptr == findClip)
	{
		assert(false);
		return false;
	}


	Sound::m_pMainSoundSystem->playSound(findClip->m_pSound, nullptr, false, &m_pChannel);

	if (nullptr == m_pChannel)
	{
		assert(false);
		return false;
	}

	m_pChannel->setCallback(SoundPlayerCallBack);
	m_pChannel->setUserData(this);
	m_pChannel->setMode(FMOD_LOOP_NORMAL);
	m_pChannel->setLoopCount(_LoopCnt);

	if (Sound::m_CurPlayer.end() == Sound::m_CurPlayer.find(this))
	{
		Sound::m_CurPlayer.insert(this);
	}

	return true;
}

void SoundPlayer::Stop()
{
	if (nullptr == m_pChannel)
	{
		assert(false);
	}

	m_pChannel->stop();	
	m_pChannel = nullptr;
}

#pragma endregion


#pragma region SOUND
FMOD::System*						Sound::m_pMainSoundSystem = nullptr;
std::map<std::wstring, SoundClip*>	Sound::m_ClipMap = std::map<std::wstring, SoundClip*>();
std::stack<SoundPlayer*>			Sound::m_SoundPlayerPool = std::stack<SoundPlayer*>();
std::set<SoundPlayer*>				Sound::m_CurPlayer = std::set<SoundPlayer*>();

bool Sound::Init(int _Cnt)
{
	FMOD_RESULT Return = FMOD::System_Create(&m_pMainSoundSystem);
	if (nullptr == m_pMainSoundSystem || FMOD_OK != Return)
	{
		assert(false);
		return false;
	}

	Return = m_pMainSoundSystem->init(32, FMOD_DEFAULT, nullptr);
	if (FMOD_OK != Return)
	{
		assert(false);
		return false;
	}

	for (size_t i = 0; i < _Cnt; i++)
	{
		m_SoundPlayerPool.push(new SoundPlayer());
	}

	return true;
}

void Sound::Update()
{
	if (nullptr != m_pMainSoundSystem)
	{
		//�̺�Ʈ üũ�� ���ش�.
		//���� ����� �������.
		m_pMainSoundSystem->update();
	}
}

void Sound::End()
{
	std::map<std::wstring, SoundClip*>::iterator Start	= m_ClipMap.begin();
	std::map<std::wstring, SoundClip*>::iterator End	= m_ClipMap.end();

	for (; Start != End; ++Start)
	{
		delete Start->second;
	}

	while (0 < m_SoundPlayerPool.size())
	{
		SoundPlayer* pPlayer = m_SoundPlayerPool.top();
		delete pPlayer;
		m_SoundPlayerPool.pop();
	}

	std::set<SoundPlayer*>::iterator PlayStart	= m_CurPlayer.begin();
	std::set<SoundPlayer*>::iterator PlayEnd	= m_CurPlayer.end();

	for (; PlayStart != PlayEnd; ++PlayStart)
	{
		delete (*PlayStart);
	}

	m_pMainSoundSystem->release();
}

SoundClip * Sound::SoundLoad(const wchar_t * _Path)
{
	std::wstring Key = Path::ExtractFileName(_Path);
	return SoundLoad(Key.c_str(), _Path);
}

SoundClip * Sound::SoundLoad(const wchar_t * _Name, const wchar_t * _Path)
{
	std::string str = CW2A(_Path, CP_UTF8).m_psz;

	FMOD::Sound* newSound = nullptr;

	FMOD_RESULT returnFMOD = m_pMainSoundSystem->createSound(str.c_str(), FMOD_DEFAULT, nullptr, &newSound);

	if (FMOD_OK != returnFMOD || nullptr == newSound)
	{
		assert(false);
	}

	//m_pMainSoundSystem->playSound(newSound, nullptr, false, nullptr);

	SoundClip* soundClip = new SoundClip();
	soundClip->m_pSound = newSound;
	m_ClipMap.insert(std::map<std::wstring, SoundClip*>::value_type(_Name, soundClip));

	return nullptr;
}


SoundClip* Sound::FindSound(const wchar_t* _Name)
{
	//std::map<>
	std::map<std::wstring, SoundClip*>::iterator findIter	= m_ClipMap.find(_Name);	
	if (findIter == m_ClipMap.end())
	{
		return nullptr;
	}
	
	return findIter->second;
	//return JTemplate::MapFindToPointer<SoundClip>(_Name, m_ClipMap);
}

void Sound::SoundPlay(const wchar_t* _Name, int _LoopCnt)
{
	if (0 == m_SoundPlayerPool.size())
	{
		return;
	}

	SoundPlayer* newPlayer = m_SoundPlayerPool.top();
	m_SoundPlayerPool.pop();
	newPlayer->Play(_Name, _LoopCnt);

	return;
}

//���������� ���� �÷��̾��� �����͸� ���
//����ϰ� �ʹٸ� �̳༮�� ����ؾ� �մϴ�.
SoundPlayer* Sound::SoundPlayNoneReturn()
{
	if (0 == m_SoundPlayerPool.size())
	{
		return nullptr;
	}

	// ž�� pop�� �ƴϴ�.
	// �̷����� ���� ������ �ƴϴ�.
	SoundPlayer* newPlayer = m_SoundPlayerPool.top();
	m_SoundPlayerPool.pop();
	newPlayer->m_Rental = true;
	m_CurPlayer.insert(newPlayer);

	return newPlayer;
}

//if (0 == m_SoundPlayerPool.size())
//{
//	return nullptr;
//}
//
//YSoundPlayer* NewPlayer = m_SoundPlayerPool.top();
//m_SoundPlayerPool.pop();
//NewPlayer->m_bRental = true;
//m_PlayPlayer.insert(NewPlayer);
//
//return NewPlayer;

void Sound::AllSoundPlayerStop()
{
	if (0 >= m_CurPlayer.size())
	{
		return;
	}

	std::set<SoundPlayer*>::iterator Start = m_CurPlayer.begin();
	std::set<SoundPlayer*>::iterator End = m_CurPlayer.end();


	// �ڵ� ���߿� �� �ڷᱸ�� end�� ��ŸƮ�� ����Ǵ� �ڵ�� ������ ���� �ʴ�.
	// ���� ���� �ڵ带 ģ��.
	// 1) m_PlayPlayer �ȿ��� �������� ���� �÷��̾���� �ִ�.
	// 2) �����÷��̾��� stop�̶�� �Լ��� ����� m_PlayPlayer�� ���� ������ ����ȴ�.
	// 3) �׷��Ƿ� �� ��쿡�� �θ� ���ؼ� �ݺ����� ó���ϴ� ���� �ƴ�
	//    �̷��� �ٸ� �ڷᱸ���� ���� ��Ƽ� ó���ϴ� ��찡 �����ϴ�.
	std::vector<SoundPlayer*> OutList;

	// �ڷᱸ���� �ٸ��ܾ��
	// �÷���
	// ������ ����Ʈ��ó
	for (; Start != End; ++Start)
	{
		OutList.push_back(*Start);
	}

	for (size_t i = 0; i < OutList.size(); i++)
	{
		OutList[i]->Stop();
	}

	m_CurPlayer.clear();
}

#pragma endregion


