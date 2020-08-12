#pragma once
#include "playerState.h"

class playerStateController
{
private:
	playerState* _state;

public:
	playerStateController(playerState * defaultState);

	void updateState();
	playerState* getState() { return _state; }
	void setState(playerState* state);
};

