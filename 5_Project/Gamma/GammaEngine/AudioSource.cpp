#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::AudioSource::AudioSource(GameObject* t) 
	: Component(t), volume(0.5f)
{
	SoundSystem::RegistSound(this);
}

//한번 재생 사운드
void GammaEngine::AudioSource::CreateSound(const char* filePath, bool loop)
{
	path = new std::wstring(SoundSystem::CreateSound(filePath, loop));
}

void  GammaEngine::AudioSource::CreateReverbSound(const char* filePath, bool loop)
{
	path = new std::wstring(SoundSystem::CreateReverbSound(filePath, loop));
}

//재생
void GammaEngine::AudioSource::Play(int channelNum)
{
	SoundSystem::Play(this, channelNum);
}

void GammaEngine::AudioSource::PlayReverb(int channelNum)
{
	SoundSystem::PlayReverb(this, channelNum);
}

void GammaEngine::AudioSource::Pause(int channelNum)
{
	SoundSystem::Pause(this, channelNum);
}

void GammaEngine::AudioSource::Stop(int channelNum)
{
	SoundSystem::Stop(this, channelNum);
}

void GammaEngine::AudioSource::SetVolume(int channelNum, float vol)
{
	SoundSystem::SetVolume(channelNum, vol);
}

void GammaEngine::AudioSource::VolumeUp(int channelNum)
{
	SoundSystem::VolumeUp(channelNum);
}

void GammaEngine::AudioSource::VolumeDown(int channelNum)
{
	SoundSystem::VolumeDown(channelNum);
}


