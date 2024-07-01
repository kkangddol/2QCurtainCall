#include "SceneManager.h"

#include "InputSystem.h"
#include "SceneSystem.h"

#include "Debug.h"

// 디버그 모드 지정을 위해 static 멤버변수 초기화
bool Debug::isDebugMode_ = false;

SceneManager::SceneManager(GameObject* object)
	:Component(object)
{

}

void SceneManager::Update()
{
// 	if (InputSystem::GetKeyJustDown('1'))
// 	{
// 		SceneSystem::Instance().SetCurrentScene("CCScene");
// 	}
// 
// 	if (InputSystem::GetKeyJustDown('2'))
// 	{
// 		SceneSystem::Instance().SetCurrentScene("AABBScene");
// 	}
// 
// 	if (InputSystem::GetKeyJustDown('3'))
// 	{
// 		SceneSystem::Instance().SetCurrentScene("OBBScene");
// 	}
}
