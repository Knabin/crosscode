#include "stdafx.h"
#include "testScene2.h"

testScene2::~testScene2()
{
}

HRESULT testScene2::init()
{
	CAMERA->setCameraMode(CAMERASTATE::TARGET);
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setIsActive(true);

	this->getDataFromFile("22.map");

	CAMERA->setMapSize(Vector2(_maxX * SIZE, _maxY * SIZE));

	for (int i = 0; i <= _maxY; ++i)
	{
		for (int j = 0; j <= _maxX; ++j)
		{
			SCENEMANAGER->getTileImage(_vTiles[i][j]->getTerrainImageNum())->frameRender(Vector2(_vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top), _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
			// 해당 타일에 오브젝트가 존재하는 경우, object manager에 추가해서 위에 오브젝트만 렌더 한 번 더 하게끔!
			// object manager에서 플레이어보다 뒤에 있어야 하는 경우에만 렌더 처리하면 될 것 같아요
			if (_vTiles[i][j]->getObjectX() != -1 && _vTiles[i][j]->getObjectImageNum() < 3)
			{
				_vTiles[i][j]->setIsActive(true);
				OBJECTMANAGER->addObject(objectType::TILEOBJECT, _vTiles[i][j]);
				SCENEMANAGER->getObjectImage(_vTiles[i][j]->getObjectImageNum())->frameRender(Vector2(_vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top), _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
			}
		}
	}

	// 디버깅용 tile 외곽선 그림
	/*for (int i = 0; i <= _maxY; ++i)
		drawLine(SCENEMANAGER->getTileBuffer()->getMemDC(), 0, i * SIZE, _maxX * SIZE, i * SIZE);
	for (int i = 0; i <= _maxX; ++i)
		drawLine(SCENEMANAGER->getTileBuffer()->getMemDC(), i * SIZE, 0, i * SIZE, _maxY * SIZE);
*/
	return S_OK;
}

void testScene2::release()
{
}

void testScene2::update()
{

}

void testScene2::render()
{
	scene::render();
}
