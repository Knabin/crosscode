#include <cmath>
#include "stdafx.h"
#include "camera.h"
#include "gameObject.h"

camera::camera()
	: _state(CAMERASTATE::NONE), _position(0.0f, 0.0f)
{
	_mapWidth = WINSIZEX;
	_mapHeight = WINSIZEY;
	_width = WINSIZEX;
	_height = WINSIZEY;
	_isZoom = false;
}

camera::~camera()
{
}


void camera::update()
{
	switch (_state)
	{
	case CAMERASTATE::NONE:
		_rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
		break;
	case CAMERASTATE::TARGET:
		if (_isShake) 
			updateShake(); 
		else 
			moveToTargetSmooth();
		break;
	case CAMERASTATE::END:
		break;
	default:
		break;
	}

	updateZoom();
}

void camera::release()
{

}

void camera::moveToTarget()
{
	if (_target == NULL) return;
	
	/*floatPoint position = _position;
	float length = getDistance(_target->getPosition().x, _target->getPosition().y, _position.x, _position.y);
	float angle = getAngle(_position.x, _position.y, _target->getPosition().x, _target->getPosition().y);
	if (length > 5.f)
	{
		_speed = 200;
		position.x += cosf(angle) * _speed * TIMEMANAGER->getElapsedTime();
		position.y -= sinf(angle) * _speed * TIMEMANAGER->getElapsedTime();
	}*/
	_position = _target->getPosition();
	//_position = position;
	_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX, WINSIZEY);

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

void camera::moveToTargetSmooth()
{
	if (_target == NULL) return;

	floatPoint position = _position;
	float length = getDistance(_target->getPosition().x, _target->getPosition().y, _position.x, _position.y);
	float angle = getAngle(_position.x, _position.y, _target->getPosition().x, _target->getPosition().y);
	if (length > 4.5f)
	{
		_speed = 5;
		position.x += cosf(angle) * _speed;
		position.y -= sinf(angle) * _speed;
	}
	else
	{
		position = _target->getPosition();
	}
	//_position = _target->getPosition();
	_position = position;
	_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX, WINSIZEY);

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

void camera::updateShake()
{
	if (_isShake)
	{
		_shakeTime -= TIMEMANAGER->getElapsedTime();
		_shakeDirectionChangeTime -= TIMEMANAGER->getElapsedTime();

		if (_shakeDirectionChangeTime < 0.f)
		{
			_shakeFlag *= -1;
			_shakeDirectionChangeTime = 0.03f;
		}
		_position.x += _shakeAmount * _shakeFlag;


		if (_shakeTime <= 0.f)
		{
			_isShake = false;
		}


		_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX, WINSIZEY);

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
}

void camera::updateZoom()
{
	if (_isZoom)
	{
		_zoomTime -= TIMEMANAGER->getElapsedTime();
		if (_zoomTime <= 0.0f)
			_isZoom = false;
	}
}

void camera::zoom(HDC hdc)
{
	if (!_isZoom) return;

	_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX, WINSIZEY);

	float width = (float)WINSIZEX / _zoomAmount;
	float height = (float)WINSIZEY / _zoomAmount;

	float zoomL = _rc.left + (WINSIZEX - width) * 0.5f;
	float zoomT = _rc.top + (WINSIZEY - height) * 0.5f;

	StretchBlt(hdc, 0, 0, WINSIZEX, WINSIZEY,
		hdc, zoomL, zoomT, width, height, SRCCOPY);
}

void camera::changeTarget(gameObject* gameObject)
{
	_target = gameObject;
	_state = CAMERASTATE::TARGET;
}

void camera::shakeStart(float amount, float time)
{
	_shakeAmount = amount;
	_shakeTime = time;
	_shakeDirectionChangeTime = 0.03f;
	_shakeFlag = 1;
	_isShake = true;
}

void camera::zoomStart(float amount, float time)
{
	_zoomAmount = amount;
	_zoomTime = time;
	_isZoom = true;
}
