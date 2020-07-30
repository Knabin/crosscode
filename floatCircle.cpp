#include "stdafx.h"
#include "floatCircle.h"

floatCircle::floatCircle()
	: x(0.0f), y(0.0f), r(0.0f)
{
}

floatCircle::floatCircle(const float & x, const float & y, const float & r)
	: x(x), y(y), r(r)
{
}

floatCircle::floatCircle(const int & x, const int & y, const int & r)
	: x(x), y(y), r(r)
{
}

floatCircle::floatCircle(const POINT & p, const int & r)
	: x(p.x), y(p.y), r(r)
{
}

floatCircle::floatCircle(const floatPoint & p, const float & r)
	: x(p.x), y(p.y), r(r)
{
}

void floatCircle::move(float dx, float dy)
{
	x += dx;
	y += dy;
}

void floatCircle::set(float centerX, float centerY, float radius)
{
	x = centerX;
	y = centerY;
	r = radius;
}

void floatCircle::setCenterPos(float centerX, float centerY)
{
	x = centerX;
	y = centerY;
}
