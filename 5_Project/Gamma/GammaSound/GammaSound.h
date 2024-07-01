#pragma once
#include <map>
#include <string>
/// <summary>
/// 23.02.09
/// 변지상의 SoundSystem
/// </summary>
/// 
/// 
namespace FMOD {
	class System;
	class Channel;
	class Reverb3D;
	class Sound;
}

class System;
class Channel;
class Reverb3D;
class Sound;
struct FMOD_VECTOR;
struct FMOD_REVERB_PROPERTIES;

class GammaSound
{
public:
	~GammaSound();

	//FMOD 시스템
	static FMOD::System* normalSystem_;
	static FMOD::System* reverbSystem_;

	//FMOD 채널
	static FMOD::Channel* channel_[100];

	//FMOD 리버브
	static FMOD::Reverb3D* concertReverb;
	static FMOD::Reverb3D* offReverb;

	//FMOD 리버브 벡터
	static FMOD_VECTOR vec;

	//리버브의 상태를 지정하는 변수
	static FMOD_REVERB_PROPERTIES concertPro;

	//사운드 시스템 초기화
	static void Initialize();
	static void Update();
	static void Finalize();

	static void CreateReverb();

	static std::wstring CreateSound(const char* filePath, bool loop);
	static std::wstring CreateReverbSound(const char* filePath, bool loop);

	static void SetReverbVector(float x, float y, float z);
	static void SetConcertProperties();
	static void SetVolume(int channelNum, float vol);

	static void Play(std::wstring path, int channelNum);
	static void PathPlay(std::wstring path, int channelNum);
	static void PlayReverb(std::wstring path, int channelNum);
	static void Pause(std::wstring path, int channelNum);
	static void Stop(std::wstring path, int channelNum);
	static void PathStop(std::wstring path, int channelNum);

	static void VolumeUp(int channelNum);
	static void VolumeDown(int channelNum);

private:
	//리버브 최대 최소 거리
	const static float mindist;
	const static float maxdist;

	static bool isPaused_;
	static bool isPlaying;

	//사운드 볼륨
	static float volume;

	//사운드 맵
	static std::map<std::wstring, FMOD::Sound*>* soundMap;

	//리버브 벡터
	float x;
	float y;
	float z;

};
