#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

namespace GammaEngine
{
	class ParticleEmitter;

	class GammaEngineAPI ParticleSystem final : public Component
	{
	public:
		ParticleSystem(GameObject* gameObject);
		~ParticleSystem();

		virtual void Update() override;
		void DrawParticle();

		std::vector<ParticleEmitter*>* GetEmitters();
		ParticleEmitter* CreateEmitter(unsigned int maxCount, std::wstring fileName, float order = 0);

	private:
		std::vector<ParticleEmitter*>* emitters_;
	};
}
