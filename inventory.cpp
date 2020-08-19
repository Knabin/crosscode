#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_money = 0;

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

void inventory::getItem(string _type, int _itemNum, bool shop)
{
	int maxCount = 0;
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i].type == _type && _vInven[i].itemNum == _itemNum)
		{
			_vInven[i].count++;
			/*if (shop)
			{
				//가격
			}*/
			return;
		}
		maxCount++;
	}
	if (maxCount >= _vInven.size())
	{
		invenObject ob;
		ob.type = _type;
		ob.itemNum = _itemNum;
		ob.count = 1;

		_vInven.push_back(ob);
	}
}

void inventory::deleteItem(string _type, int _itemNum, bool shop)
{
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i].type == _type && _vInven[i].itemNum == _itemNum)
		{
			_vInven[i].count--;
			/*if (shop)
			{
				//가격
			}*/
			if (_vInven[i].count == 0)
			{
				_vInven.erase(_vInven.begin() + i);
			}
			return;
		}
	}
}