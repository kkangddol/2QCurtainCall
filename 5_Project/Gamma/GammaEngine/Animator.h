#pragma once
#include <unordered_map>

using std::wstring;

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 애니메이션 컴포넌트
/// </summary>
namespace GammaEngine {
	class GammaEngineAPI Animator : public Component
	{
	public:
		Animator(GameObject* t);
		~Animator();

	public:
		void AddAnimation(wstring, Animation*);
		wstring GetCurrentAnimation();
		void Play(std::wstring, PLAYBACK);

		Animation* operator [] (const wstring index)
		{
			return (* animationList)[index];
		}

	private:
		std::unordered_map<std::wstring, Animation*>* animationList;
		std::wstring* currentAnimation;
		std::wstring& bitmap;
	};
}
