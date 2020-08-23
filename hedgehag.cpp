#include "stdafx.h"
#include "hedgehag.h"
#include "scene.h"
#include "player.h"

HRESULT hedgehag::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyHedgehog", L"images/enemy/hedgehog.png", 10, 7);//에너미 이미지

	IMAGEMANAGER->addFrameImage("enemyHedgehogDust", L"images/enemy/hedgehogDust.png", 5, 2);
	IMAGEMANAGER->addFrameImage("enemyHedgehogMoveDust", L"images/enemy/hedgehogMoveDust.png", 5, 1);

	EFFECTMANAGER->addEffect("enemyHedgehogDust", "enemyHedgehogDust", 1.0f, 0.5f, 5, 1.0f);//공격상태에서 제자리에 나오는 먼지 이펙트
	EFFECTMANAGER->addEffect("enemyHedgehogMoveDust", "enemyHedgehogMoveDust", 1.0f, 0.5f, 5, 1.0f);//공격상태에서 움직이는중에 나오는 먼지 이펙트

	SOUNDMANAGER->addSound("hedgehog-propeller-old", "sounds/enemy/hedgehog-propeller-old.ogg", false, false);//공격중에 구르기 할때 나는 사운드
	SOUNDMANAGER->addSound("hedgehog-hit", "sounds/enemy/hedgehog-hit.ogg", false, false);//공격당할때 나는 사운드
	SOUNDMANAGER->addSound("hedgehog-jump", "sounds/enemy/hedgehog-jump.ogg", false, false);//점프 사운드

	_name = "hedgehag";

	_maxHP = 100;
	_currentHP = _maxHP;

	_speed = 5.0f;
	_noHitSpeed = 1.0f;
	_attackSpeed = 10.0f;

	_attackPower = RND->getFromIntTo(2, 6);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;
	_jumpSoundCount = 0;

	_isAttack = false;
	_distanceChange = false;
	_effect = false;
	_idleMove = false;
	_collision = false;

	//고슴도치 기본 애니메이션
	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_L->setPlayFrame(49, 46, false, true);
	_idleMotion_L->setFPS(1);

	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_R->setPlayFrame(53, 50, false, true);
	_idleMotion_R->setFPS(1);
	//고슴도치 기본 애니메이션

	//고슴도치 위쪽 기본 애니메이션
	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_L->setPlayFrame(9, 6, false, true);
	_idleMotion_U_L->setFPS(1);

	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_R->setPlayFrame(13, 10, false, true);
	_idleMotion_U_R->setFPS(1);
	//고슴도치 위쪽 기본 애니메이션

	//고슴도치 아래쪽 기본 애니메이션
	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_L->setPlayFrame(29, 26, false, true);
	_idleMotion_D_L->setFPS(1);

	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_R->setPlayFrame(33, 30, false, true);
	_idleMotion_D_R->setFPS(1);
	//고슴도치 아래쪽 기본 애니메이션

	//고슴도치 무브 애니메이션
	_moveMotion_L = new animation;
	_moveMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_L->setPlayFrame(45, 42, false, true);
	_moveMotion_L->setFPS(1);

	_moveMotion_R = new animation;
	_moveMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_R->setPlayFrame(57, 54, false, true);
	_moveMotion_R->setFPS(1);
	//고슴도치 무브 애니메이션

	//고슴도치 위쪽 무브 애니메이션
	_moveMotion_U_L = new animation;
	_moveMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_L->setPlayFrame(5, 2, false, true);
	_moveMotion_U_L->setFPS(1);

	_moveMotion_U_R = new animation;
	_moveMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_R->setPlayFrame(17, 14, false, true);
	_moveMotion_U_R->setFPS(1);
	//고슴도치 위쪽 무브 애니메이션

	//고슴도치 아래쪽 무브 애니메이션
	_moveMotion_D_L = new animation;
	_moveMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_L->setPlayFrame(25, 22, false, true);
	_moveMotion_D_L->setFPS(1);

	_moveMotion_D_R = new animation;
	_moveMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_R->setPlayFrame(37, 34, false, true);
	_moveMotion_D_R->setFPS(1);
	//고슴도치 아래쪽 무브 애니메이션

	//고슴도치 공격당할때 애니메이션
	_hitMotion_L = new animation;
	_hitMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_L->setPlayFrame(41, 40, false, false);
	_hitMotion_L->setFPS(1);

	_hitMotion_R = new animation;
	_hitMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_R->setPlayFrame(59, 58, false, false);
	_hitMotion_R->setFPS(1);
	//고슴도치 공격당할때 애니메이션

	//고슴도치 위쪽 공격당할때 애니메이션
	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_L->setPlayFrame(1, 0, false, false);
	_hitMotion_U_L->setFPS(1);

	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_R->setPlayFrame(19, 18, false, false);
	_hitMotion_U_R->setFPS(1);
	//고슴도치 위쪽 공격당할때 애니메이션

	//고슴도치 아래쪽 공격당할때 애니메이션
	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_L->setPlayFrame(21, 20, false, false);
	_hitMotion_D_L->setFPS(1);

	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_R->setPlayFrame(39, 38, false, false);
	_hitMotion_D_R->setFPS(1);
	//고슴도치 아래쪽 공격당할때 애니메이션

	//고슴도치 공격 애니메이션
	_attackMotion_L = new animation;
	_attackMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_L->setPlayFrame(63, 62, false, true);
	_attackMotion_L->setFPS(1);

	_attackMotion_R = new animation;
	_attackMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_R->setPlayFrame(65, 64, false, true);
	_attackMotion_R->setFPS(1);
	//고슴도치 공격 애니메이션

	//고슴도치 위아래 공격 애니메이션
	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_L->setPlayFrame(61, 60, false, true);
	_attackMotion_U_L->setFPS(1);

	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_R->setPlayFrame(67, 66, false, true);
	_attackMotion_U_R->setFPS(1);
	//고슴도치 위아래 공격 애니메이션

	_width = 70;
	_height = 70;

	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);
	
	_nowOrder = 1;
	//_angleCount = 0;

	return S_OK;
}

void hedgehag::release()
{
}

void hedgehag::update()
{
	tileGet();//에너미의 타일검출 위치 가져오기
	currentTileGet();//현재 에너미의 타일번호를 _nowOrder에 대입
	move();//에너미 무브
	mapOutCollision();//에너미가 맵밖으로 벗어나는걸 방지하기 위한 함수
	animationControl();//에너미 애니메이션 컨트롤
	animationAngleControl();//에너미와 플레이어간의 앵글값에 따른 애니메이션 컨트롤
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 7);//에너미 애니메이션 업데이트
	angry();//에너미의 체력이 절반 이하가 되면 능력치 상승(공격력, 스피드, 공격딜레이)
	if (_effect)//에너미가 공격상태에서 움직이지 않은경우
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x, CAMERA->getRelativeVector2(_position).y + 40), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 40, CAMERA->getRelativeVector2(_position).y + 40), 0, 0.5f);
	}
	if (!_effect && _isAttack)//에너미가 공격상태이고 움직였을경우
	{
		EFFECTMANAGER->play("enemyHedgehogMoveDust", Vector2(CAMERA->getRelativeVector2(_position).x + 20, CAMERA->getRelativeVector2(_position).y + 40), 0, 0.5f);
	}
	_currentHpBar.update(Vector2(_position.x - 50, _position.y + 50), Vector2(_currentHP, 5), pivot::LEFTTOP);
	//cout << "고슴도치 : " << _currentHP << endl;
}

void hedgehag::render()
{
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_attackRC), D2DRenderer::DefaultBrush::Black, 2.f);//에너미 공격렉트
	_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
	_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//에너미 애니메이션 재생
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));//에너미 렉트
	//for (int i = 0; i < 3; i++)
	//{
	//	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_t[i]->getRect()));
	//}

	//for (int i = 0; i < _move.size(); ++i)
	//{
	//	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_move[i]->getRect()));
	//}
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_currentHpBar), D2D1::ColorF::Red, 0);
}

void hedgehag::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x;
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y;
	int playerNowOrder = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"))->getNowOrder();

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//에너미의 현재 체력이 멕스hp보다 작아지면
	{
		_idleMove = false;

		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (!_distanceChange && !_isAttack) //거리가 멀고 공격중이 아니면
			{
				if (_move.size() != NULL)
				{
					float d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					float an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					_position.x += cosf(an) * _speed;
					_position.y += -sinf(an) * _speed;

					if (d < 5)
					{
						deleteMove();
					}
				}
			}

			if (_distanceChange && !_isAttack && _nowOrder < playerNowOrder) //거리가 가깝고 공격중이 아니면
			{
				if (_move.size() != NULL)
				{
					float d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					float an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					_position.x += cosf(an) * _speed;
					_position.y += -sinf(an) * _speed;

					if (d < 5)
					{
						deleteMove();
					}
				}
			}

			if (!_isAttack && _t[0]->getOrderIndex() == 4 ||
				!_isAttack && _t[0]->getOrderIndex() == 5 ||
				!_isAttack && _t[0]->getOrderIndex() == 6 ||
				!_isAttack && _t[1]->getOrderIndex() == 4 ||
				!_isAttack && _t[1]->getOrderIndex() == 5 ||
				!_isAttack && _t[1]->getOrderIndex() == 6 ||
				!_isAttack && _t[2]->getOrderIndex() == 4 ||
				!_isAttack && _t[2]->getOrderIndex() == 5 ||
				!_isAttack && _t[2]->getOrderIndex() == 6 ||
				!_isAttack && _nowOrder == 4 ||
				!_isAttack && _nowOrder == 5 ||
				!_isAttack && _nowOrder == 6 ||
				!_isAttack && _nowOrder > playerNowOrder)
			{
				if (_move.size() != NULL)
				{
					float d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					float an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					_position.x += cosf(an) * _speed;
					_position.y += -sinf(an) * _speed;

					if (d < 5)
					{
						deleteMove();
					}
				}
			}

			if (_distanceChange && _nowOrder == playerNowOrder)//거리가 가깝고 층이 같으면
			{
				_attackDelay++;//공격딜레이
				if (_attackDelay >= _maxAttackDelay && !_isAttack)//공격딜레이가 일정시간 도달했고 공격상태가 아니면
				{
					_angleSave = _angle;
					_playerSaveX = _playerX;
					_playerSaveY = _playerY;
					_isAttack = true;
				}
			}

			if (_isAttack)
			{
				_effect = true;
				_attackCount++;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
				_distanceSave = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerSaveX, _playerSaveY) + 200;
			}

			if (_distanceSave > 10 && _distanceSave < 750)//에너미와 플레이어간의 임시적으로 저장해놨던 거리값이 10보다 크면 계속 이동
			{
				if (_attackCount >= 25)//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
				{
					_attackRC.update(Vector2(_position.x, _position.y), Vector2(70, 70), pivot::CENTER);//에너미 공격렉트
					_effect = false;

					if (_t[0]->getOrderIndex() - _nowOrder == 1 ||
						_t[1]->getOrderIndex() - _nowOrder == 1 ||
						_t[2]->getOrderIndex() - _nowOrder == 1 ||
						_t[0]->getOrderIndex() == 4 ||
						_t[1]->getOrderIndex() == 4 ||
						_t[2]->getOrderIndex() == 4 ||
						_t[0]->getOrderIndex() == 5 ||
						_t[1]->getOrderIndex() == 5 ||
						_t[2]->getOrderIndex() == 5 ||
						_nowOrder == playerNowOrder)
					{
						_position.x += cosf(_angleSave) * _attackSpeed;
						_position.y += -sinf(_angleSave) * _attackSpeed;
					}

					else
					{
						_isAttack = false;
						_attackDelay = 0;//공격딜레이
						_attackCount = 0;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
					}
				}
			}
			else if(_distanceSave <= 10 && _isAttack || _distanceSave >= 750 && _isAttack)
			{
				_effect = false;
				_isAttack = false;
				_attackDelay = 0;//공격딜레이
				_attackCount = 0;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
			}

			if (_distance > 500)//플레이어와 에너미의 거리가 250보다 크면
			{
				_distanceChange = false;
			}
			else
			{
				_distanceChange = true;
			}

			if (_t[0]->getOrderIndex() == 4 ||
				_t[0]->getOrderIndex() == 5 ||
				_t[0]->getOrderIndex() == 6 ||
				_t[1]->getOrderIndex() == 4 ||
				_t[1]->getOrderIndex() == 5 ||
				_t[1]->getOrderIndex() == 6 ||
				_t[2]->getOrderIndex() == 4 ||
				_t[2]->getOrderIndex() == 5 ||
				_t[2]->getOrderIndex() == 6 ||
				_nowOrder == 4 ||
				_nowOrder == 5 ||
				_nowOrder == 6)
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

				if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//오른쪽
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

				_jumpSoundCount++;
				if (_jumpSoundCount % 15 == 0)
				{
					if (!SOUNDMANAGER->isPlaySound("hedgehog-jump"))
					{
						SOUNDMANAGER->play("hedgehog-jump", 0.5f);
					}
					_jumpSoundCount = 0;
				}
			}
		}
		if (!_isAttack)//에너미의 공격상태값이 펄스면
		{
			_attackRC.update(Vector2(_position.x, _position.y), Vector2(0, 0), pivot::CENTER);//에너미의 공격 렉트크기 0
		}
	}
	else//데미지를 받지 않았을때
	{
		if (!_idleMove)
		{
			_playerSaveX = _position.x + RND->getFromIntTo(-50, 50);
			_playerSaveY = _position.y + RND->getFromIntTo(-50, 50);
			_idleMove = true;
		}

		_distanceSave = getDistance(_position.x, _position.y, _playerSaveX, _playerSaveY);
		_angleSave = getAngle(_position.x, _position.y, _playerSaveX, _playerSaveY);

		if (_distanceSave > 10 && tileMove())
		{
			_position.x += cosf(_angleSave) * _noHitSpeed;
			_position.y += -sinf(_angleSave) * _noHitSpeed;
		}
		else
		{
			_position.x += cosf(_angleSave + PI) * _noHitSpeed;
			_position.y += -sinf(_angleSave + PI) * _noHitSpeed;
			_idleMove = false;
		}
	}

	_rc.set(_position, pivot::CENTER);//에너미 렉트 위치 업데이트
	_attackRC.set(_position, pivot::CENTER);//에너미 공격 렉트 위치 업데이트
}

void hedgehag::tileGet()
{
	_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);

	int k = 1;
	currentTileIndex = Vector2(_tile.left / SIZE, _tile.top / SIZE);//현재에너미 위치에 타일

	if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//왼쪽
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y);
		nextTileIndex[1] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);
		nextTileIndex[2] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);
	}

	if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//왼쪽위
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y - k);
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
	}

	if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//오른쪽위
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y - k);
		nextTileIndex[2] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);
	}

	if ((_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45) || (_angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360))//오른쪽
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y);
		nextTileIndex[1] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
	}

	if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//아래오른쪽
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y + k);
		nextTileIndex[2] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);
	}

	if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//아래왼쪽
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y + k);
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
	}

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
}

void hedgehag::currentTileGet()
{
	_currentTileSave = Vector2(currentTileIndex.x, currentTileIndex.y);
	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;
	//다음 타일
	if (_currentTileSave.x > maxTileX) _currentTileSave.x = maxTileX;
	else if (_currentTileSave.x < 0) _currentTileSave.x = 0;
	if (_currentTileSave.y > maxTileY) _currentTileSave.y = maxTileY;
	else if (_currentTileSave.y < 0) _currentTileSave.y = 0;
	_currentTile = SCENEMANAGER->getCurrentScene()->getTiles()[_currentTileSave.y][_currentTileSave.x];
	_nowOrder = _currentTile->getOrderIndex();
}

void hedgehag::mapOutCollision()
{
	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;
	maxTileX *= SIZE;
	maxTileY *= SIZE;

	if (_position.x < 0)
	{
		_position.x += abs(0 - _rc.left);
		_effect = false;
		_isAttack = false;
		_attackDelay = 0;//공격딜레이
		_attackCount = 0;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
	}
	if (_position.x > maxTileX)
	{
		_position.x -= _rc.right - maxTileX;
		_effect = false;
		_isAttack = false;
		_attackDelay = 0;//공격딜레이
		_attackCount = 0;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
	}
	if (_position.y < 0)
	{
		_position.y += abs(0 - _rc.top);
		_effect = false;
		_isAttack = false;
		_attackDelay = 0;//공격딜레이
		_attackCount = 0;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
	}
	if (_position.y > maxTileY)
	{
		_position.y -= _rc.bottom - maxTileY;
		_effect = false;
		_isAttack = false;
		_attackDelay = 0;//공격딜레이
		_attackCount = 0;//에너미 공격상태에서 플레이어에게 공격하기까지의 딜레이
	}
}

bool hedgehag::tileMove()
{
	for (int i = 0; i < 3; i++)
	{
		//물
		if (_t[i]->getOrderIndex() == 0)
		{
			//cout << "물" << endl;
			return false;
		}

		//1층
		if (_t[i]->getOrderIndex() == 1)
		{
			//cout << "1층" << endl;
			return true;
		}

		//2층
		if (_t[i]->getOrderIndex() == 2 && _t[0]->getOrderIndex() - _nowOrder == 1)
		{
			//cout << "2층" << endl;
			return true;
		}

		//3층
		if (_t[i]->getOrderIndex() == 3 && _t[0]->getOrderIndex() - _nowOrder == 1)
		{
			//cout << "3층" << endl;
			return true;
		}

		//2층 모서리(Z-ORDER용)
		if (_t[i]->getOrderIndex() == 4 || _nowOrder == 4)
		{
			//cout << "2층 모서리" << endl;
			return false;
		}

		//갈 수 있는 모서리
		if (_t[i]->getOrderIndex() == 5 || _nowOrder == 5)
		{
			//cout << "갈 수 있는 모서리" << endl;
			return false;
		}

		//현재 내 타일과 다음검사 타일이 같으면
		//if (_t[i]->getOrderIndex() == _nowOrder)
		if (_t[0]->getOrderIndex() == _nowOrder &&
			_t[1]->getOrderIndex() == _nowOrder &&
			_t[2]->getOrderIndex() == _nowOrder)
		{
			//cout << "현재 내 타일 == 검사타일" << endl;
			return true;
		}

		//이동불가능
		if (_t[i]->getOrderIndex() == 6 || _nowOrder == 6)
		{
			//cout << "이동불가" << endl;
			return false;
		}
	}
}

void hedgehag::animationControl()
{
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_enemyMotion = _idleMotion_L;
		break;
	case ENEMY_RIGHT_IDLE:
		_enemyMotion = _idleMotion_R;
		break;
	case ENEMY_UP_LEFT_IDLE:
		_enemyMotion = _idleMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_enemyMotion = _idleMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_enemyMotion = _idleMotion_D_L;
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_enemyMotion = _idleMotion_D_R;
		break;
	case ENEMY_LEFT_MOVE:
		_enemyMotion = _moveMotion_L;
		break;
	case ENEMY_RIGHT_MOVE:
		_enemyMotion = _moveMotion_R;
		break;
	case ENEMY_UP_LEFT_MOVE:
		_enemyMotion = _moveMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_MOVE:
		_enemyMotion = _moveMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		_enemyMotion = _moveMotion_D_L;
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		_enemyMotion = _moveMotion_D_R;
		break;
	case ENEMY_LEFT_HIT:
		_enemyMotion = _hitMotion_L;

		if (!SOUNDMANAGER->isPlaySound("hedgehog-hit"))
		{
			SOUNDMANAGER->play("hedgehog-hit", 0.5f);
		}

		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_LEFT_IDLE;
		}
		break;
	case ENEMY_RIGHT_HIT:
		_enemyMotion = _hitMotion_R;

		if (!SOUNDMANAGER->isPlaySound("hedgehog-hit"))
		{
			SOUNDMANAGER->play("hedgehog-hit", 0.5f);
		}

		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_RIGHT_IDLE;
		}
		break;
	case ENEMY_UP_LEFT_HIT:
		_enemyMotion = _hitMotion_U_L;

		if (!SOUNDMANAGER->isPlaySound("hedgehog-hit"))
		{
			SOUNDMANAGER->play("hedgehog-hit", 0.5f);
		}

		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
		}
		break;
	case ENEMY_UP_RIGHT_HIT:
		_enemyMotion = _hitMotion_U_R;

		if (!SOUNDMANAGER->isPlaySound("hedgehog-hit"))
		{
			SOUNDMANAGER->play("hedgehog-hit", 0.5f);
		}

		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
		}
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_enemyMotion = _hitMotion_D_L;

		if (!SOUNDMANAGER->isPlaySound("hedgehog-hit"))
		{
			SOUNDMANAGER->play("hedgehog-hit", 0.5f);
		}

		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_enemyMotion = _hitMotion_D_R;

		if (!SOUNDMANAGER->isPlaySound("hedgehog-hit"))
		{
			SOUNDMANAGER->play("hedgehog-hit", 0.5f);
		}

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
	int playerNowOrder = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"))->getNowOrder();

	if (_maxHP > _currentHP)//에너미의 현재 체력이 멕스HP보다 작아지면
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

				if (!_isAttack && _nowOrder == playerNowOrder)
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

					if (!SOUNDMANAGER->isPlaySound("hedgehog-propeller-old"))
					{
						SOUNDMANAGER->play("hedgehog-propeller-old", 0.5f);
					}
				}
			}
		}
	}
	else//데미지를 받지 않았을때
	{
		if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//왼쪽
		{
			_enemyDirection = ENEMY_LEFT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//왼쪽위
		{
			_enemyDirection = ENEMY_UP_LEFT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//오른쪽위
		{
			_enemyDirection = ENEMY_UP_RIGHT_MOVE;
		}

		if ((_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45) || (_angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360))//오른쪽
		{
			_enemyDirection = ENEMY_RIGHT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//아래오른쪽
		{
			_enemyDirection = ENEMY_DOWN_RIGHT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//아래왼쪽
		{
			_enemyDirection = ENEMY_DOWN_LEFT_MOVE;
		}
	}
}


