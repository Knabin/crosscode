#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	///////////////�Ҹ���///////////////
	itemSet(L"�Ҹ�", 0, L"ü������", 50, 50);
	itemSet(L"�Ҹ�", 1, L"ü�����Ǵ�", 50, 100);
	///////////////�����///////////////
	itemSet(L"��", 0, L"�⺻Į",100, 0, 50);
	itemSet(L"��", 1, L"�� ���� �⺻Į", 120, 0, 55);
	itemSet(L"��", 2, L"�� �� �⺻Į", 140, 0, 60);
	itemSet(L"��", 3, L"�� Į", 160, 0, 65);
	itemSet(L"��", 4, L"���� �� Į", 180, 0, 70);
	itemSet(L"��", 5, L"���� �� Į", 200, 0, 75);
	//////////////�Ӹ����//////////////
	itemSet(L"�Ӹ�", 0, L"�⺻����",100, 0,0,50);
	itemSet(L"�Ӹ�", 1, L"�� ���� �⺻����", 100, 0, 0, 50);
	//////////////�ٸ����//////////////
	itemSet(L"�ٸ�", 0, L"�⺻�Ź�",100, 0,0,50);
	itemSet(L"�ٸ�", 1, L"�� ���� �⺻�Ź�", 100, 0, 0, 50);
	/////////////�������//////////////
	itemSet(L"����", 0, L"�⺻����",100, 0,0,50);
	itemSet(L"����", 1, L"�� ���� �⺻����", 100, 0, 0, 70, 10, 10);
	///////////////////////////////////
	itemSet(L"�ŷ�", 0, L"����ġ �ٴ�", 100, 0, 0, 50);
	itemSet(L"�ŷ�", 1, L"����", 100, 0, 0, 50);
	itemSet(L"�ŷ�", 2, L"��", 100, 0, 0, 50);
	itemSet(L"�ŷ�", 3, L"����", 100, 0, 0, 50);
	///////////////////////////////////
	itemSet(L"�߿�", 0, L"ī��", 100, 0, 0, 0);
	itemSet(L"�߿�", 1, L"�ź���", 100, 0, 0, 0);
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
