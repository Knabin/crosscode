#include "stdafx.h"
#include "bullet.h"
#include "tile.h"
#include "scene.h"

HRESULT bullet::init()
{
	_range = WINSIZEX;
	_alpha = 1.f;
	_isAlpha = false;

	_deleteBulletAngle = 0;

	SOUNDMANAGER->addSound("pS lcattack", "sounds/player/throw-ball-charged.ogg", false, false);

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
	collision();
}

void bullet::render()
{
	for (int i = 0; i < _vPlayerBullet.size(); i++)
	{
		_vPlayerBullet[i].image->frameRender(CAMERA->getRelativeVector2(_vPlayerBullet[i].rc.getCenter()), _vPlayerBullet[i].currentFrameX, _vPlayerBullet[i].currentFrameY);
		IMAGEMANAGER->addImage("player_bulletEffect", L"images/player/player_bulletEffect.png");
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
	SOUNDMANAGER->play("pS lcattack",0.5f);

	bullet.image = IMAGEMANAGER->addFrameImage("playerBullet", L"images/player/player_bullet.png", 4, 1);
	IMAGEMANAGER->addImage("player_bulletEffect", L"images/player/player_bulletEffect.png");
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.position.x = bullet.firePosition.x = x;
	bullet.position.y = bullet.firePosition.y = y;
	bullet.count = 0;
	bullet.currentFrameX = 0;
	bullet.currentFrameY = 0;
	bullet.rc.update(Vector2(0, 0), Vector2(48, 42), pivot::CENTER);
	bullet.rc.set(bullet.position, pivot::CENTER);
	bullet.nomal = false;

	POINT currentTileIndex = { x/ SIZE, y / SIZE };
	tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x];
	bullet.floor = ti->getOrderIndex();

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
	bullet.nomal = true;

	POINT currentTileIndex = { x / SIZE, y / SIZE };
	tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x];
	bullet.floor = ti->getOrderIndex();

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

void bullet::removeEffect(float x, float y)
{
	
	EFFECTMANAGER->play("player bulletRemoveEffect", CAMERA->getRelativeVector2(Vector2(x,y)), _deleteBulletAngle, 1);
}

void bullet::collision()
{
	for (int i = 0; i < _vPlayerBullet.size(); ++i)
	{
	
		POINT currentTileIndex = { _vPlayerBullet[i].position.x / SIZE, _vPlayerBullet[i].position.y / SIZE };
		
		_vPlayerBullet[i].next[0] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		_vPlayerBullet[i].next[1] = { currentTileIndex.x, currentTileIndex.y - 1 };
		_vPlayerBullet[i].next[2] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		_vPlayerBullet[i].next[3] = { currentTileIndex.x - 1, currentTileIndex.y };
		_vPlayerBullet[i].next[4] = { currentTileIndex.x + 1, currentTileIndex.y };
		_vPlayerBullet[i].next[5] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		_vPlayerBullet[i].next[6] = { currentTileIndex.x, currentTileIndex.y + 1 };
		_vPlayerBullet[i].next[7] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };

		int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
		int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

		for (int j = 0; j < 8; ++j)
		{
			if (_vPlayerBullet[i].next[j].x > maxTileX) _vPlayerBullet[i].next[j].x = maxTileX;
			else if (_vPlayerBullet[i].next[j].x < 0) _vPlayerBullet[i].next[j].x = 0;
			if (_vPlayerBullet[i].next[j].y > maxTileY) _vPlayerBullet[i].next[j].y = maxTileY;
			else if (_vPlayerBullet[i].next[j].y < 0) _vPlayerBullet[i].next[j].y = 0;
		}

		if (currentTileIndex.x >= maxTileX || currentTileIndex.x < 0)
		{
			_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
			break;
		}

		if (currentTileIndex.y >= maxTileY || currentTileIndex.y < 0)
		{
			_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
			break;
		}

		_vPlayerBullet[i]._nowOrder = SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex();

		RECT temp;

		for (int k = 0; k < 8; ++k)
		{
			tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[_vPlayerBullet[i].next[k].y][_vPlayerBullet[i].next[k].x];
			if (IntersectRect(&temp, &ti->getRect().getRect(), &_vPlayerBullet[i].rc.getRect()))
			{
				if (ti->getOrderIndex() > _vPlayerBullet[i]._nowOrder  && _vPlayerBullet[i].floor != 3)
				{
					if (_vPlayerBullet[i].nomal == true)
					{
						_deleteBulletAngle = getAngle(ti->getRect().getCenter().x, ti->getRect().getCenter().y,_vPlayerBullet[i].position.x, _vPlayerBullet[i].position.y) * 180 / PI;
						removeEffect((temp.right + temp.left) * 0.5f, (temp.top + temp.bottom) * 0.5f);
						_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
						break;
					}

					if (_vPlayerBullet[i].count >= 4)
					{
						_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
						break;
					}
					float d = getAngle(ti->getRect().getCenter().x, ti->getRect().getCenter().y, _vPlayerBullet[i].rc.getCenter().x, _vPlayerBullet[i].rc.getCenter().y);
					if ((d >= 0 && d < PI / 4) || (d >= PI + PI / 4 * 3 && d < PI2))
					{
						_vPlayerBullet[i].position.x = _vPlayerBullet[i].rc.right +10;
						_vPlayerBullet[i].angle -= PI;
					}
					else if (d >= PI / 4 && d < PI / 4 * 3)
					{
						_vPlayerBullet[i].angle = PI2 - _vPlayerBullet[i].angle;
						_vPlayerBullet[i].position.y = _vPlayerBullet[i].rc.top - 10;
					}
					else if (d >= PI + PI / 4 && d < PI2 - PI / 4)
					{
						_vPlayerBullet[i].angle = PI2 - _vPlayerBullet[i].angle;
						_vPlayerBullet[i].position.y = _vPlayerBullet[i].rc.bottom + 10;
					}
					else if ((d >= PI / 4 * 3 && d < PI + PI / 4))
					{
						_vPlayerBullet[i].position.x = _vPlayerBullet[i].rc.left - 10;
						_vPlayerBullet[i].angle -= PI;
					}

					_vPlayerBullet[i].count++;
					_vPlayerBullet[i].rc.set(_vPlayerBullet[i].position, pivot::CENTER);
					

					break;
				}
			}
			if (IntersectRect(&temp, &ti->getRect().getRect(), &_vPlayerBullet[i].rc.getRect()))
			{
				if (ti->getOrderIndex() > _vPlayerBullet[i]._nowOrder  && _vPlayerBullet[i].floor != 3)
				{
					if (_vPlayerBullet[i].nomal == true)
					{
						_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
						break;
					}

					if (_vPlayerBullet[i].count >= 4)
					{
						_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
						break;
					}
					float d = getAngle(ti->getRect().getCenter().x, ti->getRect().getCenter().y, _vPlayerBullet[i].rc.getCenter().x, _vPlayerBullet[i].rc.getCenter().y);
					if ((d >= 0 && d < PI / 4) || (d >= PI + PI / 4 * 3 && d < PI2))
					{
						_vPlayerBullet[i].position.x = _vPlayerBullet[i].rc.right +10;
						_vPlayerBullet[i].angle -= PI;
					}
					else if (d >= PI / 4 && d < PI / 4 * 3)
					{
						_vPlayerBullet[i].angle = PI2 - _vPlayerBullet[i].angle;
						_vPlayerBullet[i].position.y = _vPlayerBullet[i].rc.top - 10;
					}
					else if (d >= PI + PI / 4 && d < PI2 - PI / 4)
					{
						_vPlayerBullet[i].angle = PI2 - _vPlayerBullet[i].angle;
						_vPlayerBullet[i].position.y = _vPlayerBullet[i].rc.bottom + 10;
					}
					else if ((d >= PI / 4 * 3 && d < PI + PI / 4))
					{
						_vPlayerBullet[i].position.x = _vPlayerBullet[i].rc.left - 10;
						_vPlayerBullet[i].angle -= PI;
					}

					_vPlayerBullet[i].count++;
					_vPlayerBullet[i].rc.set(_vPlayerBullet[i].position, pivot::CENTER);
					

					break;
				}
				else if (ti->getOrderIndex() == 6  && _vPlayerBullet[i].floor == 3)
				{
					if (_vPlayerBullet[i].nomal == true)
					{
						_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
						break;
					}

					if (_vPlayerBullet[i].count >= 4)
					{
						_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
						break;
					}
					float d = getAngle(ti->getRect().getCenter().x, ti->getRect().getCenter().y, _vPlayerBullet[i].rc.getCenter().x, _vPlayerBullet[i].rc.getCenter().y);
					if ((d >= 0 && d < PI / 4) || (d >= PI + PI / 4 * 3 && d < PI2))
					{
						_vPlayerBullet[i].position.x = _vPlayerBullet[i].rc.right + 10;
						_vPlayerBullet[i].angle -= PI;
					}
					else if (d >= PI / 4 && d < PI / 4 * 3)
					{
						_vPlayerBullet[i].angle = PI2 - _vPlayerBullet[i].angle;
						_vPlayerBullet[i].position.y = _vPlayerBullet[i].rc.top - 10;
					}
					else if (d >= PI + PI / 4 && d < PI2 - PI / 4)
					{
						_vPlayerBullet[i].angle = PI2 - _vPlayerBullet[i].angle;
						_vPlayerBullet[i].position.y = _vPlayerBullet[i].rc.bottom + 10;
					}
					else if ((d >= PI / 4 * 3 && d < PI + PI / 4))
					{
						_vPlayerBullet[i].position.x = _vPlayerBullet[i].rc.left - 10;
						_vPlayerBullet[i].angle -= PI;
					}

					_vPlayerBullet[i].count++;
					_vPlayerBullet[i].rc.set(_vPlayerBullet[i].position, pivot::CENTER);


					break;
				}
			}
		}
	}	
}
