#pragma once
#include "gameNode.h"
#include "player.h"

class collisionManager : public gameNode
{
private:
	player* _player;

	int _count;//���ʹ̰��ݰ� �÷��̾� ��Ʈ, �÷��̾� ���ݰ� ���ʹ� ��Ʈ�� �浹������ ���ʹ��� ���ݻ��°��� �����ϱ����� �� �����̰�
	int _collisionCount;//���ʹ̰� �浹�������� ������ �ٽ� �浹������ ó���Ҷ������� ������ ī��Ʈ
	int _playerCollisionCount;//�÷��̾ �浹�������� ������ �ٽ� �浹������ ó���Ҷ������� ������ ī��Ʈ
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

