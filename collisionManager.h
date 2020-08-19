#pragma once
#include "gameNode.h"
#include "player.h"

class collisionManager : public gameNode
{
private:
	player* _player;

	int _count;//���ʹ̰��ݰ� �÷��̾� ��Ʈ�� �浹������ ���ʹ��� ���ݻ��°��� �����ϱ����� �� �����̰�

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

