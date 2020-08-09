#include "stdafx.h"
#include "testScene.h"

testScene::~testScene()
{
}

HRESULT testScene::init()
{
	CAMERA->setCameraMode(CAMERASTATE::TARGET);
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::Player, "player"));
	OBJECTMANAGER->findObject(objectType::Player, "player")->setIsActive(true);

	IMAGEMANAGER->addFrameImage("object b", "images/tile_object_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));

	this->getDataFromFile("1.map");

	CAMERA->setMapSize(_maxX * SIZE, _maxY * SIZE);

	for (int i = 0; i <= _maxY; ++i)
	{
		for (int j = 0; j <= _maxX; ++j)
		{
			// �׽�Ʈ������ �̹��� �ٷ� �ҷ��ͼ� ����ϴ�~ ���������δ� ���� Ÿ���� �� ��° �̹��������� ������ �ֱ� ������ �ش� �̹����� �����ؾ� ��
			SCENEMANAGER->getTileImage(_vTiles[i][j]->getPageNum())->frameRender(SCENEMANAGER->getTileBuffer()->getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
			// �ش� Ÿ�Ͽ� ������Ʈ�� �����ϴ� ���, object manager�� �߰��ؼ� ���� ������Ʈ�� ���� �� �� �� �ϰԲ�!
			// object manager���� �÷��̾�� �ڿ� �־�� �ϴ� ��쿡�� ���� ó���ϸ� �� �� ���ƿ�
			if (_vTiles[i][j]->getObjectX() != -1)
			{
				_vTiles[i][j]->setIsActive(true);
				OBJECTMANAGER->addObject(objectType::MapObject, _vTiles[i][j]);
				IMAGEMANAGER->findImage("object b")->frameRender(SCENEMANAGER->getTileBuffer()->getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
			}
		}
	}

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
	// Ÿ�� �̹����� ������ ��, ��ü �����ص� ������ �� ���������󱸿�
	SCENEMANAGER->getTileBuffer()->render(getMemDC());
}
