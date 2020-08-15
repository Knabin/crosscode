#include "stdafx.h"
#include "playGround.h"
#include "titleScene.h"
#include "mapToolScene.h"
#include "testScene.h"
#include "testScene2.h"
#include "bossTestScene.h"


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



	_ui = new uiController();
	_ui->init();

	SCENEMANAGER->addScene("title", new titleScene());			// Ÿ��Ʋ ��
	SCENEMANAGER->addScene("maptool", new mapToolScene());		// ���� ��
	SCENEMANAGER->addScene("test", new testScene());			// �׽�Ʈ��(�� ���� ��ư)
	SCENEMANAGER->addScene("test2", new testScene2());			// �׽�Ʈ��(���� �ҷ����� ��ư)
	SCENEMANAGER->addScene("boss", new bossTestScene());		// �׽�Ʈ��(�ɼ� ��ư)
	SCENEMANAGER->loadScene("title");

	_enemyManager = new enemyManager;
	_enemyManager->init();

	// Ŀ�� �߰��� ���µ� ��ǥ�� ��߳���... ������ �𸣰���
	//SetCursor(LoadCursorFromFile("cursor/cursor-2.cur"));
	//SetCursor(LoadCursorFromFile("cursor/cursor-melee.cur"));
	SetCursor(LoadCursorFromFile("cursor/cursor-throw.cur"));

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
		SCENEMANAGER->loadScene("title");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->loadScene("test");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->loadScene("test2");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->loadScene("maptool");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->loadScene("boss");
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		CAMERA->shakeStart(3.f, 0.5f);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		CAMERA->zoomStart(1.2f, 5.f, true);
	}

	// �̺�Ʈ ��� �߿��� ������Ʈ���� ����
	// TODO: UI ���� ���� �� ȭ�� ����� �ϹǷ� ���� �߰�
	if (!EVENTMANAGER->isPlayingEvent())
	{
		SCENEMANAGER->update();
		OBJECTMANAGER->update();
		_collisionManager->update();
		_enemyManager->update();
	}

	CAMERA->update();
	_ui->update();
}

//�׸��� ����
void playGround::render()
{	
	D2DRENDERER->BeginRender(D2D1::ColorF::White);
	{

		//=================================================

		SCENEMANAGER->render();
		OBJECTMANAGER->render();
		//CAMERA->zoom(getMemDC());
		TIMEMANAGER->render();
		_ui->render();
		//_enemyManager->render();

		//=============================================
	}
	D2DRENDERER->EndRender();
}
