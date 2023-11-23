#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::Engine::Engine()
{
	particleManager_ = ParticleManager::Instance();
	collisionSystem_ = CollisionSystem::Instance();
	soundSystem_ = SoundSystem::Instance();
	graphic_ = GraphicSystem::Instance();
	lightSystem_ = LightSystem::Instance();

	objectManager_ = new ObjectManager();
	sceneManager_ = new SceneManager();
	gamepadManager_ = new GamepadManager();
	input_ = new Input();
	timer_ = new Timer();
	debug_ = new Debug();
	Tween();
}

GammaEngine::Engine::~Engine()
{

}

void GammaEngine::Engine::Initialize()
{
	graphic_->Initialize(WindowSystem::hWnd);
	input_->Initialize(WindowSystem::hWnd);
	sceneManager_->Initialize();
	collisionSystem_->Initialize();
	particleManager_->Initialize();
	soundSystem_->Initialize();
	soundSystem_->SetReverbVector(vector3(0, 0, 0));
	
}

bool GammaEngine::Engine::Frame()
{
	timer_->Frame();
	sceneManager_->Update();
	ObjectManager::Frame();
	SceneManager::currentScene->Start();
	SceneManager::currentScene->Frame();
	collisionSystem_->Frame();
	input_->Frame();
	GamepadManager::Frame();
	graphic_->Frame();
	soundSystem_->Update();
	return true;
}
