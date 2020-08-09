#include "stdafx.h"
#include "player.h"
#include "tile.h"

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
}

player::~player()
{
}

HRESULT player::init()
{
	_image = IMAGEMANAGER->addFrameImage("p", "playertest.bmp", 768, 512, 12, 8, true, RGB(255, 0, 255));
	_rc.set(0, 0, 64, 64);
	_rc.setLeftTop(_x, _y);

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

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
		_state->setState(_vState[PLAYERSTATE::IDLE]);

	_state->updateState();
}

void player::render()
{
	_rc.render(getMemDC());
	_image->aniRender(getMemDC(), _x, _y, _ani);
}

void player::playerMove()
{
	RECT rcCollision;
	int tileIndex[2];
	int tileX, tileY;

	rcCollision = _rc.getRect();

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * 5.0f;

	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		_y -= moveSpeed;
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_x -= moveSpeed;
		_y -= moveSpeed;
		break;
	case PLAYERDIRECTION::LEFT:
		_x -= moveSpeed;
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_x -= moveSpeed;
		_y += moveSpeed;
		break;
	case PLAYERDIRECTION::BOTTOM:
		_y += moveSpeed;
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_x += moveSpeed;
		_y += moveSpeed;
		break;
	case PLAYERDIRECTION::RIGHT:
		_x += moveSpeed;
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_x += moveSpeed;
		_y -= moveSpeed;
		break;
	}

	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	rcCollision.left += 2;
	rcCollision.top += 2;
	rcCollision.right -= 2;
	rcCollision.bottom -= 2;

	tileX = rcCollision.left / SIZE;
	tileY = rcCollision.top / SIZE;

	switch (_direction)
	{
	case PLAYERDIRECTION::TOP:
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		break;
	case PLAYERDIRECTION::LEFT:
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		break;
	case PLAYERDIRECTION::BOTTOM:
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		break;
	case PLAYERDIRECTION::RIGHT:
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		break;
	default:
		break;
	}
}

void player::move(const float & x, const float & y)
{
	_x += x;
	_y += y;
	_rc.setLeftTop(_x, _y);
}

void player::moveAngle(const float & cangle, const float & speed)
{
	_x += cosf(cangle) * speed;
	_y -= sinf(cangle) * speed;
	_rc.setLeftTop(_x, _y);
}
