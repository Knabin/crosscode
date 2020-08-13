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
	playerState* defaltLongAttack = new defaltLongAttackState(this);

	_vState.push_back(idle);
	_vState.push_back(move);
	_vState.push_back(jump);
	_vState.push_back(guard);
	_vState.push_back(dodge);
	_vState.push_back(defaltLongAttack);

	_name = "player";
	_isActive = true;

	_state = new playerStateController(idle);
	_y = 700;
}

player::~player()
{
}

HRESULT player::init()
{
	_image = IMAGEMANAGER->addFrameImage("p", "images/player/player_move.bmp", 1152, 768, 12, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player guard", "images/player/player_guard.bmp", 288, 768, 3, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player jump", "images/player/playerjump.bmp", 192, 768, 2, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player dodge", "images/player/player_dodge.bmp", 711,696, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player longAttack", "images/player/player_longAttack.bmp", 1581, 720, 17, 8, true, RGB(255, 0, 255));
	

	_width = _height = 96;
	_pivot = pivot::CENTER;
	_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
	_tile.set(0, 0, 48, 48);
	_nowOrder = 1;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_ptMouseAbs.x = _ptMouse.x + CAMERA->getRect().left;
	_ptMouseAbs.y = _ptMouse.y + CAMERA->getRect().top;

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		// KEYDOWN 시 이동 상태로 변경
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
		}
		else if (_state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
		// UP/DOWN 키를 같이 누르면 대각선으로 방향 변경
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

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		// KEYDOWN 시 이동 상태로 변경
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
		}
		else if (_state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
		// UP/DOWN 키를 같이 누르면 대각선으로 방향 변경
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

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
		}
		else if (_state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}			

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

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_state->setState(_vState[PLAYERSTATE::DODGE]);
			_ani->start();
		}
		else if (_state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}

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

	if (_state->getState() == _vState[IDLE] &&
		(KEYMANAGER->isStayKeyDown('C') || KEYMANAGER->isStayKeyDown(VK_RBUTTON)))
	{
			_state->setState(_vState[PLAYERSTATE::GUARD]);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_state->setState(_vState[PLAYERSTATE::LONGATTACK]);
		playerFire();
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

	/*
	float angle = getAngle(_x, _y, _ptMouseAbs.x, _ptMouseAbs.y);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))	de -= PI / 50;
	if (de < 0)	de = 0;
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	de = PI / 4;

	float d1 = angle + de;
	float d2 = angle - de;

	for (int i = 0; i < 10; i++)
	{
		rc1[i].set(0, 0, 10, 10);
		rc1[i].setCenter(_x + cosf(d1) * 20 * i, _y + -sinf(d1) * 20 * i);
	}
	for (int i = 0; i < 10; i++)
	{
		rc2[i].set(0, 0, 10, 10);
		rc2[i].setCenter(_x + cosf(d2) * 20 * i, _y + -sinf(d2) * 20 * i);
	}
	*/

	// ==================== 가드상태 또는 원거리 공격시 마우스 방향으로 플레이어의 방향 바뀜 ==================== //
	if (_state->getState() == _vState[PLAYERSTATE::GUARD] || _state->getState() == _vState[PLAYERSTATE::LONGATTACK])
	{
		float angle = getAngle(_x, _y, _ptMouseAbs.x, _ptMouseAbs.y);
	
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

	if (KEYMANAGER->isOnceKeyUp('A')
		|| KEYMANAGER->isOnceKeyUp('W')
		|| KEYMANAGER->isOnceKeyUp('D')
		|| KEYMANAGER->isOnceKeyUp('S')
		|| KEYMANAGER->isOnceKeyUp('C')
		|| (KEYMANAGER->isOnceKeyUp(VK_RBUTTON) && _state->getState() == _vState[PLAYERSTATE::GUARD])
		//|| KEYMANAGER->isOnceKeyUp(VK_LBUTTON)
		)
		_state->setState(_vState[PLAYERSTATE::IDLE]);

	//if (_state->getState()->longAttack == false)
	//{
	//	_state->setState(_vState[PLAYERSTATE::IDLE]);
	//}

	_tile.setLeftTop(((int)_x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE);
	_state->updateState();
}

void player::render()
{
	//_rc.render(getMemDC());
	_tile.render(getMemDC());
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
	//RectangleMake(getMemDC(), tileIndex.x * SIZE, tileIndex.y *SIZE, SIZE, SIZE);
	Rectangle(getMemDC(), rcCollision);

	for (int i = 0; i < 10; i++)
	{
		rc1[i].render(getMemDC());
		rc2[i].render(getMemDC());
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

	POINT currentTileIndex = {_tile.left / SIZE, _tile.top / SIZE};
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
		_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
		_tile.setLeftTop(((int)_x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE);
	}
	// 층이 플레이어보다 높다면
	else if(t->getOrderIndex() > _nowOrder)
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

void player::playerDodge()
{
	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	POINT nextTileIndex;
	float moveSpeed = 8.3f;

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
		_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
		_tile.setLeftTop(((int)_x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE);
	}
}

void player::move(const float & x, const float & y)
{
	_x += x;
	_y += y;
	_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
}

void player::moveAngle(const float & cangle, const float & speed)
{
	_x += cosf(cangle) * speed;
	_y -= sinf(cangle) * speed;
	_rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot);
}

void player::playerFire()
{

}
