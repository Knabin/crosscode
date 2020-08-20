#include "stdafx.h"
#include "tile.h"
#include "player.h"

tile::tile()
	: _terrainX(-1), _terrainY(-1), _objectX(-1), _objectY(-1), _order(ORDER::ONE), _terrainType(NONE)
{
}

void tile::setTiles(int terX, int terY, int objX, int objY, int order)
{
	_terrainX = terX;
	_terrainY = terY;
	_objectX = objX;
	_objectY = objY;
	_order = (ORDER)order;
	checkTerrainType();
}

void tile::setTiles(int terX, int terY, int objX, int objY, int pageNum, int objPagenum, int order)
{
	_terrainX = terX;
	_terrainY = terY;
	_objectX = objX;
	_objectY = objY;
	_terrainImageNum = pageNum;
	_objectImageNum = objPagenum;
	_order = (ORDER)order;
	checkTerrainType();
}

void tile::render()
{
	player* p = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	if (_order == ORDER::BORDER && p->getNowOrder() != 3)
	{
		SCENEMANAGER->getObjectImage(_objectImageNum)->setSize(Vector2(48, 48) * CAMERA->getZoomAmount());
		SCENEMANAGER->getObjectImage(_objectImageNum)->frameRender(
			CAMERA->getRelativeVector2(_rc.getCenter()), _objectX, _objectY);
	}
	else
	{
		SCENEMANAGER->getTileImage(_terrainImageNum)->setSize(Vector2(48, 48) * CAMERA->getZoomAmount());
		SCENEMANAGER->getTileImage(_terrainImageNum)->frameRender(
			CAMERA->getRelativeVector2(_rc.getCenter()), _terrainX, _terrainY);

		if (_objectX == -1 || _objectImageNum == 3) return;
		SCENEMANAGER->getObjectImage(_objectImageNum)->setSize(Vector2(48, 48) * CAMERA->getZoomAmount());
		SCENEMANAGER->getObjectImage(_objectImageNum)->frameRender(
			CAMERA->getRelativeVector2(_rc.getCenter()), _objectX, _objectY);
	}
}
