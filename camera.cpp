#include <cmath>
#include "stdafx.h"
#include "camera.h"
#include "gameObject.h"


camera::camera()
	//: _cameraInfo(NULL)
	: _state(CAMERASTATE::TARGET), _position(0.0f, 0.0f)
{
}

camera::~camera()
{
}


void camera::update()
{
	switch (_state)
	{
	case camera::CAMERASTATE::TARGET:
		break;
	case camera::CAMERASTATE::MOUSE:
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

float camera::lerpX(float deltaTime)
{
	//return _x + (_target->getX() - _x) * deltaTime;
	return 0.0f;
}

float camera::lerpY(float deltaTime)
{
	return 0.0f;
}

void camera::changeTarget(gameObject * gameObject)
{
}

//
//bool camera::checkCameraX()
//{
//	if (_cameraInfo->x - _cameraInfo->width / 2 <= 0 ||
//		_cameraInfo->x + _cameraInfo->width / 2 >= _cameraInfo->backWidth)
//		return false;
//	return true;
//}
//
//bool camera::checkCameraY()
//{
//	if (_cameraInfo->y - _cameraInfo->height / 2 <= 0 ||
//		_cameraInfo->y + _cameraInfo->height / 2 >= _cameraInfo->backHeight)
//		return false;
//	return true;
//}
//
//
//void camera::cameraShake()
//{
//	_isShaking = true;
//	_shakeAmount = 2.0f;
//	_shakeCount = 0;
//}
//
//void camera::shakeStart()
//{
//	if (_isShaking)
//	{
//		++_shakeCount;
//		if (_shakeCount > 10)
//		{
//			_shakeCount = 0;
//			_shakeAmount = 0;
//			_isShaking = false;
//		}
//		else
//		{
//			_flag *= -1;
//		}
//	}
//
//}
//
//void camera::cameraFixed(float x, float y)
//{
//}
//
//void camera::FixedStart()
//{
//}
//
//void camera::changePosition(float x, float y)
//{
//	int d = getDistance(x, y, _cameraInfo->x, _cameraInfo->y);
//	float angle = getAngle(_cameraInfo->x, _cameraInfo->y, x, y);
//
//	if (d > 50)
//	{
//		_cameraInfo->x += cosf(angle) * 5;
//		_cameraInfo->y -= sinf(angle) * 5;
//	}
//}