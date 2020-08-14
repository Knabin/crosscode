#pragma once
#include "gameNode.h"

class tabUI : public gameNode
{
private:
	class player* _player;
	int _hp;
	int _exp;
	bool _on;  //메뉴 키고 끄기
	LPBYTE StateArray;
public:
	tabUI() {};
	~tabUI() {};


	HRESULT init();
	void release();
	void update();
	void render();
};

