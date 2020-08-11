#pragma once
#include "gameNode.h"
#include "player.h"
#include "collisionManager.h"
#include "uiController.h"
//#include "aStar.h"
#include "enemy.h"

class playGround : public gameNode
{
private:
	player* _player;
	collisionManager* _collisionManager;
	//aStar* _as;
	uiController* _ui;
	//int _time;
	
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

