#pragma once
#include "Component.h"

class GameObject;

/// <summary>
/// Ŭ���̾�Ʈ�� SceneManager
/// Scene ��ȯ�� ����׸�� ������ ����Ѵ�.
/// 
/// 2023.01.20 ������ �����
/// </summary>
class SceneManager : public Component
{
public:
	SceneManager(GameObject* object);

	virtual void Update() override;
};

