#include "stdafx.h"
#include "ParticleSystem.h"

GammaEngine::ParticleSystem::ParticleSystem(GameObject* gameObject)
	:Component(gameObject)
{
	ParticleManager::Instance()->RegistParticleSystem(this);
	emitters_ = new std::vector<ParticleEmitter*>();
}

GammaEngine::ParticleSystem::~ParticleSystem()
{
	for (auto& emitter : *emitters_)
	{
		delete emitter;
	}
	emitters_->clear();

	ParticleManager::Instance()->DeleteParticleSystem(this);
}

void GammaEngine::ParticleSystem::Update()
{
	for (auto& emitter : *emitters_)
	{
		emitter->Update();
	}

	for (auto& emitter : *emitters_)
	{
		for (auto& particle : *(emitter->GetRunningParticles()))
		{
			particle->Update();
		}
	}

	for (auto& emitter : *emitters_)
	{
		for (auto& returnParticle : *(emitter->returnBuffer))
		{
			emitter->runningParticles->remove(returnParticle);
			emitter->particlePool->push(returnParticle);
		}
		emitter->returnBuffer->clear();
	}
}

void GammaEngine::ParticleSystem::DrawParticle()
{
	for (auto& emitter : *emitters_)
	{
		for (auto& particle : *(emitter->GetRunningParticles()))
		{
			particle->Render();
		}
	}
}

std::vector<ParticleEmitter*>* GammaEngine::ParticleSystem::GetEmitters()
{
	return emitters_;
}

GammaEngine::ParticleEmitter* GammaEngine::ParticleSystem::CreateEmitter(unsigned int maxCount, std::wstring fileName, float order)
{
	ParticleEmitter* temp = new ParticleEmitter(maxCount, fileName, order);
	temp->particleSystem = this;
	emitters_->push_back(temp);
	return temp;
}
