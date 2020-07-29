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
