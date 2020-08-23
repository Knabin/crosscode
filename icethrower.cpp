#include "stdafx.h"
#include "icethrower.h"

icethrower::icethrower()
{
}

icethrower::~icethrower()
{
}

HRESULT icethrower::init(float centerX, float centerY)
{
	_name = "icethrower";

	_angle = PI2;
	_angle2 = PI2;
	_center.x = centerX;
	_center.y = centerY;
	_centerMeter = 150;
	_centerMeter2 = 150;
	_angleCount = 0;

	_attackImage[0] = IMAGEMANAGER->addImage("얼음1", L"images/boss/ice1.png");
	_attackImage[1] = IMAGEMANAGER->addImage("얼음2", L"images/boss/ice2.png");
	_attackImage[2] = IMAGEMANAGER->addImage("얼음3", L"images/boss/ice3.png");
	_attackSize[0] = 84.0f;
	_attackSize[1] = 66.0f;
	_attackSize[2] = 45.0f;

	IMAGEMANAGER->addFrameImage("얼음이펙트", L"images/boss/ice_move.png", 10, 1);
	IMAGEMANAGER->addFrameImage("얼음이펙트2", L"images/boss/ice_move.png", 10, 1);
	IMAGEMANAGER->addFrameImage("얼음이펙트3", L"images/boss/ice_move.png", 10, 1);

	//IMAGEMANAGER->addFrameImage("얼음충돌", L"images/boss/ice_collision.png", 10, 1);

	_currentFrameX, _currentFrameY, _frameCount = 0;
	//_collisionCurrentFrameX, _collisionCurrentFrameY, _collisionFrameCount = 0;

	//================================================================================================================================================================//

	
	for (int i = 0; i < 45; i++)
	{
		tagIcethrower attack1;
		ZeroMemory(&attack1, sizeof(attack1));
		attack1._image = _attackImage[2];
		attack1._size = _attackSize[2];

		attack1._speed = 32.5f;
		attack1._damage = 5.0f;

		attack1._fireStart = false;

		_vIcethrower.push_back(attack1);
	}
	

	//================================================================================================================================================================//

	return S_OK;
}

void icethrower::release()
{

}

void icethrower::update()
{
	//angleUpdate();

	move();

	frameUpdate();
}

void icethrower::render()
{
	/*  발사 선
	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_center.x, _center.y))),
		(CAMERA->getRelativeVector2(Vector2(_centerEnd.x, _centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);
	*/

	//IMAGEMANAGER->findImage("얼음충돌")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd.x + 150, _centerEnd.y + 550)), _collisionFrameX, _collisionFrameY);


	for (_viIcethrower = _vIcethrower.begin(); _viIcethrower != _vIcethrower.end(); ++_viIcethrower)
	{
		if (!_viIcethrower->_fireStart) continue;
		{
			//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIcethrower->_rc));

			_viIcethrower->_image->setAngle(_angle);
			_viIcethrower->_image->render(CAMERA->getRelativeVector2(Vector2(_viIcethrower->_x - _viIcethrower->_size / 2, _viIcethrower->_y - _viIcethrower->_size / 2)));
			
		}
		
		/*
		if (!_viIcethrower->_fireStart) continue;
		{
			IMAGEMANAGER->findImage("얼음이펙트")->setAngle(_angle2);
			IMAGEMANAGER->findImage("얼음이펙트")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd.x + 200, _centerEnd.y)),
				_iceEffectFrameX, _iceEffectFrameY);

			IMAGEMANAGER->findImage("얼음이펙트2")->setAngle(_angle2);
			IMAGEMANAGER->findImage("얼음이펙트2")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd.x + 150, _centerEnd.y - 50)),
				_iceEffectFrameX, _iceEffectFrameY);

			IMAGEMANAGER->findImage("얼음이펙트3")->setAngle(_angle2);
			IMAGEMANAGER->findImage("얼음이펙트3")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd.x + 250, _centerEnd.y + 50)),
				_iceEffectFrameX, _iceEffectFrameY);

			//IMAGEMANAGER->findImage("얼음충돌")->frameRender(CAMERA->getRelativeVector2(Vector2(_viIcethrower->_x, _viIcethrower->_y)), _collisionFrameX, _collisionFrameY);
			
		}

	*/

	}
}

void icethrower::angleUpdate()
{
	_centerEnd.x = cosf(_angle) * _centerMeter + _center.x;
	_centerEnd.y = -sinf(_angle) * _centerMeter + _center.y;

	_centerEnd2.x = cosf(_angle) + _center.x;
	_centerEnd2.y = -sinf(_angle) + _center.y;

	_angleCount++;

	if (_angleCount < 10)
	{
		_angle += 0.312f / 8;
	}
	if (_angleCount >= 10 && _angleCount < 20)
	{
		_angle -= 0.256f / 8;
	}
	if (_angleCount >= 20 && _angleCount < 30)
	{
		_angle += 0.206f / 8;
	}
	if (_angleCount >= 30 && _angleCount < 40)
	{
		_angle -= 0.251f / 8;
	}
	if (_angleCount >= 40 && _angleCount < 50)
	{
		_angleCount = 0;
	}
}

void icethrower::frameUpdate()
{
	_frameCount++;
	//_collisionFrameCount++;

	/*
	_iceEffectFrameY = 0;

	if (_frameCount % 5 == 0)
	{
		if (_currentFrameX >= IMAGEMANAGER->findImage("얼음이펙트")->getMaxFrameX() ||
			_currentFrameX >= IMAGEMANAGER->findImage("얼음이펙트2")->getMaxFrameX() ||
			_currentFrameX >= IMAGEMANAGER->findImage("얼음이펙트3")->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		_iceEffectFrameX = _currentFrameX;
		_currentFrameX++;
		_frameCount = 0;
	}
	*/
	/*
	_collisionFrameY = 0;

	if (_collisionFrameCount % 5 == 0)
	{
		if (_collisionCurrentFrameX >= IMAGEMANAGER->findImage("얼음충돌")->getMaxFrameX())
		{
			_collisionCurrentFrameX = 0;
		}
		_collisionFrameX = _collisionCurrentFrameX;
		_collisionCurrentFrameX++;
		_collisionFrameCount = 0;
	}
	*/
}

void icethrower::fire()
{
	for (_viIcethrower = _vIcethrower.begin(); _viIcethrower != _vIcethrower.end(); ++_viIcethrower)
	{
		if (_viIcethrower->_fireStart) continue;
		{
			int _randomNumber;
			_randomNumber = RND->getInt(3);

			_viIcethrower->_image = _attackImage[_randomNumber];
			_viIcethrower->_size = _attackSize[_randomNumber];

			_viIcethrower->_fireStart = true;
			
			_viIcethrower->_x = cosf(_angle) * _centerMeter + _center.x;
			_viIcethrower->_y = -sinf(_angle) * _centerMeter + _center.y;

			_viIcethrower->_angle = _angle;

			_viIcethrower->_rc.update(Vector2(_viIcethrower->_x, _viIcethrower->_y), Vector2(_viIcethrower->_size, _viIcethrower->_size), pivot::CENTER);
			
			break;
		}
	}
}

void icethrower::move()
{
	for (_viIcethrower = _vIcethrower.begin(); _viIcethrower != _vIcethrower.end(); ++_viIcethrower)
	{

		if (!_viIcethrower->_fireStart) continue;
		{
			_angle -= 0.002f * 1.8f;
			_angle2 += 0.10f / 2;
			_viIcethrower->_x += cosf(_viIcethrower->_angle) * _viIcethrower->_speed;
			_viIcethrower->_y += -sinf(_viIcethrower->_angle) * _viIcethrower->_speed;

			_viIcethrower->_rc.update(Vector2(_viIcethrower->_x, _viIcethrower->_y), Vector2(_viIcethrower->_size, _viIcethrower->_size), pivot::CENTER);
		}
		
	}
}

void icethrower::removeFire(int Num1)
{
	_vIcethrower.erase(_vIcethrower.begin() + Num1);
}
