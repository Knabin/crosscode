#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_money = 0;
	
	getItem(L"��", 0);
	getItem(L"��", 1);
	getItem(L"��", 2);
	getItem(L"��", 3);
	getItem(L"��", 4);
	getItem(L"��", 4);
	getItem(L"��", 5);

	getItem(L"�Ҹ�", 0);

	getItem(L"�߿�", 0);
	getItem(L"�Ӹ�", 0);
	getItem(L"�ٸ�", 0);
	getItem(L"����", 0); getItem(L"����", 1);
	getItem(L"�ŷ�", 0);
	getItem(L"�ŷ�", 0);
	getItem(L"�ŷ�", 1);
	getItem(L"�ŷ�", 2);
	getItem(L"�ŷ�", 3);

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
				//����
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
				//����
			}*/
			if (_vInven[i].count == 0)
			{
				_vInven.erase(_vInven.begin() + i);
			}
			return;
		}
	}
}