#include "stdafx.h"
#include "meerkat.h"
#include "scene.h"
#include "bullets.h"
#include "player.h"

HRESULT meerkat::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyMeerkat", L"images/enemy/meerkat.png", 10, 12);//기본, 히트, 공격모션 이미지
	_meerkatMoveImage = IMAGEMANAGER->addFrameImage("enemyMeerkatMove", L"images/enemy/meerkatMove.png", 9, 1);//무브 이미지
	IMAGEMANAGER->addFrameImage("enemyMeerkatBallEffect", L"images/enemy/meerkatBallEffect.png", 8, 1);//미어캣 총알 폭발 이펙트
	EFFECTMANAGER->addEffect("enemyMeerkatBallEffect", "enemyMeerkatBallEffect", 1.0f, 0.5f, 5, 1.0f);//미어캣 총알 폭발 이펙트

	SOUNDMANAGER->addSound("meerkat-ball-hit", "sounds/enemy/meerkat-ball-hit.ogg", false, false);

	_name = "meerkat";

	_maxHP = 100;
	_currentHP = _maxHP;

	_meerkatSpeed = 10.0f;
	
	_attackPower = RND->getFromIntTo(2, 6);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;
	_reflectCount = 0;
	_smallDistance = 250;
	_bigDistance = 500;

	_isAttack = false;
	_isMove = false;
	_reflect = false;
	_isBigMove = false;
	_oneAnimation = false;

	//미어캣 기본 애니메이션
	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_L->setPlayFrame(39, 36, false, true);
	_idleMotion_L->setFPS(1);

	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_R->setPlayFrame(20, 23, false, true);
	_idleMotion_R->setFPS(1);
	//미어캣 기본 애니메이션

	//미어캣 위쪽 기본 애니메이션
	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_L->setPlayFrame(19, 16, false, true);
	_idleMotion_U_L->setFPS(1);

	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_R->setPlayFrame(0, 3, false, true);
	_idleMotion_U_R->setFPS(1);
	//미어캣 위쪽 기본 애니메이션

	//미어캣 아래쪽 기본 애니메이션
	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_L->setPlayFrame(59, 56, false, true);
	_idleMotion_D_L->setFPS(1);

	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_R->setPlayFrame(40, 43, false, true);
	_idleMotion_D_R->setFPS(1);
	//미어캣 아래쪽 기본 애니메이션

	//미어캣 공격당할때 애니메이션
	_hitMotion_L = new animation;
	_hitMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_L->setPlayFrame(31, 30, false, false);
	_hitMotion_L->setFPS(1);

	_hitMotion_R = new animation;
	_hitMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_R->setPlayFrame(29, 28, false, false);
	_hitMotion_R->setFPS(1);
	//미어캣 공격당할때 애니메이션

	//미어캣 위쪽 공격당할때 애니메이션
	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_L->setPlayFrame(11, 10, false, false);
	_hitMotion_U_L->setFPS(1);

	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_R->setPlayFrame(9, 8, false, false);
	_hitMotion_U_R->setFPS(1);
	//미어캣 위쪽 공격당할때 애니메이션

	//미어캣 아래쪽 공격당할때 애니메이션
	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_L->setPlayFrame(51, 50, false, false);
	_hitMotion_D_L->setFPS(1);

	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_R->setPlayFrame(49, 48, false, false);
	_hitMotion_D_R->setFPS(1);
	//미어캣 아래쪽 공격당할때 애니메이션

	//미어캣 공격 애니메이션
	_attackMotion_L = new animation;
	_attackMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_L->setPlayFrame(35, 32, false, false);
	_attackMotion_L->setFPS(1);

	_attackMotion_R = new animation;
	_attackMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_R->setPlayFrame(24, 27, false, false);
	_attackMotion_R->setFPS(1);
	//미어캣 공격 애니메이션

	//미어캣 위쪽 공격 애니메이션
	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_L->setPlayFrame(15, 12, false, false);
	_attackMotion_U_L->setFPS(1);

	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_R->setPlayFrame(4, 7, false, false);
	_attackMotion_U_R->setFPS(1);
	//미어캣 위쪽 공격 애니메이션

	//미어캣 아래쪽 공격 애니메이션
	_attackMotion_D_L = new animation;
	_attackMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_D_L->setPlayFrame(55, 52, false, false);
	_attackMotion_D_L->setFPS(1);

	_attackMotion_D_R = new animation;
	_attackMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_D_R->setPlayFrame(44, 47, false, false);
	_attackMotion_D_R->setFPS(1);
	//미어캣 아래쪽 공격 애니메이션

	//미어캣이 땅속으로 들어가는 애니메이션
	_meerkatTunnelDownMotion_L = new animation;
	_meerkatTunnelDownMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelDownMotion_L->setPlayFrame(71, 79, false, false);
	_meerkatTunnelDownMotion_L->setFPS(2);

	_meerkatTunnelDownMotion_R = new animation;
	_meerkatTunnelDownMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelDownMotion_R->setPlayFrame(68, 60, false, false);
	_meerkatTunnelDownMotion_R->setFPS(2);
	//미어캣이 땅속으로 들어가는 애니메이션

	//미어캣이 땅속에서 나오는 애니메이션
	_meerkatTunnelUpMotion_L = new animation;
	_meerkatTunnelUpMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelUpMotion_L->setPlayFrame(79, 71, false, false);
	_meerkatTunnelUpMotion_L->setFPS(2);

	_meerkatTunnelUpMotion_R = new animation;
	_meerkatTunnelUpMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelUpMotion_R->setPlayFrame(60, 68, false, false);
	_meerkatTunnelUpMotion_R->setFPS(2);
	//미어캣이 땅속에서 나오는 애니메이션

	//미어캣 무브 애니메이션
	_meerkatMoveMotion = new animation;
	_meerkatMoveMotion->init(_meerkatMoveImage->getWidth(), _meerkatMoveImage->getHeight(), _meerkatMoveImage->getFrameSize().x, _meerkatMoveImage->getFrameSize().y);
	_meerkatMoveMotion->setPlayFrame(0, 8, false, true);
	_meerkatMoveMotion->setFPS(1);
	//미어캣 무브 애니메이션

	_width = 70;
	_height = 70;

	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);
	_nowOrder = 1;

	_bullet = new bullets;
	_bullet->init();

	return S_OK;
}

void meerkat::release()
{
}

void meerkat::update()
{
	tileGet();//에너미의 타울검출 위치 업데이트
	move();//에너미 무브
	mapOutCollision();//에너미가 맵밖으로 벗어나지 못하기 하기위한 함수
	animationControl();//에너미 애니메이션 컨트롤
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 7);
	angry();//에너미의 체력이 절반 이하가 되면 능력치 상승(스피드, 공격력, 공격딜레이)

	if (_isAttack)//공격상태가 트루면
	{
		_bullet->fire(_position.x, _position.y, _angle, _meerkatSpeed);
		_isAttack = false;
	}
	ballTileGet();//볼타일의 위치 업데이트
	_bullet->update();//미어캣 총알 업데이트
	for (int i = 0; i < _bullet->getvEnemyBullet().size(); i++)
	{
		if (!_isAttack)
		{
			_count++;
			if (!ballTileMove() && _count >= 25)//미어캣의 볼이 장애물에 충돌시
			{
				EFFECTMANAGER->play("enemyMeerkatBallEffect", CAMERA->getRelativeVector2(_bullet->getvEnemyBullet()[i].position).x + 25, CAMERA->getRelativeVector2(_bullet->getvEnemyBullet()[i].position).y + 25);
				_bullet->remove(i);//미어캣 볼 벡터 제거
				_count = 0;
			}
		}
	}
	_currentHpBar.update(Vector2(_position.x - 50, _position.y + 50), Vector2(_currentHP, 5), pivot::LEFTTOP);
	//cout << "미어캣 : " << _currentHP << endl;
}

void meerkat::render()
{
	if (_enemyDirection != ENEMY_TUNNEL_MOVE)
	{
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y - 10), _enemyMotion, 1.0f);
	}
	else
	{
		_meerkatMoveImage->setSize(Vector2(_meerkatMoveImage->getFrameSize()) * CAMERA->getZoomAmount());
		_meerkatMoveImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter()), _enemyMotion, 1.0f);
	}
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));//에너미 렉트
	//for (int i = 0; i < 8; i++)
	//{
	//	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_t[i]->getRect()));
	//}
	_bullet->render();
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_currentHpBar), D2D1::ColorF::Red, 0);
}

void meerkat::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x;
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y;
	int playerNowOrder = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"))->getNowOrder();

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//에너미의 현재 체력이 멕스HP보다 작아지면
	{
		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT &&
			playerNowOrder == 1)
		{
			if (_distance <= _smallDistance && !_isBigMove)//플레이어랑 에너미의 거리가 가까우면
			{
				if (tileMove())//미어캣 주변에 장애물이 없으면
				{
					if (!_isMove)//플레이어의 반대방향으로 이동시키기 위해 연산을 한번만 하기위한 조건
					{
						_angleSave = _angle + PI;
						_isMove = true;
					}
				}
			}

			if (!tileMove() && !_reflect && !_isBigMove)//미어캣 주변에 장애물이 있고 장애물의 반대방향으로 이동되게 하기위한 조건
			{
				_angleSave += PI;//장애물의 반대방향으로 이동
				_reflect = true;
			}

			if (tileMove() && !_isBigMove)//장애물이 안부딪혔으면
			{
				if (_isMove && _distance <= _smallDistance + _smallDistance / 2)
				{
					if (_playerX < _position.x)
					{
						if (_enemyDirection != ENEMY_DOWN_LEFT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_LEFT_TUNNEL;
						}
					}
					else
					{
						if (_enemyDirection != ENEMY_DOWN_RIGHT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_TUNNEL;
						}
					}
						
					_reflect = false;

					if (_enemyDirection == ENEMY_TUNNEL_MOVE)
					{
						_position.x += cosf(_angleSave) * _meerkatSpeed;
						_position.y += -sinf(_angleSave) * _meerkatSpeed;
					}
					
				}
				else
				{
					if (_playerX < _position.x)
					{
						if (_enemyDirection == ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL)
						{
							_enemyDirection = ENEMY_UP_LEFT_TUNNEL;
						}
					}
					else
					{
						if (_enemyDirection == ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_UP_RIGHT_TUNNEL;
						}
					}

					_attackDelay++;

					if (_enemyDirection == ENEMY_DOWN_LEFT_IDLE && _attackDelay >= _maxAttackDelay ||
						_enemyDirection == ENEMY_DOWN_RIGHT_IDLE && _attackDelay >= _maxAttackDelay ||
						_enemyDirection == ENEMY_LEFT_IDLE && _attackDelay >= _maxAttackDelay ||
						_enemyDirection == ENEMY_RIGHT_IDLE && _attackDelay >= _maxAttackDelay ||
						_enemyDirection == ENEMY_UP_LEFT_IDLE && _attackDelay >= _maxAttackDelay ||
						_enemyDirection == ENEMY_UP_RIGHT_IDLE && _attackDelay >= _maxAttackDelay)
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

						_attackDelay = 0;
					}
					_isMove = false;
				}
			}

			if (!tileMove() && _reflect && !_isBigMove)//미어캣 주변에 장애물이 있고 장애물의 반대방향으로 이동되게 하기위한 조건
			{
				if (_playerX < _position.x)
				{
					if (_enemyDirection != ENEMY_DOWN_LEFT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
					{
						_enemyDirection = ENEMY_DOWN_LEFT_TUNNEL;
					}
				}
				else
				{
					if (_enemyDirection != ENEMY_DOWN_RIGHT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
					{
						_enemyDirection = ENEMY_DOWN_RIGHT_TUNNEL;
					}
				}
					
				if (_enemyDirection == ENEMY_TUNNEL_MOVE)
				{
					_position.x += cosf(_angleSave) * _meerkatSpeed;
					_position.y += -sinf(_angleSave) * _meerkatSpeed;
				}
				_reflectCount++;//장애물에 부딪혔으니 장애물에 부딪힌 횟수 카운트증가
			}

			if (_reflectCount >= 2 && !_isBigMove)//벽에 부딪힌 횟수가 2번 이상이고 빅무브는 펄스인경우
			{
				_angleSave += PI / RND->getFromIntTo(1, 4);//벽에 부딪혔으면 각도값을 90도 틀어주기 위한 연산
				_reflectCount = 0;
			}

			if (_distance > _bigDistance)//플레이어와 미어캣간의 거리가 너무 먼경우
			{
				_isBigMove = true;//빅무브를 실행해라
			}

			if (_isBigMove)//빅무브
			{
				//에이스타 이동
				if (_move.size() != NULL)
				{
					float d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					float an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);

					if (_playerX < _position.x)
					{
						if (_enemyDirection != ENEMY_DOWN_LEFT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_LEFT_TUNNEL;
						}
					}
					else
					{
						if (_enemyDirection != ENEMY_DOWN_RIGHT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_TUNNEL;
						}
					}

					if (_enemyDirection == ENEMY_TUNNEL_MOVE)
					{
						_position.x += cosf(an) * _meerkatSpeed;
						_position.y += -sinf(an) * _meerkatSpeed;
					}
					
					if (d < 5)
					{
						deleteMove();
					}
				}
				//에이스타 이동
			}

			if (_distance <= _smallDistance + _smallDistance / 2)//플레이어와 미어캣의 거리가 일정거리 안이면
			{
				_isBigMove = false;//빅무브를 멈춰라
			}
		}
	}

	_rc.set(_position, pivot::CENTER);
}

void meerkat::animationControl()
{
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_enemyMotion = _idleMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_IDLE:
		_enemyMotion = _idleMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_IDLE:
		_enemyMotion = _idleMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_enemyMotion = _idleMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_enemyMotion = _idleMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_enemyMotion = _idleMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
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
		_enemyMotion = _hitMotion_L;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_LEFT_IDLE;
		}

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_HIT:
		_enemyMotion = _hitMotion_R;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_RIGHT_IDLE;
		}

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_HIT:
		_enemyMotion = _hitMotion_U_L;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
		}

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_HIT:
		_enemyMotion = _hitMotion_U_R;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
		}

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_enemyMotion = _hitMotion_D_L;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_enemyMotion = _hitMotion_D_R;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
		}

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_LEFT_ATTACK:
		_enemyMotion = _attackMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_LEFT_IDLE;
		}
		break;
	case ENEMY_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_RIGHT_IDLE;
		}
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_enemyMotion = _attackMotion_U_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_U_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
		}
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		_enemyMotion = _attackMotion_D_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_D_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
		}
		break;
	case ENEMY_TUNNEL_MOVE:
		_enemyMotion = _meerkatMoveMotion;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_TUNNEL:
		_enemyMotion = _meerkatTunnelDownMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_TUNNEL_MOVE;
		}
		break;
	case ENEMY_DOWN_RIGHT_TUNNEL:
		_enemyMotion = _meerkatTunnelDownMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_TUNNEL_MOVE;
		}
		break;
	case ENEMY_UP_LEFT_TUNNEL:
		_enemyMotion = _meerkatTunnelUpMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}
		break;
	case ENEMY_UP_RIGHT_TUNNEL:
		_enemyMotion = _meerkatTunnelUpMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
		}
		break;
	}
}

void meerkat::ballTileGet()
{
	for (int i = 0; i < _bullet->getvEnemyBullet().size(); i++)
	{
		_ballTile.set(Vector2(((int)_bullet->getvEnemyBullet()[i].position.x / SIZE) * SIZE, ((int)(_bullet->getvEnemyBullet()[i].rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);

		int k = 1;
		ballCurrentTileIndex = Vector2(_ballTile.left / SIZE, _ballTile.top / SIZE);//현재에너미 위치에 타일

		ballNextTileIndex[0] = Vector2(ballCurrentTileIndex.x - k, ballCurrentTileIndex.y);//왼쪽
		ballNextTileIndex[1] = Vector2(ballCurrentTileIndex.x - k, ballCurrentTileIndex.y + k);//왼쪽아래
		ballNextTileIndex[2] = Vector2(ballCurrentTileIndex.x, ballCurrentTileIndex.y + k);//아래
		ballNextTileIndex[3] = Vector2(ballCurrentTileIndex.x + k, ballCurrentTileIndex.y + k);//오른쪽 아래
		ballNextTileIndex[4] = Vector2(ballCurrentTileIndex.x + k, ballCurrentTileIndex.y);//오른쪽
		ballNextTileIndex[5] = Vector2(ballCurrentTileIndex.x + k, ballCurrentTileIndex.y - k);//오른쪽위
		ballNextTileIndex[6] = Vector2(ballCurrentTileIndex.x, ballCurrentTileIndex.y - k);//위
		ballNextTileIndex[7] = Vector2(ballCurrentTileIndex.x - k, ballCurrentTileIndex.y - k);//왼쪽위

		int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
		int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

		//다음 타일
		if (ballNextTileIndex[0].x > maxTileX) ballNextTileIndex[0].x = maxTileX;
		else if (ballNextTileIndex[0].x < 0) ballNextTileIndex[0].x = 0;
		if (ballNextTileIndex[0].y > maxTileY) ballNextTileIndex[0].y = maxTileY;
		else if (ballNextTileIndex[0].y < 0) ballNextTileIndex[0].y = 0;
		_ballT[0] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[0].y][ballNextTileIndex[0].x];

		//다음 타일
		if (ballNextTileIndex[1].x > maxTileX) ballNextTileIndex[1].x = maxTileX;
		else if (ballNextTileIndex[1].x < 0) ballNextTileIndex[1].x = 0;
		if (ballNextTileIndex[1].y > maxTileY) ballNextTileIndex[1].y = maxTileY;
		else if (ballNextTileIndex[1].y < 0) ballNextTileIndex[1].y = 0;
		_ballT[1] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[1].y][ballNextTileIndex[1].x];

		//다음 타일
		if (ballNextTileIndex[2].x > maxTileX) ballNextTileIndex[2].x = maxTileX;
		else if (ballNextTileIndex[2].x < 0) ballNextTileIndex[2].x = 0;
		if (ballNextTileIndex[2].y > maxTileY) ballNextTileIndex[2].y = maxTileY;
		else if (ballNextTileIndex[2].y < 0) ballNextTileIndex[2].y = 0;
		_ballT[2] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[2].y][ballNextTileIndex[2].x];

		//다음 타일
		if (ballNextTileIndex[3].x > maxTileX) ballNextTileIndex[3].x = maxTileX;
		else if (ballNextTileIndex[3].x < 0) ballNextTileIndex[3].x = 0;
		if (ballNextTileIndex[3].y > maxTileY) ballNextTileIndex[3].y = maxTileY;
		else if (ballNextTileIndex[3].y < 0) ballNextTileIndex[3].y = 0;
		_ballT[3] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[3].y][ballNextTileIndex[3].x];

		//다음 타일
		if (ballNextTileIndex[4].x > maxTileX) ballNextTileIndex[4].x = maxTileX;
		else if (ballNextTileIndex[4].x < 0) ballNextTileIndex[4].x = 0;
		if (ballNextTileIndex[4].y > maxTileY) ballNextTileIndex[4].y = maxTileY;
		else if (ballNextTileIndex[4].y < 0) ballNextTileIndex[4].y = 0;
		_ballT[4] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[4].y][ballNextTileIndex[4].x];

		//다음 타일
		if (ballNextTileIndex[5].x > maxTileX) ballNextTileIndex[5].x = maxTileX;
		else if (ballNextTileIndex[5].x < 0) ballNextTileIndex[5].x = 0;
		if (ballNextTileIndex[5].y > maxTileY) ballNextTileIndex[5].y = maxTileY;
		else if (ballNextTileIndex[5].y < 0) ballNextTileIndex[5].y = 0;
		_ballT[5] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[5].y][ballNextTileIndex[5].x];

		//다음 타일
		if (ballNextTileIndex[6].x > maxTileX) ballNextTileIndex[6].x = maxTileX;
		else if (ballNextTileIndex[6].x < 0) ballNextTileIndex[6].x = 0;
		if (ballNextTileIndex[6].y > maxTileY) ballNextTileIndex[6].y = maxTileY;
		else if (ballNextTileIndex[6].y < 0) ballNextTileIndex[6].y = 0;
		_ballT[6] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[6].y][ballNextTileIndex[6].x];

		//다음 타일
		if (ballNextTileIndex[7].x > maxTileX) ballNextTileIndex[7].x = maxTileX;
		else if (ballNextTileIndex[7].x < 0) ballNextTileIndex[7].x = 0;
		if (ballNextTileIndex[7].y > maxTileY) ballNextTileIndex[7].y = maxTileY;
		else if (ballNextTileIndex[7].y < 0) ballNextTileIndex[7].y = 0;
		_ballT[7] = SCENEMANAGER->getCurrentScene()->getTiles()[ballNextTileIndex[7].y][ballNextTileIndex[7].x];
	}
}

void meerkat::mapOutCollision()
{
	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;
	maxTileX *= SIZE;
	maxTileY *= SIZE;

	if (_position.x < 0)
	{
		_position.x += abs(0 - _rc.left);
		_angleSave += PI;
	}
	if (_position.x > maxTileX)
	{
		_position.x -= _rc.right - maxTileX;
		_angleSave += PI;
	}
	if (_position.y < 0)
	{
		_position.y += abs(0 - _rc.top);
		_angleSave += PI;
	}
	if (_position.y > maxTileY)
	{
		_position.y -= _rc.bottom - maxTileY;
		_angleSave += PI;
	}
}

bool meerkat::ballTileMove()
{
	//층이 같다면
	if (_ballT[0]->getOrderIndex() == _nowOrder && _ballT[1]->getOrderIndex() == _nowOrder && _ballT[2]->getOrderIndex() == _nowOrder &&
		_ballT[3]->getOrderIndex() == _nowOrder && _ballT[4]->getOrderIndex() == _nowOrder && _ballT[5]->getOrderIndex() == _nowOrder &&
		_ballT[6]->getOrderIndex() == _nowOrder && _ballT[7]->getOrderIndex() == _nowOrder)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void meerkat::tileGet()
{
	_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);

	int k = 1;
	currentTileIndex = Vector2(_tile.left / SIZE, _tile.top / SIZE);//현재에너미 위치에 타일

	nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y);//왼쪽
	nextTileIndex[1] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);//왼쪽아래
	nextTileIndex[2] = Vector2(currentTileIndex.x, currentTileIndex.y + k);//아래
	nextTileIndex[3] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);//오른쪽 아래
	nextTileIndex[4] = Vector2(currentTileIndex.x + k, currentTileIndex.y);//오른쪽
	nextTileIndex[5] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);//오른쪽위
	nextTileIndex[6] = Vector2(currentTileIndex.x, currentTileIndex.y - k);//위
	nextTileIndex[7] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);//왼쪽위

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

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

	//다음 타일
	if (nextTileIndex[3].x > maxTileX) nextTileIndex[3].x = maxTileX;
	else if (nextTileIndex[3].x < 0) nextTileIndex[3].x = 0;
	if (nextTileIndex[3].y > maxTileY) nextTileIndex[3].y = maxTileY;
	else if (nextTileIndex[3].y < 0) nextTileIndex[3].y = 0;
	_t[3] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[3].y][nextTileIndex[3].x];

	//다음 타일
	if (nextTileIndex[4].x > maxTileX) nextTileIndex[4].x = maxTileX;
	else if (nextTileIndex[4].x < 0) nextTileIndex[4].x = 0;
	if (nextTileIndex[4].y > maxTileY) nextTileIndex[4].y = maxTileY;
	else if (nextTileIndex[4].y < 0) nextTileIndex[4].y = 0;
	_t[4] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[4].y][nextTileIndex[4].x];

	//다음 타일
	if (nextTileIndex[5].x > maxTileX) nextTileIndex[5].x = maxTileX;
	else if (nextTileIndex[5].x < 0) nextTileIndex[5].x = 0;
	if (nextTileIndex[5].y > maxTileY) nextTileIndex[5].y = maxTileY;
	else if (nextTileIndex[5].y < 0) nextTileIndex[5].y = 0;
	_t[5] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[5].y][nextTileIndex[5].x];

	//다음 타일
	if (nextTileIndex[6].x > maxTileX) nextTileIndex[6].x = maxTileX;
	else if (nextTileIndex[6].x < 0) nextTileIndex[6].x = 0;
	if (nextTileIndex[6].y > maxTileY) nextTileIndex[6].y = maxTileY;
	else if (nextTileIndex[6].y < 0) nextTileIndex[6].y = 0;
	_t[6] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[6].y][nextTileIndex[6].x];

	//다음 타일
	if (nextTileIndex[7].x > maxTileX) nextTileIndex[7].x = maxTileX;
	else if (nextTileIndex[7].x < 0) nextTileIndex[7].x = 0;
	if (nextTileIndex[7].y > maxTileY) nextTileIndex[7].y = maxTileY;
	else if (nextTileIndex[7].y < 0) nextTileIndex[7].y = 0;
	_t[7] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[7].y][nextTileIndex[7].x];
}

bool meerkat::tileMove()
{
	//층이 같다면
	if (_t[0]->getOrderIndex() == _nowOrder && _t[1]->getOrderIndex() == _nowOrder && _t[2]->getOrderIndex() == _nowOrder &&
		_t[3]->getOrderIndex() == _nowOrder && _t[4]->getOrderIndex() == _nowOrder && _t[5]->getOrderIndex() == _nowOrder &&
		_t[6]->getOrderIndex() == _nowOrder && _t[7]->getOrderIndex() == _nowOrder)
	{
		return true;
	}
	else
	{
		return false;
	}

}
