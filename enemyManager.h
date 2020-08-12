#pragma once
#include "gameNode.h"

class enemyManager : public gameNode
{
private:
	vector<class gameObject*> _vEnemy;
	class player* _player;

public:
	virtual HRESULT init();
	virtual void update();
};

