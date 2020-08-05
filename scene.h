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
private:
	vTiles _vTile;
	viTiles _viTile;
	floatPoint _previous;
	floatPoint _next;

public:
	virtual ~scene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

