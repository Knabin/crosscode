#include "stdafx.h"
#include "gameObject.h"

gameObject::gameObject()
	: _name("No Name"), _x(WINSIZEX / 2), _y(WINSIZEY / 2), _width(32), _height(32), _pivot(pivot::CENTER), _isActive(true)
{
	_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
}

gameObject::gameObject(float x, float y)
	: _name("No Name"), _x(x), _y(y), _width(32), _height(32), _pivot(pivot::CENTER), _isActive(true)
{
	_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
}

gameObject::gameObject(const string & name, const float & x, const float & y, const float & width, const float & height, const pivot & pivot)
	: _name(name), _x(x), _y(y), _width(width), _height(height), _pivot(pivot), _isActive(true)
{
	_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
}

gameObject::~gameObject()
{
}
