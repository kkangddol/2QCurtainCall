
#include "SoundManager.h"
#include <windows.h>

/// <summary>
/// 다시 만드는 fmod c++ 기본적인 모듈
/// </summary>
/// <returns></returns>

#define NULL 0

// 생성자
// FMOD 멤버 변수들 초기화
SoundManager::SoundManager() :
	_volume(1.0f),
	pro(FMOD_PRESET_CONCERTHALL),
	pro2(FMOD_PRESET_OFF)
{

}

// 사운드 시스템 생성 및 초기화
void SoundManager::SystemInitialize()
{
	result_ = FMOD::System_Create(&system_);
	result_ = FMOD::System_Create(&system2_);

	// 100개의 채널을 초기화한다
	result_ = system_->init(200, FMOD_INIT_NORMAL, NULL);
	result_ = system2_->init(200, FMOD_INIT_NORMAL, NULL);
}

// 일반 사운드 생성
void SoundManager::CreateNormalSound(const char* _filePath, int soundNum)
{
	system_->createSound(_filePath, FMOD_LOOP_OFF, 0, &sound_[soundNum]);
}

void SoundManager::CreateNormalReverbSound(const char* _filePath, int soundNum)
{
	system2_->createSound(_filePath, FMOD_LOOP_OFF, 0, &sound_[soundNum]);
}

// 루프 사운드 생성
void SoundManager::CreateLoopSound(const char* _filePath, int soundNum)
{
	system_->createSound(_filePath, FMOD_LOOP_NORMAL, 0, &sound_[soundNum]);
}

void SoundManager::CreateLoopReverbSound(const char* _filePath, int soundNum)
{
	system2_->createSound(_filePath, FMOD_LOOP_NORMAL, 0, &sound_[soundNum]);
}

// 사운드 재생 (스피커)
void SoundManager::PlaySounds(int soundNum, int channelNum)
{
	system_->playSound(sound_[soundNum], NULL, false, &channel_[channelNum]);
}

void SoundManager::PlayReverbSounds(int soundNum, int channelNum)
{
	system2_->playSound(sound_[soundNum], NULL, false, &channel_[channelNum]);
}

void SoundManager::StopSounds(int channelNum)
{
	
}

void SoundManager::PauseSound(int channelNum)
{
	isPaused = !isPaused;
	channel_[channelNum]->setPaused(isPaused);
}

// 채널의 볼륨을 설정
void SoundManager::SetVolume(int channelNum, float vol)
{
	_volume = vol;

	channel_[channelNum]->setVolume(vol);
	
}
void SoundManager::VolumeUp()
{
	_volume += 0.1f;

	if (_volume >= 1.0f)
	{
		_volume = 1.0f;
	}

	SetVolume(0, _volume);
}

void SoundManager::VolumeDown()
{
	_volume -= 0.1f;

	if (_volume <= 0.0f)
	{
		_volume = 0.0f;
	}
	
	SetVolume(0, _volume);
}

// 리버브 생성
void SoundManager::CreateReverb()
{
	system2_->createReverb3D(&reverb_);
	//system2_->setReverbProperties(0, &pro);
}

// 리버브 상태 설정
void SoundManager::SetProperties(int channelNum)
{
	reverb_->setProperties(&pro);
	//channel_[channelNum]->setReverbProperties(0, 0.0f);
}

// 리버브 상태 설정
void SoundManager::SetProperties2(int channelNum)
{
	reverb2_->setProperties(&pro2);
	channel_[channelNum]->setReverbProperties(0, 0.0f);
}

// 벡터 설정
void SoundManager::SetReverbVector(float x, float y, float z)
{
	vec.x = x;
	vec.y = y;
	vec.z = z;
	
	reverb_->set3DAttributes(&vec, mindist, maxdist);
}

// 리버브 업
void SoundManager::ReverbUp()
{
	vec.z += 10.0f;

	if (vec.z >= 100.0f)
	{
		vec.z = 100.0f;
	}

	reverb_->set3DAttributes(&vec, mindist, maxdist);
}

// 리버브 다운
void SoundManager::ReverbDown()
{
	vec.z -= 10.0f;

	if (vec.z <= 0.0f)
	{
		vec.z = 0.0f;
	}

	reverb_->set3DAttributes(&vec, mindist, maxdist);
}

//키 입력으로 전체적인 사운드 상태를 관리
void SoundManager::KeyUpdate()
{
	if (GetAsyncKeyState(VK_UP) & 0x0001)
	{
		VolumeUp();
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		VolumeDown();
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		ReverbDown();
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		ReverbUp();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		PauseSound(0);
	}
}

// 사운드 시스템 해제
void SoundManager::SystemFinalize()
{
	system_->release();
	reverb_->release();
}