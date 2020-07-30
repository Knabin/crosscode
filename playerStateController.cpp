#include "stdafx.h"
#include "playerStateController.h"


playerStateController::playerStateController(playerState* defaultState)
{
	_state = defaultState;
	_state->enter();
}


void playerStateController::updateState()
{
	_state->update();
}

void playerStateController::setState(playerState* state)
{
	// 동일한 상태로 변경하려고 하면 아무것도 하지 않음
	if (_state == state) return;

	// 이전 상태의 exit 호출
	_state->exit();

	// 상태 변경
	_state = state;

	// 변경된 상태의 enter 호출
	_state->enter();
}
