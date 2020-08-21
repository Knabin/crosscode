#pragma once
#include "gameNode.h"

class nomalUI : public gameNode
{
private:
	class player* _player;
	int _hp;
	int _exp;

	floatRect _hpRC;
	floatRect _expRC;

	int _lvUPCount;
	

	bool _lvUP;
	animation* _lvAnim;
public:
	nomalUI() {};
	~nomalUI() {};


	HRESULT init();
	void release();
	void update();
	void render();
};

