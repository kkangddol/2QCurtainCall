#pragma once
#include "fmod.hpp"

/// <summary>
/// 변지상 제작 SoundManager
/// 23.02.02 제작 시작
/// 23.02.07 리버브 기능 제작 완료
/// </summary>

class SoundManager
{
public:
	//FMOD 실행 및 사용에 필요한 필수 변수들
	FMOD::System* system_;
	FMOD::System* system2_;
	//FMOD 사운드
	FMOD::Sound* sound_[100];
	//FMOD 채널
	FMOD::Channel* channel_[100];

	//버그를 검증하는 변수
	FMOD_RESULT result_;

	//사운드 볼륨
	float _volume;

	//이펙트가 적용되는 거리 조정
	float mindist = 0.0f;
	float maxdist = 100.0f;

	bool isPaused;

	//FMOD 리버브에 필요한 변수
	FMOD::Reverb3D* reverb_;
	FMOD::Reverb3D* reverb2_;

	//리버브의 상태를 지정하는 변수
	FMOD_REVERB_PROPERTIES pro;
	FMOD_REVERB_PROPERTIES pro2;

	//FMOD 모듈의 벡터
	FMOD_VECTOR vec;
	FMOD_VECTOR listenerVec;

public:
	SoundManager();

	//테스트 위해 싱글턴
	static SoundManager& Instance()
	{
		static SoundManager* instance = new SoundManager();
		return *instance;
	}

	//사운드 시스템 초기화 함수
	void SystemInitialize();

	//사운드를 가져오는 함수
	void CreateNormalSound(const char* _filePath, int soundNum);
	void CreateNormalReverbSound(const char* _filePath, int soundNum);
	void CreateLoopSound(const char* _filePath, int soundNum);
	void CreateLoopReverbSound(const char* _filePath, int soundNum);

	//사운드 재생하는 함수
	void PlaySounds(int soundNum, int channelNum);
	void PlayReverbSounds(int soundNum, int channelNum);
	void StopSounds(int channelNum);
	void PauseSound(int channelNum);

	//채널의 볼륨을 설정
	void SetVolume(int channelNum, float vol);
	void VolumeUp();
	void VolumeDown();

	//리버브 생성
	void CreateReverb();
	void ReverbUp();
	void ReverbDown();

	//리버브 타입 설정
	void SetProperties(int channelNum);
	void SetProperties2(int channelNum);

	//FMOD 벡터 좌표 설정
	void SetReverbVector(float x, float y, float z);
	FMOD_VECTOR GetReverbVector();

	void KeyUpdate();

	//사운드 시스템 해제
	void SystemFinalize();
};



