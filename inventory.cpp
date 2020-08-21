#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_money = 0;
	
	getItem(L"ÆÈ", 0);
	getItem(L"ÆÈ", 1);
	getItem(L"ÆÈ", 2);
	getItem(L"ÆÈ", 3);
	getItem(L"ÆÈ", 4);
	getItem(L"ÆÈ", 4);
	getItem(L"ÆÈ", 5);

	getItem(L"¼Ò¸ð", 0);

	getItem(L"Áß¿ä", 0);
	getItem(L"¸Ó¸®", 0);
	getItem(L"´Ù¸®", 0);
	getItem(L"¸öÅë", 0); getItem(L"¸öÅë", 1);
	getItem(L"°Å·¡", 0);
	getItem(L"°Å·¡", 0);
	getItem(L"°Å·¡", 1);
	getItem(L"°Å·¡", 2);
	getItem(L"°Å·¡", 3);

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

void inventory::getItem(wstring _type, int _itemNum, bool shop)
{
	int maxCount = 0;
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i].type == _type && _vInven[i].itemNum == _itemNum)
		{
			_vInven[i].count++;
			/*if (shop)
			{
				//°¡°Ý
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

void inventory::deleteItem(wstring _type, int _itemNum, bool shop)
{
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (_vInven[i].type == _type && _vInven[i].itemNum == _itemNum)
		{
			_vInven[i].count--;
			/*if (shop)
			{
				//°¡°Ý
			}*/
			if (_vInven[i].count == 0)
			{
				_vInven.erase(_vInven.begin() + i);
			}
			return;
		}
	}
}