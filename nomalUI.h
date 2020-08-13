#pragma once
#include "gameNode.h"

class nomalUI : public gameNode
{
private:
	class player* _player;
	int _hp;


public:
	nomalUI() {};
	~nomalUI() {};


	HRESULT init();
	void release();
	void update();
	void render();
};

