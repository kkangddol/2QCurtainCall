
#include "SoundManager.h"
#include <windows.h>

/// <summary>
/// �ٽ� ����� fmod c++ �⺻���� ���
/// </summary>
/// <returns></returns>

#define NULL 0

// ������
// FMOD ��� ������ �ʱ�ȭ
SoundManager::SoundManager() :
	_volume(1.0f),
	pro(FMOD_PRESET_CONCERTHALL),
	pro2(FMOD_PRESET_OFF)
{

}

// ���� �ý��� ���� �� �ʱ�ȭ
void SoundManager::SystemInitialize()
{
	result_ = FMOD::System_Create(&system_);
	result_ = FMOD::System_Create(&system2_);

	// 100���� ä���� �ʱ�ȭ�Ѵ�
	result_ = system_->init(200, FMOD_INIT_NORMAL, NULL);
	result_ = system2_->init(200, FMOD_INIT_NORMAL, NULL);
}

// �Ϲ� ���� ����
void SoundManager::CreateNormalSound(const char* _filePath, int soundNum)
{
	system_->createSound(_filePath, FMOD_LOOP_OFF, 0, &sound_[soundNum]);
}

void SoundManager::CreateNormalReverbSound(const char* _filePath, int soundNum)
{
	system2_->createSound(_filePath, FMOD_LOOP_OFF, 0, &sound_[soundNum]);
}

// ���� ���� ����
void SoundManager::CreateLoopSound(const char* _filePath, int soundNum)
{
	system_->createSound(_filePath, FMOD_LOOP_NORMAL, 0, &sound_[soundNum]);
}

void SoundManager::CreateLoopReverbSound(const char* _filePath, int soundNum)
{
	system2_->createSound(_filePath, FMOD_LOOP_NORMAL, 0, &sound_[soundNum]);
}

// ���� ��� (����Ŀ)
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

// ä���� ������ ����
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

// ������ ����
void SoundManager::CreateReverb()
{
	system2_->createReverb3D(&reverb_);
	//system2_->setReverbProperties(0, &pro);
}

// ������ ���� ����
void SoundManager::SetProperties(int channelNum)
{
	reverb_->setProperties(&pro);
	//channel_[channelNum]->setReverbProperties(0, 0.0f);
}

// ������ ���� ����
void SoundManager::SetProperties2(int channelNum)
{
	reverb2_->setProperties(&pro2);
	channel_[channelNum]->setReverbProperties(0, 0.0f);
}

// ���� ����
void SoundManager::SetReverbVector(float x, float y, float z)
{
	vec.x = x;
	vec.y = y;
	vec.z = z;
	
	reverb_->set3DAttributes(&vec, mindist, maxdist);
}

// ������ ��
void SoundManager::ReverbUp()
{
	vec.z += 10.0f;

	if (vec.z >= 100.0f)
	{
		vec.z = 100.0f;
	}

	reverb_->set3DAttributes(&vec, mindist, maxdist);
}

// ������ �ٿ�
void SoundManager::ReverbDown()
{
	vec.z -= 10.0f;

	if (vec.z <= 0.0f)
	{
		vec.z = 0.0f;
	}

	reverb_->set3DAttributes(&vec, mindist, maxdist);
}

//Ű �Է����� ��ü���� ���� ���¸� ����
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

// ���� �ý��� ����
void SoundManager::SystemFinalize()
{
	system_->release();
	reverb_->release();
}