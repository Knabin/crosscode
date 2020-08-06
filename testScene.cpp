#include "stdafx.h"
#include "testScene.h"

testScene::~testScene()
{
}

HRESULT testScene::init()
{
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::Player, "player"));
	OBJECTMANAGER->findObject(objectType::Player, "player")->setIsActive(true);

	IMAGEMANAGER->addFrameImage("terrain b", "images/tiletestbig.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));

	this->getTilesFromFile("111.map");

	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
}

void testScene::render()
{
	for (int i = 0; i <= _maxY; ++i)
	{
		for (int j = 0; j <= _maxX; ++j)
		{
			IMAGEMANAGER->findImage("terrain b")->frameRender(getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
		}
	}
}
