#include <cmath>
#include "stdafx.h"
#include "camera.h"
#include "gameObject.h"

camera::camera()
	: _state(CAMERASTATE::NONE), _position(0.0f, 0.0f), _mapSize(Vector2(WINSIZEX, WINSIZEY)),
	_width(WINSIZEX), _height(WINSIZEY), _isZoom(false), _nowZoomAmount(1.0f)
{
}

camera::~camera()
{
}


void camera::update()
{
	switch (_state)
	{
	case CAMERASTATE::NONE:
		moveToTarget();
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
	updateFade();
}

void camera::release()
{

}

void camera::moveToTarget()
{
	if (_target == NULL) return;

	_position = _target->getPosition();

	updateRect();
	checkRect();
}

void camera::moveToTargetSmooth()
{
	if (_target == NULL) return;

	Vector2 position = _position;
	float length = getDistance(_target->getPosition().x, _target->getPosition().y, _position.x, _position.y);
	float angle = getAngle(_position.x, _position.y, _target->getPosition().x, _target->getPosition().y);
	if (length > 4.5f)
	{
		_speed = 9.0f;
		position.x += cosf(angle) * _speed;
		position.y -= sinf(angle) * _speed;
	}
	else
	{
		position = _target->getPosition();
	}

	_position = position;
	updateRect();
	checkRect();
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
		_position.y = _target->getPosition().y;


		if (_shakeTime <= 0.f)
		{
			_isShake = false;
		}

		updateRect();
		checkRect();
	}
}

void camera::updateZoom()
{
	if (_isZoom)
	{
		if (_zoomTime > 0.0f)
		{
			_zoomTime -= TIMEMANAGER->getElapsedTime();

			if (_nowZoomAmount >= _zoomAmount) _nowZoomAmount = _zoomAmount;
			else _nowZoomAmount += 0.01f;
			_position = _target->getPosition();
		}
		else
		{
			if (_isZoomOutSmooth)
			{
				_nowZoomAmount -= 0.01f;
				if (_nowZoomAmount <= 1.0f)
				{
					_nowZoomAmount = 1.0f;
					_isZoomOutSmooth = false;
				}
			}
			else
				_isZoom = false;
			_position = _target->getPosition();
		}
		updateRect();
		checkRect();
	}
}

void camera::checkRect()
{
	if (_rc.left < 0.0f)
		_position.x -= (float)_rc.left;
	else if (_rc.right > _mapSize.x)
		_position.x -= (float)_rc.right - _mapSize.x;

	if (_rc.top < 0.0f)
		_position.y -= (float)_rc.top;
	else if (_rc.bottom > _mapSize.y)
		_position.y -= (float)_rc.bottom - _mapSize.y;
	
	updateRect();
}

void camera::updateRect()
{
	_rc = RectMakeCenter(_position.x, _position.y, WINSIZEX / _nowZoomAmount, WINSIZEY / _nowZoomAmount);
}

void camera::updateFade()
{
	if (_isFade)
	{
		if (_fadeTime > 0.0f)
		{
			_fadeTime -= TIMEMANAGER->getElapsedTime();
			
			if (_nowFadeAmount >= _fadeAmount)
				_nowFadeAmount = _fadeAmount;
			else _nowFadeAmount += 0.02f;
		}
		else
		{
			_nowFadeAmount -= 0.05f;
			if (_nowFadeAmount <= 0.0f)
				_isFade = false;
		}
	}
}

void camera::changeTarget(gameObject* gameObject)
{
	_target = gameObject;
}

void camera::shakeStart(float amount, float time)
{
	_shakeAmount = amount;
	_shakeTime = time;
	_shakeDirectionChangeTime = 0.05f;
	_shakeFlag = 1;
	_isShake = true;
}

void camera::zoomStart(float amount, float time, bool isZoomOutSmooth)
{
	_nowZoomAmount = 1.0f;
	_zoomAmount = amount;
	_zoomTime = time;
	_isZoom = true;
	_isZoomOutSmooth = isZoomOutSmooth;
}

void camera::fadeStart(float amount, float time)
{
	_nowFadeAmount = 0.0f;
	_fadeAmount = 1.0f;
	_fadeTime = time;
	_isFade = true;
}

RECT camera::getRelativeRect(RECT rc)
{
	rc.left -= _rc.left;
	rc.top -= _rc.top;
	rc.right -= _rc.left;
	rc.bottom -= _rc.top;

	rc.left *= _nowZoomAmount;
	rc.top *= _nowZoomAmount;
	rc.right *= _nowZoomAmount;
	rc.bottom *= _nowZoomAmount;

	return rc;
}

floatRect camera::getRelativeRect(floatRect rc)
{
	rc.left -= _rc.left;
	rc.top -= _rc.top;
	rc.right -= _rc.left;
	rc.bottom -= _rc.top;

	rc.left *= _nowZoomAmount;
	rc.top *= _nowZoomAmount;
	rc.right *= _nowZoomAmount;
	rc.bottom *= _nowZoomAmount;

	return rc;
}

Vector2 camera::getRelativeVector2(Vector2 vector)
{
	vector.x -= _rc.left;
	vector.y -= _rc.top;
	vector = vector * _nowZoomAmount;

	return vector;
}

Vector2 camera::getRelativeVector2(float x, float y)
{
	Vector2 v = Vector2(x - _rc.left, y - _rc.top) * _nowZoomAmount;
	return v;
}
