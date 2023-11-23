#include "stdafx.h"



RaycastResponse Physics::Raycast(vector2 from, vector2 to, std::string tag)
{
	RaycastResponse result;
	result.hit = false;
	result.hit = false;
	vector2 v = { to.x - from.x,to.y - from.y };
	int count = abs(v.x) > abs(v.y) ? abs(v.x) : abs(v.y);
	int checkCount = 0;
	from.x = (float)round(from.x);
	from.y = (float)round(from.y);
	vector2 d = { v.x / count,v.y / count };
	for (auto collider : *(CollisionSystem::Instance()->colliderList))
	{
		vector2 objectV = { collider->transform->position.x - from.x,collider->transform->position.y - from.y };
		float objectRange = max(collider->GetBounds().x, collider->GetBounds().y);
		if (collider->gameObject->isEnabled && collider->CompareTag(tag) && vector2::Dot(v, objectV) >= 0 && vector2::Length(v) >= vector2::Length(objectV) - objectRange)
		{
			for (int k = 0; k < count; k++)
			{
				vector2 check = { from.x + d.x * k, from.y + d.y * k };
				if (collider->InBound(check))
				{
					result.tag = *(collider->gameObject->tag);
					result.position = check;
					result.hit = true;
					return result;
				}
			}
		}
	}
	return result;
}

RaycastResponse Physics::Raycast(vector2 from, vector2 to, std::vector<std::string> tags)
{
	RaycastResponse result;
	result.hit = false;
	result.hit = false;
	vector2 v = { to.x - from.x,to.y - from.y };
	int count = abs(v.x) > abs(v.y) ? abs(v.x) : abs(v.y);
	int checkCount = 0;
	from.x = (float)round(from.x);
	from.y = (float)round(from.y);
	vector2 d = { v.x / count,v.y / count };
	for (auto collider : *(CollisionSystem::Instance()->colliderList))
	{
		vector2 objectV = { collider->transform->position.x - from.x,collider->transform->position.y - from.y };
		float objectRange = max(collider->GetBounds().x, collider->GetBounds().y);
		if (collider->gameObject->isEnabled && collider->CompareTags(tags) && vector2::Dot(v, objectV) >= 0 && vector2::Length(v) >= vector2::Length(objectV) - objectRange)
		{
			for (int k = 0; k < count; k++)
			{
				vector2 check = { from.x + d.x * k, from.y + d.y * k };
				if (collider->InBound(check))
				{
					result.tag = *(collider->gameObject->tag);
					result.position = check;
					result.hit = true;
					return result;
				}
			}
		}
	}
	return result;
}