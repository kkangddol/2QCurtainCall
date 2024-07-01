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

//생성 및 초기화
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

//업데이트
void GammaSound::Update()
{
	normalSystem_->update();
	reverbSystem_->update();
}

//해제
void GammaSound::Finalize()
{
	normalSystem_->release();
	reverbSystem_->release();
}

//리버브 벡터 설정
void GammaSound::SetReverbVector(float x, float y, float z)
{
	vec.x = x;
	vec.y = y;
	vec.z = z;

	concertReverb->set3DAttributes(&vec, mindist, maxdist);
}

//리버브 생성
void GammaSound::CreateReverb()
{
	reverbSystem_->createReverb3D(&concertReverb);
}

//리버브 프로퍼티
void GammaSound::SetConcertProperties()
{
	concertReverb->setProperties(&concertPro);
}

//일반 사운드 생성
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

//리버브 사운드 생성
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

//볼륨 설정
void GammaSound::SetVolume(int channelNum, float vol)
{
	volume = vol;

	channel_[channelNum]->setVolume(volume);
}

//일반 사운드 재생
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

//리버브 사운드 재생
void GammaSound::PlayReverb(std::wstring path, int channelNum)
{
	reverbSystem_->playSound((*soundMap)[path], NULL, false, &channel_[channelNum]);
	channel_[channelNum]->isPlaying(&isPlaying);
}

//사운드 일시정지
void GammaSound::Pause(std::wstring path, int channelNum)
{
	isPaused_ = !isPaused_;

	channel_[channelNum]->setPaused(isPaused_);
}

//사운드 정지
void GammaSound::Stop(std::wstring path, int channelNum)
{
	channel_[channelNum]->stop();
}

void GammaSound::PathStop(std::wstring path, int channelNum)
{
	channel_[channelNum]->stop();
}

//볼륨 업
void GammaSound::VolumeUp(int channelNum)
{
	volume += 0.1f;

	if (volume >= 1.0f)
	{
		volume = 1.0f;
	}

	SetVolume(channelNum, volume);
}

//볼륨 다운
void GammaSound::VolumeDown(int channelNum)
{
	volume -= 0.1f;

	if (volume >= 0.0f)
	{
		volume = 0.0f;
	}

	SetVolume(channelNum, volume);
}


