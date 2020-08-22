#pragma once
#include "gameObject.h"
#include "item.h"

struct invenObject
{
	wstring type;
	int itemNum;
	int count;
	
	invenObject()
	{}

	invenObject(wstring ptype, int pitemNum, int pcount)
		: type(ptype), itemNum(pitemNum), count(pcount)
	{}
};

class inventory: public gameObject
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
	void getItem(wstring _type, int _itemNum, int count = 1, bool shop = 0);
	void deleteItem(wstring _type, int _itemNum, int count = 1, bool shop = 0);

	inline int getMoney() { return _money; }
	//������ ����(�ε��)
	void setInvenMoney(int price) { _money = price; }
	//������ ���� price��ġ�� ���� ���̳ʽ�
	void setMoney(int price) { _money -= price; }

	int getCount(wstring type, int num);

	vector<invenObject> getInven() { return _vInven; }
};

