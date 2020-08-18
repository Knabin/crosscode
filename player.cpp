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
	playerState* longAttackIdle = new longAttackIdleState(this);
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
	_vState.push_back(longAttackIdle);
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

	_dodgeCount = 4; //���� �⺻ Ƚ��

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
	IMAGEMANAGER->addImage("player longAttackLine", L"images/player/player_longAttack_Line.png");

	_width = _height = 96;
	_pivot = pivot::CENTER;
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);
	_nowOrder = 1;
	_tileRect.update(Vector2(0, 0), Vector2(40, 40), pivot::CENTER);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	
	if (KEYMANAGER->isStayKeyDown('A') && _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE])
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
		// ================== ���� ó��==================
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
			_state->getState() != _vState[PLAYERSTATE::DODGE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
	}

	if (KEYMANAGER->isStayKeyDown('D') && _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE])
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
		// ================== ���� ó��==================
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
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] && _state->getState() != _vState[PLAYERSTATE::DODGE]
			&& _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] && _state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
	}

	if (KEYMANAGER->isStayKeyDown('W') && _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE])
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
		// ================== ���� ó��==================
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
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] && _state->getState() != _vState[PLAYERSTATE::DODGE]
			&& _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] && _state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}
	}

	if (KEYMANAGER->isStayKeyDown('S') && _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE])
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
		// ================== ���� ó��==================
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
		else if (_state->getState() != _vState[PLAYERSTATE::LEFT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_ATTACK] && _state->getState() != _vState[PLAYERSTATE::RIGHT_FINALATTACK] && _state->getState() != _vState[PLAYERSTATE::DODGE]
			&& _state->getState() != _vState[PLAYERSTATE::LONGATTACKIDLE] && _state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE])
		{
			_state->setState(_vState[PLAYERSTATE::MOVE]);
		}

	}

	_combocount++;   // �������� �޺� ī��Ʈ��

	// ==================���� ���� �ʱ�ȭ��==================
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
	if (KEYMANAGER->isOnceKeyDown('V')) //��������Ű
	{
		playerMeleeattack();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))	// ������ ���� , �ָ� ���Ÿ� ����
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
			playerFire();
		}
	}

	if (_state->getState() == _vState[LONGATTACK])
	{
		float angle = getAngle(_position.x, _position.y,
			_ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left,
			_ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top);

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))	de -= PI / 50;
		if (de < 0)	de = 0;
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	de = PI / 4;

		float d1 = angle - de;
		float d2 = angle + de;

		for (int i = 0; i < 10; i++)
		{
			rc1[i].update(Vector2(_position.x + cosf(d1) * 20 * i, _position.y + -sinf(d1) * 20 * i), Vector2(10, 10), pivot::CENTER);
		}
		for (int i = 0; i < 10; i++)
		{
			rc2[i].update(Vector2(_position.x + cosf(d2) * 20 * i, _position.y + -sinf(d2) * 20 * i), Vector2(10, 10), pivot::CENTER);
		}
	}


	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _state->getState() != _vState[PLAYERSTATE::LONGATTACK] && _state->getState() != _vState[PLAYERSTATE::LONGATTACKMOVE])
	{
		_fullCount++;
		if (_fullCount > 15)
		{
			_state->setState(_vState[PLAYERSTATE::LONGATTACKIDLE]);
		}
	}

	//�� ���� ������ �� ���콺 ���� ��ư �� �� �� ���� ���
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE])
	{
		_state->setState(_vState[PLAYERSTATE::LONGATTACK]);
		_state->getState()->setLongAttack();
		playerFire();
	}

	if (_state->getState() == _vState[PLAYERSTATE::DODGE] && _ani->isPlay() == false)
	{
		_state->setState(_vState[PLAYERSTATE::IDLE]);
	}

	// ==================== ������� �Ǵ� ���Ÿ� ���ݽ� ���콺 �������� �÷��̾��� ���� �ٲ� ==================== //
	if (_state->getState() == _vState[PLAYERSTATE::GUARD] || _state->getState() == _vState[PLAYERSTATE::LONGATTACK] || _state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE])
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

	//========================================�����̰� ���� �����ϴ� ��� ====================================================
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('S') ||
		KEYMANAGER->isOnceKeyUp('A') && KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('D') && KEYMANAGER->isOnceKeyUp('W') ||
		KEYMANAGER->isOnceKeyUp('A') && KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('D') && KEYMANAGER->isOnceKeyUp('S'))
		_state->setState(_vState[PLAYERSTATE::MOVESTOP]);

	if (KEYMANAGER->isOnceKeyUp('C')
		|| (KEYMANAGER->isOnceKeyUp(VK_RBUTTON) && _state->getState() == _vState[PLAYERSTATE::GUARD])
		|| _state->getState() == _vState[MOVESTOP] && !_ani->isPlay()
		|| _state->getState() == _vState[RIGHT_FINALATTACK] && !_ani->isPlay()
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

	cout << _nowOrder << endl;
	_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	_state->updateState();
}

void player::render()
{
	//_rc.render(getMemDC());
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_tileRect));
	_image->setSize(_image->getFrameSize() * CAMERA->getZoomAmount());
	_image->aniRender(CAMERA->getRelativeVector2(_position.x, _position.y), _ani, 1.0f);
	//RectangleMake(getMemDC(), tileIndex.x * SIZE, tileIndex.y *SIZE, SIZE, SIZE);
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(floatRect(rcCollision)));

	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(SCENEMANAGER->getCurrentScene()->getTiles()[next[0].y][next[0].x]->getRect()),
		D2D1::ColorF::Aqua, 0);
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(SCENEMANAGER->getCurrentScene()->getTiles()[next[1].y][next[1].x]->getRect()),
		D2D1::ColorF::Aqua, 0);
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(SCENEMANAGER->getCurrentScene()->getTiles()[next[2].y][next[2].x]->getRect()),
		D2D1::ColorF::Aqua, 0);

	if (_state->getState() == _vState[PLAYERSTATE::LONGATTACK] ||
		_state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE] ||
		_state->getState() == _vState[PLAYERSTATE::LONGATTACKMOVE])
	{
		for (int i = 0; i < 10; ++i)
		{
			D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(rc1[i]));
			D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(rc2[i]));
		}
	}
}

void player::playerMove()
{
	// ���� �ִ� �������� �տ� üũ
	// üũ�� Ÿ�ϰ� ���� ���ٸ�
	//		�׳� �̵�
	// üũ�� Ÿ�ϰ� ���� �ٸ��ٸ�
	//		���ٸ�
	//			1���̶�� ������
	//			�ƴ϶�� �̵����� ����
	//		���ٸ�

	//			���� ���� 0�̶�� ��������
	//			(���� �վ�Ÿ�ϰ� ���� ���ٸ� �ű���� ������)
	//			�ƴ϶�� (���� �ð���ŭ) ������
	// **���� �Լ����� �������� �� �� üũ�ؼ� player ������ �ְ� idle�� �̵�

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
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y + 1 };
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x - 1, currentTileIndex.y - 1 };
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		next[0] = { currentTileIndex.x - 1, currentTileIndex.y +1};
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y  };
		next[2] = { currentTileIndex.x, currentTileIndex.y +1};
		break;
	case PLAYERDIRECTION::BOTTOM:
		next[0] = { currentTileIndex.x, currentTileIndex.y +1};
		next[1] = { currentTileIndex.x - 1, currentTileIndex.y +1};
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y +1};
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y +1};
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y  };
		next[2] = { currentTileIndex.x, currentTileIndex.y +1};
		break;
	case PLAYERDIRECTION::RIGHT:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[2] = { currentTileIndex.x + 1, currentTileIndex.y + 1 };
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		next[0] = { currentTileIndex.x + 1, currentTileIndex.y - 1 };
		next[1] = { currentTileIndex.x + 1, currentTileIndex.y };
		next[2] = { currentTileIndex.x, currentTileIndex.y - 1 };
		break;
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();



	// ���� Ÿ��
	for (int i = 0; i < 3; ++i)
	{
		if (next[i].x > maxTileX) next[i].x = maxTileX;
		else if (next[i].x < 0) next[i].x = 0;
		if (next[i].y > maxTileY) next[i].y = maxTileY;
		else if (next[i].y < 0) next[i].y = 0;
	}

	RECT temp;
	
	int _backOrder = _nowOrder;
	_nowOrder = SCENEMANAGER->getCurrentScene()->getTiles()[currentTileIndex.y][currentTileIndex.x]->getOrderIndex();
	if (_nowOrder == 4)
	{
		_nowOrder = _backOrder;
	}
	
	
	// ���� ���ٸ�
	//if (ti->getOrderIndex() == _nowOrder)
	{
		switch (_direction)
		{
		case PLAYERDIRECTION::TOP:
			move(0, -moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 4)
				{
					move(0, 4.5f);
					break;
				}
			}
			break;
		case PLAYERDIRECTION::LEFT_TOP:
			moveAngle(PI * 0.75, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder + 1 && ti->getOrderIndex() != 4)
				{
					moveAngle(PI * 1.75f, moveSpeed);
					break;
				}
			}
			break;
		case PLAYERDIRECTION::LEFT:
			move(-moveSpeed, 0);

			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder +1 && ti->getOrderIndex() != 4)
				{
					move(4.5f, 0);
					break;
				}
			}
			break;
		case PLAYERDIRECTION::LEFT_BOTTOM:
			moveAngle(PI * 1.25, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder +1 && ti->getOrderIndex() != 4)
				{
					moveAngle(PI * 0.25f, moveSpeed);
					break;
				}
			}
			break;
		case PLAYERDIRECTION::BOTTOM:
			move(0, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder +1 && ti->getOrderIndex() != 4)
				{
					move(0, -4.5f);
					break;
				}
			}
			break;
		case PLAYERDIRECTION::RIGHT_BOTTOM:
			moveAngle(PI * 1.75, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder +1 && ti->getOrderIndex() != 4)
				{
					moveAngle(PI * 0.75f, moveSpeed);
					break;
				}
			}
			break;
		case PLAYERDIRECTION::RIGHT:
			move(moveSpeed, 0);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder +1 && ti->getOrderIndex() != 4)
				{
					move(-4.5f, 0);
					break;
				}
			}
			break;
		case PLAYERDIRECTION::RIGHT_TOP:
			moveAngle(PI * 0.25, moveSpeed);
			for (int i = 0; i < 3; ++i)
			{
				tile* ti = SCENEMANAGER->getCurrentScene()->getTiles()[next[i].y][next[i].x];
				if (IntersectRect(&temp, &ti->getRect().getRect(), &_tileRect.getRect()) && ti->getOrderIndex() > _nowOrder +1 && ti->getOrderIndex() != 4)
				{
					moveAngle(PI * 1.25f, moveSpeed);
					break;
				}
			}
			break;
		}
		_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
		//_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);
	}
	// ���� �÷��̾�� ���ٸ�
	/*if (t->getOrderIndex() > _nowOrder)
	{
		// �� �� ���̶��
		if (t->getOrderIndex() - _nowOrder == 1)
		{
			// TODO: ����
		}
	}
	// ���� �÷��̾�� ���ٸ�
	else
	{
		// ���� ó��
		if (_nowOrder == 0) return;
		// TODO: ����
	}*/
}

void player::playerDodge()		//ȸ�ǽ� ������
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

void player::playerLongAttackMove()
{
	POINT currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };
	POINT nextTileIndex;
	float moveSpeed = 1.5f;

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

void player::playermeleeattackMove()	// ��������+����Ű �����̸鼭 �����Ҷ� Ÿ��üũ
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

void player::playerfinalattackMove() // �������� ������Ÿ �����̴°� Ÿ��üũ
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
	_tileRect.set(_position + Vector2(0, 30), pivot::CENTER);
}

void player::moveAngle(const float & cangle, const float & speed)
{
	_position.x += cosf(cangle) * speed;
	_position.y -= sinf(cangle) * speed;
	_rc = RectMakePivot(_position, Vector2(_width, _height), _pivot);
	_tileRect.set(_position + Vector2(0, 30), pivot::CENTER);
}

void player::playerFire()
{
}

void player::playerMeleeattack()   //���� �⺻����
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
