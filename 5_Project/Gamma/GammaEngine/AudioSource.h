#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

namespace GammaEngine
{
	/// <summary>
	/// 23.02.09
	/// 변지상 제작 AudioSource 컴포넌트
	/// </summary>
	class GammaEngineAPI AudioSource : public Component
	{
	public:
		//생성자
		AudioSource(GameObject* t);

		virtual void CreateSound(const char* filePath, bool loop);
		virtual void CreateReverbSound(const char* filePath, bool loop);

		virtual void Play(int channelNum);
		virtual void PlayReverb(int channelNum);

		virtual void Pause(int channelNum);
		virtual void Stop(int channelNum);

		virtual void SetVolume(int channelNum, float vol);
		virtual void VolumeUp(int channelNum);
		virtual void VolumeDown(int channelNum);

	public:
		std::wstring* path;
	private:
		float volume;		//볼륨
	};
}



