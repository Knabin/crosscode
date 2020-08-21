#pragma once
#include "gameNode.h"
#include "player.h"
#include "collisionManager.h"
#include "uiController.h"
#include "enemyManager.h"
#include "puzzleCollision.h"

class playGround : public gameNode
{
private:
	player* _player;
	collisionManager* _collisionManager;
	uiController* _ui;
	enemyManager* _enemyManager;
	puzzleCollision* _puzzleCollision;

	float _test;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

