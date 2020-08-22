#pragma once
#include "gameObject.h"
#include "tabUI.h"

class loadUI : public gameObject
{
private:
	tabUI* _tab;
	class player* _player;
	class inventory* _inv;

	floatRect _exit;
	tagSlot _slot[5];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setTabUI(class tabUI* t) { _tab = t; }
	void setInventory(class inventory* i) { _inv = i; }

	void loadData();
	void load(int num);
};

