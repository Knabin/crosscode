#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_name = "inven";
	_money = 0;
	

	/*getItem(L"거래", 2);
	getItem(L"거래", 2);
	getItem(L"거래", 0);
	getItem(L"거래", 0);
	getItem(L"거래", 0);

	getItem(L"거래", 1);
	getItem(L"거래", 1);
	getItem(L"거래", 5);
	getItem(L"거래", 5);
	getItem(L"거래", 5);
	getItem(L"거래", 5);
	getItem(L"거래", 5);

	getItem(L"거래", 3);
	getItem(L"거래", 4);
	getItem(L"거래", 4);*/


	_it = new item;
	_it->init();

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
}

void inventory::render()
{
}

void inventory::getItem(wstring _type, int _itemNum, int count, bool shop)
{
	int maxCount = 0;
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i].type == _type && _vInven[i].itemNum == _itemNum)
		{
			_vInven[i].count += count;
			
			if (shop)
			{
				_money -= _it->getItemInfo(_type, _itemNum).price;
			}
			return;
		}
		maxCount++;	
	}
	if (maxCount >= _vInven.size())
	{
		invenObject ob;
		ob.type = _type;
		ob.itemNum = _itemNum;
		ob.count = count;

		_vInven.push_back(ob);

		if (shop)
		{
			_money -= _it->getItemInfo(_type, _itemNum).price;
		}
	}

}

void inventory::deleteItem(wstring _type, int _itemNum, int count, bool shop)
{
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i].type == _type && _vInven[i].itemNum == _itemNum)
		{
			_vInven[i].count -= count;
			if (shop)
			{
				_money += _it->getItemInfo(_type, _itemNum).price;
			}
			if (_vInven[i].count == 0)
			{
				_vInven.erase(_vInven.begin() + i);
			}
			return;
		}
	}
}

int inventory::getCount(wstring type, int num)
{
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i].type == type && _vInven[i].itemNum == num)
		{
			return _vInven[i].count;
		}
	}

	return 0;
}
