#pragma once
#include <string>
#include <unordered_map>

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

class Component;
class Transform;

/// <summary>
/// Spine model class
/// </summary>
namespace GammaEngine
{
	class GammaEngineAPI SpineModel
	{
	public:
		SpineModel(spine::Skeleton*, spine::AnimationStateData*, spine::AnimationState*);
	public:
		static SpineModel* Create(std::string, std::string, std::string);
		static void Initialize();
		void Update();
		void Render(Matrix3x3,Material*, std::vector<IEffect*>*);

	public:
		spine::Skeleton* skeleton;
		spine::AnimationStateData* animationStateData;
		spine::AnimationState* animationState;
		std::wstring* image;

	public:
		static std::unordered_map<std::string, SpineModel*>* spineModelMap;
	};
}
