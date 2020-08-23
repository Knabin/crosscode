#include "stdafx.h"
#include "stoneshower.h"

stoneshower::stoneshower()
{
}

stoneshower::~stoneshower()
{
}

HRESULT stoneshower::init(float centerX, float centerY)
{
	
	_name = "stoneshower";

	_angle = PI / 2 + (PI);
	_centerMeter = 50;


	IMAGEMANAGER->addImage("바위", L"images/boss/stone.png");

	_currentFrameX, _currentFrameY, _frameCount = 0;


	for (int i = 0; i < 19; i++)
	{
		tagStoneshower attack2;
		ZeroMemory(&attack2, sizeof(attack2));

		attack2._size = 72.0f;
		attack2._damage = 10.0f;

		attack2._center.x = centerX;
		attack2._center.y = centerY;


		attack2._speed = 15.5f;

		attack2._fireStart = false;

		_vStoneshower.push_back(attack2);

	}

	
	for (int i = 0; i < 8; i++)
	{
		tagStoneshower dust;
		ZeroMemory(&dust, sizeof(dust));

		dust._image = IMAGEMANAGER->addFrameImage("먼지", L"images/boss/dust.png", 9, 1);

		dust._fireStart = false;
		

		_vDust.push_back(dust);

	}
	


	return S_OK;
}

void stoneshower::release()
{

}

void stoneshower::update()
{

	frameUpdate();
	
	move();

}

void stoneshower::render()
{

	for (_viStoneshower = _vStoneshower.begin(); _viStoneshower != _vStoneshower.end(); ++_viStoneshower)
	{
		if (!_viStoneshower->_fireStart) continue;
		{
			//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viStoneshower->_rc));

			IMAGEMANAGER->findImage("바위")->render(CAMERA->getRelativeVector2(Vector2(_viStoneshower->_x - _viStoneshower->_size / 2, _viStoneshower->_y - _viStoneshower->_size / 2)));
		}

	}

}

void stoneshower::dustDraw(float centerX, float centerY)
{
	for (_viDust = _vDust.begin(); _viDust != _vDust.end(); ++_viDust)
	{
		if (_viDust->_fireStart == true)
		{
			_vDust.begin()->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX + 125, centerY)),
				_dustFrameX, _dustFrameY);

			(_vDust.begin() + 1)->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX - 125, centerY)),
				_dustFrameX, _dustFrameY);

			(_vDust.begin() + 2)->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX, centerY - 125)),
				_dustFrameX, _dustFrameY);

			(_vDust.begin() + 3)->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX, centerY + 125)),
				_dustFrameX, _dustFrameY);

			(_vDust.begin() + 4)->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX + 50, centerY - 50)),
				_dustFrameX, _dustFrameY);

			(_vDust.begin() + 5)->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX + 50, centerY + 50)),
				_dustFrameX, _dustFrameY);

			(_vDust.begin() + 6)->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX - 50, centerY - 50)),
				_dustFrameX, _dustFrameY);

			(_vDust.begin() + 7)->_image->frameRender(CAMERA->getRelativeVector2(Vector2(centerX - 50, centerY + 50)),
				_dustFrameX, _dustFrameY);
		}

	}

}

void stoneshower::frameUpdate()
{
	_frameCount++;

	for (_viDust = _vDust.begin(); _viDust != _vDust.end(); ++_viDust)
	{
		if (_viDust->_fireStart == true)
		{
			_dustFrameY = 0;

			if (_frameCount % 5 == 0)
			{
				if (_currentFrameX >= IMAGEMANAGER->findImage("먼지")->getMaxFrameX())
				{
					_currentFrameX = 0;
					_viDust->_fireStart = false;
				}
				_dustFrameX = _currentFrameX;
				_currentFrameX++;
				_frameCount = 0;
			}
		}
	}
}

void stoneshower::fire()
{
	for (_viStoneshower = _vStoneshower.begin(); _viStoneshower != _vStoneshower.end(); ++_viStoneshower)
	{
		if (_viStoneshower->_fireStart) continue;
		{

			_viStoneshower->_fireStart = true;

			int _randomFire;
			_randomFire = RND->getFromIntTo(-500, 500);



			_viStoneshower->_x = cosf(_angle) * _centerMeter + _viStoneshower->_center.x + _randomFire;
			_viStoneshower->_y = -sinf(_angle) * _centerMeter + _viStoneshower->_center.y;

			_viStoneshower->_angle = _angle;

			_viStoneshower->_rc.update(Vector2(_viStoneshower->_x, _viStoneshower->_y), Vector2(_viStoneshower->_size, _viStoneshower->_size), pivot::CENTER);

			break;

		}

	}

}

void stoneshower::move()
{
	for (_viStoneshower = _vStoneshower.begin(); _viStoneshower != _vStoneshower.end(); ++_viStoneshower)
	{
		if (!_viStoneshower->_fireStart) continue;
		{
			
			_viStoneshower->_x += cosf(_viStoneshower->_angle) * _viStoneshower->_speed;
			_viStoneshower->_y += -sinf(_viStoneshower->_angle) * _viStoneshower->_speed;

			_viStoneshower->_y += _viStoneshower->_speed;

			_viStoneshower->_rc.update(Vector2(_viStoneshower->_x, _viStoneshower->_y), Vector2(_viStoneshower->_size, _viStoneshower->_size), pivot::CENTER);
			
		}
	}
}

void stoneshower::dustTrue(int Num2)
{
	_vDust[Num2]._fireStart = true;
}

void stoneshower::dustFalse(int Num3)
{
	_vDust[Num3]._fireStart = false;
}

void stoneshower::removeFire(int Num4)
{
	_vStoneshower.erase(_vStoneshower.begin() + Num4);
}
