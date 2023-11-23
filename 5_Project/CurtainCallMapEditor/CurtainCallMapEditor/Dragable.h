#pragma once
#include "Component.h"
#include "Vector2D.h"

class GameObject;


/// <summary>
/// 드래그에 대한 처리를 할 클라이언트의 컴포넌트
/// 
/// 23.02.18 강석원 집
/// </summary>
class Dragable : public Component
{
public:
	Dragable(GameObject* obj);
	~Dragable();

	virtual void Update() override;

public:
	void StartDrag();
	void EndDrag();

private:
	void FollowMouse();
	void CheckDrag();

private:
	int order_;
	Vector2D size_;
	Vector2D offSet_;
	bool isDragging_;
};

