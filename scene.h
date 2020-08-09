#pragma once
#include "gameNode.h"
#include "tile.h"

class scene : public gameNode
{
public:
	typedef vector<tile*>						vTileOneLine;
	typedef vector<tile*>::iterator				viTileOneLine;
	typedef vector<vector<tile*>>				vTiles;
	typedef vector<vector<tile*>>::iterator		viTiles;
protected:
	// �ش� �� Ÿ�� ���� ����
	vTiles _vTiles;
	viTiles _viTiles;

	int _maxX;
	int _maxY;

	// ĳ���� �̵� ��ġ ���� ����
	floatPoint _previous;
	floatPoint _next;

public:
	virtual ~scene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getDataFromFile(string fileName);
	void getTilesFromFile(string fileName);
	void getEnemiesFromFile(string fileName);

	vTiles& getTiles() { return _vTiles; }
};

