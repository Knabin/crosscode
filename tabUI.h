#pragma once
#include "gameNode.h"
#include "button.h"

#include "item.h"

class tabUI : public gameNode
{
private:
	class player* _player;
	class inventory* _inven;

	int _hp;
	int _exp;

	floatRect _hpRC;
	floatRect _expRC;

	int _money;

	bool _on;	//∏ﬁ¥∫ ≈∞∞Ì ≤Ù±‚
	bool _eq;	//¿Â∫Ò
	bool _iv;	//¿Œ∫•
	bool _sv;	//ºº¿Ã∫Í
	bool _st;	//Ω∫≈»
	bool _eqSelect;
	int _invenIndex;
	LPBYTE StateArray;
	
	item* _item;

	int _equipList;
	int _eqSelectNum;
	//[1]∏”∏Æ,[2]∆»1,[3]∆»3,[4]∏ˆ≈Î,[5]¥Ÿ∏Æ, πÃ¬¯øÎΩ√ 99999
	int _equip[5];

	vector<int> _equipItemNum;

	int _time;
	int _timeCount;

	vector<struct invenObject> _vIv;

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

	void setInventory(class inventory* inven) { _inven = inven; }
};

