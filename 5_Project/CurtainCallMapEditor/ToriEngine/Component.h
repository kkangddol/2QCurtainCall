#pragma once

class GameObject;
class Collider;

/// <summary>
/// 컴포넌트 베이스 클래스
/// 생성할때 무조건 componentID_를 ComponentID enum 으로 초기화 해줘야한다.
/// 
/// 22.12.21 강석원 인재원
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



