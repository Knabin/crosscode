#pragma once
#include "playerState.h"

class playerStateController
{
private:
	playerState* _state;

public:
	playerStateController(playerState * defaultState);

	void updateState();
	void setState(playerState* state);
};

