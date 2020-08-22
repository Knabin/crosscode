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

	_prevScene = "puzzle";
	_prevPoint = Vector2(1750, 170);

	_nextScene = "mountain";
	_nextPoint = Vector2(50, 1700);
	
	townBlock* block = new townBlock();
	block->setPosition(Vector2(150, 1650));
	block->init();
	OBJECTMANAGER->addObject(objectType::MAPOBJECT, block);


	// 중복 실행되지 않게
	if (!EVENTMANAGER->getFirstEvent())
	{
		iPlayerMove* moveEvent = new iPlayerMove(Vector2(36 * SIZE, 47 * SIZE - 300));
		iDialog* dialogEvent = new iDialog(new dialog("1"));
		EVENTMANAGER->addEvent(moveEvent);
		EVENTMANAGER->addEvent(dialogEvent);
		EVENTMANAGER->setFirstEvent(true);
	}
	else if (EVENTMANAGER->getPuzzleEvent() && !EVENTMANAGER->getSecondEvent())
	{
		iCameraMove* cameraEvent = new iCameraMove(block, 5.f);
		iDialog* dialogEvent = new iDialog(new dialog("3"));
		EVENTMANAGER->addEvent(cameraEvent);
		EVENTMANAGER->addEvent(dialogEvent);
		EVENTMANAGER->setSecondEvent(true);
	}

	SOUNDMANAGER->stopAll("bgm town");
	if (!SOUNDMANAGER->isPlaySound("bgm town"))
		SOUNDMANAGER->play("bgm town", 0.3f);

	return S_OK;
}

void townScene::release()
{
}

void townScene::update()
{
	if (getDistance(_prevPoint.x, _prevPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 80
		&& !EVENTMANAGER->getPuzzleEvent())
	{
		if (!EVENTMANAGER->isPlayingEvent())
		{
			iMoveScene* m = new iMoveScene(L"puzzle", Vector2(9 * SIZE, 33 * SIZE));
			EVENTMANAGER->addEvent(m);
		}
	}
	else if (getDistance(_prevPoint.x, _prevPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 200 &&
		!EVENTMANAGER->getPuzzleEvent())
	{
		dynamic_cast<door*>(OBJECTMANAGER->findObject(objectType::MAPOBJECT, "door"))->setIsOpen(true);
	}
	else
		dynamic_cast<door*>(OBJECTMANAGER->findObject(objectType::MAPOBJECT, "door"))->setIsOpen(false);

	if (getDistance(_nextPoint.x, _nextPoint.y, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y) <= 80 &&
		EVENTMANAGER->getPuzzleEvent())
	{
		if (!EVENTMANAGER->isPlayingEvent())
		{
			iMoveScene* m = new iMoveScene(L"mountain", Vector2((float)76 * SIZE, 34.5f * SIZE));
			EVENTMANAGER->addEvent(m);
		}
	}
}

void townScene::render()
{
	scene::render();
	D2DRENDERER->DrawEllipse(CAMERA->getRelativeVector2(_prevPoint), 10);
	D2DRENDERER->DrawEllipse(CAMERA->getRelativeVector2(_nextPoint), 10);
}
