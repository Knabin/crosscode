#include "stdafx.h"
#include "floatRect.h"

floatRect::floatRect()
	: left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) 
{
}

floatRect::floatRect(const float & left, const float & top, const float & right, const float & bottom)
	: left(left), top(top), right(right), bottom(bottom) 
{
}

floatRect::floatRect(const int & left, const int & top, const int & right, const int & bottom)
	: left((float)left), top((float)top), right((float)right), bottom((float)bottom) 
{
}

floatRect::floatRect(const vector2 & position, const vector2 & size, const pivot & pivot)
{
	*this = RectMakePivot(position, size, pivot);
}

floatRect::floatRect(const RECT & rc)
	: left((float)rc.left), top((float)rc.top), right((float)rc.right), bottom((float)rc.bottom)
{
}

const RECT floatRect::getRect()
{
	return { (LONG)left, (LONG)top, (LONG)right, (LONG)bottom };
}

float floatRect::getWidth()
{
	return right - left;
}

float floatRect::getHeight()
{
	return bottom - top;
}

vector2 floatRect::getCenter()
{
	return vector2(left + (right - left) * 0.5f, top + (bottom - top) * 0.5f);
}

float floatRect::getCenterX()
{
	return left + (right - left) * 0.5f;
}

float floatRect::getCenterY()
{
	return top + (bottom - top) * 0.5f;
}

vector2 floatRect::getBottom()
{
	return vector2(left + (right - left) * 0.5f, bottom);
}

vector2 floatRect::getSize()
{
	return vector2((right - left), (bottom - top));
}

void floatRect::setLeftTop(float _left, float _top)
{
	float w = getWidth();
	float h = getHeight();

	left = _left;
	top = _top;
	right = _left + w;
	bottom = _top + h;
}

void floatRect::setCenter(float centerX, float centerY)
{
	float w = getWidth() * 0.5f;
	float h = getHeight() * 0.5f;

	left = centerX - w;
	top = centerY - h;
	right = centerX + w;
	bottom = centerY + h;
}

void floatRect::update(const vector2 & position, const vector2 & size, const pivot & pivot)
{
	*this = RectMakePivot(position, size, pivot);
}

void floatRect::move(const vector2 & moveValue)
{
	left += moveValue.x;
	right += moveValue.x;
	top += moveValue.y;
	bottom += moveValue.y;
}

void floatRect::move(const float & dx, const float & dy)
{
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}

const floatRect & floatRect::operator=(const RECT & rc)
{
	this->left = (float)rc.left;
	this->right = (float)rc.right;
	this->top = (float)rc.top;
	this->bottom = (float)rc.bottom;
	return *this;
}
