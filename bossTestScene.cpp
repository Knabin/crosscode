#include "stdafx.h"
#include "bossTestScene.h"
#include "bossBlock.h"
#include "iEvent.h"
#include "dialog.h"

bossTestScene::~bossTestScene()
{
}

HRESULT bossTestScene::init()
{
	IMAGEMANAGER->addImage("bossHpbar", L"images/boss/bossHpbar.png");

	CAMERA->setCameraMode(CAMERASTATE::NONE);
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
	}

	bossBlock* block = new bossBlock();
	block->setPosition(Vector2(1080, 1910));
	block->init();
	block->setIsActive(false);

	_cameraTarget = new gameObject();
	_cameraTarget->setName("target");

	OBJECTMANAGER->addObject(objectType::MAPOBJECT, block);
	OBJECTMANAGER->addObject(objectType::MAPOBJECT, _cameraTarget);

	_hpBar = new bossHPBar();
	_hpBar->setMaxHP(1665);
	_hpBar->setHP(1665);
	_hpBar->init();
	_hpBar->setIsActive(false);
	OBJECTMANAGER->addObject(objectType::UI, _hpBar);

	
	SOUNDMANAGER->stopAll("bgm boss");
	if (!SOUNDMANAGER->isPlaySound("bgm boss"))
		SOUNDMANAGER->play("bgm boss", 0.3f);
	

	// 보스방 이벤트
	// 주석 풀면 이벤트 나와요 카메라 움직임도 조금 자연스러워짐~
	
	EVENTMANAGER->addEvent(new iPlayerTurn(0));
	EVENTMANAGER->addEvent(new iPlayerMove(Vector2(1070, 1350)));
	EVENTMANAGER->addEvent(new iDialog(new dialog("4")));
	EVENTMANAGER->addEvent(new iObjectActive(block, 1.0f));
	EVENTMANAGER->addEvent(new iPlayerTurn(4));
	EVENTMANAGER->addEvent(new iCameraMove(block, 3.0f));
	EVENTMANAGER->addEvent(new iDialog(new dialog("5")));
	EVENTMANAGER->addEvent(new iShake(5.f, 1.f));
	EVENTMANAGER->addEvent(new iShake(0.f, 2.f));
	EVENTMANAGER->addEvent(new iShake(10.f, 1.f));
	EVENTMANAGER->addEvent(new iShake(0.f, 2.f));
	
	return S_OK;
}

void bossTestScene::release()
{
}

void bossTestScene::update()
{
	_hp = (float)_boss->getBossHp() / (float)_boss->getBossMaxHp() * 1665;

	_hpBar->setHP(_hp);

	if (!EVENTMANAGER->isPlayingEvent() && !EVENTMANAGER->getBossFirstEvent())
	{
		EVENTMANAGER->setBossFirstEvent(true);
		EVENTMANAGER->addEvent(new iCameraMove(_boss, 5.0f));
		
		EVENTMANAGER->addEvent(new iDialog(new dialog("6")));
	}
	if (!EVENTMANAGER->isPlayingEvent() && !EVENTMANAGER->getBossSecondEvent())
	{
		EVENTMANAGER->setBossSecondEvent(true);
		CAMERA->setCameraMode(CAMERASTATE::TARGET);
		_hpBar->setIsActive(true);
	}

	_cameraTarget->setPosition(OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition() - Vector2(0, 300));
}

void bossTestScene::render()
{
	scene::render();
}
