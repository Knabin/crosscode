#pragma once
#include "gameNode.h"
#include "player.h"

class bossCollision : public gameNode
{

private:
	player* _player;


public:


	bossCollision();
	~bossCollision();

	HRESULT init();
	void release();
	void update();
	void render();

	void icethrowerCollision();
	void stoneCollision();
	void flameCollision();
	void iceguideCollision();

};

