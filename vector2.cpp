#include "stdafx.h"
#include "vector2.h"

vector2::vector2()
	: x(0.0f), y(0.0f)
{
}

vector2::vector2(const float & x, const float & y)
	: x(x), y(y)
{
}

vector2::vector2(const int & x, const int & y)
	: x(static_cast<float>(x)), y(static_cast<float>(y))
{
}

vector2::vector2(const POINT & point)
	: x(static_cast<float>(point.x)), y(static_cast<float>(point.y))
{
}

const int vector2::getIntX()
{
	return FLOAT_TO_INT(this->x);
}

const int vector2::getIntY()
{
	return FLOAT_TO_INT(this->y);
}

const POINT vector2::getPoint()
{
	return { (LONG)x, (LONG)y };
}

vector2 vector2::operator+(const vector2 & v)
{
	vector2 result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	return result;
}

vector2 vector2::operator-(const vector2 & v)
{
	vector2 result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	return result;
}

void vector2::operator+=(const vector2 & v)
{
	this->x += v.x;
	this->y += v.y;
}

void vector2::operator-=(const vector2 & v)
{
	this->x -= v.x;
	this->y -= v.y;
}

vector2 vector2::operator*(const float & scalar)
{
	vector2 result;
	result.x = this->x * scalar;
	result.y = this->y * scalar;
	return result;
}

vector2 vector2::operator/(const float & scalar)
{
	vector2 result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;
	return result;
}

const bool vector2::operator==(const vector2 & v)
{
	if (FLOAT_EQUAL(this->x, v.x))
	{
		if (FLOAT_EQUAL(this->y, v.y))
			return true;
	}
	return false;
}

const bool vector2::operator!=(const vector2 & v)
{
	return !((*this) == v);
}

// return normalized vector2
vector2 vector2::normalize(const vector2 * const pVector2)
{
	vector2 result = *pVector2;

	float length = sqrtf(result.x * result.x + result.y * result.y);
	result.x /= length;
	result.y /= length;

	return result;
}

// vector2 to radian
float vector2::toRadian(const vector2 * const pVector2)
{
	int sign = 1;
	vector2 dir = *pVector2;
	dir = vector2::normalize(&dir);
	float result = (acos(dir.x));
	if (dir.y > 0.0f)
	{
		result = PI2 - result;
	}
	return result;
}

// size of vector2
float vector2::length(const vector2 * const pVector2)
{
	return sqrt(pVector2->x * pVector2->x + pVector2->y * pVector2->y);
}

float vector2::dot(const vector2 * const pVector2A, const vector2 * const pVector2B)
{
	return  pVector2A->x * pVector2B->x + pVector2A->y * pVector2B->y;
}

float vector2::cross(const vector2 * const pVector2A, const vector2 * const pVector2B)
{
	return pVector2A->x * pVector2B->y - pVector2A->y * pVector2B->x;
}
