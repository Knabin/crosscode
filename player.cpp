#include "stdafx.h"
#include "player.h"
#include "tile.h"
#include "scene.h"

player::player()
{
	playerState* idle = new idleState(this);
	playerState* move = new moveState(this);
	playerState* jump = new jumpState(this);

	_vState.push_back(idle);
	_vState.push_back(move);
	_vState.push_back(jump);

	_name = "player";
	_isActive = true;

	_state = new playerStateController(idle);
	_y = 700;

	_attackPower = RND->getFromIntTo(5, 10);
	_count = 0;
	_isAttack = false;
}

player::~player()
{
}

HRESULT player::init()
{
	_image = IMAGEMANAGER->addFrameImage("p", "playertest.bmp", 1152, 768, 12, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player jump", "images/playerjump.bmp", 192, 768, 2, 8, true, RGB(255, 0, 255));
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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		// KEYDOWN �� �̵� ���·� ����
		_state->setState(_vState[PLAYERSTATE::MOVE]);

		// UP/DOWN Ű�� ���� ������ �밢������ ���� ����
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_direction = PLAYERDIRECTION::LEFT_TOP;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_direction = PLAYERDIRECTION::LEFT_BOTTOM;
		}
		else
		{
			_direction = PLAYERDIRECTION::LEFT;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		// KEYDOWN �� �̵� ���·� ����
		_state->setState(_vState[PLAYERSTATE::MOVE]);
		
		// UP/DOWN Ű�� ���� ������ �밢������ ���� ����
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_direction = PLAYERDIRECTION::RIGHT_TOP;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_direction = PLAYERDIRECTION::RIGHT_BOTTOM;
		}
		else
		{
			_direction = PLAYERDIRECTION::RIGHT;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_state->setState(_vState[PLAYERSTATE::MOVE]);
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_direction = PLAYERDIRECTION::RIGHT_TOP;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_direction = PLAYERDIRECTION::LEFT_TOP;
		}
		else
		{
			_direction = PLAYERDIRECTION::TOP;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_state->setState(_vState[PLAYERSTATE::MOVE]);
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_direction = PLAYERDIRECTION::RIGHT_BOTTOM;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_direction = PLAYERDIRECTION::LEFT_BOTTOM;
		}
		else
		{
			_direction = PLAYERDIRECTION::BOTTOM;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_attackRC.set(0, 0, 100, 100);
		_attackRC.setCenter(_x, _y);
		_isAttack = true;
	}

	if (_isAttack)
	{
		_count++;
		if (_count % 5 == 0)
		{
			_attackRC.set(0, 0, 0, 0);
			_count = 0;
			_isAttack = false;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
		_state->setState(_vState[PLAYERSTATE::IDLE]);

	_tile.setLeftTop(((int)_x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE);
	_state->updateState();
}

void player::render()
{
	_attackRC.render(getMemDC());
	//_rc.render(getMemDC());
	_tile.render(getMemDC());
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
	//RectangleMake(getMemDC(), tileIndex.x * SIZE, tileIndex.y *SIZE, SIZE, SIZE);
	Rectangle(getMemDC(), rcCollision);
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

	// ���� Ÿ��
	if (nextTileIndex.x > maxTileX) nextTileIndex.x = maxTileX;
	else if (nextTileIndex.x < 0) nextTileIndex.x = 0;
	if (nextTileIndex.y > maxTileY) nextTileIndex.y = maxTileY;
	else if (nextTileIndex.y < 0) nextTileIndex.y = 0;
	tile* t = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex.y][nextTileIndex.x];

	// ���� ���ٸ�
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
	// ���� �÷��̾�� ���ٸ�
	else if(t->getOrderIndex() > _nowOrder)
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
