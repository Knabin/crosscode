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

	//����������,�����۹�ȣ,�����̿�
	void getItem(string _type, int _itemNum, bool shop);
	void deleteItem(string _type, int _itemNum, bool shop);

	inline int getMoney() { return _money; }
	//������ ���� price��ġ�� ���� ���̳ʽ�
	void setMoney(int price) { _money -= price; }
};

