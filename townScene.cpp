#include "stdafx.h"
#include "townScene.h"

townScene::~townScene()
{
}

HRESULT townScene::init()
{
	CAMERA->setCameraMode(CAMERASTATE::NONE);
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setIsActive(true);

	this->getDataFromFile("townmap.map");


	CAMERA->setMapSize(Vector2(_maxX * SIZE, _maxY * SIZE));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(35 * SIZE, (_maxY - 1) * SIZE));

	if (_vTiles.size() != 0)
	{
		for (int i = 0; i <= _maxY; ++i)
		{
			for (int j = 0; j <= _maxX; ++j)
			{
				// 해당 타일에 오브젝트가 존재하는 경우, object manager에 추가해서 위에 오브젝트만 렌더 한 번 더 하게끔!
				// object manager에서 플레이어보다 뒤에 있어야 하는 경우에만 렌더 처리하면 될 것 같아요
				if (_vTiles[i][j]->getObjectX() != -1 && _vTiles[i][j]->getObjectImageNum() < 3 && _vTiles[i][j]->getOrderIndex() == 4)
				{
					OBJECTMANAGER->addObject(objectType::TILEOBJECT, _vTiles[i][j]);
					if (i + 1 > _maxY) continue;
					OBJECTMANAGER->addObject(objectType::MAPOBJECT, _vTiles[i + 1][j]);
					//SCENEMANAGER->getObjectImage(_vTiles[i][j]->getObjectImageNum())->frameRender(Vector2(_vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top), _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
				}
			}
		}
	}

	return S_OK;
}

void townScene::release()
{
}

void townScene::update()
{
}

void townScene::render()
{
	scene::render();
}
