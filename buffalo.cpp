#include "stdafx.h"
#include "buffalo.h"
#include "scene.h"
#include "player.h"

HRESULT buffalo::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyIdleMoveAttackPrepare", L"images/enemy/buffalo_idle_move_attackPrepare.png", 6, 18);
	_attackImage = IMAGEMANAGER->addFrameImage("enemyAttack", L"images/enemy/buffalo_attack.png", 6, 12);
	_hitImage = IMAGEMANAGER->addFrameImage("enemyHit", L"images/enemy/buffalo_hit.png", 4, 6);

	_name = "buffalo";

	_maxHP = 100;
	_currentHP = _maxHP;

	_speed = 5.0f;
	_noHitSpeed = 1.0f;
	_attackSpeed = 10.0f;

	_attackPower = RND->getFromIntTo(10, 20);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;

	_isAttack = false;
	_distanceChange = false;
	_idleMove = false;
	_oneAnimation = false;
	_wallCollision = false;

	//버팔로 위쪽 기본 애니메이션
	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_R->setPlayFrame(0, 3, false, true);
	_idleMotion_U_R->setFPS(1);

	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_L->setPlayFrame(21, 18, false, true);
	_idleMotion_U_L->setFPS(1);
	//버팔로 위쪽 기본 애니메이션

	//버팔로 기본 애니메이션
	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_R->setPlayFrame(6, 9, false, true);
	_idleMotion_R->setFPS(1);

	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_L->setPlayFrame(27, 24, false, true);
	_idleMotion_L->setFPS(1);
	//버팔로 기본 애니메이션

	//버팔로 아래쪽 기본 애니메이션
	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_R->setPlayFrame(12, 15, false, true);
	_idleMotion_D_R->setFPS(1);

	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_L->setPlayFrame(33, 30, false, true);
	_idleMotion_D_L->setFPS(1);
	//버팔로 아래쪽 기본 애니메이션

	//버팔로 위쪽 무브 애니메이션
	_moveMotion_U_R = new animation;
	_moveMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_R->setPlayFrame(36, 39, false, true);
	_moveMotion_U_R->setFPS(1);

	_moveMotion_U_L = new animation;
	_moveMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_L->setPlayFrame(57, 54, false, true);
	_moveMotion_U_L->setFPS(1);
	//버팔로 위쪽 무브 애니메이션

	//버팔로 무브 애니메이션
	_moveMotion_R = new animation;
	_moveMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_R->setPlayFrame(42, 45, false, true);
	_moveMotion_R->setFPS(1);

	_moveMotion_L = new animation;
	_moveMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_L->setPlayFrame(63, 60, false, true);
	_moveMotion_L->setFPS(1);
	//버팔로 무브 애니메이션

	//버팔로 아래쪽 무브 애니메이션
	_moveMotion_D_R = new animation;
	_moveMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_R->setPlayFrame(48, 51, false, true);
	_moveMotion_D_R->setFPS(1);

	_moveMotion_D_L = new animation;
	_moveMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_L->setPlayFrame(69, 66, false, true);
	_moveMotion_D_L->setFPS(1);
	//버팔로 아래쪽 무브 애니메이션

	//버팔로 위쪽 돌진공격준비 애니메이션
	_attackPrepareMotion_U_R = new animation;
	_attackPrepareMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_U_R->setPlayFrame(72, 77, false, false);
	_attackPrepareMotion_U_R->setFPS(1);

	_attackPrepareMotion_U_L = new animation;
	_attackPrepareMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_U_L->setPlayFrame(96, 91, false, false);
	_attackPrepareMotion_U_L->setFPS(1);
	//버팔로 위쪽 돌진공격준비 애니메이션

	//버팔로 돌진공격준비 애니메이션
	_attackPrepareMotion_R = new animation;
	_attackPrepareMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_R->setPlayFrame(78, 83, false, false);
	_attackPrepareMotion_R->setFPS(1);

	_attackPrepareMotion_L = new animation;
	_attackPrepareMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_L->setPlayFrame(101, 96, false, false);
	_attackPrepareMotion_L->setFPS(1);
	//버팔로 돌진공격준비 애니메이션

	//버팔로 아래쪽 돌진공격준비 애니메이션
	_attackPrepareMotion_D_R = new animation;
	_attackPrepareMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_D_R->setPlayFrame(84, 89, false, false);
	_attackPrepareMotion_D_R->setFPS(1);

	_attackPrepareMotion_D_L = new animation;
	_attackPrepareMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_D_L->setPlayFrame(107, 102, false, false);
	_attackPrepareMotion_D_L->setFPS(1);
	//버팔로 아래쪽 돌진공격준비 애니메이션

	//버팔로 위쪽 근접공격 애니메이션
	_meleeAttackMotion_U_R = new animation;
	_meleeAttackMotion_U_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_U_R->setPlayFrame(0, 3, false, false);
	_meleeAttackMotion_U_R->setFPS(1);

	_meleeAttackMotion_U_L = new animation;
	_meleeAttackMotion_U_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_U_L->setPlayFrame(21, 18, false, false);
	_meleeAttackMotion_U_L->setFPS(1);
	//버팔로 위쪽 근접공격 애니메이션

	//버팔로 근접공격 애니메이션
	_meleeAttackMotion_R = new animation;
	_meleeAttackMotion_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_R->setPlayFrame(6, 9, false, false);
	_meleeAttackMotion_R->setFPS(1);

	_meleeAttackMotion_L = new animation;
	_meleeAttackMotion_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_L->setPlayFrame(27, 24, false, false);
	_meleeAttackMotion_L->setFPS(1);
	//버팔로 근접공격 애니메이션

	//버팔로 아래쪽 근접공격 애니메이션
	_meleeAttackMotion_D_R = new animation;
	_meleeAttackMotion_D_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_D_R->setPlayFrame(12, 15, false, false);
	_meleeAttackMotion_D_R->setFPS(1);

	_meleeAttackMotion_D_L = new animation;
	_meleeAttackMotion_D_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_D_L->setPlayFrame(33, 30, false, false);
	_meleeAttackMotion_D_L->setFPS(1);
	//버팔로 아래쪽 근접공격 애니메이션

	//버팔로 위쪽 돌진공격 애니메이션
	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_U_R->setPlayFrame(37, 40, false, true);
	_attackMotion_U_R->setFPS(1);

	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_U_L->setPlayFrame(58, 55, false, true);
	_attackMotion_U_L->setFPS(1);
	//버팔로 위쪽 돌진공격 애니메이션

	//버팔로 돌진공격 애니메이션
	_attackMotion_R = new animation;
	_attackMotion_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_R->setPlayFrame(42, 47, false, true);
	_attackMotion_R->setFPS(1);

	_attackMotion_L = new animation;
	_attackMotion_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_L->setPlayFrame(65, 60, false, true);
	_attackMotion_L->setFPS(1);
	//버팔로 돌진공격 애니메이션

	//버팔로 아래쪽 돌진공격 애니메이션
	_attackMotion_D_R = new animation;
	_attackMotion_D_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_D_R->setPlayFrame(48, 53, false, true);
	_attackMotion_D_R->setFPS(1);

	_attackMotion_D_L = new animation;
	_attackMotion_D_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_D_L->setPlayFrame(71, 66, false, true);
	_attackMotion_D_L->setFPS(1);
	//버팔로 아래쪽 돌진공격 애니메이션

	//버팔로 위쪽 히트 애니메이션
	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_U_R->setPlayFrame(0, 3, false, false);
	_hitMotion_U_R->setFPS(1);

	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_U_L->setPlayFrame(15, 12, false, false);
	_hitMotion_U_L->setFPS(1);
	//버팔로 위쪽 히트 애니메이션

	//버팔로 히트 애니메이션
	_hitMotion_R = new animation;
	_hitMotion_R->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_R->setPlayFrame(5, 8, false, false);
	_hitMotion_R->setFPS(1);

	_hitMotion_L = new animation;
	_hitMotion_L->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_L->setPlayFrame(19, 16, false, false);
	_hitMotion_L->setFPS(1);
	//버팔로 히트 애니메이션

	//버팔로 아래쪽 히트 애니메이션
	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_D_R->setPlayFrame(8, 11, false, false);
	_hitMotion_D_R->setFPS(1);

	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_D_L->setPlayFrame(23, 20, false, false);
	_hitMotion_D_L->setFPS(1);
	//버팔로 아래쪽 히트 애니메이션

	_width = 100;
	_height = 100;

	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);

	_nowOrder = 1;

	return S_OK;
}

void buffalo::release()
{
}

void buffalo::update()
{
	tileGet();//버팔로 타일 검출 업데이트
	move();//버팔로 무브
	mapOutCollision();//에너미가 맵밖으로 벗어나는걸 방지하기 위한 함수
	animationControl();//변경된 디렉션 상태값에 따라 애니메이션 실행
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 7);//버팔로 애니메이션 업데이트
	angry();//버팔로의 체력이 절반이하가 되면 능력치 상승(스피드, 공격속도, 공격력)

	if (_enemyDirection == ENEMY_UP_LEFT_ATTACK || _enemyDirection == ENEMY_UP_RIGHT_ATTACK || _enemyDirection == ENEMY_LEFT_ATTACK || _enemyDirection == ENEMY_RIGHT_ATTACK ||
		_enemyDirection == ENEMY_DOWN_LEFT_ATTACK || _enemyDirection == ENEMY_DOWN_RIGHT_ATTACK)
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x, CAMERA->getRelativeVector2(_position).y + 40), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 40, CAMERA->getRelativeVector2(_position).y + 40), 0, 0.5f);
	}

	if (_enemyDirection == ENEMY_UP_LEFT_MELEE_ATTACK)
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 50, CAMERA->getRelativeVector2(_position).y - 30), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 25, CAMERA->getRelativeVector2(_position).y - 30), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 50, CAMERA->getRelativeVector2(_position).y - 5), 0, 0.5f);
	}

	if (_enemyDirection == ENEMY_UP_RIGHT_MELEE_ATTACK)
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y - 30), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 45, CAMERA->getRelativeVector2(_position).y - 30), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y - 5), 0, 0.5f);
	}

	if (_enemyDirection == ENEMY_LEFT_MELEE_ATTACK)
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 50, CAMERA->getRelativeVector2(_position).y), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 50, CAMERA->getRelativeVector2(_position).y + 40), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 50, CAMERA->getRelativeVector2(_position).y + 80), 0, 0.5f);
	}

	if (_enemyDirection == ENEMY_RIGHT_MELEE_ATTACK)
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 40), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 80), 0, 0.5f);
	}

	if (_enemyDirection == ENEMY_DOWN_LEFT_MELEE_ATTACK)
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 40, CAMERA->getRelativeVector2(_position).y + 100), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 15, CAMERA->getRelativeVector2(_position).y + 100), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x - 40, CAMERA->getRelativeVector2(_position).y + 75), 0, 0.5f);
	}

	if (_enemyDirection == ENEMY_DOWN_RIGHT_MELEE_ATTACK)
	{
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 60, CAMERA->getRelativeVector2(_position).y + 100), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 35, CAMERA->getRelativeVector2(_position).y + 100), 0, 0.5f);
		EFFECTMANAGER->play("enemyHedgehogDust", Vector2(CAMERA->getRelativeVector2(_position).x + 60, CAMERA->getRelativeVector2(_position).y + 75), 0, 0.5f);
	}
	_currentHpBar.update(Vector2(_position.x - 50, _position.y + 50), Vector2(_currentHP, 5), pivot::LEFTTOP);
	//cout << "버팔로 : " << _currentHP << endl;
}

void buffalo::render()
{
	animationDraw();
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));//버팔로 렉트
	//for (int i = 0; i < 3; i++)
	//{
	//	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_t[i]->getRect()));
	//}
	//for (int i = 0; i < _move.size(); i++)
	//{
	//	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_move[i]->getRect()));
	//}
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_currentHpBar), D2D1::ColorF::Red, 0);
	//D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_attackRC), D2D1::ColorF::Black, 0);//버팔로 공격렉트
}

void buffalo::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x;
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y;
	int playerNowOrder = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"))->getNowOrder();

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//공격받았으면
	{
		_idleMove = false;

		if (_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (!_distanceChange && !_isAttack && !_wallCollision &&
				_enemyDirection != ENEMY_UP_LEFT_ATTACK_PREPARE &&
				_enemyDirection != ENEMY_UP_RIGHT_ATTACK_PREPARE &&
				_enemyDirection != ENEMY_LEFT_ATTACK_PREPARE &&
				_enemyDirection != ENEMY_RIGHT_ATTACK_PREPARE &&
				_enemyDirection != ENEMY_DOWN_LEFT_ATTACK_PREPARE &&
				_enemyDirection != ENEMY_DOWN_RIGHT_ATTACK_PREPARE &&
				_enemyDirection != ENEMY_UP_LEFT_ATTACK &&
				_enemyDirection != ENEMY_UP_RIGHT_ATTACK &&
				_enemyDirection != ENEMY_LEFT_ATTACK &&
				_enemyDirection != ENEMY_RIGHT_ATTACK &&
				_enemyDirection != ENEMY_DOWN_LEFT_ATTACK &&
				_enemyDirection != ENEMY_DOWN_RIGHT_ATTACK)
			{
				if (_move.size() != NULL && playerNowOrder == 1)
				{
					d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);

					_position.x += cosf(an) * _speed;
					_position.y += -sinf(an) * _speed;

					if (d < 5)
					{
						deleteMove();
					}

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
			else if (_distanceChange && _distance > 200 && !_isAttack && !_wallCollision && playerNowOrder == 1)
			{
				_attackDelay++;
			}

			if (_attackDelay >= _maxAttackDelay && !_isAttack && !_wallCollision && playerNowOrder == 1)
			{
				_angleSave = _angle;
				_playerSaveX = _playerX;
				_playerSaveY = _playerY;

				if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//왼쪽
				{
					_enemyDirection = ENEMY_LEFT_ATTACK_PREPARE;
					_attackDelay = 0;
				}

				if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//왼쪽위
				{
					_enemyDirection = ENEMY_UP_LEFT_ATTACK_PREPARE;
					_attackDelay = 0;
				}

				if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//오른쪽위
				{
					_enemyDirection = ENEMY_UP_RIGHT_ATTACK_PREPARE;
					_attackDelay = 0;
				}

				if ((_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45) || (_angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360))//오른쪽
				{
					_enemyDirection = ENEMY_RIGHT_ATTACK_PREPARE;
					_attackDelay = 0;
				}

				if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//아래오른쪽
				{
					_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK_PREPARE;
					_attackDelay = 0;
				}

				if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//아래왼쪽
				{
					_enemyDirection = ENEMY_DOWN_LEFT_ATTACK_PREPARE;
					_attackDelay = 0;
				}
			}

			if (_isAttack)//에너미 공격시작
			{
				if (tileMove())//장애물에 부딪힌게 아니라면
				{
					if (_enemyDirection != ENEMY_UP_LEFT_MELEE_ATTACK &&
						_enemyDirection != ENEMY_UP_RIGHT_MELEE_ATTACK &&
						_enemyDirection != ENEMY_LEFT_MELEE_ATTACK &&
						_enemyDirection != ENEMY_RIGHT_MELEE_ATTACK &&
						_enemyDirection != ENEMY_DOWN_LEFT_MELEE_ATTACK &&
						_enemyDirection != ENEMY_DOWN_RIGHT_MELEE_ATTACK)
					{
						_position.x += cosf(_angleSave) * _attackSpeed;
						_position.y += -sinf(_angleSave) * _attackSpeed;
					}
				}
				else//장애물에 부딪혔으면
				{
					_wallCollision = true;
					_isAttack = false;
				}
				_attackRC.update(Vector2(_position.x, _position.y), Vector2(100, 100), pivot::CENTER);
			}

			if (_wallCollision)
			{
				_position.x += cosf(_angleSave + PI) * _attackSpeed;
				_position.y += -sinf(_angleSave + PI) * _attackSpeed;
				_count++;
				if (_count % 5 == 0)
				{
					if (_enemyDirection == ENEMY_UP_LEFT_ATTACK)
					{
						_count = 0;
						_enemyDirection = ENEMY_UP_LEFT_HIT;
					}
					if (_enemyDirection == ENEMY_UP_RIGHT_ATTACK)
					{
						_count = 0;
						_enemyDirection = ENEMY_UP_RIGHT_HIT;
					}
					if (_enemyDirection == ENEMY_LEFT_ATTACK)
					{
						_count = 0;
						_enemyDirection = ENEMY_LEFT_HIT;
					}
					if (_enemyDirection == ENEMY_RIGHT_ATTACK)
					{
						_count = 0;
						_enemyDirection = ENEMY_RIGHT_HIT;
					}
					if (_enemyDirection == ENEMY_DOWN_LEFT_ATTACK)
					{
						_count = 0;
						_enemyDirection = ENEMY_DOWN_LEFT_HIT;
					}
					if (_enemyDirection == ENEMY_DOWN_RIGHT_ATTACK)
					{
						_count = 0;
						_enemyDirection = ENEMY_DOWN_RIGHT_HIT;
					}
					_wallCollision = false;
				}
			}

			if (_distance <= 200 && !_isAttack && tileMove() && !_wallCollision)
			{
				_count++;
				if (_count % 55 == 0)
				{
					if (_enemyDirection != ENEMY_UP_LEFT_ATTACK_PREPARE &&
						_enemyDirection != ENEMY_UP_RIGHT_ATTACK_PREPARE &&
						_enemyDirection != ENEMY_LEFT_ATTACK_PREPARE &&
						_enemyDirection != ENEMY_RIGHT_ATTACK_PREPARE &&
						_enemyDirection != ENEMY_DOWN_LEFT_ATTACK_PREPARE &&
						_enemyDirection != ENEMY_DOWN_RIGHT_ATTACK_PREPARE)
					{
						if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//왼쪽
						{
							_enemyDirection = ENEMY_LEFT_MELEE_ATTACK;
							_count = 0;
						}

						if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//왼쪽위
						{
							_enemyDirection = ENEMY_UP_LEFT_MELEE_ATTACK;
							_count = 0;
						}

						if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//오른쪽위
						{
							_enemyDirection = ENEMY_UP_RIGHT_MELEE_ATTACK;
							_count = 0;
						}

						if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//오른쪽
						{
							_enemyDirection = ENEMY_RIGHT_MELEE_ATTACK;
							_count = 0;
						}

						if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//아래오른쪽
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_MELEE_ATTACK;
							_count = 0;
						}

						if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//아래왼쪽
						{
							_enemyDirection = ENEMY_DOWN_LEFT_MELEE_ATTACK;
							_count = 0;
						}
					}
				}
			}
		}

		if (_enemyDirection == ENEMY_UP_LEFT_ATTACK_PREPARE)
		{
			if (_attackCount >= 3 && !_enemyMotion->isPlay())
			{
				_enemyDirection = ENEMY_UP_LEFT_ATTACK;
				_isAttack = true;
				_attackCount = 0;
			}
		}

		if (_enemyDirection == ENEMY_UP_RIGHT_ATTACK_PREPARE)
		{
			if (_attackCount >= 3 && !_enemyMotion->isPlay())
			{
				_enemyDirection = ENEMY_UP_RIGHT_ATTACK;
				_isAttack = true;
				_attackCount = 0;
			}
		}

		if (_enemyDirection == ENEMY_LEFT_ATTACK_PREPARE)
		{
			if (_attackCount >= 3 && !_enemyMotion->isPlay())
			{
				_enemyDirection = ENEMY_LEFT_ATTACK;
				_isAttack = true;
				_attackCount = 0;
			}
		}

		if (_enemyDirection == ENEMY_RIGHT_ATTACK_PREPARE)
		{
			if (_attackCount >= 3 && !_enemyMotion->isPlay())
			{
				_enemyDirection = ENEMY_RIGHT_ATTACK;
				_isAttack = true;
				_attackCount = 0;
			}
		}

		if (_enemyDirection == ENEMY_DOWN_LEFT_ATTACK_PREPARE)
		{
			if (_attackCount >= 3 && !_enemyMotion->isPlay())
			{
				_enemyDirection = ENEMY_DOWN_LEFT_ATTACK;
				_isAttack = true;
				_attackCount = 0;
			}
		}

		if (_enemyDirection == ENEMY_DOWN_RIGHT_ATTACK_PREPARE)
		{
			if (_attackCount >= 3 && !_enemyMotion->isPlay())
			{
				_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK;
				_isAttack = true;
				_attackCount = 0;
			}
		}

		if (_distance > 450)
		{
			_distanceChange = false;
		}
		else
		{
			_distanceChange = true;
		}

		if (!_isAttack)//버팔로의 공격상태값이 펄스면
		{
			_attackRC.update(Vector2(_position.x, _position.y), Vector2(0, 0), pivot::CENTER);
		}

	}
	else//공격받지 않았으면
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

	_rc.set(_position, pivot::CENTER);//버팔로 렉트 위치 업데이트
	//_attackRC.set(_position, pivot::CENTER);//버팔로 공격렉트 위치 업데이트
}

void buffalo::animationDraw()
{
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_enemyAnimationImage = _enemyImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_RIGHT_IDLE:
		_enemyAnimationImage = _enemyImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_UP_LEFT_IDLE:
		_enemyAnimationImage = _enemyImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_enemyAnimationImage = _enemyImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_enemyAnimationImage = _enemyImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_enemyAnimationImage = _enemyImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_LEFT_MOVE:
		_enemyAnimationImage = _enemyImage;
		break;
	case ENEMY_RIGHT_MOVE:
		_enemyAnimationImage = _enemyImage;
		break;
	case ENEMY_UP_LEFT_MOVE:
		_enemyAnimationImage = _enemyImage;
		break;
	case ENEMY_UP_RIGHT_MOVE:
		_enemyAnimationImage = _enemyImage;
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		_enemyAnimationImage = _enemyImage;
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		_enemyAnimationImage = _enemyImage;
		break;
	case ENEMY_LEFT_HIT:
		_enemyAnimationImage = _hitImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_RIGHT_HIT:
		_enemyAnimationImage = _hitImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_UP_LEFT_HIT:
		_enemyAnimationImage = _hitImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_UP_RIGHT_HIT:
		_enemyAnimationImage = _hitImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_enemyAnimationImage = _hitImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_enemyAnimationImage = _hitImage;

		if (SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->stop("buffalo-run");
		}
		break;
	case ENEMY_LEFT_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->play("buffalo-run", 0.5f);
		}
		break;
	case ENEMY_RIGHT_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->play("buffalo-run", 0.5f);
		}
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->play("buffalo-run", 0.5f);
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->play("buffalo-run", 0.5f);
		}
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->play("buffalo-run", 0.5f);
		}
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-run"))
		{
			SOUNDMANAGER->play("buffalo-run", 0.5f);
		}
		break;
	case ENEMY_UP_LEFT_ATTACK_PREPARE:
		_enemyAnimationImage = _enemyImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-gasp"))
		{
			SOUNDMANAGER->play("buffalo-gasp", 0.5f);
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK_PREPARE:
		_enemyAnimationImage = _enemyImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-gasp"))
		{
			SOUNDMANAGER->play("buffalo-gasp", 0.5f);
		}
		break;
	case ENEMY_LEFT_ATTACK_PREPARE:
		_enemyAnimationImage = _enemyImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-gasp"))
		{
			SOUNDMANAGER->play("buffalo-gasp", 0.5f);
		}
		break;
	case ENEMY_RIGHT_ATTACK_PREPARE:
		_enemyAnimationImage = _enemyImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-gasp"))
		{
			SOUNDMANAGER->play("buffalo-gasp", 0.5f);
		}
		break;
	case ENEMY_DOWN_LEFT_ATTACK_PREPARE:
		_enemyAnimationImage = _enemyImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-gasp"))
		{
			SOUNDMANAGER->play("buffalo-gasp", 0.5f);
		}
		break;
	case ENEMY_DOWN_RIGHT_ATTACK_PREPARE:
		_enemyAnimationImage = _enemyImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-gasp"))
		{
			SOUNDMANAGER->play("buffalo-gasp", 0.5f);
		}
		break;
	case ENEMY_UP_LEFT_MELEE_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-attack"))
		{
			SOUNDMANAGER->play("buffalo-attack", 0.5f);
		}
		break;
	case ENEMY_UP_RIGHT_MELEE_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-attack"))
		{
			SOUNDMANAGER->play("buffalo-attack", 0.5f);
		}
		break;
	case ENEMY_LEFT_MELEE_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-attack"))
		{
			SOUNDMANAGER->play("buffalo-attack", 0.5f);
		}
		break;
	case ENEMY_RIGHT_MELEE_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-attack"))
		{
			SOUNDMANAGER->play("buffalo-attack", 0.5f);
		}
		break;
	case ENEMY_DOWN_LEFT_MELEE_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-attack"))
		{
			SOUNDMANAGER->play("buffalo-attack", 0.5f);
		}
		break;
	case ENEMY_DOWN_RIGHT_MELEE_ATTACK:
		_enemyAnimationImage = _attackImage;

		if (!SOUNDMANAGER->isPlaySound("buffalo-attack"))
		{
			SOUNDMANAGER->play("buffalo-attack", 0.5f);
		}
		break;
	}
	_enemyAnimationImage->setSize(Vector2(_enemyAnimationImage->getFrameSize()) * CAMERA->getZoomAmount());
	_enemyAnimationImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//버팔로 애니메이션 재생
}

void buffalo::animationControl()
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
		_enemyMotion = _moveMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_MOVE:
		_enemyMotion = _moveMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_MOVE:
		_enemyMotion = _moveMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_MOVE:
		_enemyMotion = _moveMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		_enemyMotion = _moveMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		_enemyMotion = _moveMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_LEFT_HIT:
		_enemyMotion = _hitMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_LEFT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_RIGHT_HIT:
		_enemyMotion = _hitMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_RIGHT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_UP_LEFT_HIT:
		_enemyMotion = _hitMotion_U_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_UP_LEFT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_UP_RIGHT_HIT:
		_enemyMotion = _hitMotion_U_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_UP_RIGHT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_enemyMotion = _hitMotion_D_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_enemyMotion = _hitMotion_D_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_LEFT_ATTACK:
		_enemyMotion = _attackMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}

		if (_isAttack)
		{
			_attackRC.set(_position, pivot::CENTER);
		}
		break;
	case ENEMY_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}

		if (_isAttack)
		{
			_attackRC.set(_position, pivot::CENTER);
		}
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_enemyMotion = _attackMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}

		if (_isAttack)
		{
			_attackRC.set(_position, pivot::CENTER);
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}

		if (_isAttack)
		{
			_attackRC.set(_position, pivot::CENTER);
		}
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		_enemyMotion = _attackMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}

		if (_isAttack)
		{
			_attackRC.set(_position, pivot::CENTER);
		}
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}

		if (_isAttack)
		{
			_attackRC.set(_position, pivot::CENTER);
		}
		break;
	case ENEMY_UP_LEFT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}
		break;
	case ENEMY_LEFT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		break;
	case ENEMY_DOWN_LEFT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		break;
	case ENEMY_DOWN_RIGHT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_U_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}

		if (_isAttack)
		{
			_attackRC.set(Vector2(_position.x - 50, _position.y - 50), pivot::CENTER);
		}
		break;
	case ENEMY_UP_RIGHT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_U_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}

		if (_isAttack)
		{
			_attackRC.set(Vector2(_position.x + 50, _position.y - 50), pivot::CENTER);
		}
		break;
	case ENEMY_LEFT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_LEFT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}

		if (_isAttack)
		{
			_attackRC.set(Vector2(_position.x - 50, _position.y), pivot::CENTER);
		}
		break;
	case ENEMY_RIGHT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_RIGHT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}

		if (_isAttack)
		{
			_attackRC.set(Vector2(_position.x + 50, _position.y), pivot::CENTER);
		}
		break;
	case ENEMY_DOWN_LEFT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_D_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}

		if (_isAttack)
		{
			_attackRC.set(Vector2(_position.x - 50, _position.y + 50), pivot::CENTER);
		}
		break;
	case ENEMY_DOWN_RIGHT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_D_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}

		if (_isAttack)
		{
			_attackRC.set(Vector2(_position.x + 50, _position.y + 50), pivot::CENTER);
		}
		break;
	}
}

void buffalo::tileGet()
{
	//vector<vector<tile*>> _vTilesSave = SCENEMANAGER->getCurrentScene()->getTiles();

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
	//_t[0] = _vTilesSave[nextTileIndex[0].y][nextTileIndex[0].x];

	//다음 타일
	if (nextTileIndex[1].x > maxTileX) nextTileIndex[1].x = maxTileX;
	else if (nextTileIndex[1].x < 0) nextTileIndex[1].x = 0;
	if (nextTileIndex[1].y > maxTileY) nextTileIndex[1].y = maxTileY;
	else if (nextTileIndex[1].y < 0) nextTileIndex[1].y = 0;
	_t[1] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[1].y][nextTileIndex[1].x];
	//_t[1] = _vTilesSave[nextTileIndex[1].y][nextTileIndex[1].x];

	//다음 타일
	if (nextTileIndex[2].x > maxTileX) nextTileIndex[2].x = maxTileX;
	else if (nextTileIndex[2].x < 0) nextTileIndex[2].x = 0;
	if (nextTileIndex[2].y > maxTileY) nextTileIndex[2].y = maxTileY;
	else if (nextTileIndex[2].y < 0) nextTileIndex[2].y = 0;
	_t[2] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[2].y][nextTileIndex[2].x];
	//_t[2] = _vTilesSave[nextTileIndex[2].y][nextTileIndex[2].x];
}

void buffalo::mapOutCollision()
{
	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;
	maxTileX *= SIZE;
	maxTileY *= SIZE;

	if (_position.x < 0)
	{
		_position.x += abs(0 - _rc.left);
		_isAttack = false;
		_wallCollision = true;
	}
	if (_position.x > maxTileX)
	{
		_position.x -= _rc.right - maxTileX;
		_isAttack = false;
		_wallCollision = true;
	}
	if (_position.y < 0)
	{
		_position.y += abs(0 - _rc.top);
		_isAttack = false;
		_wallCollision = true;
	}
	if (_position.y > maxTileY)
	{
		_position.y -= _rc.bottom - maxTileY;
		_isAttack = false;
		_wallCollision = true;
	}
}

bool buffalo::tileMove()
{
	if (_t[0]->getOrderIndex() == _nowOrder && _t[1]->getOrderIndex() == _nowOrder && _t[2]->getOrderIndex() == _nowOrder)
	{
		return true;
	}
	else
	{
		return false;
	}
}
