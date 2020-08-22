#pragma once
#include "player.h"

class puzzleCollision
{
private:
	player* _player;

	int _count;

	bool _puzzleTabButtonCollision[6];//탑버튼이 충돌했으면 프레임을 재생시키기 위한 변수
	bool _puzzleComplete[6];//탑버튼이 충돌하고 프레임이 마지막 프레임까지 재생하고 끝났는지 여부를 알기위한 변수

public:
	puzzleCollision() {};
	~puzzleCollision() {};

	HRESULT init();
	void release();
	void update();
	void puzzleBlueWallCollision();
	void puzzleOrangeWallCollision();
	void puzzleTabButtonCollision();
	void puzzleDestructCollision();
	void puzzleComplete();
};

