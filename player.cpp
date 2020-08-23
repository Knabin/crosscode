#include "stdafx.h"
#include "player.h"
#include "tile.h"
#include "scene.h"
#include "bullet.h"


player::player()
{
	playerState* idle = new idleState(this);
	playerState* move = new moveState(this);
	playerState* jump = new jumpState(this);
	playerState* guard = new guardState(this);
	playerState* dodge = new dodgeState(this);
	playerState* longAttack = new longAttackState(this);
	playerState* longAttackIdle = new longAttackIdleState(this);
	playerState* longAttackMove = new longAttackMoveState(this);
	playerState* movestop = new movestopState(this);
	playerState* leftattackstate = new leftattackState(this);
	playerState* rightattackstate = new rightattackState(this);
	playerState* rightfinalattackstate = new rightfinalattackState(this);
	playerState* lethalchargestate = new lethalchargeState(this);
	playerState* lethalattackstate = new lethalattackState(this);
	playerState* beAttackedstate = new beAttackedState(this);

	_vState.push_back(idle);
	_vState.push_back(move);
	_vState.push_back(jump);
	_vState.push_back(guard);
	_vState.push_back(dodge);
	_vState.push_back(longAttack);
	_vState.push_back(longAttackIdle);
	_vState.push_back(longAttackMove);
	_vState.push_back(movestop);
	_vState.push_back(leftattackstate);
	_vState.push_back(rightattackstate);
	_vState.push_back(rightfinalattackstate);
	_vState.push_back(lethalchargestate);
	_vState.push_back(lethalattackstate);
	_vState.push_back(beAttackedstate);

	_name = "player";
	_isActive = true;

	_combo = 0;
	_iscombo = false;
	_fullCount = 0;
	_attackEffectCount = 0;
	_dodgeCount = 4; //닷지 기본 횟수
	_lineCount = 3;

	_lethalCount = 2;
	_lethalCharge = 0;
	_isLethal = false;

	_attackCount = 0;
	_state = new playerStateController(idle);
	_position.y = 700;
	_attackAngle = 0;
	
	_beAttacked = false;

	_pSp = 0;
}

player::~player()
{
}

HRESULT player::init()
{
	_image = IMAGEMANAGER->addFrameImage("p", L"images/player/player_move.png", 12, 8);
	IMAGEMANAGER->addFrameImage("player guard", L"images/player/player_guard.png", 3, 8);
	IMAGEMANAGER->addFrameImage("player jump", L"images/player/player_jump.png", 2, 8);
	IMAGEMANAGER->addFrameImage("player dodge", L"images/player/player_dodge.png", 9, 8);
	IMAGEMANAGER->addFrameImage("player longAttack", L"images/player/player_longAttack1.png", 17, 8);
	IMAGEMANAGER->addFrameImage("player longAttackMove", L"images/player/player_longAttackMove.png", 7, 8);
	IMAGEMANAGER->addFrameImage("p_meleeattack_left", L"images/player/meleeattack_left1.png", 8, 7);
	IMAGEMANAGER->addFrameImage("p_meleeattack_right", L"images/player/meleeattack_right1.png", 8, 7);
	IMAGEMANAGER->addImage("player longAttackTwoLine", L"images/player/player_longAttack_TwoLine.png");
	IMAGEMANAGER->addImage("player longAttackLine", L"images/player/player_longAttack_Line.png");
	IMAGEMANAGER->addFrameImage("player aim", L"images/player/player_aim.png", 2, 1);
	IMAGEMANAGER->addFrameImage("player charge", L"images/player/player_charge1.png", 6, 8);
	IMAGEMANAGER->addFrameImage("player chargeeffect", L"images/player/player_chargeeffect.png", 6, 1);
	
	IMAGEMANAGER->addFrameImage("player beAttacked", L"images/player/player_beAttacked.png", 2, 8);
	
	IMAGEMANAGER->addImage("player shadow", L"images/player/player_shadow.png");

	IMAGEMANAGER->addImage("player range", L"images/player/player_attackrange.png");
	EFFECTMANAGER->addEffect("player range", "player range", 1, 0.1f, 1, 1.0f);

	IMAGEMANAGER->addFrameImage("player dodgeDust", L"images/player/player_dodgedust.png", 5,1);

	EFFECTMANAGER->addEffect("player dodgeDust1", "player dodgeDust", 1, 0.2f, 1, 1.f);
	EFFECTMANAGER->addEffect("player dodgeDust2", "player dodgeDust", 1, 0.4f, 1, 1.f);
	EFFECTMANAGER->addEffect("player dodgeDust3", "player dodgeDust", 1, 0.6f, 1, 1.f);

	IMAGEMANAGER->addFrameImage("player bulletRemoveEffectImg", L"images/player/player_bulletRemoveEffect.png", 5, 1);
	EFFECTMANAGER->addEffect("player bulletRemoveEffect", "player bulletRemoveEffectImg", 1, 0.5f, 10, 1.f);
	//EFFECTMANAGER->addEffect("player bulletRemoveEffect1", "player bulletRemoveEffectImg", 1, 0.5f, 1, 1.f);

	IMAGEMANAGER->addFrameImage("leftattackeffect", L"images/player/leftattackeffect.png", 7, 1);
	IMAGEMANAGER->addFrameImage("rightattackeffect", L"images/player/rightattackeffect.png", 7, 1);
	_attackImg = IMAGEMANAGER->addFrameImage("finalattackeffect", L"images/player/finalattackeffect.png", 4, 1);

	EFFECTMANAGER->addEffect("leftattackeffect", "leftattackeffect",1,0.5f,5,1.0f);
	EFFECTMANAGER->addEffect("rightattackeffect", "rightattackeffect", 1, 0.5f, 5, 1.0f);
	EFFECTMANAGER->addEffect("finalattackeffect", "finalattackeffect", 1, 0.3f, 5, 1.0f);

	EFFECTMANAGER->addEffect("player chargeeffect", "player chargeeffect", 1, 0.5f, 1, 1.0f);


	//=================================== 근거리 이펙트 용=================================
	for (int i = 0; i < 40; i++)
	{
		_attackAni[i] = new animation;
		_attackAni[i]->init(_attackImg->getWidth(), _attackImg->getHeight(), _attackImg->getFrameSize().x, _attackImg->getFrameSize().y);
		_attackAni[i]->setPlayFrame(0, 3, false, false);
		_attackAni[i]->setFPS(3);
	}
	//===================================================================================

	_width = _height = 96;
	_pivot = pivot::CENTER;
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);
	_nowOrder = 1;
	_beginOrder = 1;
	_backOrder = 1;
	_tileRect.update(Vector2(0, 0), Vector2(40, 40), pivot::CENTER);
	_jumpCount = 60;
	_jumpPower = 0;
	_gravity = 3;
	_jumping = false;
	
	_bullet = new bullet;
	_bullet->init();
	_attacking = false;
	_attackCollision = false;
	 _pHp = 100;
	 _playerMaxHP = 100;
	 _pXp = 0;
	 _playerLevelUpXp = 100;
	 _pSp = 1;
	 _pSpcharge = 0;
	 _pLevel = 1;

	 _pDef = 0;
	 _pCrt = 5;
	 _pfR  =0;
	 _pIR = 0;
	 _pER = 0;
	 _pPR = 0;
	 _pAtk = 5;

	_attackPower = 50;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (_pHp < 0)
		_pHp = 0;

	if (_pHp >= _playerMaxHP)
		_pHp = _playerMaxHP;

	if (_state->getState() != _vState[PLAYERSTATE::JUMP])
	{
		if (_jumpCount > 59)
			_jumpPower = 0;
		else
		{
			_jumpCount++;

			_jumpPower += _gravity;
			if (_jumpCount > 29)
			{
				_gravity = -3;
			}
			else
			{
				_gravity = 3;
			}
		}
	}
	_bullet->update();
	if (EVENTMANAGER->isPlayingEvent())
	{
		_state->updateState();
		return;
	}
	if (KEYMANAGER->isStayKeyDown('W') 
		&& _state->getState() != _vState[PLAYERSTATE::LETHAL_CHARGE] && 
		_state->getState() != _vState[PLAYERSTATE::LETHAL_ATTACK] &&
		_state->getState() != _vState[PLAYERSTATE::GUARD])
	{
		if (_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] && 
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] && 
			_state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				_direction = PLAYERDIRECTION::RIGHT_TOP;
			}
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				_direction = PLAYERDIRECTION::LEFT_TOP;
			}
			else
			{
				_direction = PLAYERDIRECTION::TOP;
			}
		}
		// ================== 공격 처리==================
		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			playerMeleeattack();
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _dodgeCount > 0)
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
			_dodgeCount--;
		}
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::DODGE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
	}

	if (KEYMANAGER->isStayKeyDown('S') && 
		_state->getState() != _vState[PLAYERSTATE::LETHAL_CHARGE] && _state->getState() != _vState[PLAYERSTATE::LETHAL_ATTACK] &&
		_state->getState() != _vState[PLAYERSTATE::GUARD])
	{
		if (_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] && 
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] && 
			_state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				_direction = PLAYERDIRECTION::RIGHT_BOTTOM;
			}
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				_direction = PLAYERDIRECTION::LEFT_BOTTOM;
			}
			else
			{
				_direction = PLAYERDIRECTION::BOTTOM;
			}
		}
		// ================== 공격 처리==================
		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			playerMeleeattack();

		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _dodgeCount > 0)
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
			_dodgeCount--;
		}
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::DODGE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
	}

	if (KEYMANAGER->isStayKeyDown('A') && 
		_state->getState() != _vState[PLAYERSTATE::LETHAL_CHARGE] && _state->getState() != _vState[PLAYERSTATE::LETHAL_ATTACK] &&
		_state->getState() != _vState[PLAYERSTATE::GUARD])
	{
		if (_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] && _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] && _state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_direction = PLAYERDIRECTION::LEFT_TOP;
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				_direction = PLAYERDIRECTION::LEFT_BOTTOM;
			}
			else
			{
				_direction = PLAYERDIRECTION::LEFT;
			}
		}

		// ================== 공격 처리==================
		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			playerMeleeattack();
			vector <gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _dodgeCount > 0)
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
			_dodgeCount--;
		}
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::DODGE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
	}

	if (KEYMANAGER->isStayKeyDown('D') && 
		_state->getState() != _vState[PLAYERSTATE::LETHAL_CHARGE] && _state->getState() != _vState[PLAYERSTATE::LETHAL_ATTACK] &&
		_state->getState() != _vState[PLAYERSTATE::GUARD])
	{
		if (_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] && _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] && _state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_direction = PLAYERDIRECTION::RIGHT_TOP;
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				_direction = PLAYERDIRECTION::RIGHT_BOTTOM;
			}
			else
			{
				_direction = PLAYERDIRECTION::RIGHT;
			}
		}
		// ================== 공격 처리==================
		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			playerMeleeattack();
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _dodgeCount > 0)
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
			_dodgeCount--;
		}
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::DODGE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE] &&
			_state->getState() != _vState[PLAYERSTATE::LONGATTACK] &&
			_state->getState() != _vState[PLAYERSTATE::JUMP])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
	}

	if (_state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE])
	{
		if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('W'))
		{
			_state->setState(_vState[PLAYERSTATE::LONGATTACKMOVE]);
		}
	}

	_combocount++;   // 근접공격 콤보 카운트용

	// ==================근접 공격 초기화용==================
	if (_state->getState() != _vState[LEFT_ATTACK] && _state->getState() != _vState[RIGHT_ATTACK])
	{
		_iscombo = false;
		_combo = 0;
	}

	if ((_state->getState() == _vState[LEFT_ATTACK] || _state->getState() == _vState[RIGHT_ATTACK]) && _combo <= 4 && _ani->isPlay() == false && _combocount > 30)
	{
		_state->setState(_vState[PLAYERSTATE::IDLE]);
		_iscombo = false;
		_combo = 0;
	}
	// =============================================================================

	if (_state->getState() == _vState[IDLE] &&
		(KEYMANAGER->isStayKeyDown('C') || KEYMANAGER->isStayKeyDown(VK_RBUTTON)))
	{
		_state->setState(_vState[PLAYERSTATE::GUARD]);
	}
	if (KEYMANAGER->isOnceKeyDown('V')) //근접공격키
	{
		playerMeleeattack();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))	// 가까우면 근접 , 멀면 원거리 공격
	{
		_fullCount = 0;
		if (getDistance(_position.x, _position.y, _ptMouse.x /
			CAMERA->getZoomAmount() + CAMERA->getRect().left, _ptMouse.y /
			CAMERA->getZoomAmount() + CAMERA->getRect().top) < 150)
		{
			playerMeleeattack();
		}
		else if (getDistance(_position.x, _position.y, _ptMouse.x /
			CAMERA->getZoomAmount() + CAMERA->getRect().left, _ptMouse.y /
			CAMERA->getZoomAmount() + CAMERA->getRect().top) >= 100)
		{
			_state->setState(_vState[PLAYERSTATE::LONGATTACK]);
			_state->getState()->setLongAttack();
			_angle = getAngle(_position.x, _position.y,
				_ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left,
				_ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top);
			_angle = _angle + RND->getFromFloatTo(-de, de);

			_bullet->nomalFire(_position.x, _position.y, _angle, 17.0f);
			SOUNDMANAGER->play("pS lattack", 1.0f);
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && 
		_state->getState() != _vState[PLAYERSTATE::LONGATTACK] && 
		_state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE])
	{
		_fullCount++;
		if (_fullCount > 10)
		{
			_state->setState(_vState[PLAYERSTATE::LONGATTACKIDLE]);
		}
	}

	//롱 어택 무브일 때 마우스 왼쪽 버튼 뗄 시 롱 어택 모션
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && (_state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE] || _state->getState() == _vState[PLAYERSTATE::LONGATTACKMOVE]))
	{
		_state->setState(_vState[PLAYERSTATE::LONGATTACK]);
		_state->getState()->setLongAttack();
		_bullet->fire(_position.x, _position.y, _angle, 17.0f);
	}

	if (_state->getState() == _vState[PLAYERSTATE::DODGE] && _ani->isPlay() == false)
	{
		_state->setState(_vState[PLAYERSTATE::IDLE]);
	}

	// ==================== 가드상태 또는 원거리 공격시 마우스 방향으로 플레이어의 방향 바뀜 ==================== //
	if (_state->getState() == _vState[PLAYERSTATE::GUARD] ||
		_state->getState() == _vState[PLAYERSTATE::LONGATTACK] ||
		_state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE] ||
		_state->getState() == _vState[PLAYERSTATE::LONGATTACKMOVE])
	{
		_angle = getAngle(_position.x, _position.y,
			_ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left,
			_ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top);

		for (int i = 0; i < 8; i++)
		{
			float min = PI / 2 - PI / 8 + PI / 4 * i;
			float max = PI / 2 + PI / 8 + PI / 4 * i;

			if (min > PI2)
			{
				min -= PI2;
			}
			if (max > PI2)
			{
				max -= PI2;
			}

			if (_angle > min && _angle <= max && i != 6)
			{
				_direction = (PLAYERDIRECTION)i;
			}
			else if (((_angle <= PI2 && _angle > min) || (_angle >= 0 && _angle <= max)) && i == 6)
			{
				_direction = (PLAYERDIRECTION)i;
			}
		}
	}
	// ============================================= 회피 이펙트 ============================================= //
	if (_state->getState() == _vState[PLAYERSTATE::DODGE] && _dodgeCount > 1)
	{
		playerDodgeEffect();
	}

	if (_state->getState() == _vState[PLAYERSTATE::BE_ATTACKED])
	{
		_beAttackedCount++;
		if (_beAttackedCount >= 25)
		{
			_state->setState(_vState[PLAYERSTATE::IDLE]);
			_beAttackedCount = 0;
		}
	}

	//========================================움직이고 나서 정지하는 모션 ====================================================
	if ((KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('S') ||
		KEYMANAGER->isOnceKeyUp('A') && KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('D') && KEYMANAGER->isOnceKeyUp('W') ||
		KEYMANAGER->isOnceKeyUp('A') && KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('D') && KEYMANAGER->isOnceKeyUp('S')))
	{
		if (_state->getState() == _vState[PLAYERSTATE::MOVE])
			_state->setState(_vState[PLAYERSTATE::MOVESTOP]);
		if (_state->getState() == _vState[PLAYERSTATE::LONGATTACKMOVE])
			_state->setState(_vState[PLAYERSTATE::LONGATTACKIDLE]);
	}

	if (KEYMANAGER->isOnceKeyUp('C')
		|| (KEYMANAGER->isOnceKeyUp(VK_RBUTTON) && _state->getState() == _vState[PLAYERSTATE::GUARD])
		|| (_state->getState() == _vState[MOVESTOP] && !_ani->isPlay())
		|| (_state->getState() == _vState[RIGHT_FINALATTACK] && !_ani->isPlay())
		|| (_state->getState() == _vState[LETHAL_ATTACK] && !_ani->isPlay())
		)
	{
		if (_state->getState() == _vState[RIGHT_FINALATTACK] || _state->getState() == _vState[LETHAL_ATTACK])
		{
			for (int i = 0; i < 40; i++)
			{
				_attackAni[i]->stop();
				_attacking = true;
			}
		}

		_lethalCharge = 0;
		_isLethal = false;
		_lethalCharge = 0;
		_state->setState(_vState[PLAYERSTATE::IDLE]);
	}

	if (_state->getState() == _vState[LETHAL_CHARGE] && KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		_isLethal = false;
		_lethalCharge = 0;
		_attackEffectCount = 0;
		_state->setState(_vState[PLAYERSTATE::IDLE]);
	}

	if (_state->getState() == _vState[PLAYERSTATE::LONGATTACK] && _state->getState()->isAttack() == false && _state->getState()->isLongAttack() == false)
	{
		_state->setState(_vState[PLAYERSTATE::IDLE]);
	}

	if (_dodgeCount < 4)
	{
		_dodgeCharge++;
	}

	if (_dodgeCharge > 20)
	{
		_dodgeCount++;
		_dodgeCharge = 0;
	}

	_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	_state->updateState();

	if (_state->getState() != _vState[PLAYERSTATE::JUMP])
	{
		POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
		int _nowOrder2 = SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex();

		if (_nowOrder2 == 5 || _nowOrder2 == 6 || _nowOrder2 == 7)
		{
			float an = getAngle(_position.x, _position.y, _tile.left + 24, _tile.top + 24);
			float speed = 40;
			switch (_direction)
			{
			case PLAYERDIRECTION::TOP:
				_position.y -= sinf(an) * speed;
				break;
			case PLAYERDIRECTION::LEFT_TOP:
				_position.x += cosf(an) * speed;
				_position.y -= sinf(an) * speed;
				break;
			case PLAYERDIRECTION::LEFT:
				_position.x += cosf(an) * speed;
				_position.y -= sinf(an) * speed;
				break;
			case PLAYERDIRECTION::LEFT_BOTTOM:
				_position.x += cosf(an) * speed;
				_position.y -= sinf(an) * speed;
				break;
			case PLAYERDIRECTION::BOTTOM:
				_position.y -= sinf(an) * speed;
				break;
			case PLAYERDIRECTION::RIGHT_BOTTOM:
				_position.x -= cosf(an) * speed;
				_position.y -= sinf(an) * speed;
				break;
			case PLAYERDIRECTION::RIGHT:
				_position.x -= cosf(an) * speed;
				_position.y -= sinf(an) * speed;
				break;
			case PLAYERDIRECTION::RIGHT_TOP:
				_position.x -= cosf(an) * speed;
				_position.y -= sinf(an) * speed;
				break;
			}
			_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		}
	}

	//=================================== 근거리 이펙트 용=================================
	if (_state->getState() == _vState[PLAYERSTATE::RIGHT_FINALATTACK] || _state->getState() == _vState[PLAYERSTATE::LETHAL_ATTACK])
	{
		_attackEffectCount++;

		if (_attackEffectCount > 1)
		{
			if (!_attackAni[_attackCount]->isPlay())
			{
				_attackAni[_attackCount]->start();

			}
		}

		if (_attackEffectCount > 1)
		{
			if (_attackCount + 10 < 39)
				_attackCount++;

			_attackEffectCount = 0;
		}

		for (int i = _attackCount; i < _attackCount + 10; i++)
		{
			_attackAni[i]->frameUpdate(TIMEMANAGER->getElapsedTime() * 30);
		}

		for (int i = _attackCount; i < _attackCount + 10; i++)
		{
			if (!_attackAni[i]->isPlay())
			{
				_attackAni[i]->start();

			}
		}
		//===================================================================================	
	}

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		if ((_state->getState() == _vState[IDLE] || _state->getState() == _vState[MOVE]) && !_isLethal && _pSp > 0)
		{
			CAMERA->zoomStart(1.3f, 0.75f, true);
			_pSp--;
			_isLethal = true;
			_lethalCount--;
			_state->setState(_vState[PLAYERSTATE::LETHAL_CHARGE]);
			EFFECTMANAGER->play("player chargeeffect", Vector2(CAMERA->getRelativeVector2(_position).x+100, CAMERA->getRelativeVector2(_position).y+100),0,0.5f);
		}
		playerLethalattack();
	}

	if (_pSp == 0 && _pSpcharge < 200 && (_state->getState() == _vState[IDLE] || _state->getState() == _vState[MOVE]))
	{
		_pSpcharge++;
	}

	if (_pSp >= 1 && _pSp <= 3 &&(_state->getState() == _vState[LEFT_ATTACK] || _state->getState() == _vState[RIGHT_ATTACK] || _state->getState() == _vState[RIGHT_FINALATTACK] || _state->getState() == _vState[LONGATTACK]))
	{
		_pSpcharge++;
	}

	if (_pSpcharge > 190)
	{
		_pSp++;
		_pSpcharge = 0;
	}

	if (_state->getState() == _vState[LETHAL_CHARGE])
	{
		_lethalCharge++;
	}
	else
	{
		_lethalCharge = 0;
	}

	
	_attackPower = _pAtk + RND->getFromIntTo(0, _pCrt);
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
}

void player::render()
{

	//_rc.render(getMemDC());
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_tileRect));
	_image->setSize(_image->getFrameSize() * CAMERA->getZoomAmount());
	_image->aniRender(CAMERA->getRelativeVector2(_position.x, _position.y - _jumpPower), _ani, 1.0f);
	IMAGEMANAGER->findImage("player shadow")->setAlpha(0.2);
	IMAGEMANAGER->findImage("player shadow")->render(CAMERA->getRelativeVector2(_position.x - 25, _position.y + 10));
	//RectangleMake(getMemDC(), tileIndex.x * SIZE, tileIndex.y *SIZE, SIZE, SIZE);
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(floatRect(rcCollision)));
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_attackRC));

	/*D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(SCENEMANAGER->getCurrentScene()->getTiles()[next[0].y][next[0].x]->getRect()),
		D2D1::ColorF::Aqua, 0);
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(SCENEMANAGER->getCurrentScene()->getTiles()[next[1].y][next[1].x]->getRect()),
		D2D1::ColorF::Aqua, 0);
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(SCENEMANAGER->getCurrentScene()->getTiles()[next[2].y][next[2].x]->getRect()),
		D2D1::ColorF::Aqua, 0);
	*/

	if (_state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE] ||
		_state->getState() == _vState[PLAYERSTATE::LONGATTACKMOVE])
	{
		_angle = getAngle(_position.x, _position.y,
			_ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left,
			_ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top);

		float d1 = _angle;

		for (int i = 0; i < 12; i++)
		{
			IMAGEMANAGER->findImage("player longAttackLine")->render
			(CAMERA->getRelativeVector2(_position.x - 15 + cosf(d1) * 50 * i, _position.y - 10 + -sinf(d1) * 50 * i), 1.f);
		}
	}

	if (_state->getState() == _vState[PLAYERSTATE::LONGATTACK])
	{
		_angle = getAngle(_position.x, _position.y,
			_ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left,
			_ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top);

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))	de -= PI / 50;
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	de = PI / 4;
		if (de < 0)	de = 0;

		d1 = _angle - de;
		d2 = _angle + de;

		for (int i = 0; i < 6; i++)
		{
			IMAGEMANAGER->findImage("player longAttackTwoLine")->render
			(CAMERA->getRelativeVector2(_position.x + cosf(d1) * 50 * i, _position.y + -sinf(d1) * 50 * i), 1.f);
		}
		for (int i = 0; i < 6; i++)
		{
			IMAGEMANAGER->findImage("player longAttackTwoLine")->render
			(CAMERA->getRelativeVector2(_position.x + cosf(d2) * 50 * i, _position.y + -sinf(d2) * 50 * i), 1.f);
		}
	}
	//=================================== 근거리 이펙트 용=================================
	if (_state->getState() == _vState[PLAYERSTATE::RIGHT_FINALATTACK])
	for (int i = _attackCount; i < _attackCount+10; i++)
	{
		_attackImg->setAngle(_attackAngle);
		_attackImg->aniRender(Vector2(CAMERA->getRelativeVector2(_position).x - 8+ cosf(PI/9 * i) * 70, CAMERA->getRelativeVector2(_position).y -sinf(PI / 9 * i) * 70), _attackAni[i], 1.f);

		_attackAngle -= 10;
		
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			if (_attackAngle < 315)
				_attackAngle = 0;
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			if (_attackAngle < 245)
				_attackAngle = 290;
			break;
		case PLAYERDIRECTION::LEFT:
			if (_attackAngle < 200)
				_attackAngle = 245;
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			if (_attackAngle < 175)
				_attackAngle = 220;
			break;
		case PLAYERDIRECTION::BOTTOM:
			if (_attackAngle < 135)
				_attackAngle = 180;
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			if (_attackAngle < 45)
				_attackAngle = 130;
			break;
		case PLAYERDIRECTION::RIGHT:
			if (_attackAngle < 45)
				_attackAngle = 90;
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			if (_attackAngle < 0)
				_attackAngle = 40;
			break;
		}
	}
	//=======================================================================================
	if (_state->getState() == _vState[PLAYERSTATE::LETHAL_ATTACK])
		for (int i = _attackCount; i < _attackCount + 10; i++)
		{
			_attackImg->setAngle(_attackAngle);
			_attackImg->aniRender(Vector2(CAMERA->getRelativeVector2(_position).x - 8 + cosf(PI / 9 * i) * 100, CAMERA->getRelativeVector2(_position).y - sinf(PI / 9 * i) * 100), _attackAni[i], 1.f);

			_attackAngle -= 10;

			switch (_direction)
			{
			case PLAYERDIRECTION::TOP:
				if (_attackAngle < 315)
					_attackAngle = 0;
				break;
			case PLAYERDIRECTION::LEFT_TOP:
				if (_attackAngle < 245)
					_attackAngle = 290;
				break;
			case PLAYERDIRECTION::LEFT:
				if (_attackAngle < 200)
					_attackAngle = 245;
				break;
			case PLAYERDIRECTION::LEFT_BOTTOM:
				if (_attackAngle < 175)
					_attackAngle = 220;
				break;
			case PLAYERDIRECTION::BOTTOM:
				if (_attackAngle < 135)
					_attackAngle = 180;
				break;
			case PLAYERDIRECTION::RIGHT_BOTTOM:
				if (_attackAngle < 45)
					_attackAngle = 130;
				break;
			case PLAYERDIRECTION::RIGHT:
				if (_attackAngle < 45)
					_attackAngle = 90;
				break;
			case PLAYERDIRECTION::RIGHT_TOP:
				if (_attackAngle < 0)
					_attackAngle = 40;
				break;
			}
		}
	//=======================================================================================
	_bullet->render();
}

void player::playerMove()
{
	// 보고 있는 방향으로 앞에 체크
	// 체크한 타일과 층이 같다면
	//		그냥 이동
	// 체크한 타일과 층이 다르다면
	//		높다면
	//			1차이라면 점프함
	//			아니라면 이동하지 않음
	//		낮다면
	
	//			현재 층이 0이라면 빠져나감
	//			(만약 앞앞타일과 층이 같다면 거기까지 점프함)
	//			아니라면 (누른 시간만큼) 점프함
	// **점프 함수에서 착지했을 때 층 체크해서 player 갱신해 주고 idle로 이동


	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	//POINT nextTileIndex;
	//POINT next[3];
	float moveSpeed = 4.5f;
	
	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		next[0] = { currentTileIndex.x, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x, currentTileIndex.y - 2 };
		next[4] = { currentTileIndex.x - 1, currentTileIndex.y - 2 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y - 2 };
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x -2 , currentTileIndex.y - 2 };
		next[4] = { currentTileIndex.x -2, currentTileIndex.y - 1 };
		next[5] = { currentTileIndex.x - 1, currentTileIndex.y - 2 };
		break;
	case PLAYERDIRECTION::LEFT:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x - 2, currentTileIndex.y + 1 };
		next[4] = { currentTileIndex.x - 2, currentTileIndex.y };
		next[5] = { currentTileIndex.x - 2, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x - 2, currentTileIndex.y + 2 };
		next[4] = { currentTileIndex.x - 2, currentTileIndex.y + 1 };
		next[5] = { currentTileIndex.x - 1, currentTileIndex.y + 2 };
		break;
	case PLAYERDIRECTION::BOTTOM:
		next[0] = { currentTileIndex.x, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x, currentTileIndex.y + 3 };
		next[4] = { currentTileIndex.x - 1, currentTileIndex.y + 3 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y + 3 };
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x + 2, currentTileIndex.y + 2 };
		next[4] = { currentTileIndex.x + 2, currentTileIndex.y + 1 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y + 2 };
		break;
	case PLAYERDIRECTION::RIGHT:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x + 2, currentTileIndex.y };
		next[4] = { currentTileIndex.x + 2, currentTileIndex.y - 1 };
		next[5] = { currentTileIndex.x + 2, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x + 2, currentTileIndex.y - 2 };
		next[4] = { currentTileIndex.x + 2, currentTileIndex.y - 1 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y - 2 };
		break;
	}
	
	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;
	
	// 다음 타일
	for (int i = 0; i < 6; ++i)
	{
		if (next[i].x > maxTileX) next[i].x = maxTileX;
		else if (next[i].x < 0) next[i].x = 0;
		if (next[i].y > maxTileY) next[i].y = maxTileY;
		else if (next[i].y < 0) next[i].y = 0;
	}
	
	RECT temp;
	
	_backOrder = _nowOrder;
	if(currentTileIndex.x < maxTileX && currentTileIndex.y < maxTileY)
		_nowOrder = SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex();
	if (_nowOrder == 4 || _nowOrder == 5)
	{
		_nowOrder = _backOrder;
	}

	_beginOrder = _nowOrder;

	// 층이 같다면
	//if (ti->getOrderIndex() == _nowOrder)

	switch (_direction)
	{
		case PLAYERDIRECTION::TOP:
			move(0, -moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() -1 !=  _nowOrder)
					{
						move(0, 4.5f);
						break;
					}
					/*else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;
						
						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];
							
							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5 )
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}
							
						}
					}
				}
			}
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			moveAngle(PI * 0.75, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() - 1 != _nowOrder)
					{
						moveAngle(PI * 1.75f, moveSpeed);
						break;
					}
					/*else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;

						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];

							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5)
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}

						}
					}
				}
			}
			break;
		case PLAYERDIRECTION::LEFT:
			move(-moveSpeed, 0);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() - 1 != _nowOrder)
					{
						move(4.5f, 0);
						break;
					}
					/*else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;
						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];

							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5)
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}

						}
					}
				}
			}
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			moveAngle(PI * 1.25, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() - 1 != _nowOrder)
					{
						moveAngle(PI * 0.25f, moveSpeed);
						break;
					}
					/*else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;
						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];

							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5)
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}

						}
					}
				}
			}
			break;
		case PLAYERDIRECTION::BOTTOM:
			move(0, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() - 1 != _nowOrder)
					{
						move(0, -4.5f);
						break;
					}
				/*	else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;
						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];

							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5)
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}

						}
					}
				}
			}
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			moveAngle(PI * 1.75, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() - 1 != _nowOrder)
					{
						moveAngle(PI * 0.75f, moveSpeed);
						break;
					}
					/*else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;
						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];

							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5)
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}

						}
					}
				}
			}
			break;
		case PLAYERDIRECTION::RIGHT:
			move(moveSpeed, 0);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() - 1 != _nowOrder)
					{
						move(-4.5f, 0);
						break;
					}
					/*else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;
						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];

							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5)
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}

						}
					}
				}
			}
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			moveAngle(PI * 0.25, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder && ti->getOrderIndex() != 4 && ti->getOrderIndex() != 5 && ti->getOrderIndex() - 1 != _nowOrder)
					{
						moveAngle(PI * 1.25f, moveSpeed);
						break;
					}
					/*else if (SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex() == 5)
					{
						break;
					}*/
					else if ((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder)
					{
						_state->setState(_vState[PLAYERSTATE::JUMP]);
						_jumpCount = 0;
						break;
					}
					else if (ti->getOrderIndex() == 5)
					{
						for (int j = 3; j < 6; j++)
						{
							ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[j].y][next[j].x];

							if (((ti->getOrderIndex() == _nowOrder + 1 && _nowOrder != 3) || ti->getOrderIndex() < _nowOrder) && ti->getOrderIndex() != 5)
							{
								_state->setState(_vState[PLAYERSTATE::JUMP]);
								_jumpCount = 0;
								break;
							}

						}
					}
				}
			}
			break;
	}
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
	//_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	
	// 층이 플레이어보다 높다면
	/*if (t->getOrderIndex() > _nowOrder)
	{
		// 한 층 차이라면
		if (t->getOrderIndex() - _nowOrder == 1)
		{
			// TODO: 점프
		}
	}
	// 층이 플레이어보다 낮다면
	else
	{
		// 예외 처리
		if (_nowOrder == 0) return;
		// TODO: 점프
	}*/
}

void player::playerDodge()		//회피시 움직임
{
	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	POINT nextTileIndex;
	float moveSpeed = 8.3f;
	
	if (_dodgeCount < 1)
	{
		moveSpeed = 2.0f;
	}
	
	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::BOTTOM:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		break;
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	if (t->getOrderIndex() == _nowOrder)
	{
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			move(0, -moveSpeed);
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			moveAngle(PI * 0.75, moveSpeed);
			break;
		case PLAYERDIRECTION::LEFT:
			move(-moveSpeed, 0);
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			moveAngle(PI * 1.25, moveSpeed);
			break;
		case PLAYERDIRECTION::BOTTOM:
			move(0, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			moveAngle(PI * 1.75, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT:
			move(moveSpeed, 0);
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			moveAngle(PI * 0.25, moveSpeed);
			break;
		}
		_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	}
}

void player::playerJumpMove()
{
	_jumpCount++;

	float moveSpeed = 4;
	

	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	
	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		next[0] = { currentTileIndex.x, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x, currentTileIndex.y - 2 };
		next[4] = { currentTileIndex.x - 1, currentTileIndex.y - 2 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y - 2 };
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x - 2 , currentTileIndex.y - 2 };
		next[4] = { currentTileIndex.x - 2, currentTileIndex.y - 1 };
		next[5] = { currentTileIndex.x - 1, currentTileIndex.y - 2 };
		break;
	case PLAYERDIRECTION::LEFT:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x - 2, currentTileIndex.y + 1 };
		next[4] = { currentTileIndex.x - 2, currentTileIndex.y };
		next[5] = { currentTileIndex.x - 2, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x - 2, currentTileIndex.y + 2 };
		next[4] = { currentTileIndex.x - 2, currentTileIndex.y + 1 };
		next[5] = { currentTileIndex.x - 1, currentTileIndex.y + 2 };
		break;
	case PLAYERDIRECTION::BOTTOM:
		next[0] = { currentTileIndex.x, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x, currentTileIndex.y + 3 };
		next[4] = { currentTileIndex.x - 1, currentTileIndex.y + 3 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y + 3 };
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x + 2, currentTileIndex.y + 2 };
		next[4] = { currentTileIndex.x + 2, currentTileIndex.y + 1 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y + 2 };
		break;
	case PLAYERDIRECTION::RIGHT:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		next[3] = { currentTileIndex.x + 2, currentTileIndex.y };
		next[4] = { currentTileIndex.x + 2, currentTileIndex.y - 1 };
		next[5] = { currentTileIndex.x + 2, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y - 1 };
		next[3] = { currentTileIndex.x + 2, currentTileIndex.y - 2 };
		next[4] = { currentTileIndex.x + 2, currentTileIndex.y - 1 };
		next[5] = { currentTileIndex.x + 1, currentTileIndex.y - 2 };
		break;
	}

	//int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	//int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();



	//// 다음 타일
	//for (int i = 0; i < 3; ++i)
	//{
	//	if (next[i].x > maxTileX) next[i].x = maxTileX;
	//	else if (next[i].x < 0) next[i].x = 0;
	//	if (next[i].y > maxTileY) next[i].y = maxTileY;
	//	else if (next[i].y < 0) next[i].y = 0;
	//}


	RECT temp;

	/*int _backOrder = _nowOrder;
	_nowOrder = SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex();
	if (_nowOrder == 4 || _nowOrder == 5)
	{
		_nowOrder = _backOrder;
	}*/

	//cout << _beginOrder << endl;
	// 층이 같다면
	//if (ti->getOrderIndex() == _nowOrder)
	{
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			//move(0, -moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i+3].y][next[i+3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						move(0, 4.5f);
						break;
					}
				}
			}
			
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			//moveAngle(PI * 0.75, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i + 3].y][next[i + 3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						moveAngle(PI * 1.75f, moveSpeed);
						break;
					}
				}
			}
			break;
		case PLAYERDIRECTION::LEFT:
			//move(-moveSpeed, 0);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i + 3].y][next[i + 3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						move(4.5f, 0);
						break;
					}
				}
			}
			
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			//moveAngle(PI * 1.25, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i + 3].y][next[i + 3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						moveAngle(PI * 0.25f, moveSpeed);
						break;
					}
				}
			}
			break;
		case PLAYERDIRECTION::BOTTOM:
			//move(0, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i + 3].y][next[i + 3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						move(0, -4.5f);
						break;
					}
				}
			}
			
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			//moveAngle(PI * 1.75, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i + 3].y][next[i + 3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						moveAngle(PI * 0.75f, moveSpeed);
						break;
					}
				}
			}
			
			break;
		case PLAYERDIRECTION::RIGHT:
			//move(moveSpeed, 0);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i + 3].y][next[i + 3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						move(-4.5f, 0);
						break;
					}
				}
			}
			
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			//moveAngle(PI * 0.25, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				tile* ti2 = SCENEMANAGER->getCurrentScene()->getTiles()[next[i + 3].y][next[i + 3].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()))
				{
					if (ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 5 && ti->getOrderIndex() != 6 || (ti2->getOrderIndex() == _beginOrder + 2 && _beginOrder == 1))
					{
						_jumping = true;
						moveAngle(PI * 1.25f, moveSpeed);
						break;
					}
				}
			}
			break;
		}

		if (!_jumping)
		{
			if (KEYMANAGER->isStayKeyDown('W') && _direction != PLAYERDIRECTION::BOTTOM)
			{
				move(0, -moveSpeed);
			}
			if (KEYMANAGER->isStayKeyDown('S') && _direction != PLAYERDIRECTION::TOP)
			{
				move(0, moveSpeed);
			}

			if (KEYMANAGER->isStayKeyDown('A') && _direction != PLAYERDIRECTION::RIGHT)
			{
				if (KEYMANAGER->isStayKeyDown('W') && _direction != PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					moveAngle(PI * 0.75, moveSpeed*0.4);
				}
				else if (KEYMANAGER->isStayKeyDown('S') && _direction != PLAYERDIRECTION::RIGHT_TOP)
				{
					moveAngle(PI * 1.25, moveSpeed*0.4);
				}
				else
				{
					move(-moveSpeed, 0);
				}
			}

			if (KEYMANAGER->isStayKeyDown('D') && _direction != PLAYERDIRECTION::LEFT)
			{
				if (KEYMANAGER->isStayKeyDown('W') && _direction != PLAYERDIRECTION::LEFT_BOTTOM)
				{
					moveAngle(PI * 0.25, moveSpeed*0.4);
				}
				else if (KEYMANAGER->isStayKeyDown('S') && _direction != PLAYERDIRECTION::LEFT_TOP)
				{
					moveAngle(PI * 1.75, moveSpeed*0.4);
				}
				else
				{
					move(moveSpeed, 0);
				}
			}
		}
		_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		//_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	}

	_jumpPower += _gravity;
	if (_jumpCount > 29)
	{
		_gravity = -3;
	}
	if (_jumpCount > 59)
	{
		//_jumpCount = 0;
		_state->setState(_vState[PLAYERSTATE::IDLE]);
		_jumpPower = 0;
		_gravity = 3;
		_jumping = false;	
	}
}

void player::playerLongAttackMove()
{
	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	POINT nextTileIndex;
	float moveSpeed = 2.f;

	nextTileIndex = { currentTileIndex.x, currentTileIndex.y };

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y - 1 };
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y + 1 };
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
			
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y + 1 };		
		}
		else
		{
			nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y };		
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y - 1 };		
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y + 1 };		
		}
		else
		{
			nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y };
		}
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	if (t->getOrderIndex() == _nowOrder)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			move(0, -moveSpeed);
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			move(0, moveSpeed);
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				moveAngle(PI * 0.75, moveSpeed);
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				moveAngle(PI * 1.25, moveSpeed);
			}
			else
			{
				move(-moveSpeed, 0);
			}
		}

		if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				moveAngle(PI * 0.25, moveSpeed);
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				moveAngle(PI * 1.75, moveSpeed);
			}
			else
			{
				move(moveSpeed, 0);
			}
		}

		_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	}
}

void player::playermeleeattackMove()	// 근접공격+방향키 움직이면서 공격할때 타일체크
{
	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	POINT nextTileIndex;
	float moveSpeed = 1.0f;

	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::BOTTOM:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		break;
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	if (t->getOrderIndex() == _nowOrder)
	{
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				move(0, -moveSpeed);
			}
			break;
		case PLAYERDIRECTION::LEFT_TOP:

			if (KEYMANAGER->isStayKeyDown('W'))
			{
				if (KEYMANAGER->isStayKeyDown('A'))
				{
					moveAngle(PI*0.75, moveSpeed);
				}
			}
			break;
		case PLAYERDIRECTION::LEFT:
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				move(-moveSpeed, 0);
			}
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				if (KEYMANAGER->isStayKeyDown('A'))
				{
					moveAngle(PI*1.25, moveSpeed);
				}
			}
			break;
		case PLAYERDIRECTION::BOTTOM:
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				move(0, moveSpeed);
			}
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				if (KEYMANAGER->isStayKeyDown('D'))
				{
					moveAngle(PI*1.75, moveSpeed);
				}
			}
			break;
		case PLAYERDIRECTION::RIGHT:
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				move(moveSpeed, 0);
			}
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				if (KEYMANAGER->isStayKeyDown('D'))
				{
					moveAngle(PI*0.25, moveSpeed);
				}
			}
			break;
		}
		_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	}
}

void player::playerfinalattackMove() // 근접공격 마지막타 움직이는거 타일체크
{
	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	POINT nextTileIndex;
	float moveSpeed = 4.0f;

	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::BOTTOM:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		break;
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	if (t->getOrderIndex() == _nowOrder)
	{
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y-15), Vector2(200, 200), pivot::CENTER);
			move(0, -moveSpeed);
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x-10, _position.y - 10), Vector2(200, 200), pivot::CENTER);
			moveAngle(PI*0.75, moveSpeed);
			break;
		case PLAYERDIRECTION::LEFT:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x-15, _position.y), Vector2(200, 200), pivot::CENTER);
			move(-moveSpeed, 0);
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 10, _position.y + 10), Vector2(200, 200), pivot::CENTER);
			moveAngle(PI*1.25, moveSpeed);
			break;
		case PLAYERDIRECTION::BOTTOM:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y + 15), Vector2(200, 200), pivot::CENTER);
			move(0, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x+10, _position.y + 10), Vector2(200, 200), pivot::CENTER);
			moveAngle(PI*1.75, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 15, _position.y), Vector2(200, 200), pivot::CENTER);
			move(moveSpeed, 0);
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 10, _position.y - 10), Vector2(200, 200), pivot::CENTER);
			moveAngle(PI*0.25, moveSpeed);
			break;
		}
		_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	}
}

void player::move(const float & x, const float & y)
{
	_position.x += x;
	_position.y += y;
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
	_tileRect.set(_position + Vector2(0, 30), pivot::CENTER);
}

void player::moveAngle(const float & cangle, const float & speed)
{
	float _speed = speed;
	_position.x += cosf(cangle) * _speed;
	_position.y -= sinf(cangle) * _speed;
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
	_tileRect.set(_position + Vector2(0, 30), pivot::CENTER);
}

void player::playerMeleeattack()   //근접 기본공격
{
	_combocount = 0;
	EFFECTMANAGER->play("player range", Vector2(CAMERA->getRelativeVector2(_position).x+140, CAMERA->getRelativeVector2(_position).y+150));
	if (_state->getState() == _vState[IDLE] && !_iscombo || _state->getState() == _vState[MOVE] && !_iscombo)
	{
		
		_state->setState(_vState[PLAYERSTATE::LEFT_ATTACK]);
		_iscombo = true;
		_combo++;
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 50));
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 50), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y-30), Vector2(180, 100), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 50), 315);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 50), pivot::CENTER);
			_attackRC.update(Vector2(_position.x-15, _position.y-30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 60), 270);
			_attackRC.set(Vector2(_position.x + 70, _position.y + 60), pivot::CENTER);
			_attackRC.update(Vector2(_position.x-30, _position.y), Vector2(100, 180), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 80), 225);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x-15, _position.y+30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::BOTTOM:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 80), 180);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y+30), Vector2(180, 100), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 80), 135);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x+15, _position.y+30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 70), 90);
			_attackRC.set(Vector2(_position.x + 100, _position.y + 70), pivot::CENTER);
			_attackRC.update(Vector2(_position.x+30, _position.y), Vector2(100, 180), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 60), 45);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 60), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 15, _position.y - 30), Vector2(130, 120), pivot::CENTER);
			break;
		}
	}
	if (!_ani->isPlay() && _iscombo &&  _combo == 1)
	{
		_attacking = true;
		_state->setState(_vState[PLAYERSTATE::RIGHT_ATTACK]);
		_combo++;
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 50));
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 50), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y - 30), Vector2(180, 100), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 50), 315);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 50), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 15, _position.y - 30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 60), 270);
			_attackRC.set(Vector2(_position.x + 70, _position.y + 60), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 30, _position.y), Vector2(100, 180), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 80), 225);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 15, _position.y + 30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::BOTTOM:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 80), 180);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y + 30), Vector2(180, 100), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 80), 135);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 15, _position.y + 30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 70), 90);
			_attackRC.set(Vector2(_position.x + 100, _position.y + 70), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 30, _position.y), Vector2(100, 180), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			EFFECTMANAGER->play("rightattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 60), 45);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 60), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 15, _position.y - 30), Vector2(130, 120), pivot::CENTER);
			break;
		}
	}
	if (!_ani->isPlay() && _iscombo && _combo == 2)
	{
		_state->setState(_vState[PLAYERSTATE::LEFT_ATTACK]);
		_combo++;

		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 50));
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 50), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y - 30), Vector2(180, 100), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 50), 315);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 50), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 15, _position.y - 30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 60), 270);
			_attackRC.set(Vector2(_position.x + 70, _position.y + 60), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 30, _position.y), Vector2(100, 180), pivot::CENTER);
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 80), 225);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 15, _position.y + 30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::BOTTOM:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 80), 180);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 90, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y + 30), Vector2(180, 100), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 80), 135);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 80), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 15, _position.y + 30), Vector2(130, 120), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 70), 90);
			_attackRC.set(Vector2(_position.x + 100, _position.y + 70), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 30, _position.y), Vector2(100, 180), pivot::CENTER);
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			EFFECTMANAGER->play("leftattackeffect", Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 60), 45);
			_attackRC.set(Vector2(CAMERA->getRelativeVector2(_position).x + 100, CAMERA->getRelativeVector2(_position).y + 60), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 15, _position.y - 30), Vector2(130, 120), pivot::CENTER);
			break;
		}
	}
	if (!_ani->isPlay() && _iscombo && _combo == 3)
	{
		//cout << _state->getState() << endl;
		_attackCount = 0;
		_state->setState(_vState[PLAYERSTATE::RIGHT_FINALATTACK]);
		_iscombo = false;
		_combo++;
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			_attackAngle = 0;
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			_attackAngle = 290;
			break;
		case PLAYERDIRECTION::LEFT:
			_attackAngle = 245;
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			_attackAngle = 220;
			break;
		case PLAYERDIRECTION::BOTTOM:
			_attackAngle = 180;
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			_attackAngle = 130;
			break;
		case PLAYERDIRECTION::RIGHT:
			_attackAngle = 90;
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			_attackAngle = 40;
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			_attackAni[i]->start();
		}
	}

	if (_combo >= 4 && _combocount > 10)
		_combo = 0;

	
}

void player::playerDodgeEffect()
{
	if (_direction == PLAYERDIRECTION::LEFT)
	{
		EFFECTMANAGER->play("player dodgeDust1", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50));
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x + 50, CAMERA->getRelativeVector2(_position).y + 50), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 50), 0, 0.2f);
	}
	else if (_direction == PLAYERDIRECTION::RIGHT)
	{
		EFFECTMANAGER->play("player dodgeDust1", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50));
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x, CAMERA->getRelativeVector2(_position).y + 50), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x - 25, CAMERA->getRelativeVector2(_position).y + 50), 0, 0.2f);
	}
	else if (_direction == PLAYERDIRECTION::TOP)
	{
		EFFECTMANAGER->play("player dodgeDust1", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50));
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 70), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 90), 0, 0.2f);
	}
	else if (_direction == PLAYERDIRECTION::BOTTOM)
	{
		//EFFECTMANAGER->play("player dodgeDust1", CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50);
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y - 10), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y - 30), 0, 0.2f);
	}
	else if (_direction == PLAYERDIRECTION::LEFT_TOP)
	{
		EFFECTMANAGER->play("player dodgeDust1", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50));
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x + 50, CAMERA->getRelativeVector2(_position).y + 70), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y + 90), 0, 0.2f);
	}
	else if (_direction == PLAYERDIRECTION::LEFT_BOTTOM)
	{
		//EFFECTMANAGER->play("player dodgeDust1", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50));
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x + 50, CAMERA->getRelativeVector2(_position).y), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x + 70, CAMERA->getRelativeVector2(_position).y - 20), 0, 0.2f);
	}
	else if (_direction == PLAYERDIRECTION::RIGHT_TOP)
	{
		EFFECTMANAGER->play("player dodgeDust1", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50));
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x, CAMERA->getRelativeVector2(_position).y + 70), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x - 25, CAMERA->getRelativeVector2(_position).y + 90), 0, 0.2f);
	}
	else if (_direction == PLAYERDIRECTION::RIGHT_BOTTOM)
	{
		//EFFECTMANAGER->play("player dodgeDust1", Vector2(CAMERA->getRelativeVector2(_position).x + 25, CAMERA->getRelativeVector2(_position).y + 50));
		EFFECTMANAGER->play("player dodgeDust2", Vector2(CAMERA->getRelativeVector2(_position).x, CAMERA->getRelativeVector2(_position).y), 0, 0.6f);
		EFFECTMANAGER->play("player dodgeDust3", Vector2(CAMERA->getRelativeVector2(_position).x - 25, CAMERA->getRelativeVector2(_position).y - 20), 0, 0.2f);
	}
}

void player::playerLethalattack()
{
	if (_state->getState() == _vState[LETHAL_CHARGE] && _isLethal && _lethalCharge > 35)
	{
			_state->setState(_vState[PLAYERSTATE::LETHAL_ATTACK]);
			_isLethal = false;
			_attackCount = 0;
			_lethalCharge = 0;

			switch (_direction)
			{
			case PLAYERDIRECTION::TOP:
				_attackAngle = 0;
				break;
			case PLAYERDIRECTION::LEFT_TOP:
				_attackAngle = 290;
				break;
			case PLAYERDIRECTION::LEFT:
				_attackAngle = 245;
				break;
			case PLAYERDIRECTION::LEFT_BOTTOM:
				_attackAngle = 220;
				break;
			case PLAYERDIRECTION::BOTTOM:
				_attackAngle = 180;
				break;
			case PLAYERDIRECTION::RIGHT_BOTTOM:
				_attackAngle = 130;
				break;
			case PLAYERDIRECTION::RIGHT:
				_attackAngle = 90;
				break;
			case PLAYERDIRECTION::RIGHT_TOP:
				_attackAngle = 40;
				break;
			}
			for (int i = 0; i < 4; i++)
			{
				_attackAni[i]->start();
			}
			//_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
	}
	
}

void player::playerLethalattackMove()
{
	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	POINT nextTileIndex;
	float moveSpeed = 6.0f;

	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		nextTileIndex = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::BOTTOM:
		nextTileIndex = { currentTileIndex.x, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y };
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		nextTileIndex = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		break;
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize() - 1;
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize() - 1;

	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	if (t->getOrderIndex() == _nowOrder)
	{
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y - 15), Vector2(240, 240), pivot::CENTER);
			move(0, -moveSpeed);
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 10, _position.y - 10), Vector2(240, 240), pivot::CENTER);
			moveAngle(PI*0.75, moveSpeed);
			break;
		case PLAYERDIRECTION::LEFT:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 15, _position.y), Vector2(240, 240), pivot::CENTER);
			move(-moveSpeed, 0);
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x - 10, _position.y + 10), Vector2(240, 240), pivot::CENTER);
			moveAngle(PI*1.25, moveSpeed);
			break;
		case PLAYERDIRECTION::BOTTOM:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x, _position.y + 15), Vector2(240, 240), pivot::CENTER);
			move(0, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 10, _position.y + 10), Vector2(240, 240), pivot::CENTER);
			moveAngle(PI*1.75, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 15, _position.y), Vector2(240, 240), pivot::CENTER);
			move(moveSpeed, 0);
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			_attackRC.set(Vector2(_position.x, _position.y), pivot::CENTER);
			_attackRC.update(Vector2(_position.x + 10, _position.y - 10), Vector2(240, 240), pivot::CENTER);
			moveAngle(PI*0.25, moveSpeed);
			break;
		}
		_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	}
}

void player::setIdle()
{
	_state->setState(_vState[PLAYERSTATE::IDLE]);
}
