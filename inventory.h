#pragma once
#include "gameNode.h"
#include "item.h"

struct invenObject
{
	wstring type;
	int itemNum;
	int count;
};

class inventory: public gameNode
{
private:
	vector<invenObject> _vInven;
	int _money;
	item* _it;
public:
	inventory() {};
	~inventory() {};

	HRESULT init();
	void release();
	void update();
	void render();

	//아이템종료,아이템번호,상점이용
	void getItem(wstring _type, int _itemNum, bool shop = 0);
	void deleteItem(wstring _type, int _itemNum, bool shop = 0);

	inline int getMoney() { return _money; }
	//소지금 변경 price수치에 따른 마이너스
	void setMoney(int price) { _money -= price; }

	int getCount(wstring type, int num);

	vector<invenObject> getInven() { return _vInven; }
};

