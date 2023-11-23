#include "UIScene.h"

#include "GameObject.h"
#include "SceneSystem.h"
#include "Scene.h"

#include "UIManager.h"
#include "TextRenderer.h"

#define SCENENAME "UIScene"

/// <summary>
/// UIScene을 생성한다.
/// 
/// 23.02.14 강석원 인재원
/// </summary>
void UIScene::Initialize(int width, int height)
{
	Scene& UIScene = SceneSystem::Instance().CreateScene(SCENENAME);
	SceneSystem::Instance().SetUIScene(SCENENAME);
	SceneSystem::Instance().SetCurrentScene(SCENENAME);

	GameObject& textObj1 = UIScene.CreateObject();
	TextRenderer* text_1 = textObj1.AddComponent<TextRenderer>();

	text_1->SetText("CurtainCallMapEditor");
	text_1->SetPosition(0, 0);
	text_1->SetRGBA(1.0f, 1.0f, 1.0f, 1.0f);
}