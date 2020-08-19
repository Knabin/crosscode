#include "stdafx.h"
#include "flamethrower.h"

flamethrower::flamethrower()
{
}

flamethrower::~flamethrower()
{
}

HRESULT flamethrower::init(float centerX, float centerY)
{
	IMAGEMANAGER->addFrameImage("ÃæÀü", L"images/boss/charge.png", 14, 1);
	IMAGEMANAGER->addFrameImage("ÃæÀü2", L"images/boss/charge2.png", 8, 1);
	IMAGEMANAGER->addFrameImage("È­¿°Æø¹ß", L"images/boss/fire_explosion.png", 12, 1);
	IMAGEMANAGER->addFrameImage("È­¿°", L"images/boss/fire_explosion.png", 12, 1);
	

	_chargeCurrentFrameX, _chargeCurrentFrameY, _chargeFrameCount = 0;
	_chargeCurrentFrameX2, _chargeCurrentFrameY2, _chargeFrameCount2 = 0;
	_firePointCurrentFrameX, _firePointCurrentFrameY, _firePointFrameCount = 0;
	_currentFrameX, _currentFrameY, _frameCount = 0;

	_angle = PI;
	_angle2 = PI;
	_center.x = centerX;
	_center.y = centerY;
	_centerMeter = 150;
	_centerMeter2 = 50;

	_angleCount = 20;

	//================================================================================================================================================================//

	for (int i = 0; i < 99; i++)
	{
		tagFlamethrower attack3;
		ZeroMemory(&attack3, sizeof(attack3));

		attack3._speed = 20.0f;

		attack3._size = 64.0f;


		attack3._fireStart = false;

		_vFlamethrower.push_back(attack3);
	}


	for (int i = 0; i < 7; i++)
	{
		tagFlamethrower effect;
		ZeroMemory(&effect, sizeof(effect));
		effect._speed = 0.001f;
		

		effect._fireStart = false;

		_vFlameEffect.push_back(effect);
	}


	return S_OK;
}

void flamethrower::release()
{
}

void flamethrower::update()
{
	angleUpdate();

	frameUpdate();

	move();

}

void flamethrower::render()
{
	/*
	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_center.x, _center.y))),
		(CAMERA->getRelativeVector2(Vector2(_centerEnd.x, _centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);
	*/
	for (_viFlamethrower = _vFlamethrower.begin(); _viFlamethrower != _vFlamethrower.end(); ++_viFlamethrower)
	{
		if (!_viFlamethrower->_fireStart) continue;
		{

			D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viFlamethrower->_rc));
			IMAGEMANAGER->findImage("È­¿°")->frameRender(CAMERA->getRelativeVector2(Vector2(_viFlamethrower->_x, _viFlamethrower->_y)),
				_flameFrameX, _flameFrameY);
			
		}
	}

	for (_viFlameEffect = _vFlameEffect.begin(); _viFlameEffect != _vFlameEffect.end(); ++_viFlameEffect)
	{
		if (!_viFlameEffect->_fireStart) continue;
		{

			IMAGEMANAGER->findImage("È­¿°Æø¹ß")->frameRender(CAMERA->getRelativeVector2(Vector2(_viFlameEffect->_x, _viFlameEffect->_y)),
				_firePointFrameX, _firePointFrameY);
		}
	}
}

void flamethrower::angleUpdate()
{
	_centerEnd.x = cosf(_angle) * _centerMeter + _center.x;
	_centerEnd.y = -sinf(_angle) * _centerMeter + _center.y;

	_centerEnd2.x = cosf(_angle2) * _centerMeter2 + _center.x;
	_centerEnd2.y = -sinf(_angle2) * _centerMeter2 + _center.y;

	_angleCount++;

	if (_angleCount < 130)
	{
		_angle += 0.312f / 3;
	}
	if (_angleCount >= 130 && _angleCount < 140)
	{
		_angle -= 0.256f / 3;
	}
	if (_angleCount >= 140 && _angleCount < 150)
	{
		_angle += 0.306f / 3;
	}
	if (_angleCount >= 150 && _angleCount < 160)
	{
		_angle -= 0.251f / 3;
	}
	if (_angleCount >= 160 && _angleCount < 170)
	{
		_angleCount = 120;
	}

}

void flamethrower::frameUpdate()
{
	_chargeFrameCount++;
	_chargeFrameCount2++;
	_firePointFrameCount++;
	_frameCount++;

	_chargeFrameY = 0;

	if (_chargeFrameCount % 4 == 0)
	{
		if (_chargeCurrentFrameX >= IMAGEMANAGER->findImage("ÃæÀü")->getMaxFrameX())
		{
			_chargeCurrentFrameX = 0;
		}
		_chargeFrameX = _chargeCurrentFrameX;
		_chargeCurrentFrameX++;
		_chargeFrameCount = 0;
	}

	_chargeFrameY2 = 0;

	if (_chargeFrameCount2 % 13 == 0)
	{
		if (_chargeCurrentFrameX2 >= IMAGEMANAGER->findImage("ÃæÀü2")->getMaxFrameX())
		{
			_chargeCurrentFrameX2 = 0;
		}
		_chargeFrameX2 = _chargeCurrentFrameX2;
		_chargeCurrentFrameX2++;
		_chargeFrameCount2 = 0;
	}

	for (int i = 0; i < _vFlameEffect.size(); ++i)
	{
		_firePointFrameY = 0;

		if (_firePointFrameCount % 7 == 0) 
		{
			if (_firePointCurrentFrameX >= IMAGEMANAGER->findImage("È­¿°Æø¹ß")->getMaxFrameX())
			{
				
				//(_vFlameEffect.begin() + i)->_fireStart = false;
				_firePointCurrentFrameX = 0;
				
			}
			_firePointFrameX = _firePointCurrentFrameX;
			_firePointCurrentFrameX++;
			_firePointFrameCount = 0;

			return;
		}

	}

	for (int i = 0; i < _vFlamethrower.size(); ++i)
	{
		_flameFrameY = 0;

		if (_frameCount % 3 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("È­¿°")->getMaxFrameX())
			{
				_currentFrameX = 0;

			}
			_flameFrameX = _currentFrameX;
			_currentFrameX++;
			_frameCount = 0;

			return;
		}

	}


}

void flamethrower::fire()
{
	for (_viFlamethrower = _vFlamethrower.begin(); _viFlamethrower != _vFlamethrower.end(); ++_viFlamethrower)
	{
		if (_viFlamethrower->_fireStart) continue;
		{
			_viFlamethrower->_fireStart = true;

			_viFlamethrower->_x = cosf(_angle) * _centerMeter + _center.x;
			_viFlamethrower->_y = -sinf(_angle) * _centerMeter + _center.y;

			_viFlamethrower->_angle = _angle;

			_viFlamethrower->_rc.update(Vector2(_viFlamethrower->_x, _viFlamethrower->_y), Vector2(_viFlamethrower->_size, _viFlamethrower->_size), pivot::CENTER);

			break;
		}
	}

	
	for (_viFlameEffect = _vFlameEffect.begin(); _viFlameEffect != _vFlameEffect.end(); ++_viFlameEffect)
	{
		if (_viFlameEffect->_fireStart) continue;
		{
			_viFlameEffect->_fireStart = true;

			_viFlameEffect->_x = cosf(_angle2) * _centerMeter2 + _center.x;
			_viFlameEffect->_y = -sinf(_angle2) * _centerMeter2 + _center.y;

			_viFlameEffect->_angle = _angle2;

			_viFlameEffect->_rc.update(Vector2(_viFlameEffect->_x, _viFlameEffect->_y), Vector2(_viFlameEffect->_size, _viFlameEffect->_size), pivot::CENTER);

			break;
		}
	}
	
}

void flamethrower::move()
{
	for (_viFlamethrower = _vFlamethrower.begin(); _viFlamethrower != _vFlamethrower.end(); ++_viFlamethrower)
	{
		if (!_viFlamethrower->_fireStart) continue;
		{

			_viFlamethrower->_x += cosf(_viFlamethrower->_angle)  * _viFlamethrower->_speed;
			_viFlamethrower->_y += -sinf(_viFlamethrower->_angle) * _viFlamethrower->_speed;

			//_viFlamethrower->_x += _viFlamethrower->_speed;

			_viFlamethrower->_rc.update(Vector2(_viFlamethrower->_x, _viFlamethrower->_y), Vector2(_viFlamethrower->_size, _viFlamethrower->_size), pivot::CENTER);


		}
	}


	for (_viFlameEffect = _vFlameEffect.begin(); _viFlameEffect != _vFlameEffect.end(); ++_viFlameEffect)
	{
		if (!_viFlameEffect->_fireStart) continue;
		{

			_angle2 += 1.01f;

			_viFlameEffect->_x += cosf(_viFlameEffect->_angle)  * _viFlameEffect->_speed;
			_viFlameEffect->_y += -sinf(_viFlameEffect->_angle) * _viFlameEffect->_speed;

			_viFlameEffect->_x += _viFlameEffect->_speed;


			_viFlameEffect->_rc.update(Vector2(_viFlameEffect->_x, _viFlameEffect->_y), Vector2(_viFlameEffect->_size, _viFlameEffect->_size), pivot::CENTER);
			//_viFlameEffect->_x -= _viFlameEffect->_speed / 4;

		}
	}
}

void flamethrower::chargeDraw(float centerX, float centerY)
{
	IMAGEMANAGER->findImage("ÃæÀü")->frameRender(CAMERA->getRelativeVector2(Vector2(centerX, centerY)),
		_chargeFrameX, _chargeFrameY);

}

void flamethrower::chargeDraw2(float centerX, float centerY)
{
	IMAGEMANAGER->findImage("ÃæÀü2")->frameRender(CAMERA->getRelativeVector2(Vector2(centerX, centerY)),
		_chargeFrameX2, _chargeFrameY2);
}

void flamethrower::fireEffectDraw()
{
	IMAGEMANAGER->findImage("È­¿°")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd2.x + 250, _centerEnd2.y)),
		_firePointFrameX, _firePointFrameY);

}
