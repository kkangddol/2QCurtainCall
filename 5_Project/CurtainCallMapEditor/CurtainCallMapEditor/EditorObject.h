#pragma once
#include <string>
#include "Component.h"
#include "Vector2D.h"

class GameObject;

/// <summary>
/// 배치한 오브젝트의 정보를 저장하는 컴포넌트
/// 
/// 23.02.19 강석원 집
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
	int objectID;				// 트리거 또는 리액턴트의 이름(종류)
	int triggerID;				// 이 녀석과 연결된 트리거
	int reactantID;				// 이 녀석과 연결된 리액턴트
	int index;					// 각각의 고유 ID
	int linkedIndex;			// 이 녀석과 연결된 오브젝트 ID
	GameObject* linkedObject;	// 이 녀석과 연결된 오브젝트의 주소 (호버링 시 같이 깜빡이기 위해?)

private:
	Vector2D size_;
};
