#pragma once
#include "gameNode.h"
#include "player.h"

class playGround : public gameNode
{
private:
	player* _player;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	

};

