#include "stdafx.h"
#include "bossTestScene.h"

bossTestScene::~bossTestScene()
{
}

HRESULT bossTestScene::init()
{
	CAMERA->setCameraMode(CAMERASTATE::TARGET);
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setIsActive(true);

	this->getDataFromFile("bossmap2.map");


	CAMERA->setMapSize(Vector2(_maxX * SIZE, _maxY * SIZE));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(_maxX * SIZE * 0.5f, (float)_maxY * SIZE - 100));

	_boss = new boss;
	_boss->init();
	OBJECTMANAGER->addObject(objectType::BOSS, _boss);

	if (_vTiles.size() != 0)
	{
		for (int i = 0; i <= _maxY; ++i)
		{
			for (int j = 0; j <= _maxX; ++j)
			{
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
	}

	// ������ tile �ܰ��� �׸�
	//for (int i = 0; i <= _maxY; ++i)
	//	drawLine(SCENEMANAGER->getTileBuffer()->getMemDC(), 0, i * SIZE, _maxX * SIZE, i * SIZE);
	//for (int i = 0; i <= _maxX; ++i)
	//	drawLine(SCENEMANAGER->getTileBuffer()->getMemDC(), i * SIZE, 0, i * SIZE, _maxY * SIZE);

	return S_OK;
}

void bossTestScene::release()
{
}

void bossTestScene::update()
{
}

void bossTestScene::render()
{
	scene::render();
}
