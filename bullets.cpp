#include "stdafx.h"
#include "bullets.h"

HRESULT bullets::init()
{
	_range = WINSIZEX;

	return S_OK;
}

void bullets::release()
{
}

void bullets::update()
{
	move();
}

void bullets::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_vBullet[i].rc));
		_vBullet[i].image->frameRender(CAMERA->getRelativeVector2(_vBullet[i].rc.getCenter()), _vBullet[i].currentFrameX, _vBullet[i].currentFrameY);

		_vBullet[i].count++;
		if (_vBullet[i].count % 5 == 0)
		{
			_vBullet[i].currentFrameX++;
			if (_vBullet[i].currentFrameX >= _vBullet[i].image->getMaxFrameX())
			{
				_vBullet[i].currentFrameX = 0;
			}
			_vBullet[i].count = 0;
		}
	}
}

void bullets::fire(float x, float y, float angle, float speed)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.image = IMAGEMANAGER->addFrameImage("enemyBullet", L"images/enemy/meerkatBall.png", 4, 1);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.position.x = bullet.firePosition.x = x;
	bullet.position.y = bullet.firePosition.y = y;
	bullet.count = 0;
	bullet.currentFrameX = 0;
	bullet.currentFrameY = 0;
	bullet.rc.update(Vector2(bullet.position.x, bullet.position.y), Vector2(50, 50), pivot::CENTER);
	bullet.rc.set(bullet.position, pivot::CENTER);

	_vBullet.push_back(bullet);
}

void bullets::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->position.x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->position.y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc.set(_viBullet->position, pivot::CENTER);

		if (_range < getDistance(_viBullet->position.x, _viBullet->position.y, 
			_viBullet->firePosition.x, _viBullet->firePosition.y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bullets::remove(int num)
{
	_vBullet.erase(_vBullet.begin() + num);
}
