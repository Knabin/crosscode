#include "stdafx.h"
#include "player.h"
#include "tile.h"
#include "scene.h"

player::player()
{
	playerState* idle = new idleState(this);
	playerState* move = new moveState(this);
	playerState* jump = new jumpState(this);
	playerState* guard = new guardState(this);
	playerState* dodge = new dodgeState(this);
	playerState* longAttack = new longAttackState(this);
	playerState* longAttackMove = new longAttackMoveState(this);
	playerState* movestop = new movestopState(this);
	playerState* leftattackstate = new leftattackState(this);
	playerState* rightattackstate = new rightattackState(this);
	playerState* rightfinalattackstate = new rightfinalattackState(this);

	_vState.push_back(idle);
	_vState.push_back(move);
	_vState.push_back(jump);
	_vState.push_back(guard);
	_vState.push_back(dodge);
	_vState.push_back(longAttack);
	_vState.push_back(longAttackMove);
	_vState.push_back(movestop);
	_vState.push_back(leftattackstate);
	_vState.push_back(rightattackstate);
	_vState.push_back(rightfinalattackstate);

	_name = "player";
	_isActive = true;

	_combo = 0;
	_iscombo = false;
	_fullCount = 0;

	_dodgeCount = 4; //닷지 기본 횟수

	_state = new playerStateController(idle);
	_position.y = 700;
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


	_width = _height = 96;
	_pivot = pivot::CENTER;
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);
	_nowOrder = 1;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (KEYMANAGER->isStayKeyDown('A'))
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
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] &&_state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}

	}

	if (KEYMANAGER->isStayKeyDown('D'))
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
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] && _state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}

	}

	if (KEYMANAGER->isStayKeyDown('W'))
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
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] && _state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}

	}

	if (KEYMANAGER->isStayKeyDown('S'))
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
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] && _state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
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

		if (getDistance(_position.x, _position.y, _ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left, _ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top) < 150)
		{
			playerMeleeattack();
		}
		else if (getDistance(_position.x, _position.y, _ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left, _ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top) >= 100 && _state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE])
		{
			_state->setState(_vState[PLAYERSTATE::LONGATTACK]);
			_state->getState()->setLongAttack();
			playerFire();
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _state->getState() != _vState[PLAYERSTATE::LONGATTACK])
	
	{
		_fullCount++;
		if (_fullCount > 10)
		{
			_state->setState(_vState[PLAYERSTATE::LONGATTACKMOVE]);
		}
	}


	if (_state->getState() == _vState[PLAYERSTATE::DODGE] && _ani->isPlay() == false)
	{
		_state->setState(_vState[PLAYERSTATE::IDLE]);
	}

	/* 원거리 공격 버튼 누를 시 점선이 중앙으로 모임
			float angle = getAngle(_x, _y, _ptMouseAbs.x, _ptMouseAbs.y);
		de -= PI / 15;
		float d1 = angle + de;
		_rc.setCenter(_x + cosf(d1), _y + -sinf(d1));
	*/

	// ==================== 가드상태 또는 원거리 공격시 마우스 방향으로 플레이어의 방향 바뀜 ==================== //
	if (_state->getState() == _vState[PLAYERSTATE::GUARD] || _state->getState() == _vState[PLAYERSTATE::LONGATTACK])
	{
		float angle = getAngle(_position.x, _position.y,
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

			if (angle > min && angle <= max && i != 6)
			{
				_direction = (PLAYERDIRECTION)i;
			}
			else if (((angle <= PI2 && angle > min) || (angle >= 0 && angle <= max)) && i == 6)
			{
				_direction = (PLAYERDIRECTION)i;
			}
		}
	}

	if (_state->getState() == _vState[LONGATTACK])
	{
		float angle = getAngle(_position.x, _position.y, _ptMouse.x, _ptMouse.y);

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))	de -= PI / 50;
		if (de < 0)	de = 0;
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	de = PI / 4;

		float d1 = angle + de;
		float d2 = angle - de;

		for (int i = 0; i < 10; i++)
		{
			rc1[i].update(Vector2(_position.x + cosf(d1) * 20 * i, _position.y + -sinf(d1) * 20 * i), Vector2(10, 10), pivot::CENTER);
		}
		for (int i = 0; i < 10; i++)
		{
			rc2[i].update(Vector2(_position.x + cosf(d2) * 20 * i, _position.y + -sinf(d2) * 20 * i), Vector2(10, 10), pivot::CENTER);
		}
	}


	//========================================움직이고 나서 정지하는 모션 ====================================================
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('S') ||
		KEYMANAGER->isOnceKeyUp('A') && KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('D') && KEYMANAGER->isOnceKeyUp('W') ||
		KEYMANAGER->isOnceKeyUp('A') && KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('D') && KEYMANAGER->isOnceKeyUp('S'))
		_state->setState(_vState[PLAYERSTATE::MOVESTOP]);


	if (KEYMANAGER->isOnceKeyUp('C')
		|| (KEYMANAGER->isOnceKeyUp(VK_RBUTTON) && _state->getState() == _vState[PLAYERSTATE::GUARD])
		|| _state->getState() == _vState[MOVESTOP] && !_ani->isPlay()
		|| _state->getState() == _vState[RIGHT_FINALATTACK] && !_ani->isPlay()
		//|| KEYMANAGER->isOnceKeyUp(VK_LBUTTON)
		)
		_state->setState(_vState[PLAYERSTATE::IDLE]);


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
}

void player::render()
{
	//_rc.render(getMemDC());
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_tile));
	_image->setSize(_image->getFrameSize() * CAMERA->getZoomAmount());
	_image->aniRender(CAMERA->getRelativeVector2(_position.x, _position.y), _ani, 1.0f);
	//RectangleMake(getMemDC(), tileIndex.x * SIZE, tileIndex.y *SIZE, SIZE, SIZE);
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(floatRect(rcCollision)));

	for (int i = 0; i < 10; ++i)
	{
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(rc1[i]));
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(rc2[i]));
	}
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
	POINT nextTileIndex;
	float moveSpeed = 4.5f;

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

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();

	// 다음 타일
	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	// 층이 같다면
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
	// 층이 플레이어보다 높다면
	else if (t->getOrderIndex() > _nowOrder)
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
	}
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

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();

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

void player::playerLongAttackMove()		//원거리 공격시 움직임
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

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();

	// 다음 타일
	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	// 층이 같다면
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

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();

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

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();


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
			moveAngle(PI*0.75, moveSpeed);
			break;
		case PLAYERDIRECTION::LEFT:
			move(-moveSpeed, 0);
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			moveAngle(PI*1.25, moveSpeed);
			break;
		case PLAYERDIRECTION::BOTTOM:
			move(0, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			moveAngle(PI*1.75, moveSpeed);
			break;
		case PLAYERDIRECTION::RIGHT:
			move(moveSpeed, 0);
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
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
}

void player::moveAngle(const float & cangle, const float & speed)
{
	_position.x += cosf(cangle) * speed;
	_position.y -= sinf(cangle) * speed;
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
}

void player::playerFire()
{

}

void player::playerMeleeattack()   //근접 기본공격
{
	_combocount = 0;
	if (_state->getState() == _vState[IDLE] && !_iscombo || _state->getState() == _vState[MOVE] && !_iscombo)
	{
		_state->setState(_vState[PLAYERSTATE::LEFT_ATTACK]);
		_iscombo = true;
		_combo++;
	}
	if (!_ani->isPlay() && _iscombo &&  _combo == 1)
	{
		_state->setState(_vState[PLAYERSTATE::RIGHT_ATTACK]);
		_combo++;

	}
	if (!_ani->isPlay() && _iscombo && _combo == 2)
	{
		_state->setState(_vState[PLAYERSTATE::LEFT_ATTACK]);
		_combo++;
	}
	if (!_ani->isPlay() && _iscombo && _combo == 3)
	{
		_state->setState(_vState[PLAYERSTATE::RIGHT_FINALATTACK]);
		_iscombo = false;
		_combo++;
	}

	if (_combo >= 4 && _combocount > 10)
		_combo = 0;
}
