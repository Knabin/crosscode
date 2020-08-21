#pragma once
#include "gameNode.h"
#include "button.h"
#include "inventory.h"
#include "item.h"

class tabUI : public gameNode
{
private:
	class player* _player;
	int _hp;
	int _exp;

	floatRect _hpRC;
	floatRect _expRC;

	int _money;

	bool _on;	//메뉴 키고 끄기
	bool _eq;	//장비
	bool _iv;	//인벤
	bool _sv;	//세이브
	bool _st;	//스탯
	bool _eqSelect;
	int _invenIndex;
	LPBYTE StateArray;
	
	item* _item;

	int _time;
	int _timeCount;

	vector<invenObject> _vIv;

	floatRect _eqRect[5];
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
	void equipSelect();

	void setInven(vector<invenObject> inven) { _vIv = inven; }

	inline int getMoney() { return _money; }
	void setMoney(int m) { _money = m; }
};

