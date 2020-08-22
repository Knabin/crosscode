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
	

	int _count;//에너미 사망시 히트 애니메이션을 실행하고 에너미를 벡터에서 삭제하는데 딜레이를 주기위해 필요한 변수
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();

	void enemyDead();//에너미 사망

	void setInventory(class inventory* inven) { _inven = inven; }
};

