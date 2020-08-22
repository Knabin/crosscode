#pragma once
#include "gameNode.h"
#include "nomalUI.h"
#include "tabUI.h"
#include "shop.h"
#include "inventory.h"
// ui Controller에서는 화면 최상위에 표시되어야 할 UI type의 gameObject들을 받아와 관리합니다.

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

