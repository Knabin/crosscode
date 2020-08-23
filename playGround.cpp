#include "stdafx.h"
#include "playGround.h"

#include "initLoadingScene.h"


playGround::playGround()
{
}



playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	_player = new player();
	_player->init();
	_player->setIsActive(false);
	OBJECTMANAGER->addObject(objectType::PLAYER, _player);

	_collisionManager = new collisionManager;
	_collisionManager->init();

	SCENEMANAGER->addScene(L"loading", new initLoadingScene());
	SCENEMANAGER->loadScene(L"loading");

	_puzzleCollision = new puzzleCollision;
	_puzzleCollision->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_bossCollision = new bossCollision;
	_bossCollision->init();

	_ui = new uiController();
	_ui->init();

	_test = 0.f;

	ShowCursor(false);

	
	return S_OK;
}

//�޸� ����
void playGround::release()
{
	
}

//����
void playGround::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->loadScene(L"title");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->loadScene(L"test");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->loadScene(L"test2");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->loadScene(L"maptool");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->loadScene(L"boss");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->loadScene(L"puzzle");
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(9 * SIZE, 33 * SIZE));
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->loadScene(L"mountain");
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2((float)76 * SIZE, 34.0f * SIZE));
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		SCENEMANAGER->loadScene(L"town");
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(36 * SIZE, 47 * SIZE));
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(Vector2(450, 1400)));
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		CAMERA->shakeStart(3.f, 0.5f);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		CAMERA->zoomStart(1.2f, 5.f, true);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		CAMERA->fadeStart(1.f, 1.5f);
	}


	// �̺�Ʈ ��� ��, UI�� ȭ���� ������ �ִ� ��쿡�� ������Ʈ���� ����
	if (!EVENTMANAGER->isPlayingEvent() && !_ui->isUIOn() && !_ui->UIon())
	{
		_collisionManager->update();
		_enemyManager->update();
		_bossCollision->update();
		_enemyManager->setInventory(_ui->getInven());
	}

	_puzzleCollision->update();
	EVENTMANAGER->update();
	SCENEMANAGER->update();
	if (!_ui->isUIOn() && !_ui->UIon())
	{
		OBJECTMANAGER->update();
	}
	EFFECTMANAGER->update();
	CAMERA->update();
	_ui->update();
}

//�׸��� ����
void playGround::render()
{	
	D2DRENDERER->BeginRender(D2D1::ColorF::Black);
	{

		//=================================================

		SCENEMANAGER->render();
		if (!_ui->isUIOn() && !_ui->UIon())
		EFFECTMANAGER->render();
		OBJECTMANAGER->render();
		TIMEMANAGER->render();
		_collisionManager->render();
		_ui->render();
		//_enemyManager->render();
		if (_ui->isUIOn() || _ui->UIon())
			EFFECTMANAGER->render();
		EFFECTMANAGER->render();

		if (EVENTMANAGER->isPlayingEvent())
		{
			D2DRENDERER->DrawRotationFillRectangle(floatRect(Vector2(0, 0), Vector2(WINSIZEX, 80), pivot::LEFTTOP), D2D1::ColorF::Black, 0);
		}

		// ���¿� ���� ���콺 ���� ó��
		if (EVENTMANAGER->isPlayingEvent() || _ui->isUIOn() || SCENEMANAGER->getCurrentSceneName() == L"title" || SCENEMANAGER->getCurrentSceneName() == L"maptool")
		{
			IMAGEMANAGER->findImage("cursor normal")->render(Vector2(_ptMouse));
		}
		else if (_player->mouseCheck())
		{
			IMAGEMANAGER->findImage("cursor melee")->render(Vector2(_ptMouse));
		}
		else if (_player->isLongAttacking())
		{
			IMAGEMANAGER->findImage("cursor charge")->render(Vector2(_ptMouse));
		}
		else
		{
			IMAGEMANAGER->findImage("cursor throw")->render(Vector2(_ptMouse));
		}

		if (CAMERA->getIsFade())
		{
			IMAGEMANAGER->findImage("black")->setAlpha(CAMERA->getFadeAmount());
			IMAGEMANAGER->findImage("black")->setSize(Vector2(WINSIZEX, WINSIZEY));
			IMAGEMANAGER->findImage("black")->render(Vector2(0, 0));
		}

		//=============================================
	}
	D2DRENDERER->EndRender();
}
