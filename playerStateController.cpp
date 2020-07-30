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
	// ������ ���·� �����Ϸ��� �ϸ� �ƹ��͵� ���� ����
	if (_state == state) return;

	// ���� ������ exit ȣ��
	_state->exit();

	// ���� ����
	_state = state;

	// ����� ������ enter ȣ��
	_state->enter();
}
