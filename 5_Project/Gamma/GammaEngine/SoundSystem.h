#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// 사운드 리스트(채널)
// 1 타이틀BGM
// 2 인게임 BGM
// 3 UI 버튼 선택음
// 4 UI 버튼 클릭음
// 5 게임종료 (박수/빵빠레)
// 6 게임 준비 (시계소리)
// 7 커튼 소리
// 8 걷는 소리
// 9 달리는 소리
// 10 점프 소리
// 11 착지 소리
// 12 상자 끄는 소리
// 13 상자 착지 소리
// 14 발판 소리
// 15 레버 소리
// 16 바퀴 소리
// 17 원판 소리
// 18 스위치 소리
// 19 아치 소리
// 20 해 달 구름 소리
// 21 엘리베이터 소리
// 22 비 소리
// 23 텍스트 생성 소리
// 24 삑사리 음
// 25 기믹 성공 시 도장 소리
// 26 사다리 소리

using namespace GammaEngine;

namespace GammaEngine
{
	class AudioSource;

	/// <summary>
	/// 23.02.09
	/// 변지상의 SoundSystem
	/// </summary>
	class GammaEngineAPI SoundSystem :public Singleton<SoundSystem>
	{
	public:
		SoundSystem();
		~SoundSystem();

		//사운드 시스템 초기화 및 해제
		void Initialize();
		void Update();
		void Finalize();

		static void CreateReverb();
		static std::wstring CreateSound(const char* filePath, bool loop);
		static std::wstring CreateReverbSound(const char* filePath, bool loop);

		static void SetReverbVector(vector3);
		static void SetConcertProperties();

		static void Play(AudioSource* sound, int channelNum);
		static void PathPlay(std::wstring filePath, int channelNum);
		static void PlayReverb(AudioSource* sound, int channelNum);
		static void Pause(AudioSource* sound, int channelNum);
		static void Stop(AudioSource* sound, int channelNum);
		static void PathStop(std::wstring filePath, int channelNum);

		static void SetVolume(int,float);
		static void VolumeUp(int channelNum);
		static void VolumeDown(int channelNum);
		//사운드 등록
		static int RegistSound(AudioSource* sound);

	private:
		//등록하는 SoundList
		static std::vector<AudioSource*>* soundList;

		float mindist = 0.0f;
		float maxdist = 100.0f;
	};
}