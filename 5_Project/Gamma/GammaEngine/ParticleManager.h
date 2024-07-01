#pragma once
namespace GammaEngine
{
	class ParticleSystem;

	class ParticleManager final : public Singleton<ParticleManager>
	{
	public:
		ParticleManager();
		~ParticleManager();

		void Initialize();
		void Finalize();
		void DrawParticle();
		void RegistParticleSystem(ParticleSystem* ps);
		void DeleteParticleSystem(ParticleSystem* ps);
		std::vector<ParticleSystem*>* GetSystems() const;

	private:
		std::vector<ParticleSystem*>* particleSystems_;
	};

}

