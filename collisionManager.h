#pragma once
#include "gameNode.h"
#include "player.h"

class collisionManager : public gameNode
{
private:
	player* _player;

	int _count;//에너미공격과 플레이어 렉트, 플레이어 공격과 에너미 렉트가 충돌했을때 에너미의 공격상태값을 변경하기전에 줄 딜레이값
	int _collisionCount;//에너미가 충돌당했을때 다음에 다시 충돌판정을 처리할때까지의 딜레이 카운트
	int _playerCollisionCount;//플레이어가 충돌당했을때 다음에 다시 충돌판정을 처리할때까지의 딜레이 카운트
	int interW, interH;

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

	void playerHitCollision();

	void enemyCollision();
	void bulletCollision();

};

