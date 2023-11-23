#include "GammaSound.h"
#include "fmod.hpp"


 FMOD::System* GammaSound::normalSystem_;
 FMOD::System* GammaSound::reverbSystem_;

 FMOD::Channel* GammaSound::channel_[100];

 FMOD::Reverb3D* GammaSound::concertReverb;

 std::map<std::wstring, FMOD::Sound*>* GammaSound::soundMap;

 FMOD_VECTOR GammaSound::vec;
 FMOD_REVERB_PROPERTIES GammaSound::concertPro;

 const float GammaSound::mindist = 0.0f;
 const float GammaSound::maxdist = 100.0f;

 bool GammaSound::isPaused_ = false;
 bool GammaSound::isPlaying = false;

 float GammaSound::volume = 0.5f;

GammaSound::~GammaSound()
{

}

//���� �� �ʱ�ȭ
void GammaSound::Initialize()
{
	System_Create(&normalSystem_);
	System_Create(&reverbSystem_);

	normalSystem_->init(200, FMOD_INIT_NORMAL, nullptr);
	reverbSystem_->init(200, FMOD_INIT_NORMAL, nullptr);

	concertPro = FMOD_PRESET_CONCERTHALL;
	soundMap = new std::map<std::wstring, FMOD::Sound*>();

	CreateReverb();
	SetConcertProperties();
}

//������Ʈ
void GammaSound::Update()
{
	normalSystem_->update();
	reverbSystem_->update();
}

//����
void GammaSound::Finalize()
{
	normalSystem_->release();
	reverbSystem_->release();
}

//������ ���� ����
void GammaSound::SetReverbVector(float x, float y, float z)
{
	vec.x = x;
	vec.y = y;
	vec.z = z;

	concertReverb->set3DAttributes(&vec, mindist, maxdist);
}

//������ ����
void GammaSound::CreateReverb()
{
	reverbSystem_->createReverb3D(&concertReverb);
}

//������ ������Ƽ
void GammaSound::SetConcertProperties()
{
	concertReverb->setProperties(&concertPro);
}

//�Ϲ� ���� ����
std::wstring GammaSound::CreateSound(const char* filePath, bool loop)
{
	FMOD::Sound* sound = nullptr;
	std::wstring path = std::wstring(filePath, filePath + strlen(filePath));
	soundMap->insert(std::make_pair(path, sound));
	if (loop)
	{
		GammaSound::normalSystem_->createSound(filePath, FMOD_LOOP_NORMAL, 0, &(*soundMap)[path]);
	}
	else
	{
		GammaSound::normalSystem_->createSound(filePath, FMOD_LOOP_OFF, 0, &(*soundMap)[path]);
	}
	return path;
}

//������ ���� ����
std::wstring GammaSound::CreateReverbSound(const char* filePath, bool loop)
{
	FMOD::Sound* sound = nullptr;
	std::wstring path = std::wstring(filePath, filePath + strlen(filePath));
	soundMap->insert(std::make_pair(path, sound));
	if (loop)
		GammaSound::reverbSystem_->createSound(filePath, FMOD_LOOP_NORMAL, 0, &(*soundMap)[path]);
	else
		GammaSound::reverbSystem_->createSound(filePath, FMOD_LOOP_OFF, 0, &(*soundMap)[path]);
	return path;
}

//���� ����
void GammaSound::SetVolume(int channelNum, float vol)
{
	volume = vol;

	channel_[channelNum]->setVolume(volume);
}

//�Ϲ� ���� ���
void GammaSound::Play(std::wstring path, int channelNum)
{
	normalSystem_->playSound((*soundMap)[path], NULL, false, &channel_[channelNum]);
	channel_[channelNum]->isPlaying(&isPlaying);
}

void GammaSound::PathPlay(std::wstring path, int channelNum)
{
	normalSystem_->playSound((*soundMap)[path], NULL, false, &channel_[channelNum]);
	channel_[channelNum]->isPlaying(&isPlaying);
}

//������ ���� ���
void GammaSound::PlayReverb(std::wstring path, int channelNum)
{
	reverbSystem_->playSound((*soundMap)[path], NULL, false, &channel_[channelNum]);
	channel_[channelNum]->isPlaying(&isPlaying);
}

//���� �Ͻ�����
void GammaSound::Pause(std::wstring path, int channelNum)
{
	isPaused_ = !isPaused_;

	channel_[channelNum]->setPaused(isPaused_);
}

//���� ����
void GammaSound::Stop(std::wstring path, int channelNum)
{
	channel_[channelNum]->stop();
}

void GammaSound::PathStop(std::wstring path, int channelNum)
{
	channel_[channelNum]->stop();
}

//���� ��
void GammaSound::VolumeUp(int channelNum)
{
	volume += 0.1f;

	if (volume >= 1.0f)
	{
		volume = 1.0f;
	}

	SetVolume(channelNum, volume);
}

//���� �ٿ�
void GammaSound::VolumeDown(int channelNum)
{
	volume -= 0.1f;

	if (volume >= 0.0f)
	{
		volume = 0.0f;
	}

	SetVolume(channelNum, volume);
}


