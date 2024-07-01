#include "ClientCore.h"

#include "SceneSystem.h"
#include "Scene.h"

#include "ObjectSystem.h"
#include "GameObject.h"

#include "UIScene.h"
#include "MapEditorScene.h"

#include "SceneManager.h"
#include "UIManager.h"
#include "TextRenderer.h"

#define UISCENENAME "UIScene"

void ClientCore::Initialize(const int screenWidth, const int screenHeight)
{
	GameObject* sceneManager = new GameObject();
	ObjectSystem::Instance().RegistIndestructible(*sceneManager);
	sceneManager->AddComponent<SceneManager>();

	UIScene UIInit;
	UIInit.Initialize(screenWidth, screenHeight);

	MapEditorScene mapEditor;
	mapEditor.Initialize();

	SceneSystem::Instance().SetCurrentScene("MapEditorScene");
}
