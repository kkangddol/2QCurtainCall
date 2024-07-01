#include "CC.h"

bool DetectCC(float x1, float y1, float radius1,
	float x2, float y2, float radius2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dr = radius1 + radius2;

	return dx * dx + dy * dy <= dr * dr;
}
