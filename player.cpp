#include "stdafx.h"
#include "player.h"

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
	_image = IMAGEMANAGER->addFrameImage("p", "playertest.bmp", 768, 912, 16, 19, true, RGB(255, 0, 255));

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		// KEYDOWN 시 이동 상태로 변경
		_state->setState(_vState[PLAYERSTATE::MOVE]);
		
		// UP/DOWN 키를 같이 누르면 대각선으로 방향 변경
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
	_image->aniRender(getMemDC(), _x, _y, _ani);
}

void player::move(const float & x, const float & y)
{
	_x += x;
	_y += y;
	_rc.setCenter(_x, _y);
}

void player::moveAngle(const float & cangle, const float & speed)
{
	_x += cosf(cangle) * speed;
	_y -= sinf(cangle) * speed;
	_rc.setCenter(_x, _y);
}
