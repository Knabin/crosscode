#include "stdafx.h"
#include "floatPoint.h"

floatPoint::floatPoint()
	: x(0.0f), y(0.0f)
{
}

floatPoint::floatPoint(const float & x, const float & y)
	: x(x), y(y)
{
}

floatPoint::floatPoint(const int & x, const int & y)
	: x((float)x), y((float)y)
{
}

floatPoint::floatPoint(const vector2 & vector)
	: x(vector.x), y(vector.y)
{
}

void floatPoint::move(const float & dx, const float & dy)
{
	x += dx;
	y += dy;
}

void floatPoint::move(const vector2 & moveValue)
{
	x += moveValue.x;
	y += moveValue.y;
}
