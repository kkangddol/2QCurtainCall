#include "stdafx.h"
#include "ParticleManager.h"

GammaEngine::ParticleManager::ParticleManager()
{
	particleSystems_ = new std::vector<ParticleSystem*>();
}

GammaEngine::ParticleManager::~ParticleManager()
{
	
}

void GammaEngine::ParticleManager::Initialize()
{

}

void GammaEngine::ParticleManager::Finalize()
{
	delete particleSystems_;
}

void GammaEngine::ParticleManager::DrawParticle()
{
	for (auto& particleSystem : *particleSystems_)
	{
		particleSystem->DrawParticle();
	}
}

void GammaEngine::ParticleManager::RegistParticleSystem(ParticleSystem* ps)
{
	particleSystems_->push_back(ps);
}

void GammaEngine::ParticleManager::DeleteParticleSystem(ParticleSystem* ps)
{
	particleSystems_->erase(remove(particleSystems_->begin(), particleSystems_->end(), ps));
}

std::vector<ParticleSystem*>* GammaEngine::ParticleManager::GetSystems() const
{
	return particleSystems_;
}
