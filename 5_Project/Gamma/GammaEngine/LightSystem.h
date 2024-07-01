#pragma once
#include <vector>
namespace GammaEngine
{
	class GammaEngineAPI LightSystem : public Singleton<LightSystem>
	{
	public:
		LightSystem();
		~LightSystem();
		static void Add(Light*);
		static void Add(LightAdapter* adapter);
		static void Remove(Light* light);
		static void Remove(LightAdapter* adapter);
	public:
		static std::vector<Light*>* lightList;
		static std::vector<LightAdapter*>* lightAdapterList;
	
	};
}
