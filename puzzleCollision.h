#pragma once
#include "player.h"

class puzzleCollision
{
private:
	player* _player;

	int _count;

	bool _puzzleTabButtonCollision[6];

public:
	puzzleCollision() {};
	~puzzleCollision() {};

	HRESULT init();
	void release();
	void update();
	void puzzleBlueWallCollision();
	void puzzleOrangeWallCollision();
	void puzzleComboButtonCollision();
	void puzzleTabButtonCollision();
	void puzzleDestructCollision();
};

