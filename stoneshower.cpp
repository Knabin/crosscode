#include "stdafx.h"
#include "stoneshower.h"

stoneshower::stoneshower()
{
}

stoneshower::~stoneshower()
{
}

HRESULT stoneshower::init()
{
	
	IMAGEMANAGER->addImage("바위", L"images/boss/stone.png");
	IMAGEMANAGER->addFrameImage("먼지", L"images/boss/dust.png", 9, 1);

	_currentFrameX, _currentFrameY, _frameCount = 0;


	for (int i = 0; i < 5; i++)
	{
		tagStoneshower attack2;
		ZeroMemory(&attack2, sizeof(attack2));

		attack2._x = WINSIZEX / 2 + (i * 56);
		attack2._y = WINSIZEY / 2 + 1000;

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
				}
				_dustFrameX = _currentFrameX;
				_currentFrameX++;
				_frameCount = 0;
			}

		}
	}
}

void stoneshower::render(float centerX, float centerY)
{
	for (_viStoneshower = _vStoneshower.begin(); _viStoneshower != _vStoneshower.end(); ++_viStoneshower)
	{
		IMAGEMANAGER->findImage("바위")->render(CAMERA->getRelativeVector2(Vector2(_viStoneshower->_x, _viStoneshower->_y)));

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

void stoneshower::dustTrue(int Num2)
{
	_vDust[Num2]._fireStart = true;
}

void stoneshower::dustFalse(int Num3)
{
	_vDust[Num3]._fireStart = false;
}
