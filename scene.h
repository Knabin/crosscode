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
	vTiles _vTiles;
	viTiles _viTiles;
	floatPoint _previous;
	floatPoint _next;

	int _maxX;
	int _maxY;

public:
	virtual ~scene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getTilesFromFile(string fileName);

	vTiles& getTiles() { return _vTiles; }
};

