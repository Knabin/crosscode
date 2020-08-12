#pragma once
#include "gameNode.h"
#include "player.h"
#include "collisionManager.h"
#include "uiController.h"
#include "enemyManager.h"

class playGround : public gameNode
{
private:
	player* _player;
	collisionManager* _collisionManager;
	uiController* _ui;
	enemyManager* _enemyManager;
	
public:
	bool _test;
	bool _test2;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

