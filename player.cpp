#include "stdafx.h"
#include "player.h"

player::player()
{
	playerState* idle = new idleState();
	playerState* move = new moveState();
	playerState* jump = new jumpState();

	_vState.push_back(idle);
	_vState.push_back(move);
	_vState.push_back(jump);

	_state = new playerStateController(idle);
}

player::~player()
{
}

void player::init()
{
}

void player::release()
{
}

void player::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_state->setState(_vState[MOVE]);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_state->setState(_vState[IDLE]);
	}
	_state->updateState();
}

void player::render()
{
}

void player::move(const float & x, const float & y)
{
}

void player::moveAngle(const float & cangle, const float & speed)
{
}
