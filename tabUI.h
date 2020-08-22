#pragma once
#include "gameNode.h"
#include "button.h"

#include "item.h"

struct tagSlot
{
	bool isSaved;
	string fileName;
	floatRect rc;
	int level;
	int time;
	int credit;
	wstring map;

	tagSlot()
	{
		isSaved = false;
		fileName = "";
		level = 0;
		time = 0;
		credit = 0;
		map = L"";
	}
};

class tabUI : public gameNode
{
private:
	class player* _player;
	class inventory* _inven;

	int _hp;
	int _exp;

	floatRect _hpRC;
	floatRect _expRC;

	bool _on;	//¸Þ´º Å°°í ²ô±â
	bool _eq;	//Àåºñ
	bool _iv;	//ÀÎº¥
	bool _sv;	//¼¼ÀÌºê
	bool _st;	//½ºÅÈ
	bool _eqSelect;
	int _invenIndex;
	LPBYTE StateArray;
	
	item* _item;

	int _equipList;
	int _eqSelectNum;
	//[1]¸Ó¸®,[2]ÆÈ1,[3]ÆÈ3,[4]¸öÅë,[5]´Ù¸®, ¹ÌÂø¿ë½Ã 99999
	int _equip[5];

	vector<int> _equipItemNum;

	int _time;
	int _timeCount;

	vector<struct invenObject> _vIv;

	floatRect _eqRect[5];
	
	// ³ªºó Ãß°¡
	tagSlot _saveSlot[5];
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

	void saveData(int num);
	void loadData();

	void setTime(int time) { _time = time; }
	void setEq(int index, int value) { _equip[index] = value; }

	void setInven(vector<invenObject> inven) { _vIv = inven; }

	void setInventory(class inventory* inven) { _inven = inven; }
};

