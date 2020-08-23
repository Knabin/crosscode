#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	///////////////소모템///////////////
	itemSet(L"소모", 0, L"체력포션", 500, 50);
	///////////////팔장비///////////////
	itemSet(L"팔", 0, L"기본칼",300, 0, 5);
	itemSet(L"팔", 1, L"빔소드", 1300, 0, 15,10);
	//////////////머리장비//////////////
	itemSet(L"머리", 0, L"기본투구",300, 0,0,5);
	itemSet(L"머리", 1, L"고성능 헤드셋", 1000, 10, 0, 10,0,0,10);
	//////////////다리장비//////////////
	itemSet(L"다리", 0, L"기본신발",300, 0,0,5);
	itemSet(L"다리", 1, L"불꽃 부츠", 1000, 10, 0, 10,0,10);
	/////////////몸통장비//////////////
	itemSet(L"몸통", 0, L"기본갑옷",300, 0,0,5);
	itemSet(L"몸통", 1, L"본 아머", 1500, 10, 0, 10, 10, 0,0,5,5);
	///////////////////////////////////
	itemSet(L"거래", 0, L"고슴됴치 바늘", 100);
	itemSet(L"거래", 1, L"헤드셋", 100);
	itemSet(L"거래", 2, L"뿔", 100);
	itemSet(L"거래", 3, L"소 뼈", 100);
	itemSet(L"거래", 4, L"두개골", 100);
	itemSet(L"거래", 5, L"가죽", 100);
	///////////////////////////////////
	itemSet(L"중요", 0, L"통행권", 100);
	itemSet(L"중요", 1, L"신분증", 100);
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

void item::itemSet(wstring type, int _itemNum, wstring _itemName, int _price,int _hp,int _atk,int _def ,int _crt,int _fireR,int _iceR ,int _electricR ,int _psycoR)
{
	vItem _vItem;
	mItem _mItem;
	itemObject _item;
	_item.itemNum = _itemNum;
	_item.itemName = _itemName;
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
	
	_mItem.insert(pair<wstring, vItem>(type,_vItem));

	_tItem.push_back(_mItem);
}

itemObject item::getItemInfo(wstring type, int num)
{
	iterTotalItem _tiItem;
	miItem _miItem;
	itemObject result;
	//result.itemNum = -1;
	for (_tiItem = _tItem.begin(); _tiItem != _tItem.end(); ++_tiItem)
	{
		for (_miItem = _tiItem->begin(); _miItem != _tiItem->end(); ++_miItem)
		{
			if (!(_miItem->first == type)) break;
			
			viItem _viItem;
			for (_viItem = _miItem->second.begin(); _viItem != _miItem->second.end(); ++_viItem)
			{
				if ((*_viItem).itemNum != num) continue;
				
				result = *_viItem;
				return result;
			}
		}
	}

	return result;
}
