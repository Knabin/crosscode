#include "stdafx.h"
#include "mine.h"

mine::mine()
{
}

mine::~mine()
{
}

HRESULT mine::init(float centerX, float centerY)
{
	_angle = PI / 2;
	_centerMeter = 50;

	//Áö·Ú1ÁÂ
	_randomDropX = RND->getFromIntTo(-200, 400);
	_randomDropY = RND->getFromIntTo(-175, 175);

	//Áö·Ú1¿ì
	_randomDropX2 = RND->getFromIntTo(-400, 200);
	_randomDropY2 = RND->getFromIntTo(-150, 200);

	//Áö·Ú2ÁÂ
	_randomDropX3 = RND->getFromIntTo(-175, 425);
	_randomDropY3 = RND->getFromIntTo(-125, 225);

	//Áö·Ú2¿ì
	_randomDropX4 = RND->getFromIntTo(-425, 175);
	_randomDropY4 = RND->getFromIntTo(100, 250);

	//Áö·Ú3ÁÂ
	_randomDropX5 = RND->getFromIntTo(-150, 450);
	_randomDropY5 = RND->getFromIntTo(125, 275);

	//Áö·Ú3¿ì
	_randomDropX6 = RND->getFromIntTo(-450, 150);
	_randomDropY6 = RND->getFromIntTo(150, 300);

	IMAGEMANAGER->addImage("Áö·Ú", L"images/boss/mine.png");
	IMAGEMANAGER->addFrameImage("Æø¹ß", L"images/boss/explosion.png", 18, 1);

	_currentFrameX, _currentFrameY, _frameCount = 0;

	//================================================================================================================================================================//

	for (int i = 0; i < 3; i++)
	{
		tagMine _Mine;

		_Mine._center.x = centerX - 268 + (57 * i);
		_Mine._center.y = centerY  - (44 * i);
		_Mine._speed = 20.0f;

		_Mine._fireStart = false;

		_vMine.push_back(_Mine);
	}

	for (int i = 0; i < 3; i++)
	{
		tagMine _Mine2;

		_Mine2._center.x = centerX + 403 - (57 * i);
		_Mine2._center.y = centerY - (44 * i);
		_Mine2._speed = 20.0f;

		_Mine2._fireStart = false;

		_vMine2.push_back(_Mine2);
	}

	return S_OK;
}

void mine::release()
{
}

void mine::update()
{
	_frameCount++;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fire();
	}

	_explosionFrameY = 0;

	if (_frameCount % 4 == 0)
	{
		if (_currentFrameX >= IMAGEMANAGER->findImage("Æø¹ß")->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		_explosionFrameX = _currentFrameX;
		_currentFrameX++;
		_frameCount = 0;
	}

	move();

}

void mine::render(float centerX, float centerY)
{
	for (_viMine = _vMine.begin(); _viMine != _vMine.end(); ++_viMine)
	{
		if (!_viMine->_fireStart) continue;
		{
			//_viMine->_rc.render(getMemDC());

			IMAGEMANAGER->findImage("Áö·Ú")->render(CAMERA->getRelativeVector2(Vector2(_viMine->_x , _viMine->_y)));
		}

		if (_vMine.begin()->_fireStart && !(_vMine.begin() + 1)->_fireStart)
		{
			IMAGEMANAGER->findImage("Æø¹ß")->frameRender(CAMERA->getRelativeVector2(Vector2((centerX - 268) + 25, centerY - 45)),
				_explosionFrameX, _explosionFrameY);

		}

		if ((_vMine.begin() + 1)->_fireStart && !(_vMine.begin() + 2)->_fireStart)
		{
			IMAGEMANAGER->findImage("Æø¹ß")->frameRender(CAMERA->getRelativeVector2(Vector2((centerX - 211) + 25, (centerY - 44) - 35)),
				_explosionFrameX, _explosionFrameY);


		}

		if ((_vMine.begin() + 2)->_fireStart && (_vMine.begin() + 1)->_y < 100)
		{
			IMAGEMANAGER->findImage("Æø¹ß")->frameRender(CAMERA->getRelativeVector2(Vector2((centerX - 154) + 25 , (centerY - 88) - 35)),
				_explosionFrameX, _explosionFrameY);
		}

	}

	for (_viMine2 = _vMine2.begin(); _viMine2 != _vMine2.end(); ++_viMine2)
	{

		if (!_viMine2->_fireStart) continue;
		{
			//_viMine2->_rc.render(getMemDC());

			IMAGEMANAGER->findImage("Áö·Ú")->render(CAMERA->getRelativeVector2(Vector2(_viMine2->_x, _viMine2->_y)));
		}

		if (_vMine2.begin()->_fireStart && !(_vMine2.begin() + 1)->_fireStart)
		{
			IMAGEMANAGER->findImage("Æø¹ß")->frameRender(CAMERA->getRelativeVector2(Vector2((centerX + 403) + 25, centerY - 45)),
				_explosionFrameX, _explosionFrameY);
		}

		if ((_vMine2.begin() + 1)->_fireStart && !(_vMine2.begin() + 2)->_fireStart)
		{
			IMAGEMANAGER->findImage("Æø¹ß")->frameRender(CAMERA->getRelativeVector2(Vector2((centerX + 346) + 25, (centerY - 44) - 35)),
				_explosionFrameX, _explosionFrameY);
		}

		if ((_vMine2.begin() + 2)->_fireStart && (_vMine2.begin() + 1)->_y < 100)
		{
			IMAGEMANAGER->findImage("Æø¹ß")->frameRender(CAMERA->getRelativeVector2(Vector2((centerX + 289) + 25, (centerY - 88) - 35)),
				_explosionFrameX, _explosionFrameY);
		}
	}

}

void mine::fire()
{
	for (_viMine = _vMine.begin(); _viMine != _vMine.end(); ++_viMine)
	{
		if (_viMine->_fireStart) continue;
		{
			_currentFrameX = 0;
			_viMine->_fireStart = true;
			_viMine->_x = cosf(_angle) * _centerMeter + _viMine->_center.x;
			_viMine->_y = -sinf(_angle) * _centerMeter + _viMine->_center.y;
			_viMine->_angle = _angle;

			_viMine->_rc.update(Vector2(_viMine->_x, _viMine->_y), Vector2(42, 42), pivot::CENTER);

			break;
		}

	}

	for (_viMine2 = _vMine2.begin(); _viMine2 != _vMine2.end(); ++_viMine2)
	{
		if (_viMine2->_fireStart) continue;
		{
			_viMine2->_fireStart = true;
			_viMine2->_x = cosf(_angle) * _centerMeter + _viMine2->_center.x;
			_viMine2->_y = -sinf(_angle) * _centerMeter + _viMine2->_center.y;
			_viMine2->_angle = _angle;

			_viMine2->_rc.update(Vector2(_viMine2->_x, _viMine2->_y), Vector2(42, 42), pivot::CENTER);

			break;
		}
	}

}

void mine::move()
{
	for (_viMine = _vMine.begin(); _viMine != _vMine.end(); ++_viMine)
	{
		if (!_viMine->_fireStart) continue;
		{
			_viMine->_x += cosf(_viMine->_angle) * _viMine->_speed;
			_viMine->_y += -sinf(_viMine->_angle) * _viMine->_speed;

			_viMine->_rc.update(Vector2(_viMine->_x, _viMine->_y), Vector2(42, 42), pivot::CENTER);
		}
	}

	
	if (_vMine.begin()->_y < - 700)
	{
		_vMine.begin()->_angle = PI + (PI / 2);

		_vMine.begin()->_x += _randomDropX;

	}

	if ((_vMine.begin() + 1)->_y < - 700)
	{
		(_vMine.begin() + 1)->_angle = PI + (PI / 2);

		(_vMine.begin() + 1)->_x += _randomDropX3;
	}

	if ((_vMine.begin() + 2)->_y < - 700)
	{
		(_vMine.begin() + 2)->_angle = PI + (PI / 2);

		(_vMine.begin() + 2)->_x += _randomDropX5;
	}

	if (_vMine.begin()->_y > (WINSIZEY / 2 + 600) + _randomDropY)
	{
		_vMine.begin()->_speed = 0;
	}

	if ((_vMine.begin() + 1)->_y > (WINSIZEY / 2 + 600) + _randomDropY3)
	{
		(_vMine.begin() + 1)->_speed = 0;
	}

	if ((_vMine.begin() + 2)->_y > (WINSIZEY / 2 + 600) + _randomDropY5)
	{
		(_vMine.begin() + 2)->_speed = 0;
	}
	



	for (_viMine2 = _vMine2.begin(); _viMine2 != _vMine2.end(); ++_viMine2)
	{
		if (!_viMine2->_fireStart) continue;
		{
			_viMine2->_x += cosf(_viMine2->_angle) * _viMine2->_speed;
			_viMine2->_y += -sinf(_viMine2->_angle) * _viMine2->_speed;

			_viMine2->_rc.update(Vector2(_viMine2->_x, _viMine2->_y), Vector2(42, 42), pivot::CENTER);
		}
	}
	
	if (_vMine2.begin()->_y < - 700)
	{
		_vMine2.begin()->_angle = PI + (PI / 2);

		_vMine2.begin()->_x += _randomDropX2;
	}

	if ((_vMine2.begin() + 1)->_y < - 700)
	{
		(_vMine2.begin() + 1)->_angle = PI + (PI / 2);

		(_vMine2.begin() + 1)->_x += _randomDropX4;
	}

	if ((_vMine2.begin() + 2)->_y < - 700)
	{
		(_vMine2.begin() + 2)->_angle = PI + (PI / 2);

		(_vMine2.begin() + 2)->_x += _randomDropX6;
	}

	if (_vMine2.begin()->_y > (WINSIZEY / 2 + 600) + _randomDropY2)
	{
		_vMine2.begin()->_speed = 0;
	}

	if ((_vMine2.begin() + 1)->_y > (WINSIZEY / 2 + 600) + _randomDropY4)
	{
		(_vMine2.begin() + 1)->_speed = 0;
	}

	if ((_vMine2.begin() + 2)->_y > (WINSIZEY / 2 + 600) + _randomDropY4)
	{
		(_vMine2.begin() + 2)->_speed = 0;
	}
	
}
