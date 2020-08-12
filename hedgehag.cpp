#include "stdafx.h"
#include "hedgehag.h"

HRESULT hedgehag::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyHedgehog", "images/enemy/hedgehog.bmp", 1200, 672, 10, 7, true, RGB(255, 0, 255));//에너미 이미지
	EFFECTMANAGER->addEffect("enemyHedgehogDust", "images/enemy/hedgehogDust.bmp", 240, 102, 48, 102, 1.0f, 0.5f, 200);//공격상태에서 제자리에 나오는 먼지 이펙트
	EFFECTMANAGER->addEffect("enemyHedgehogMoveDust", "images/enemy/hedgehogMoveDust.bmp", 240, 51, 48, 51, 1.0f, 0.5f, 200);//공격상태에서 움직이는중에 나오는 먼지 이펙트

	_maxHP = 100;
	_currentHP = _maxHP;

	_speed = 5.0f;
	_attackSpeed = 10.0f;

	_attackPower = RND->getFromIntTo(2, 6);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;

	_isAttack = false;
	_distanceChange = false;
	_effect = false;

	//고슴도치 기본 애니메이션
	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_L->setPlayFrame(49, 46, false, true);
	_idleMotion_L->setFPS(1);

	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_R->setPlayFrame(53, 50, false, true);
	_idleMotion_R->setFPS(1);
	//고슴도치 기본 애니메이션

	//고슴도치 위쪽 기본 애니메이션
	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_U_L->setPlayFrame(9, 6, false, true);
	_idleMotion_U_L->setFPS(1);

	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_U_R->setPlayFrame(13, 10, false, true);
	_idleMotion_U_R->setFPS(1);
	//고슴도치 위쪽 기본 애니메이션

	//고슴도치 아래쪽 기본 애니메이션
	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_D_L->setPlayFrame(29, 26, false, true);
	_idleMotion_D_L->setFPS(1);

	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_D_R->setPlayFrame(33, 30, false, true);
	_idleMotion_D_R->setFPS(1);
	//고슴도치 아래쪽 기본 애니메이션

	//고슴도치 무브 애니메이션
	_moveMotion_L = new animation;
	_moveMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_moveMotion_L->setPlayFrame(45, 42, false, true);
	_moveMotion_L->setFPS(1);

	_moveMotion_R = new animation;
	_moveMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_moveMotion_R->setPlayFrame(57, 54, false, true);
	_moveMotion_R->setFPS(1);
	//고슴도치 무브 애니메이션

	//고슴도치 위쪽 무브 애니메이션
	_moveMotion_U_L = new animation;
	_moveMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_moveMotion_U_L->setPlayFrame(5, 2, false, true);
	_moveMotion_U_L->setFPS(1);

	_moveMotion_U_R = new animation;
	_moveMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_moveMotion_U_R->setPlayFrame(17, 14, false, true);
	_moveMotion_U_R->setFPS(1);
	//고슴도치 위쪽 무브 애니메이션

	//고슴도치 아래쪽 무브 애니메이션
	_moveMotion_D_L = new animation;
	_moveMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_moveMotion_D_L->setPlayFrame(25, 22, false, true);
	_moveMotion_D_L->setFPS(1);

	_moveMotion_D_R = new animation;
	_moveMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_moveMotion_D_R->setPlayFrame(37, 34, false, true);
	_moveMotion_D_R->setFPS(1);
	//고슴도치 아래쪽 무브 애니메이션

	//고슴도치 공격당할때 애니메이션
	_hitMotion_L = new animation;
	_hitMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_L->setPlayFrame(41, 40, false, false);
	_hitMotion_L->setFPS(1);

	_hitMotion_R = new animation;
	_hitMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_R->setPlayFrame(59, 58, false, false);
	_hitMotion_R->setFPS(1);
	//고슴도치 공격당할때 애니메이션

	//고슴도치 위쪽 공격당할때 애니메이션
	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_U_L->setPlayFrame(1, 0, false, false);
	_hitMotion_U_L->setFPS(1);

	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_U_R->setPlayFrame(19, 18, false, false);
	_hitMotion_U_R->setFPS(1);
	//고슴도치 위쪽 공격당할때 애니메이션

	//고슴도치 아래쪽 공격당할때 애니메이션
	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_D_L->setPlayFrame(21, 20, false, false);
	_hitMotion_D_L->setFPS(1);

	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_D_R->setPlayFrame(39, 38, false, false);
	_hitMotion_D_R->setFPS(1);
	//고슴도치 아래쪽 공격당할때 애니메이션

	//고슴도치 공격 애니메이션
	_attackMotion_L = new animation;
	_attackMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_L->setPlayFrame(63, 62, false, true);
	_attackMotion_L->setFPS(1);

	_attackMotion_R = new animation;
	_attackMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_R->setPlayFrame(65, 64, false, true);
	_attackMotion_R->setFPS(1);
	//고슴도치 공격 애니메이션

	//고슴도치 위아래 공격 애니메이션
	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_U_L->setPlayFrame(61, 60, false, true);
	_attackMotion_U_L->setFPS(1);

	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_U_R->setPlayFrame(67, 66, false, true);
	_attackMotion_U_R->setFPS(1);
	//고슴도치 위아래 공격 애니메이션

	_rc.set(0, 0, 70, 70);
	_rc.setCenter(_x, _y);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	return S_OK;
}

void hedgehag::release()
{
}

void hedgehag::update()
{
	move();//에너미 무브
	animationControl();//에너미 애니메이션 컨트롤
	animationAngleControl();//에너미와 플레이어간의 앵글값에 따른 애니메이션 컨트롤
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);//에너미 애니메이션 업데이트
	angry();//에너미의 체력이 절반 이하가 되면 능력치 상승(공격력, 스피드, 공격딜레이)
	if (_effect)//에너미가 공격상태에서 움직이지 않은경우
	{
		EFFECTMANAGER->play("enemyHedgehogDust", _rc.getCenter().x - 25, _rc.getCenter().y);
		EFFECTMANAGER->play("enemyHedgehogDust", _rc.getCenter().x + 25, _rc.getCenter().y);
	}
	if (!_effect && _isAttack)//에너미가 공격상태이고 움직였을경우
	{
		EFFECTMANAGER->play("enemyHedgehogMoveDust", _rc.getCenter().x, _rc.getCenter().y);
	}
}

void hedgehag::render()
{
	_attackRC.render(getMemDC());//에너미 공격렉트
	_enemyImage->aniRender(getMemDC(), _rc.getCenter().x - (_enemyImage->getFrameWidth() / 2), _rc.getCenter().y - (_enemyImage->getFrameHeight() / 2), _enemyMotion);//에너미 애니메이션 재생
	_rc.render(getMemDC());//에너미 렉트

	//RectangleMakeCenter(getMemDC(), _rc.getCenter().x, _rc.getCenter().y, 10, 10);
	//RectangleMakeCenter(getMemDC(), _playerX, _playerY, 10, 10);
}

void hedgehag::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getX();
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getY();

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//에너미의 현재 체력이 멕스hp보다 작아지면
	{
		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (!_distanceChange && !_isAttack)//플레이어와 에너미의 거리가 250보다 크면
			{

				if (_move.size() != NULL)
				{
					float d = getDistance(_x, _y, _move[_move.size() - 1]->getPosition().x,
						_move[_move.size() - 1]->getPosition().y);
					float an = getAngle(_x, _y, _move[_move.size() - 1]->getPosition().x,
						_move[_move.size() - 1]->getPosition().y);

					_x += cosf(an) * _speed;
					_y += -sinf(an) * _speed;

					if (d < 5)
					{
						deleteMove();
					}
				}
				
			}
			else if (_distanceChange)
			{
				if (_move.size() != NULL)
				{
					clearMove();
				}

				_attackDelay++;//공격딜레이
				if (_attackDelay >= _maxAttackDelay && !_isAttack)
				{
					_angleSave = _angle;//에너미와 플레이어간의 각도값을 임시적으로 저장해놓을 변수
					_playerSaveX = _playerX;//플레이어의 좌표를 일시적으로 저장해놓을 변수
					_playerSaveY = _playerY;//플레이어의 좌표를 일시적으로 저장해놓을 변수
					_isAttack = true;//에너미 공격시작
				}
			}

			if (_isAttack)//에너미 공격시작
			{
				_effect = true;
				_attackCount++;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
				_distanceSave = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerSaveX, _playerSaveY) + 200;//일시적으로 저장해놓은 플레이어 좌표와 에너미간의 거리값을 업데이트 하는 변수
				_attackRC.set(0, 0, 70, 70);//에너미 공격렉트

				if (_distanceSave > 10 && _distanceSave < 450)//에너미와 플레이어간의 임시적으로 저장해놨던 거리값이 10보다 크면 계속 이동
				{
					if (_attackCount >= 25)//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
					{
						_x += cosf(_angleSave) * _attackSpeed;
						_y -= sinf(_angleSave) * _attackSpeed;
						_effect = false;
					}
				}
				else if (_distanceSave < 10 || _distanceSave > 450)
				{
					_effect = false;
					_isAttack = false;
					_attackDelay = 0;//공격딜레이
					_attackCount = 0;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
				}
			}

			if (_distance > 250)//플레이어와 에너미의 거리가 250보다 크면
			{
				_distanceChange = false;
			}
			else
			{
				_distanceChange = true;
			}
		}
	}

	if (!_isAttack)//에너미의 공격상태값이 펄스면
	{
		_attackRC.set(0, 0, 0, 0);//에너미의 공격 렉트크기 0
	}

	_rc.setCenter(_x, _y);//에너미 렉트 위치 업데이트
	_attackRC.setCenter(_x, _y);//에너미 공격 렉트 위치 업데이트
}

void hedgehag::animationControl()
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
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _moveMotion_L;
		break;
	case ENEMY_RIGHT_MOVE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _moveMotion_R;
		break;
	case ENEMY_UP_LEFT_MOVE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _moveMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_MOVE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _moveMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _moveMotion_D_L;
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _moveMotion_D_R;
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
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		break;
	}

	if (!_enemyMotion->isPlay())
	{
		_enemyMotion->start();
	}
}

void hedgehag::animationAngleControl()
{
	if (_maxHP > _currentHP)//에너미의 현재 체력이 멕트HP보다 작아지면
	{
		if (!_distanceChange && !_isAttack)//플레이어와 에너미의 거리가 250보다 크면
		{
			if (_enemyDirection != ENEMY_LEFT_HIT &&
				_enemyDirection != ENEMY_UP_LEFT_HIT &&
				_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
				_enemyDirection != ENEMY_RIGHT_HIT &&
				_enemyDirection != ENEMY_UP_RIGHT_HIT &&
				_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
			{
				if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//왼쪽
				{
					_enemyDirection = ENEMY_LEFT_MOVE;
				}

				if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//왼쪽위
				{
					_enemyDirection = ENEMY_UP_LEFT_MOVE;
				}

				if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//오른쪽위
				{
					_enemyDirection = ENEMY_UP_RIGHT_MOVE;
				}

				if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//오른쪽
				{
					_enemyDirection = ENEMY_RIGHT_MOVE;
				}

				if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//아래오른쪽
				{
					_enemyDirection = ENEMY_DOWN_RIGHT_MOVE;
				}

				if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//아래왼쪽
				{
					_enemyDirection = ENEMY_DOWN_LEFT_MOVE;
				}
			}
		}
		else
		{
			if (_enemyDirection != ENEMY_LEFT_HIT &&
				_enemyDirection != ENEMY_UP_LEFT_HIT &&
				_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
				_enemyDirection != ENEMY_RIGHT_HIT &&
				_enemyDirection != ENEMY_UP_RIGHT_HIT &&
				_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
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

				if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//오른쪽
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

				if (_isAttack)//에너미 공격시작
				{
					if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225 &&
						_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_RIGHT_ATTACK ||
						_enemyDirection != ENEMY_RIGHT_ATTACK)//왼쪽
					{
						_enemyDirection = ENEMY_LEFT_ATTACK;
					}

					if ((_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135 &&
						_enemyDirection != ENEMY_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_RIGHT_ATTACK ||
						_enemyDirection != ENEMY_RIGHT_ATTACK) ||
						(_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270 &&
							_enemyDirection != ENEMY_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_RIGHT_ATTACK ||
							_enemyDirection != ENEMY_RIGHT_ATTACK))//왼쪽위와 왼쪽아래
					{
						_enemyDirection = ENEMY_UP_LEFT_ATTACK;
					}

					if ((_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90 &&
						_enemyDirection != ENEMY_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
						_enemyDirection != ENEMY_RIGHT_ATTACK) ||
						(_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315 &&
							_enemyDirection != ENEMY_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
							_enemyDirection != ENEMY_RIGHT_ATTACK))//오른쪽위와 오른쪽아래
					{
						_enemyDirection = ENEMY_UP_RIGHT_ATTACK;
					}

					if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45 &&
						_enemyDirection != ENEMY_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_RIGHT_ATTACK) ||//오른쪽 
						(_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360 &&
							_enemyDirection != ENEMY_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_RIGHT_ATTACK))
					{
						_enemyDirection = ENEMY_RIGHT_ATTACK;
					}
				}
			}
		}
	}
}
