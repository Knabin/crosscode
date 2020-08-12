#pragma once
#include "gameNode.h"
#include "hedgehag.h"
#include "aStar.h"
#include <vector>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

class enemyManager : public gameNode
{
private:
	aStar* _as;

	int _count;

private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void enemyDead();

};

