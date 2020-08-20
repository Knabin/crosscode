#pragma once
#include "gameNode.h"


class shop : public gameNode
{
private:
	bool _shopOn;
	int _type;
public:
	shop() {};
	~shop() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void shopOn(int type);
	
	void setShopOn(bool b) { _shopOn = b; }
};

