#pragma once

class GameObject;
class Collider;

/// <summary>
/// ������Ʈ ���̽� Ŭ����
/// �����Ҷ� ������ componentID_�� ComponentID enum ���� �ʱ�ȭ ������Ѵ�.
/// 
/// 22.12.21 ������ �����
/// </summary>
class Component
{
public:
	Component(GameObject* obj);
	virtual ~Component() {}

	virtual void Update() {}

	virtual void OnCollisionEnter(Collider* other) {}
	virtual void OnCollisionStay(Collider* other) {}
	virtual void OnCollisionExit(Collider* other) {}

	void Enable()
	{
		isEnable_ = true;
	}

	void Disable()
	{
		isEnable_ = false;
	}

	void SetObject(GameObject* object);
	GameObject* GetObj() const;

protected:
	GameObject* object_;
	bool isEnable_;
};



