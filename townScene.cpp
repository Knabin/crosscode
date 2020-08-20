#include "stdafx.h"
#include "townScene.h"
#include "iEvent.h"
#include "dialog.h"
#include "door.h"

townScene::~townScene()
{
}

HRESULT townScene::init()
{
	CAMERA->setCameraMode(CAMERASTATE::NONE);
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setIsActive(true);

	this->getDataFromFile("townmap2.map");


	CAMERA->setMapSize(Vector2(_maxX * SIZE, _maxY * SIZE));

	if (_vTiles.size() != 0)
	{
		for (int i = 0; i <= _maxY; ++i)
		{
			for (int j = 0; j <= _maxX; ++j)
			{
				// �ش� Ÿ�Ͽ� ������Ʈ�� �����ϴ� ���, object manager�� �߰��ؼ� ���� ������Ʈ�� ���� �� �� �� �ϰԲ�!
				// object manager���� �÷��̾�� �ڿ� �־�� �ϴ� ��쿡�� ���� ó���ϸ� �� �� ���ƿ�
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

	_prevScene = "puzzle";
	_prevPoint = Vector2(1750, 170);

	_nextScene = "mountain";
	_nextPoint = Vector2(50, 1700);

	iPlayerMove* moveEvent = new iPlayerMove(Vector2(36 * SIZE, 47 * SIZE - 400));
	iDialog* dialogEvent = new iDialog(new dialog("1"));
	EVENTMANAGER->addEvent(moveEvent);
	EVENTMANAGER->addEvent(dialogEvent);

	return S_OK;
}

void townScene::release()
{
}

void townScene::update()
{
	if (getDistance(_prevPoint.x, _prevPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 80)
	{
		SCENEMANAGER->loadScene(_prevScene);
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(9 * SIZE, 33 * SIZE));
	}
	else if (getDistance(_prevPoint.x, _prevPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 200)
	{
		dynamic_cast<door*>(OBJECTMANAGER->findObject(objectType::MAPOBJECT, "door"))->setIsOpen(true);
	}
	else
		dynamic_cast<door*>(OBJECTMANAGER->findObject(objectType::MAPOBJECT, "door"))->setIsOpen(false);

	if (getDistance(_nextPoint.x, _nextPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 80)
	{
		SCENEMANAGER->loadScene(_nextScene);
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2((float)76 * SIZE, 34.5f * SIZE));
	}
}

void townScene::render()
{
	scene::render();
	D2DRENDERER->DrawEllipse(CAMERA->getRelativeVector2(_prevPoint), 10);
	D2DRENDERER->DrawEllipse(CAMERA->getRelativeVector2(_nextPoint), 10);
}
