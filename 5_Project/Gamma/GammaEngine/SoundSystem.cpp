#include "stdafx.h"
#include "GammaSound.h"


using namespace GammaEngine;

std::vector<AudioSource*>* GammaEngine::SoundSystem::soundList;

GammaEngine::SoundSystem::SoundSystem()
{
	soundList = new std::vector<AudioSource*>();
}

GammaEngine::SoundSystem::~SoundSystem()
{

}

void GammaEngine::SoundSystem::Initialize()
{
	GammaSound::Initialize();
}

void GammaEngine::SoundSystem::Update()
{
	GammaSound::Update();
}

void GammaEngine::SoundSystem::Finalize()
{
	GammaSound::Finalize();
}

//리버브 벡터 설정
void GammaEngine::SoundSystem::SetReverbVector(vector3 val)
{
	GammaSound::SetReverbVector(val.x, val.y, val.z);
}

//리버브 생성
void GammaEngine::SoundSystem::CreateReverb()
{
	GammaSound::CreateReverb();
}

std::wstring GammaEngine::SoundSystem::CreateSound(const char* filePath,bool loop)
{
	return GammaSound::CreateSound(filePath, loop);
}
std::wstring GammaEngine::SoundSystem::CreateReverbSound(const char* filePath, bool loop)
{
	return GammaSound::CreateReverbSound(filePath, loop);
}
void GammaEngine::SoundSystem::SetVolume(int channelNum, float vol)
{
	GammaSound::SetVolume(channelNum, vol);
}
//리버브 타입 설정
void GammaEngine::SoundSystem::SetConcertProperties()
{
	GammaSound::SetConcertProperties();
}

int GammaEngine::SoundSystem::RegistSound(AudioSource* sound)
{
	soundList->push_back(sound);
	return (int)soundList->size() - 1;
}

void GammaEngine::SoundSystem::Play(AudioSource* sound, int channelNum)
{
	GammaSound::Play(*sound->path, channelNum);
}

void GammaEngine::SoundSystem::PathPlay(std::wstring filePath, int channelNum)
{
	GammaSound::PathPlay(filePath, channelNum);
}

void GammaEngine::SoundSystem::PlayReverb(AudioSource* sound, int channelNum)
{
	GammaSound::PlayReverb(*sound->path, channelNum);
}

void GammaEngine::SoundSystem::Pause(AudioSource* sound, int channelNum)
{
	GammaSound::Pause(*sound->path, channelNum);
}

void GammaEngine::SoundSystem::Stop(AudioSource* sound, int channelNum)
{
	GammaSound::Stop(*sound->path, channelNum);
}

void GammaEngine::SoundSystem::PathStop(std::wstring filePath, int channelNum)
{
	GammaSound::PathStop(filePath, channelNum);
}

void GammaEngine::SoundSystem::VolumeUp(int channelNum)
{
	GammaSound::VolumeUp(channelNum);
}

void GammaEngine::SoundSystem::VolumeDown(int channelNum)
{
	GammaSound::VolumeDown(channelNum);
}
