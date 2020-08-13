#pragma once
#include "gameNode.h"
#include "nomalUI.h"
// ui Controller에서는 화면 최상위에 표시되어야 할 UI type의 gameObject들을 받아와 관리합니다.

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

