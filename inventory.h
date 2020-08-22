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

	//����������,�����۹�ȣ,�����̿�
	void getItem(wstring _type, int _itemNum, bool shop = 0);
	void deleteItem(wstring _type, int _itemNum, bool shop = 0);

	inline int getMoney() { return _money; }
	//������ ���� price��ġ�� ���� ���̳ʽ�
	void setMoney(int price) { _money -= price; }

	int getCount(wstring type, int num);

	vector<invenObject> getInven() { return _vInven; }
};

