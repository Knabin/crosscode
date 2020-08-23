#pragma once
#include "gameNode.h"
#include "player.h"

class bossCollision : public gameNode
{

private:
	player* _player;
	int _collisionCount;
	int _playerCollisionCount;


public:


	bossCollision();
	~bossCollision();

	HRESULT init();
	void release();
	void update();
	void render();

	void icethrowerCollision();
	void mineCollision();
	void stoneCollision();
	void flameCollision();
	void iceguideCollision();

	void bossHandCollision();
	void bossMineCollision();

	void bossBulletCollision();
	void bossAttackCollision();

	void newMineCollision();
	void newBossMineCollision();


};

