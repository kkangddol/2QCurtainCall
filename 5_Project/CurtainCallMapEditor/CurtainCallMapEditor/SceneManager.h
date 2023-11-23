#pragma once
#include "Component.h"

class GameObject;

/// <summary>
/// 클라이언트의 SceneManager
/// Scene 전환과 디버그모드 설정을 담당한다.
/// 
/// 2023.01.20 강석원 인재원
/// </summary>
class SceneManager : public Component
{
public:
	SceneManager(GameObject* object);

	virtual void Update() override;
};

