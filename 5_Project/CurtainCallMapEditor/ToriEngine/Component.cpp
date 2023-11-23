#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* obj)
	:object_(obj), isEnable_(true)
{

}

void Component::SetObject(GameObject* object)
{
	object_ = object;
}

GameObject* Component::GetObj() const
{
	return object_;
}
