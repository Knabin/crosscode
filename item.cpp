#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	///////////////소모템///////////////
	itemSet("소모", 0, "체력포션", 50, 50);
	///////////////팔장비///////////////
	itemSet("팔", 0, "기본칼",100, 0, 0,50);
	//////////////머리장비//////////////
	itemSet("머리", 0, "기본투구",100, 0,0,50);
	//////////////다리장비//////////////
	itemSet("다리", 0, "기본신발",100, 0,0,50);
	/////////////몸통장비//////////////
	itemSet("몸통", 0, "기본갑옷",100, 0,0,50);
	///////////////////////////////////

	return S_OK;
}

void item::release()
{
}

void item::update()
{

}

void item::render()
{
}

void item::itemSet(string type, int _itemNum, const char _itemName[100], int _price,int _hp,int _atk,int _def ,int _crt,int _fireR,int _iceR ,int _electricR ,int _psycoR)
{
	vItem _vItem;
	mItem _mItem;
	itemObject _item;
	_item.itemNum = _itemNum;
	_item.itemName[100] = _itemName[100];
	_item.price = _price;
	_item.hp = _hp;
	_item.atk = _atk;
	_item.def = _def;
	_item.crt = _crt;
	_item.fireR = _fireR;
	_item.iceR = _iceR;
	_item.electricR = _electricR;
	_item.psycoR = _psycoR;

	_vItem.push_back(_item);
	
	_mItem.insert(pair<string, vItem>(type,_vItem));

	_tItem.push_back(_mItem);
}