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

//초기화 함수
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

	SCENEMANAGER->addScene("title", new titleScene());			// 타이틀 씬
	SCENEMANAGER->addScene("maptool", new mapToolScene());		// 맵툴 씬
	SCENEMANAGER->addScene("test", new testScene());			// 테스트용(새 게임 버튼)
	SCENEMANAGER->addScene("test2", new testScene2());			// 테스트용(게임 불러오기 버튼)
	SCENEMANAGER->addScene("boss", new bossTestScene());		// 테스트용(옵션 버튼)
	SCENEMANAGER->loadScene("title");

	_enemyManager = new enemyManager;
	_enemyManager->init();

	// 커서 추가해 놨는데 좌표가 어긋나요... 이유는 모르겠음
	//SetCursor(LoadCursorFromFile("cursor/cursor-2.cur"));
	//SetCursor(LoadCursorFromFile("cursor/cursor-melee.cur"));
	SetCursor(LoadCursorFromFile("cursor/cursor-throw.cur"));

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
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
		CAMERA->shakeStart(10.f, 1.f);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		CAMERA->zoomStart(3.0f, 5.f);
	}

	// 이벤트 재생 중에는 업데이트하지 않음
	// TODO: UI 켜져 있을 때 화면 멈춰야 하므로 조건 추가
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

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, CAMERA->getMapWidth(), CAMERA->getMapHeight(), WHITENESS);
	//=================================================

	SCENEMANAGER->render();
	OBJECTMANAGER->render();
	CAMERA->zoom(getMemDC());
	TIMEMANAGER->render(getMemDC());
	_ui->render();
	//_enemyManager->render();

	//=============================================
	_backBuffer->render(getHDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top, WINSIZEX, WINSIZEY);
}
