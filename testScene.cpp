#include "stdafx.h"
#include "testScene.h"

testScene::~testScene()
{
}

HRESULT testScene::init()
{
	CAMERA->setCameraMode(CAMERASTATE::TARGET);
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setIsActive(true);

	IMAGEMANAGER->addFrameImage("object b", "images/tile/tile_object_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));

	this->getDataFromFile("1.map");
	
	CAMERA->setMapSize(_maxX * SIZE, _maxY * SIZE);

	if (_vTiles.size() != 0)
	{
		for (int i = 0; i <= _maxY; ++i)
		{
			for (int j = 0; j <= _maxX; ++j)
			{
				SCENEMANAGER->getTileImage(_vTiles[i][j]->getTerrainImageNum())->frameRender(SCENEMANAGER->getTileBuffer()->getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
				// 해당 타일에 오브젝트가 존재하는 경우, object manager에 추가해서 위에 오브젝트만 렌더 한 번 더 하게끔!
				// object manager에서 플레이어보다 뒤에 있어야 하는 경우에만 렌더 처리하면 될 것 같아요
				if (_vTiles[i][j]->getObjectX() != -1 && _vTiles[i][j]->getObjectImageNum() < 3)
				{
					_vTiles[i][j]->setIsActive(true);
					OBJECTMANAGER->addObject(objectType::TILEOBJECT, _vTiles[i][j]);
					SCENEMANAGER->getObjectImage(_vTiles[i][j]->getObjectImageNum())->frameRender(SCENEMANAGER->getTileBuffer()->getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
				}
			}
		}
	}

	// 디버깅용 tile 외곽선 그림
	for(int i = 0; i <= _maxY; ++i)
		drawLine(SCENEMANAGER->getTileBuffer()->getMemDC(), 0, i * SIZE, _maxX * SIZE, i * SIZE);
	for (int i = 0; i <= _maxX; ++i)
		drawLine(SCENEMANAGER->getTileBuffer()->getMemDC(), i * SIZE, 0, i * SIZE, _maxY * SIZE);

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
	// 타일 이미지를 렌더해 줌, 전체 렌더해도 프레임 안 떨어지더라구요
	SCENEMANAGER->getTileBuffer()->render(getMemDC());
}
