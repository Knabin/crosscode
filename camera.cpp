#include <cmath>
#include "stdafx.h"
#include "camera.h"
#include "gameObject.h"


camera::camera()
	: _state(CAMERASTATE::NONE), _position(0.0f, 0.0f)
{
	_mapWidth = WINSIZEX;
	_mapHeight = WINSIZEY;
}

camera::~camera()
{
}


void camera::update()
{
	switch (_state)
	{
	case camera::CAMERASTATE::TARGET:
		moveToTarget();
		break;
	case camera::CAMERASTATE::END:
		break;
	default:
		break;
	}
}

void camera::release()
{

}

void camera::moveToTarget()
{
	if (_target == NULL) return;
	
	floatPoint position = _position;
	float length = getDistance(_target->getPosition().x, _target->getPosition().y, _position.x, _position.y);
	float angle = getAngle(_position.x, _position.y, _target->getPosition().x, _target->getPosition().y);
	if (length > 50.0f)
	{
		// TODO: 카메라 선형 보간 필요
		_speed = 300.0f;
		position.x += cosf(angle) * _speed * TIMEMANAGER->getElapsedTime();
		position.y -= sinf(angle) * _speed * TIMEMANAGER->getElapsedTime();

		_position = position;
		_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX, WINSIZEY);
	}
	else
	{
		_position = position;
		_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX, WINSIZEY);
	}

	if (_rc.left < 0.0f)
		_position.x -= _rc.left;
	else if (_rc.right > _mapWidth)
		_position.x -= _rc.right - _mapWidth;
	
	if (_rc.top < 0.0f)
		_position.y -= _rc.top;
	else if (_rc.bottom > _mapHeight)
		_position.y -= _rc.bottom - _mapHeight;

	_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX, WINSIZEY);
}

void camera::changeTarget(gameObject* gameObject)
{
	_target = gameObject;
	_state = CAMERASTATE::TARGET;
}