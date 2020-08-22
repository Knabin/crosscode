#pragma once
#include "gameNode.h"
#include "item.h"

class shop : public gameNode
{
private:
	bool _shopOn;
	int _type;

	class inventory* _inven;

	item* _it;

	wstring _itemName1;
	wstring _itemName2;
	wstring _itemName3;

	wstring _itemNum1;
	wstring _itemNum1M;
	
	wstring _itemNum2;
	wstring _itemNum2M;
	
	wstring _itemNum3;
	wstring _itemNum3M;
	
	wstring _itemType[3];
	int _itemNum[3];

public:
	shop() {};
	~shop() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void shopOn(int type);
	
	void setShopOn(bool b) { _shopOn = b; }
	wstring getItemType(int i) { return _itemType[i]; }
	inline int getItemNum(int i) { return _itemNum[i]; }

	void setItemCount(int i, wstring count);
	void setInventory(class inventory* inven) { _inven = inven; }
};

