#pragma once
#include "gameNode.h"
#include "nomalUI.h"
#include "tabUI.h"
#include "shop.h"
#include "inventory.h"
// ui Controller������ ȭ�� �ֻ����� ǥ�õǾ�� �� UI type�� gameObject���� �޾ƿ� �����մϴ�.

class uiController : public gameNode
{
private:
	vector<class gameObject*> _vUiObjects;

	vector<class gameObject*> _vVendor; 

	wstring scene;
	nomalUI* _nm;
	tabUI* _tu;
	shop* _shop;
	inventory* _inven;

	bool _uiOn;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	bool isUIOn() { return _tu->getOn(); }
	bool UIon() { return _uiOn; }

	class inventory* getInven() { return _inven; }
};

