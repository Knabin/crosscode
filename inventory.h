#pragma once
#include "gameNode.h"

struct invenObject
{
	string type;
	int itemNum;
	int count;
};

class inventory: public gameNode
{
private:
	vector<invenObject> _vInven;
	int _money;
public:
	inventory() {};
	~inventory() {};

	HRESULT init();
	void release();
	void update();
	void render();

	//아이템종료,아이템번호,상점이용
	void getItem(string _type, int _itemNum, bool shop);
	void deleteItem(string _type, int _itemNum, bool shop);

	inline int getMoney() { return _money; }
	//소지금 변경 price수치에 따른 마이너스
	void setMoney(int price) { _money -= price; }
};

