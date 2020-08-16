#include "stdafx.h"
#include "gameObject.h"

gameObject::gameObject()
	: _name("No Name"), _position(WINSIZEX / 2, WINSIZEY / 2), _width(32), _height(32), _pivot(pivot::CENTER), _isActive(true), _isAlive(true)
{
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
}

gameObject::gameObject(float x, float y)
	: _name("No Name"), _position(x, y), _width(32), _height(32), _pivot(pivot::CENTER), _isActive(true), _isAlive(true)
{
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
}

gameObject::gameObject(Vector2 position)
	: _name("No Name"), _position(position), _width(32), _height(32), _pivot(pivot::CENTER), _isActive(true), _isAlive(true)
{
}

gameObject::gameObject(const string & name, const float & x, const float & y, const float & width, const float & height, const pivot & pivot)
	: _name(name), _position(x, y), _width(width), _height(height), _pivot(pivot), _isActive(true), _isAlive(true)
{
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
}

gameObject::~gameObject()
{
}
