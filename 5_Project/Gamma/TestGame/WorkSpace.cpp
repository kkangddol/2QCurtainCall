#include "WorkSpace.h"
#include "GammaEngine.h"
#include "Player.h"
#include "MainCamera.h"

using namespace GammaEngine;

WorkSpace::WorkSpace()
{
	//Create Scene
	Scene* scene = new Scene("SpineScene");
	//spineScene->SetInitializer(SpineWorkSpace::SpineSceneInit);
	//SpineSceneInit();
	// 
	//Camera
	GameObject* camera = scene->CreateObject();
	camera->AddComponent<Camera>();
	camera->AddComponent<MainCamera>();



	GameObject* player = scene->CreateObject();

	player->transform->position = vector2(200, -200);
	player->AddComponent<Player>();

	player->AddComponent<RectangleRenderer>();
	player->GetComponent<RectangleRenderer>()->SetSize(vector2(100,100));

	player->AddComponent<BoxCollider>();
	player->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));

	player->AddComponent<Rigidbody>();
	player->GetComponent<Rigidbody>()->useGravity=true;
	



	GameObject* floor = scene->CreateObject();
	floor->AddComponent<RectangleRenderer>();
	floor->GetComponent<RectangleRenderer>()->SetSize(vector2(1000, 100));

	floor->AddComponent<BoxCollider>();
	floor->GetComponent<BoxCollider>()->SetBounds(vector2(1000, 100));

	floor->AddComponent<Rigidbody>();
	floor->GetComponent<Rigidbody>()->mass = 0;

	//AddScene
	SceneManager::AddScene(scene);
}

void WorkSpace::DefaultSceneInit()
{
	Scene* spineScene = SceneManager::GetCurrentScene();
	//Camera
	GameObject* camera = spineScene->CreateObject();
	camera->AddComponent<Camera>();
	camera->AddComponent<MainCamera>();

	GameObject* spineObj = spineScene->CreateObject();
	spineObj->AddComponent<SpineRenderer>();
	spineObj->AddComponent<EllipseRenderer>();

	spineObj->GetComponent <EllipseRenderer>()->size = vector2(10, 10);
}



/*
void asdfhjaskldf(scene* scene)
{
	//GameObject* newObject = scene.CreateObject();
	// camera->AddComponent<Camera>();
	// camera->AddComponent<MainCamera>();
}
*/