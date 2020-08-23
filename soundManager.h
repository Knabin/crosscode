#pragma once
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

// 사용할 갯수에 맞춰서 BUFFER 수정 요망
#define SOUNDBUFFER 50
#define EXTRACHANNELBUFFER 20

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class soundManager
{
public:
	static soundManager* getInstance()
	{
		static soundManager instance;
		return &instance;
	}
private:
	soundManager();
	~soundManager();

private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;

	typedef map<string, Channel**>			 arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	arrSounds		_mTotalSounds;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);

	// 일반 재생 함수
	void play(string keyName, float volume = 1.0f);
	// 배경음악 재생 함수
	void playBGM(string keyName, float volume = 1.0f);

	void stop(string keyName);
	// 해당 사운드 제외하고 전부 다 stop 처리하는 함수
	void stopAll(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//사운드 이벤트 처리용 (호옥시 몰라서 hoxy...)
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
};

