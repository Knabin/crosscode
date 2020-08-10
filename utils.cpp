#include "stdafx.h"
#include "utils.h"

float UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float UTIL::getAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float distance = sqrtf(x * x + y * y);

	float angle = acosf(x / distance);

	if (y2 > y1)
	{
		angle = PI2 - angle;
		if (angle >= PI2) angle -= PI2;
	}

	return angle;
}

void UTIL::drawLine(HDC hdc, float startX, float startY, float endX, float endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}
