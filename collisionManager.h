#pragma once
#include "gameNode.h"
#include "player.h"

class collisionManager : public gameNode
{
private:
	player* _player;

	int _count;//에너미공격과 플레이어 렉트가 충돌했을때 에너미의 공격상태값을 변경하기전에 줄 딜레이값

	bool _pushOut;

public:
	collisionManager() {};
	~collisionManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void buffaloCollision();
	void hedgehagCollision();
	void meerkatCollision();

	void enemyCollision();
	void bulletCollision();
};

