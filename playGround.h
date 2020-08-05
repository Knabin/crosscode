#pragma once
#include "gameNode.h"
#include "player.h"
#include "uiController.h"

class playGround : public gameNode
{
private:
	player* _player;
	uiController* _ui;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

