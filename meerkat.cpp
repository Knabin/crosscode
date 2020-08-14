#include "stdafx.h"
#include "meerkat.h"
#include "scene.h"

HRESULT meerkat::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyMeerkat", "images/enemy/meerkat.bmp", 960, 1440, 10, 12, true, RGB(255, 0, 255));//기본, 히트, 공격모션 이미지
	_meerkatMoveImage = IMAGEMANAGER->addFrameImage("enemyMeerkatMove", "images/enemy/meerkatMove.bmp", 576, 65, 9, 1, true, RGB(255, 0, 255));//무브 이미지

	_maxHP = 100;
	_currentHP = _maxHP;

	_speed = 5.0f;
	
	_attackPower = RND->getFromIntTo(2, 6);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;
	_smallDistance = 250;
	_bigDistance = 500;

	_isAttack = false;
	_isMove = false;

	//미어캣 기본 애니메이션
	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_L->setPlayFrame(39, 36, false, true);
	_idleMotion_L->setFPS(1);

	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_R->setPlayFrame(20, 23, false, true);
	_idleMotion_R->setFPS(1);
	//미어캣 기본 애니메이션

	//미어캣 위쪽 기본 애니메이션
	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_U_L->setPlayFrame(19, 16, false, true);
	_idleMotion_U_L->setFPS(1);

	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_U_R->setPlayFrame(0, 3, false, true);
	_idleMotion_U_R->setFPS(1);
	//미어캣 위쪽 기본 애니메이션

	//미어캣 아래쪽 기본 애니메이션
	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_D_L->setPlayFrame(59, 56, false, true);
	_idleMotion_D_L->setFPS(1);

	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_D_R->setPlayFrame(40, 43, false, true);
	_idleMotion_D_R->setFPS(1);
	//미어캣 아래쪽 기본 애니메이션

	//미어캣 공격당할때 애니메이션
	_hitMotion_L = new animation;
	_hitMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_L->setPlayFrame(31, 30, false, false);
	_hitMotion_L->setFPS(1);

	_hitMotion_R = new animation;
	_hitMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_R->setPlayFrame(29, 28, false, false);
	_hitMotion_R->setFPS(1);
	//미어캣 공격당할때 애니메이션

	//미어캣 위쪽 공격당할때 애니메이션
	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_U_L->setPlayFrame(11, 10, false, false);
	_hitMotion_U_L->setFPS(1);

	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_U_R->setPlayFrame(9, 8, false, false);
	_hitMotion_U_R->setFPS(1);
	//미어캣 위쪽 공격당할때 애니메이션

	//미어캣 아래쪽 공격당할때 애니메이션
	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_D_L->setPlayFrame(51, 50, false, false);
	_hitMotion_D_L->setFPS(1);

	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_D_R->setPlayFrame(49, 48, false, false);
	_hitMotion_D_R->setFPS(1);
	//미어캣 아래쪽 공격당할때 애니메이션

	//미어캣 공격 애니메이션
	_attackMotion_L = new animation;
	_attackMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_L->setPlayFrame(35, 32, false, false);
	_attackMotion_L->setFPS(1);

	_attackMotion_R = new animation;
	_attackMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_R->setPlayFrame(24, 27, false, false);
	_attackMotion_R->setFPS(1);
	//미어캣 공격 애니메이션

	//미어캣 위쪽 공격 애니메이션
	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_U_L->setPlayFrame(15, 12, false, false);
	_attackMotion_U_L->setFPS(1);

	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_U_R->setPlayFrame(4, 7, false, false);
	_attackMotion_U_R->setFPS(1);
	//미어캣 위쪽 공격 애니메이션

	//미어캣 아래쪽 공격 애니메이션
	_attackMotion_D_L = new animation;
	_attackMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_D_L->setPlayFrame(55, 52, false, false);
	_attackMotion_D_L->setFPS(1);

	_attackMotion_D_R = new animation;
	_attackMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_D_R->setPlayFrame(44, 47, false, false);
	_attackMotion_D_R->setFPS(1);
	//미어캣 아래쪽 공격 애니메이션

	//미어캣 무브 애니메이션
	_meerkatMoveMotion = new animation;
	_meerkatMoveMotion->init(_meerkatMoveImage->getWidth(), _meerkatMoveImage->getHeight(), _meerkatMoveImage->getFrameWidth(), _meerkatMoveImage->getFrameHeight());
	_meerkatMoveMotion->setPlayFrame(0, 8, false, true);
	_meerkatMoveMotion->setFPS(1);
	//미어캣 무브 애니메이션

	_rc.set(0, 0, 70, 70);
	_rc.setCenter(_x, _y);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.set(0, 0, 48, 48);
	_nowOrder = 1;

	return S_OK;
}

void meerkat::release()
{
}

void meerkat::update()
{
	tileGet();//에너미의 타울검출 위치 업데이트
	move();//에너미 무브
	animationControl();//에너미 애니메이션 컨트롤
	animationAngleControl();//에너미와 플레이어간의 앵글값에 따른 애니메이션 컨트롤
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	angry();//에너미의 체력이 절반 이하가 되면 능력치 상승(스피드, 공격력, 공격딜레이)
}

void meerkat::render()
{
	_attackRC.render(getMemDC());//에너미 공격렉트
	if (_enemyDirection != ENEMY_MOVE)
	{
		_enemyImage->aniRender(getMemDC(), _rc.getCenter().x - (_enemyImage->getFrameWidth() / 2), _rc.getCenter().y - (_enemyImage->getFrameHeight() / 2), _enemyMotion);
	}
	else
	{
		_meerkatMoveImage->aniRender(getMemDC(), _rc.getCenter().x - (_meerkatMoveImage->getFrameWidth() / 2), _rc.getCenter().y - (_meerkatMoveImage->getFrameHeight() / 2), _enemyMotion);
	}
	//_rc.render(getMemDC());//에너미 렉트
	for (int i = 0; i < 3; i++)
	{
		RectangleMake(getMemDC(), _t[i]->getRect().getCenter().x, _t[i]->getRect().getCenter().y, SIZE, SIZE);
	}
}

void meerkat::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getX();
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getY();

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//에너미의 현재 체력이 멕스HP보다 작아지면
	{
		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (_distance <= _smallDistance)//플레이어랑 에너미의 거리가 가까우면
			{
				if (tileMove())
				{
					if (!_isMove)
					{
						_distanceSave = _distance;
						_angleSave = _angle + PI;
						_isMove = true;
					}

					if (_isMove)
					{
						_x += cosf(_angleSave) * _speed;
						_y += -sinf(_angleSave) * _speed;
					}
				}
			}
			else if (_distance > _smallDistance && _distance < _bigDistance)//플레이어랑 에너미의 거리가 일정거리이상 멀고 너무멀지 않으면
			{
				_isMove = false;
				//투척공격
				//투척공격
			}
			else//플레이어와 에너미의 거리가 너무 멀면
			{
				_isMove = false;
				if (tileMove())
				{
					_x += cosf(_angle) * _speed;
					_y += -sinf(_angle) * _speed;
				}
			}
		}
	}

	_rc.setCenter(_x, _y);
}

void meerkat::animationControl()
{
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_L;
		break;
	case ENEMY_RIGHT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_R;
		break;
	case ENEMY_UP_LEFT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_D_L;
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_D_R;
		break;
	case ENEMY_LEFT_MOVE:
		break;
	case ENEMY_RIGHT_MOVE:
		break;
	case ENEMY_UP_LEFT_MOVE:
		break;
	case ENEMY_UP_RIGHT_MOVE:
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		break;
	case ENEMY_LEFT_HIT:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _hitMotion_L;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_LEFT_IDLE;
		}
		break;
	case ENEMY_RIGHT_HIT:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _hitMotion_R;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_RIGHT_IDLE;
		}
		break;
	case ENEMY_UP_LEFT_HIT:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _hitMotion_U_L;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
		}
		break;
	case ENEMY_UP_RIGHT_HIT:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _hitMotion_U_R;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
		}
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _hitMotion_D_L;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _hitMotion_D_R;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
		}
		break;
	case ENEMY_LEFT_ATTACK:
		_enemyMotion = _attackMotion_L;
		break;
	case ENEMY_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_R;
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_enemyMotion = _attackMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		_enemyMotion = _attackMotion_D_L;
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_D_R;
		break;
	case ENEMY_MOVE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _meerkatMoveMotion;
		break;
	}

	if (!_enemyMotion->isPlay())
	{
		_enemyMotion->start();
	}
}

void meerkat::animationAngleControl()
{
	if (_maxHP > _currentHP)//에너미의 현재 체력이 멕스HP보다 작아지면
	{
		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)//에너미가 히트 애니메이션이 아닐경우
		{
			if (!_isAttack)//에너미가 공격중이 아니면
			{
				if (_distance <= _smallDistance)//플레이어랑 에너미의 거리가 가까우면
				{
					_enemyDirection = ENEMY_MOVE;

				}
				else if (_distance > _smallDistance && _distance < _bigDistance)//플레이어랑 에너미의 거리가 일정거리이상 멀고 너무멀지 않으면
				{
					if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//왼쪽
					{
						_enemyDirection = ENEMY_LEFT_IDLE;
					}

					if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//왼쪽위
					{
						_enemyDirection = ENEMY_UP_LEFT_IDLE;
					}

					if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//오른쪽위
					{
						_enemyDirection = ENEMY_UP_RIGHT_IDLE;
					}

					if (_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45 || _angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360)//오른쪽
					{
						_enemyDirection = ENEMY_RIGHT_IDLE;
					}

					if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//아래오른쪽
					{
						_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
					}

					if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//아래왼쪽
					{
						_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
					}
				}
				else//플레이어와 에너미의 거리가 너무 멀면
				{
					_enemyDirection = ENEMY_MOVE;
				}
			}
			else//공격상태값이 트루면
			{
				if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//왼쪽
				{
					_enemyDirection = ENEMY_LEFT_ATTACK;
				}

				if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//왼쪽위
				{
					_enemyDirection = ENEMY_UP_LEFT_ATTACK;
				}

				if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//오른쪽위
				{
					_enemyDirection = ENEMY_UP_RIGHT_ATTACK;
				}

				if (_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45 || _angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360)//오른쪽
				{
					_enemyDirection = ENEMY_RIGHT_ATTACK;
				}

				if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//아래오른쪽
				{
					_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK;
				}

				if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//아래왼쪽
				{
					_enemyDirection = ENEMY_DOWN_LEFT_ATTACK;
				}
			}
		}
	}
}

void meerkat::tileGet()
{
	_tile.setLeftTop(((int)_x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE);

	int k = 1;
	currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };//현재에너미 위치에 타일

	if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//왼쪽
	{
		nextTileIndex[0] = { currentTileIndex.x - k, currentTileIndex.y };
		nextTileIndex[1] = { currentTileIndex.x - k, currentTileIndex.y + k };
		nextTileIndex[2] = { currentTileIndex.x - k, currentTileIndex.y - k };
	}

	if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//왼쪽위
	{
		nextTileIndex[0] = { currentTileIndex.x - k, currentTileIndex.y - k };
		nextTileIndex[1] = { currentTileIndex.x, currentTileIndex.y - k };
		nextTileIndex[2] = { currentTileIndex.x + k, currentTileIndex.y - k };
	}

	if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//오른쪽위
	{
		nextTileIndex[0] = { currentTileIndex.x + k, currentTileIndex.y - k };
		nextTileIndex[1] = { currentTileIndex.x, currentTileIndex.y - k };
		nextTileIndex[2] = { currentTileIndex.x - k, currentTileIndex.y - k };
	}

	if (_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45 || _angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360)//오른쪽
	{
		nextTileIndex[0] = { currentTileIndex.x + k, currentTileIndex.y };
		nextTileIndex[1] = { currentTileIndex.x + k, currentTileIndex.y - k };
		nextTileIndex[2] = { currentTileIndex.x + k, currentTileIndex.y + k };
	}

	if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//아래오른쪽
	{
		nextTileIndex[0] = { currentTileIndex.x + k, currentTileIndex.y + k };
		nextTileIndex[1] = { currentTileIndex.x, currentTileIndex.y + k };
		nextTileIndex[2] = { currentTileIndex.x - k, currentTileIndex.y + k };
	}

	if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//아래 오른쪽
	{
		nextTileIndex[0] = { currentTileIndex.x - k, currentTileIndex.y + k };
		nextTileIndex[1] = { currentTileIndex.x, currentTileIndex.y + k };
		nextTileIndex[2] = { currentTileIndex.x + k, currentTileIndex.y + k };
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();

	//다음 타일
	if (nextTileIndex[0].x > maxTileX) nextTileIndex[0].x = maxTileX;
	else if (nextTileIndex[0].x < 0) nextTileIndex[0].x = 0;
	if (nextTileIndex[0].y > maxTileY) nextTileIndex[0].y = maxTileY;
	else if (nextTileIndex[0].y < 0) nextTileIndex[0].y = 0;
	_t[0] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[0].y][nextTileIndex[0].x];

	//다음 타일
	if (nextTileIndex[1].x > maxTileX) nextTileIndex[1].x = maxTileX;
	else if (nextTileIndex[1].x < 0) nextTileIndex[1].x = 0;
	if (nextTileIndex[1].y > maxTileY) nextTileIndex[1].y = maxTileY;
	else if (nextTileIndex[1].y < 0) nextTileIndex[1].y = 0;
	_t[1] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[1].y][nextTileIndex[1].x];

	//다음 타일
	if (nextTileIndex[2].x > maxTileX) nextTileIndex[2].x = maxTileX;
	else if (nextTileIndex[2].x < 0) nextTileIndex[2].x = 0;
	if (nextTileIndex[2].y > maxTileY) nextTileIndex[2].y = maxTileY;
	else if (nextTileIndex[2].y < 0) nextTileIndex[2].y = 0;
	_t[2] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[2].y][nextTileIndex[2].x];
}

bool meerkat::tileMove()
{
	//층이 같다면
	if (_t[0]->getOrderIndex() == _nowOrder && _t[1]->getOrderIndex() == _nowOrder && _t[2]->getOrderIndex() == _nowOrder)
	{
		return true;
	}
	else
	{
		return false;
	}

}
