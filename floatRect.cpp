#include "stdafx.h"
#include "floatRect.h"


/**************************************************************************************************
## floatRect::floatRect ##
**************************************************************************************************/
floatRect::floatRect()
	:left(0.f), top(0.f), right(0.f), bottom(0.f) {}

floatRect::floatRect(const float& left, const float& top, const float& right, const float& bottom)
	: left(left), top(top), right(right), bottom(bottom) {}

floatRect::floatRect(const int& left, const int& top, const int& right, const int& bottom)
	: left((float)left), top((float)top), right((float)right), bottom((float)bottom) {}

floatRect::floatRect(const Vector2& pos, const Vector2& size, const pivot& pivot)
{
	*this = RectMakePivot(pos, size, pivot);
}

floatRect::floatRect(const RECT& rc)
	:left((float)rc.left), top((float)rc.top), right((float)rc.right), bottom((float)rc.bottom) {}

/**************************************************************************************************
## floatRect::getRect ##
@@ return RECT : LONG형 RECT로 변환 후 반환
**************************************************************************************************/
const RECT floatRect::getRect()
{
	return { (LONG)left,(LONG)top,(LONG)right,(LONG)bottom };
}
float floatRect::GetWidth()
{
	return right - left;
}
float floatRect::GetHeight()
{
	return bottom - top;
}
/**************************************************************************************************
## floatRect::getCenter ##
@@ return Vector2 : 중심 좌표
**************************************************************************************************/
Vector2 floatRect::getCenter()
{
	return Vector2(left + (right - left) / 2.f, top + (bottom - top) / 2.f);
}
Vector2 floatRect::GetBottom()
{
	return Vector2(left + (right - left) / 2.f, bottom);
}
Vector2 floatRect::getSize()
{
	return Vector2((right - left), (bottom - top));
}
/**************************************************************************************************
## floatRect::update ##
@@ Vector2 pos : 좌표
@@ Vector2 size : 사이즈
@@ Pivot pivot : 피봇

floatRect 정보 갱신
**************************************************************************************************/
void floatRect::update(const Vector2& pos, const Vector2& size, const pivot& pivot)
{
	*this = ::RectMakePivot(pos, size, pivot);
}
void floatRect::set(const Vector2 & pos, const pivot& pivot)
{
	*this = ::RectMakePivot(pos, Vector2(right - left, bottom - top), pivot);
}
/**************************************************************************************************
## floatRect::Move ##
@@ Vector2 moveValue : 이동방향 * 이동량
**************************************************************************************************/
void floatRect::Move(const Vector2& moveValue)
{
	left += moveValue.x;
	right += moveValue.x;
	top += moveValue.y;
	bottom += moveValue.y;
}

/**************************************************************************************************
## floatRect::operator = ##
@@ RECT rc : RECT
***************************************************************************************************/
const floatRect& ::floatRect::operator=(const RECT& rc)
{
	this->left = (float)rc.left;
	this->right = (float)rc.right;
	this->top = (float)rc.top;
	this->bottom = (float)rc.bottom;
	return *this;
}

