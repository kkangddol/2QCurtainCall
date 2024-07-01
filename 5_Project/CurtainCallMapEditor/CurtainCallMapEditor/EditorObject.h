#pragma once
#include <string>
#include "Component.h"
#include "Vector2D.h"

class GameObject;

/// <summary>
/// ��ġ�� ������Ʈ�� ������ �����ϴ� ������Ʈ
/// 
/// 23.02.19 ������ ��
/// </summary>
class EditorObject : public Component
{
public:
	EditorObject(GameObject* obj);

	virtual void Update() override;

public:
	void CheckRightClick();
	EditorObject* GetLinkedComponent();

private:
	void HighLight(bool callLinked);

public:
	int objectID;				// Ʈ���� �Ǵ� ������Ʈ�� �̸�(����)
	int triggerID;				// �� �༮�� ����� Ʈ����
	int reactantID;				// �� �༮�� ����� ������Ʈ
	int index;					// ������ ���� ID
	int linkedIndex;			// �� �༮�� ����� ������Ʈ ID
	GameObject* linkedObject;	// �� �༮�� ����� ������Ʈ�� �ּ� (ȣ���� �� ���� �����̱� ����?)

private:
	Vector2D size_;
};
