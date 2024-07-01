#pragma once
#include "Component.h"
#include "Vector2D.h"

class GameObject;


/// <summary>
/// �巡�׿� ���� ó���� �� Ŭ���̾�Ʈ�� ������Ʈ
/// 
/// 23.02.18 ������ ��
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

