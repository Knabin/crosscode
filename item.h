#pragma once
#include "gameNode.h"

struct itemObject
{
	int itemNum;
	wstring itemName;
	int price;
	int hp;
	int atk;
	int def;
	int crt;
	int fireR;
	int iceR;
	int electricR;
	int psycoR;
};

class item: public gameNode
{
private:
	typedef vector<itemObject> vItem;
	typedef vector<itemObject>::iterator viItem;

	typedef map<wstring, vItem> mItem;
	typedef map<wstring, vItem>::iterator miItem;

	typedef vector<mItem> totalItem;
	typedef vector<mItem>::iterator iterTotalItem;
public:
	item() {};
	~item() {};

	totalItem _tItem;

	HRESULT init();
	void release();
	void update();
	void render();

	//����������,�����۹�ȣ,�������̸�,����,(ü��,���ݷ�,����,ũ��Ƽ��,�����׷�,�������׷�,�������׷�,���������׷�) == ���Է½� 0
	void itemSet(wstring type, int itemNum, wstring _itemName, int price,int _hp = 0, int _atk = 0, int _def = 0, int _crt = 0, int _fireR = 0, int _iceR = 0, int _electricR = 0, int _psycoR = 0);

	
	itemObject getItemInfo(wstring type, int num);
};

