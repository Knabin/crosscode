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
			// �ش� Ÿ�Ͽ� ������Ʈ�� �����ϴ� ���, object manager�� �߰��ؼ� ���� ������Ʈ�� ���� �� �� �� �ϰԲ�!
			// object manager���� �÷��̾�� �ڿ� �־�� �ϴ� ��쿡�� ���� ó���ϸ� �� �� ���ƿ�
			if (_vTiles[i][j]->getObjectX() != -1 && _vTiles[i][j]->getObjectImageNum() < 3)
			{
				_vTiles[i][j]->setIsActive(true);
				OBJECTMANAGER->addObject(objectType::TILEOBJECT, _vTiles[i][j]);
				SCENEMANAGER->getObjectImage(_vTiles[i][j]->getObjectImageNum())->frameRender(Vector2(_vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top), _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
			}
		}
	}

	// ������ tile �ܰ��� �׸�
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
