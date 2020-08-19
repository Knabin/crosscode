#include "stdafx.h"
#include "flamethrower.h"

flamethrower::flamethrower()
{
}

flamethrower::~flamethrower()
{
}

HRESULT flamethrower::init()
{
	IMAGEMANAGER->addFrameImage("面傈", L"images/boss/charge.png", 14, 1);
	IMAGEMANAGER->addFrameImage("面傈2", L"images/boss/charge2.png", 8, 1);

	_chargeCurrentFrameX, _chargeCurrentFrameY, _chargeFrameCount = 0;
	_chargeCurrentFrameX2, _chargeCurrentFrameY2, _chargeFrameCount2 = 0;

	return S_OK;
}

void flamethrower::release()
{
}

void flamethrower::update()
{
	frameUpdate();
}

void flamethrower::render()
{
}

void flamethrower::angleUpdate()
{
}

void flamethrower::frameUpdate()
{
	_chargeFrameCount++;
	_chargeFrameCount2++;

	_chargeFrameY = 0;

	if (_chargeFrameCount % 4 == 0)
	{
		if (_chargeCurrentFrameX >= IMAGEMANAGER->findImage("面傈")->getMaxFrameX())
		{
			_chargeCurrentFrameX = 0;
		}
		_chargeFrameX = _chargeCurrentFrameX;
		_chargeCurrentFrameX++;
		_chargeFrameCount = 0;
	}

	_chargeFrameY2 = 0;

	if (_chargeFrameCount2 % 12 == 0)
	{
		if (_chargeCurrentFrameX2 >= IMAGEMANAGER->findImage("面傈2")->getMaxFrameX())
		{
			_chargeCurrentFrameX2 = 0;
		}
		_chargeFrameX2 = _chargeCurrentFrameX2;
		_chargeCurrentFrameX2++;
		_chargeFrameCount2 = 0;
	}

}

void flamethrower::fire()
{
}

void flamethrower::move()
{
}

void flamethrower::chargeDraw(float centerX, float centerY)
{
	IMAGEMANAGER->findImage("面傈")->frameRender(CAMERA->getRelativeVector2(Vector2(centerX, centerY)),
		_chargeFrameX, _chargeFrameY);

}

void flamethrower::chargeDraw2(float centerX, float centerY)
{
	IMAGEMANAGER->findImage("面傈2")->frameRender(CAMERA->getRelativeVector2(Vector2(centerX, centerY)),
		_chargeFrameX2, _chargeFrameY2);
}
