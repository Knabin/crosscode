#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init()
{
	_range = WINSIZEX;
	_alpha = 1.f;
	_isAlpha = false;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	if (_isAlpha == false)
	{
		_alpha -= 0.1f;
	}
	else
	{
		_alpha += 0.1f;
	}

	if (_alpha < 0)
	{
		_isAlpha = true;
	}
	else if (_alpha > 0.5)
	{
		_isAlpha = false;
	}

	move();
}

void bullet::render()
{
	for (int i = 0; i < _vPlayerBullet.size(); i++)
	{
		_vPlayerBullet[i].image->frameRender(CAMERA->getRelativeVector2(_vPlayerBullet[i].rc.getCenter()), _vPlayerBullet[i].currentFrameX, _vPlayerBullet[i].currentFrameY);
		IMAGEMANAGER->findImage("player_bulletEffect")->setAlpha(_alpha);
		IMAGEMANAGER->findImage("player_bulletEffect")->render(CAMERA->getRelativeVector2(_vPlayerBullet[i].rc.getCenter().x - 24, _vPlayerBullet[i].rc.getCenter().y - 23));

		_vPlayerBullet[i].count++;
		if (_vPlayerBullet[i].count % 5 == 0)
		{
			_vPlayerBullet[i].currentFrameX++;
			if (_vPlayerBullet[i].currentFrameX >= _vPlayerBullet[i].image->getMaxFrameX())
			{
				_vPlayerBullet[i].currentFrameX = 0;
			}
			_vPlayerBullet[i].count = 0;
		}
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	tagPlayerBullet bullet;
	ZeroMemory(&bullet, sizeof(tagPlayerBullet));

	bullet.image = IMAGEMANAGER->addFrameImage("playerBullet", L"images/player/player_bullet.png", 4, 1);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.position.x = bullet.firePosition.x = x;
	bullet.position.y = bullet.firePosition.y = y;
	bullet.count = 0;
	bullet.currentFrameX = 0;
	bullet.currentFrameY = 0;
	bullet.rc.update(Vector2(0, 0), Vector2(48, 42), pivot::CENTER);
	bullet.rc.set(bullet.position, pivot::CENTER);

	_vPlayerBullet.push_back(bullet);
}

void bullet::nomalFire(float x, float y, float angle, float speed)
{
	tagPlayerBullet bullet;
	ZeroMemory(&bullet, sizeof(tagPlayerBullet));

	bullet.image = IMAGEMANAGER->addImage("player_nomalbullet", L"images/player/player_nomal_bullet.png");
	IMAGEMANAGER->addImage("player_bulletEffect", L"images/player/player_bulletEffect.png");
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.position.x = bullet.firePosition.x = x;
	bullet.position.y = bullet.firePosition.y = y;
	bullet.count = 0;
	bullet.currentFrameX = 0;
	bullet.currentFrameY = 0;
	bullet.rc.update(Vector2(0, 0), Vector2(24, 24), pivot::CENTER);
	bullet.rc.set(bullet.position, pivot::CENTER);

	_vPlayerBullet.push_back(bullet);
}

void bullet::move()
{
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); )
	{
		_viPlayerBullet->position.x += cosf(_viPlayerBullet->angle) * _viPlayerBullet->speed;
		_viPlayerBullet->position.y += -sinf(_viPlayerBullet->angle) * _viPlayerBullet->speed;

		_viPlayerBullet->rc.set(_viPlayerBullet->position, pivot::CENTER);

		if (_range < getDistance(_viPlayerBullet->position.x, _viPlayerBullet->position.y,
			_viPlayerBullet->firePosition.x, _viPlayerBullet->firePosition.y))
		{
			_viPlayerBullet = _vPlayerBullet.erase(_viPlayerBullet);
		}
		else ++_viPlayerBullet;
	}
}

void bullet::remove(int arrNum)
{
	_vPlayerBullet.erase(_vPlayerBullet.begin() + arrNum);
}
