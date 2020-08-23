#include "stdafx.h"
#include "mountainScene.h"
#include "iEvent.h"

mountainScene::~mountainScene()
{
}

HRESULT mountainScene::init()
{
	CAMERA->setCameraMode(CAMERASTATE::NONE);
	//CAMERA->setCameraMode(CAMERASTATE::TARGET);
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setIsActive(true);

	this->getDataFromFile("mountainmap2.map");

	CAMERA->setMapSize(Vector2(_maxX * SIZE, _maxY * SIZE));

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
					OBJECTMANAGER->addObject(objectType::TILEOBJECT, _vTiles[i + 1][j]);
					//SCENEMANAGER->getObjectImage(_vTiles[i][j]->getObjectImageNum())->frameRender(Vector2(_vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top), _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
				}
			}
		}
	}

	_prevScene = "town";
	_prevPoint = Vector2((_maxX - 1) * SIZE, 1650);

	_nextScene = "boss";
	_nextPoint = Vector2(450, 1100);

	SOUNDMANAGER->stopAll("bgm town");
	if (!SOUNDMANAGER->isPlaySound("bgm town"))
		SOUNDMANAGER->play("bgm town", 0.3f);

	return S_OK;
}

void mountainScene::release()
{
}

void mountainScene::update()
{
	if (getDistance(_prevPoint.x, _prevPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 80)
	{
		if (!EVENTMANAGER->isPlayingEvent())
		{
			iMoveScene* m = new iMoveScene(L"town", Vector2(200, 1700));
			EVENTMANAGER->addEvent(m);
		}
	}

	if (getDistance(_nextPoint.x, _nextPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 80)
	{
		if (!EVENTMANAGER->isPlayingEvent())
		{
			iMoveScene* m = new iMoveScene(L"boss", Vector2(1070, 1850));
			EVENTMANAGER->addEvent(m);
		}
	}
}

void mountainScene::render()
{
	scene::render();
	//D2DRENDERER->DrawEllipse(CAMERA->getRelativeVector2(_prevPoint), 10);
	//D2DRENDERER->DrawEllipse(CAMERA->getRelativeVector2(_nextPoint), 10);
}
