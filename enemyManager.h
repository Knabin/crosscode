#pragma once
#include "gameNode.h"
#include "aStar.h"
#include "scene.h"

class enemyManager : public gameNode
{
private:
	vector<class gameObject*> _vEnemy;

	scene* _sc;
	aStar* _as;

	class player* _player;

	int _time;
	int _index;

	class inventory* _inven;
	

	int _count;//���ʹ� ����� ��Ʈ �ִϸ��̼��� �����ϰ� ���ʹ̸� ���Ϳ��� �����ϴµ� �����̸� �ֱ����� �ʿ��� ����
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();

	void enemyDead();//���ʹ� ���

	void setInventory(class inventory* inven) { _inven = inven; }
};

