#pragma once
#include "gameNode.h"
#include "nomalUI.h"
#include "tabUI.h"
// ui Controller������ ȭ�� �ֻ����� ǥ�õǾ�� �� UI type�� gameObject���� �޾ƿ� �����մϴ�.

class uiController : public gameNode
{
private:
	vector<class gameObject*> _vUiObjects;
	string scene;
	nomalUI* _nm;
	tabUI* _tu;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	bool isUIOn() { return _tu->getOn(); }
};

