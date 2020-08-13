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

floatRect::floatRect(const float & x, const float & y, const float & width, const float & height, const pivot & pivot)
{
	*this = RectMakePivot(floatPoint(x, y), floatPoint(width, height), pivot);
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

floatPoint floatRect::getCenter()
{
	return floatPoint(left + (right - left) * 0.5f, top + (bottom - top) * 0.5f);
}

floatPoint floatRect::getSize()
{
	return floatPoint((right - left), (bottom - top));
}

void floatRect::set(const float & x, const float & y, const float & width, const float & height)
{
	left = x - width * 0.5f;
	top = y - height * 0.5f;
	right = left + width;
	bottom = top + height;
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

void floatRect::move(const float & moveX, const float & moveY)
{
	left += moveX;
	right += moveX;
	top += moveY;
	bottom += moveY;
}

const floatRect & floatRect::operator=(const RECT & rc)
{
	this->left = (float)rc.left;
	this->right = (float)rc.right;
	this->top = (float)rc.top;
	this->bottom = (float)rc.bottom;
	return *this;
}

const bool floatRect::operator==(const floatRect & rc)
{
	if (this->left == rc.left && this->right == rc.right &&
		this->top == rc.top && this->bottom == this->bottom) return true;
	return false;
}
