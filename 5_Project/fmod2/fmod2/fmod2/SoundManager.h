#pragma once
#include "fmod.hpp"

/// <summary>
/// ������ ���� SoundManager
/// 23.02.02 ���� ����
/// 23.02.07 ������ ��� ���� �Ϸ�
/// </summary>

class SoundManager
{
public:
	//FMOD ���� �� ��뿡 �ʿ��� �ʼ� ������
	FMOD::System* system_;
	FMOD::System* system2_;
	//FMOD ����
	FMOD::Sound* sound_[100];
	//FMOD ä��
	FMOD::Channel* channel_[100];

	//���׸� �����ϴ� ����
	FMOD_RESULT result_;

	//���� ����
	float _volume;

	//����Ʈ�� ����Ǵ� �Ÿ� ����
	float mindist = 0.0f;
	float maxdist = 100.0f;

	bool isPaused;

	//FMOD �����꿡 �ʿ��� ����
	FMOD::Reverb3D* reverb_;
	FMOD::Reverb3D* reverb2_;

	//�������� ���¸� �����ϴ� ����
	FMOD_REVERB_PROPERTIES pro;
	FMOD_REVERB_PROPERTIES pro2;

	//FMOD ����� ����
	FMOD_VECTOR vec;
	FMOD_VECTOR listenerVec;

public:
	SoundManager();

	//�׽�Ʈ ���� �̱���
	static SoundManager& Instance()
	{
		static SoundManager* instance = new SoundManager();
		return *instance;
	}

	//���� �ý��� �ʱ�ȭ �Լ�
	void SystemInitialize();

	//���带 �������� �Լ�
	void CreateNormalSound(const char* _filePath, int soundNum);
	void CreateNormalReverbSound(const char* _filePath, int soundNum);
	void CreateLoopSound(const char* _filePath, int soundNum);
	void CreateLoopReverbSound(const char* _filePath, int soundNum);

	//���� ����ϴ� �Լ�
	void PlaySounds(int soundNum, int channelNum);
	void PlayReverbSounds(int soundNum, int channelNum);
	void StopSounds(int channelNum);
	void PauseSound(int channelNum);

	//ä���� ������ ����
	void SetVolume(int channelNum, float vol);
	void VolumeUp();
	void VolumeDown();

	//������ ����
	void CreateReverb();
	void ReverbUp();
	void ReverbDown();

	//������ Ÿ�� ����
	void SetProperties(int channelNum);
	void SetProperties2(int channelNum);

	//FMOD ���� ��ǥ ����
	void SetReverbVector(float x, float y, float z);
	FMOD_VECTOR GetReverbVector();

	void KeyUpdate();

	//���� �ý��� ����
	void SystemFinalize();
};



