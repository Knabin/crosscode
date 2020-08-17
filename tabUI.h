#pragma once
#include "gameNode.h"
#include "button.h"

class tabUI : public gameNode
{
private:
	class player* _player;
	int _hp;
	int _exp;

	floatRect _hpRC;
	floatRect _expRC;

	bool _on;	//메뉴 키고 끄기
	bool _eq;	//장비
	bool _iv;	//인벤
	bool _sv;	//세이브
	bool _st;	//스탯
	int _invenIndex;
	LPBYTE StateArray;
public:
	tabUI() {};
	~tabUI() {};

	bool getOn() { return _on; }

	HRESULT init();
	void release();
	void update();
	void render();
	void inEquip();
	void inInven();
	void inSave();
	void inStat();
	void outMenu();
	void InventoryList();
};

