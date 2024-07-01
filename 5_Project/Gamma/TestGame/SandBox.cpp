#include "GammaEngine.h"
#include "SandBox.h"
#include "SpineTest.h"
#include "MainCamera.h"

using namespace GammaEngine;

void SpineSceneInit()
{
	Scene* spineScene = SceneManager::GetCurrentScene();
	GameObject* camera = CreateCamera(spineScene);
	GameObject* spineObj = spineScene->CreateObject();
	spineObj->AddComponent<SpineRenderer>();
	spineObj->AddComponent<EllipseRenderer>();
	spineObj->AddComponent<SpineTest>();

	spineObj->GetComponent <EllipseRenderer>()->size = vector2(10, 10);
}

GameObject* CreateCamera(Scene* scene)
{
	GameObject* camera = scene->CreateObject();
	camera->AddComponent<Camera>();
	camera->AddComponent<MainCamera>();
	return camera;
}
