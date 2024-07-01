#pragma once
#include <map>

using std::wstring;

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 애니메이션 컴포넌트
/// </summary>
/// 
/// 
/// 
namespace GammaEngine {
	struct PrintData
	{
		float spacing =  1;
		float scale = 1;
		bool waving = false;
		vector4 color =vector4(0,0,0,1);
		float speed = 0.05f;
		float appear =0.01f;
		bool sound = false;
	};
	
	class TextSegment;
	class GammaEngineAPI TextAnimator : public Component
	{
	public:
		TextAnimator(GameObject* t);
		~TextAnimator();

	public:
		static void AddAnimation(std::wstring, PrintData);
		void Play();
		void Render();

		
	public:
		static std::map<std::wstring, PrintData>* dataList;
		TextAnimationRenderer* renderer_;
	};
}

