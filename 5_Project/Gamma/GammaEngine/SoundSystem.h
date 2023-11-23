#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// ���� ����Ʈ(ä��)
// 1 Ÿ��ƲBGM
// 2 �ΰ��� BGM
// 3 UI ��ư ������
// 4 UI ��ư Ŭ����
// 5 �������� (�ڼ�/������)
// 6 ���� �غ� (�ð�Ҹ�)
// 7 Ŀư �Ҹ�
// 8 �ȴ� �Ҹ�
// 9 �޸��� �Ҹ�
// 10 ���� �Ҹ�
// 11 ���� �Ҹ�
// 12 ���� ���� �Ҹ�
// 13 ���� ���� �Ҹ�
// 14 ���� �Ҹ�
// 15 ���� �Ҹ�
// 16 ���� �Ҹ�
// 17 ���� �Ҹ�
// 18 ����ġ �Ҹ�
// 19 ��ġ �Ҹ�
// 20 �� �� ���� �Ҹ�
// 21 ���������� �Ҹ�
// 22 �� �Ҹ�
// 23 �ؽ�Ʈ ���� �Ҹ�
// 24 ��縮 ��
// 25 ��� ���� �� ���� �Ҹ�
// 26 ��ٸ� �Ҹ�

using namespace GammaEngine;

namespace GammaEngine
{
	class AudioSource;

	/// <summary>
	/// 23.02.09
	/// �������� SoundSystem
	/// </summary>
	class GammaEngineAPI SoundSystem :public Singleton<SoundSystem>
	{
	public:
		SoundSystem();
		~SoundSystem();

		//���� �ý��� �ʱ�ȭ �� ����
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
		//���� ���
		static int RegistSound(AudioSource* sound);

	private:
		//����ϴ� SoundList
		static std::vector<AudioSource*>* soundList;

		float mindist = 0.0f;
		float maxdist = 100.0f;
	};
}