#include "stdafx.h"
#include "iceguide.h"

iceguide::iceguide()
{
}

iceguide::~iceguide()
{
}

HRESULT iceguide::init(float centerX, float centerY)
{
	IMAGEMANAGER->addImage("ªœ¡∑æÛ¿Ω", L"images/boss/cold2.png");

	_angle = PI / 2 + (PI2);
	_angle2 = PI / 2;
	_center.x = centerX;
	_center.y = centerY;
	_centerMeter = 10;

	_meterCount = 0;

	//================================================================================================================================================================//

	for (int i = 0; i < 7; i++)
	{
		tagIceguide attack4;
		ZeroMemory(&attack4, sizeof(attack4));
		attack4._speed = 15.5f;
		attack4._size = 170.0f;

		attack4._frameX = 0, attack4._frameCount, attack4._currentFrameX = 0;

		attack4._fireStart = false;

		_vIceguide.push_back(attack4);

		_vIceguide2.push_back(attack4);

		_vIceguide3.push_back(attack4);
	}

	

	return S_OK;
}

void iceguide::release()
{
}

void iceguide::update()
{
	move();

	angleUpdate();

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		fire();
		
	}

}

void iceguide::render()
{
	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_center.x, _center.y))),
		(CAMERA->getRelativeVector2(Vector2(_centerEnd.x, _centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);

	for (_viIceguide = _vIceguide.begin(); _viIceguide != _vIceguide.end(); ++_viIceguide)
	{
		if (!_viIceguide->_fireStart) continue;
		{
			D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIceguide->_rc));

			IMAGEMANAGER->findImage("ªœ¡∑æÛ¿Ω")->render(CAMERA->getRelativeVector2(Vector2(_viIceguide->_x - _viIceguide->_size / 2, _viIceguide->_y - _viIceguide->_size / 2)));
		}		
	}
}

void iceguide::fire()
{
	for (_viIceguide = _vIceguide.begin(); _viIceguide != _vIceguide.end(); ++_viIceguide)
	{		
		if (_viIceguide->_fireStart) continue;
		{
			_meterCount++;

			_viIceguide->_fireStart = true;

			_viIceguide->_x = cosf(_angle) * _centerMeter + _center.x + (50 * _meterCount);
			_viIceguide->_y = -sinf(_angle) * _centerMeter + _center.y + (50 * _meterCount);

			_viIceguide->_angle = _angle;

			_viIceguide->_rc.update(Vector2(_viIceguide->_x, _viIceguide->_y), Vector2(_viIceguide->_size, _viIceguide->_size), pivot::CENTER);

			break;
		}			
	}
}

void iceguide::move()
{
	for (_viIceguide = _vIceguide.begin(); _viIceguide != _vIceguide.end(); ++_viIceguide)
	{
		if (_viIceguide->_fireStart) continue;
		{
			
			_viIceguide->_x += cosf(_viIceguide->_angle) * _viIceguide->_speed;
			_viIceguide->_y += -sinf(_viIceguide->_angle) * _viIceguide->_speed;

			_viIceguide->_rc.update(Vector2(_viIceguide->_x, _viIceguide->_y), Vector2(_viIceguide->_size, _viIceguide->_size), pivot::CENTER);

		}
	}
}

void iceguide::angleUpdate()
{
	_centerEnd.x = cosf(_angle) * _centerMeter + _center.x;
	_centerEnd.y = -sinf(_angle) * _centerMeter + _center.y;
	
}
