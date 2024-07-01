#include "Core.h"

#include "ToriD2D.h"
#include "SceneSystem.h"
#include "Scene.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "CollisionSystem.h"
#include "RenderSystem.h"
#include "ObjectSystem.h"
#include "Debug.h"

int Core::screenWidth = 0;
int Core::screenHeight = 0;

Core::Core()
	: sceneSystem_(SceneSystem::Instance()),
	timeSystem_(TimeSystem::Instance()),
	inputSystem_(InputSystem::Instance()),
	collisionSystem_(CollisionSystem::Instance()),
	renderSystem_(RenderSystem::Instance()),
	objectSystem_(ObjectSystem::Instance())
{
}

Core::~Core()
{
}

void Core::Initialize(const HWND& hWnd, int pScreenWidth, int pScreeHeight)
{
	screenWidth = pScreenWidth;
	screenHeight = pScreeHeight;
	sceneSystem_.Initialize();
	timeSystem_.Initialize();
	inputSystem_.Initialize(hWnd);
	collisionSystem_.Initialize();
	renderSystem_.Initialize(hWnd);
	objectSystem_.Initialize();
}

void Core::Finalize()
{
	sceneSystem_.Finalize();
	timeSystem_.Finalize();
	inputSystem_.Finalize();
	collisionSystem_.Finalize();
	renderSystem_.Finalize();
	objectSystem_.Finalize();
}

void Core::CycleOnce() const
{
	timeSystem_.MeasureTime();

	PhysicsUpdate();
	Input();
	Update();
	Render();
	inputSystem_.mouseScrollDelta = (short)0;
	inputSystem_.OnClickEvent();
}

void Core::Resize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

void Core::PhysicsUpdate() const
{
	collisionSystem_.CheckCollision();
}

void Core::Input() const
{
	inputSystem_.AgingStatus();
	inputSystem_.CheckInput();
}

void Core::Update() const
{
	objectSystem_.UpdateIndestructible();
	objectSystem_.Update(sceneSystem_.GetCurrentScene());
	objectSystem_.Update(sceneSystem_.GetUIScene());
}

void Core::Render() const
{
	renderSystem_.Render(sceneSystem_.GetCurrentScene(), sceneSystem_.GetUIScene());
}

