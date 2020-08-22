#pragma once
#include "player.h"

class puzzleCollision
{
private:
	player* _player;

	int _count;

	bool _puzzleTabButtonCollision[6];//ž��ư�� �浹������ �������� �����Ű�� ���� ����
	bool _puzzleComplete[6];//ž��ư�� �浹�ϰ� �������� ������ �����ӱ��� ����ϰ� �������� ���θ� �˱����� ����

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

