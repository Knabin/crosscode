#include "stdafx.h"
#include "playGround.h"
#include "titleScene.h"
#include "mapToolScene.h"
#include "testScene.h"
#include "testScene2.h"
#include "bossTestScene.h"
#include "puzzleScene.h"
#include "mountainScene.h"
#include "townScene.h"


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

	SCENEMANAGER->addScene("title", new titleScene());			// Ÿ��Ʋ ��
	SCENEMANAGER->addScene("maptool", new mapToolScene());		// ���� ��
	SCENEMANAGER->addScene("test", new testScene());			// �׽�Ʈ��(�� ���� ��ư)
	SCENEMANAGER->addScene("test2", new testScene2());			// �׽�Ʈ��(���� �ҷ����� ��ư)
	SCENEMANAGER->addScene("boss", new bossTestScene());		// �׽�Ʈ��(�ɼ� ��ư)
	SCENEMANAGER->addScene("puzzle", new puzzleScene());
	SCENEMANAGER->addScene("mountain", new mountainScene());
	SCENEMANAGER->addScene("town", new townScene());
	SCENEMANAGER->loadScene("title");


	// ============== ����Ʈ �ִ� ��! =================
	// ����Ʈ ���: VK_F8 �� Ȯ��
	IMAGEMANAGER->addFrameImage("test", L"images/test.png", 4, 2);
	// addEffect(����Ʈ �̸�, �̹��� �̸�, fps, elapsedTime, ����(���� �� ���ÿ� �� �Ÿ� ������ ���), ũ��(scale))
	EFFECTMANAGER->addEffect("test", "test", 1, 1.0f, 5, 5.0f);

	//IMAGEMANAGER->addImage(cursor)

	_enemyManager = new enemyManager;
	_enemyManager->init();

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
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->loadScene("puzzle");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->loadScene("mountain");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		SCENEMANAGER->loadScene("town");
		/*
		_test += 30.f;
		// ============== ����Ʈ ȸ���ؼ� ����ϴ� ��! =================
		// play(����Ʈ �̸�, ��ġ, ��ġ, �ޱ۰�)
		//EFFECTMANAGER->play("test", 200, 200, _test);
		EFFECTMANAGER->play("test", Vector2(200, 200), 180, 0.3f);
		*/
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
	if (!EVENTMANAGER->isPlayingEvent() && !_ui->isUIOn())
	{
		SCENEMANAGER->update();
		OBJECTMANAGER->update();
		_collisionManager->update();
		_enemyManager->update();
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
		OBJECTMANAGER->render();
		TIMEMANAGER->render();
		_ui->render();
		EFFECTMANAGER->render();
		//_enemyManager->render();

		if (EVENTMANAGER->isPlayingEvent() || _ui->isUIOn())
		{
		//	render
		}

		//=============================================
	}
	D2DRENDERER->EndRender();
}
