#pragma once
#include <map>
#include <string>
/// <summary>
/// 23.02.09
/// �������� SoundSystem
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

	//FMOD �ý���
	static FMOD::System* normalSystem_;
	static FMOD::System* reverbSystem_;

	//FMOD ä��
	static FMOD::Channel* channel_[100];

	//FMOD ������
	static FMOD::Reverb3D* concertReverb;
	static FMOD::Reverb3D* offReverb;

	//FMOD ������ ����
	static FMOD_VECTOR vec;

	//�������� ���¸� �����ϴ� ����
	static FMOD_REVERB_PROPERTIES concertPro;

	//���� �ý��� �ʱ�ȭ
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
	//������ �ִ� �ּ� �Ÿ�
	const static float mindist;
	const static float maxdist;

	static bool isPaused_;
	static bool isPlaying;

	//���� ����
	static float volume;

	//���� ��
	static std::map<std::wstring, FMOD::Sound*>* soundMap;

	//������ ����
	float x;
	float y;
	float z;

};
