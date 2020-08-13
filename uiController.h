#pragma once
#include "gameNode.h"
#include "nomalUI.h"
// ui Controller������ ȭ�� �ֻ����� ǥ�õǾ�� �� UI type�� gameObject���� �޾ƿ� �����մϴ�.

class uiController : public gameNode
{
private:
	vector<class gameObject*> _vUiObjects;
	nomalUI* _nm;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

