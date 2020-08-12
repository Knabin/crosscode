#include "stdafx.h"
#include "tile.h"

tile::tile()
	: _terrainX(-1), _terrainY(-1), _objectX(-1), _objectY(-1), _order(ORDER::ONE)
{
}

void tile::setTiles(int terX, int terY, int objX, int objY, int order)
{
	_terrainX = terX;
	_terrainY = terY;
	_objectX = objX;
	_objectY = objY;
	_order = (ORDER)order;
}

void tile::setTiles(int terX, int terY, int objX, int objY, int pageNum, int order)
{
	_terrainX = terX;
	_terrainY = terY;
	_objectX = objX;
	_objectY = objY;
	_terrainImageNum = pageNum;
	_order = (ORDER)order;
}

void tile::render()
{
	SCENEMANAGER->getObjectImage(_objectImageNum)->frameRender(getMemDC(), _rc.left, _rc.top, _objectX, _objectY);
}
