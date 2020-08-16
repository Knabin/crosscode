#include "stdafx.h"
#include "icethrower.h"

icethrower::icethrower()
{
}

icethrower::~icethrower()
{
}

HRESULT icethrower::init()
{

	_angle = PI2;
	_angle2 = PI2;
	_center.x = WINSIZEX / 2 + 125;
	_center.y = WINSIZEY / 2 + 600;
	_centerMeter = 150;
	_centerMeter2 = 150;

	_attackImage[0] = IMAGEMANAGER->addImage("얼음1", L"images/boss/ice1.png");
	_attackImage[1] = IMAGEMANAGER->addImage("얼음2", L"images/boss/ice2.png");
	_attackImage[2] = IMAGEMANAGER->addImage("얼음3", L"images/boss/ice3.png");
	_attackSize[0] = 84.0f;
	_attackSize[1] = 66.0f;
	_attackSize[2] = 45.0f;

	IMAGEMANAGER->addFrameImage("보스바텀방어막2", L"images/boss/bottom_second.png", 5, 1);

	IMAGEMANAGER->addFrameImage("얼음이펙트", L"images/boss/ice_move.png", 10, 1);
	IMAGEMANAGER->addFrameImage("얼음이펙트2", L"images/boss/ice_move.png", 10, 1);
	IMAGEMANAGER->addFrameImage("얼음이펙트3", L"images/boss/ice_move.png", 10, 1);

	_currentFrameX, _currentFrameY, _frameCount = 0;

	//================================================================================================================================================================//

	for (int i = 0; i < 21; i++)
	{
		tagIcethrower attack1;
		ZeroMemory(&attack1, sizeof(attack1));
		attack1._image = _attackImage[2];
		attack1._size = _attackSize[2];

		attack1._speed = 30.5f;

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
	_centerEnd.x = cosf(_angle) * _centerMeter + _center.x;
	_centerEnd.y = -sinf(_angle) * _centerMeter + _center.y;

	_centerEnd2.x = cosf(_angle) + _center.x;
	_centerEnd2.y = -sinf(_angle) + _center.y;

	_frameCount++;

	move();


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

}

void icethrower::render()
{
	/*
	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_center.x, _center.y))),
		(CAMERA->getRelativeVector2(Vector2(_centerEnd.x, _centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);
	*/

	for (_viIcethrower = _vIcethrower.begin(); _viIcethrower != _vIcethrower.end(); ++_viIcethrower)
	{
		if (!_viIcethrower->_fireStart) continue;
		{
			D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIcethrower->_rc));

			_viIcethrower->_image->setAngle(_angle);
			_viIcethrower->_image->render(CAMERA->getRelativeVector2(Vector2(_viIcethrower->_x - _viIcethrower->_size / 2, _viIcethrower->_y - _viIcethrower->_size / 2)));
			
		}
		
		if (_viIcethrower->_fireStart && _angle >= PI)
		{
			IMAGEMANAGER->findImage("얼음이펙트")->setAngle(_angle2);
			IMAGEMANAGER->findImage("얼음이펙트")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd.x, _centerEnd.y)),
				_iceEffectFrameX, _iceEffectFrameY);

			IMAGEMANAGER->findImage("얼음이펙트2")->setAngle(_angle2);
			IMAGEMANAGER->findImage("얼음이펙트2")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd.x - 50, _centerEnd.y - 50)),
				_iceEffectFrameX, _iceEffectFrameY);

			IMAGEMANAGER->findImage("얼음이펙트3")->setAngle(_angle2);
			IMAGEMANAGER->findImage("얼음이펙트3")->frameRender(CAMERA->getRelativeVector2(Vector2(_centerEnd.x + 50, _centerEnd.y + 50)),
				_iceEffectFrameX, _iceEffectFrameY);

		}
	}
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
			_angle -= 0.003f;
			_angle2 += 0.15f;
			_viIcethrower->_x += cosf(_viIcethrower->_angle) * _viIcethrower->_speed;
			_viIcethrower->_y += -sinf(_viIcethrower->_angle) * _viIcethrower->_speed;


			_viIcethrower->_x -= _viIcethrower->_speed / 4;
			_viIcethrower->_rc.update(Vector2(_viIcethrower->_x, _viIcethrower->_y), Vector2(_viIcethrower->_size, _viIcethrower->_size), pivot::CENTER);
		}

		if (_viIcethrower->_fireStart && _angle < PI / 2)
		{
			_viIcethrower->_fireStart = false;
		}
	}
}

void icethrower::removeFire(int Num1)
{
	_vIcethrower.erase(_vIcethrower.begin() + Num1);
}
