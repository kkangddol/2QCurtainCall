#include "AABB.h"

bool DetectAABB(float left1, float top1, float right1, float bottom1,
	float left2, float top2, float right2, float bottom2)
{
	if (top1 < bottom2)
	{
		if (bottom1 < top2)
		{
			return false;
		}
	}
	else if (top2 < bottom1)
	{
		if (bottom2 < top1)
		{
			return false;
		}
	}

	if (left1 < right2)
	{
		if (right1 < left2)
		{
			return false;
		}
	}
	else if (left2 < right1)
	{
		if (right2 < left1)
		{
			return false;
		}
	}

	return true;
}

