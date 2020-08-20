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

	SCENEMANAGER->addScene("title", new titleScene());			// 타이틀 씬
	SCENEMANAGER->addScene("maptool", new mapToolScene());		// 맵툴 씬
	SCENEMANAGER->addScene("test", new testScene());			// 테스트용(새 게임 버튼)
	SCENEMANAGER->addScene("test2", new testScene2());			// 테스트용(게임 불러오기 버튼)
	SCENEMANAGER->addScene("boss", new bossTestScene());		// 테스트용(옵션 버튼)
	SCENEMANAGER->addScene("puzzle", new puzzleScene());
	SCENEMANAGER->addScene("mountain", new mountainScene());
	SCENEMANAGER->addScene("town", new townScene());
	SCENEMANAGER->loadScene("title");

	IMAGEMANAGER->addImage("cursor normal", L"cursor/cursor-3.png");
	IMAGEMANAGER->addImage("cursor melee", L"cursor/cursor-melee-3.png");
	IMAGEMANAGER->addImage("cursor throw", L"cursor/cursor-throw-3.png");

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_ui = new uiController();
	_ui->init();

	_test = 0.f;

	ShowCursor(false);

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
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->loadScene("puzzle");
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(9 * SIZE, 33 * SIZE));
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->loadScene("mountain");
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2((float)76 * SIZE, 34.5f * SIZE));
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		SCENEMANAGER->loadScene("town");
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setPosition(Vector2(36 * SIZE, 47 * SIZE));
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		CAMERA->shakeStart(3.f, 0.5f);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		CAMERA->zoomStart(1.2f, 5.f, true);
	}

	// 이벤트 재생 중, UI가 화면을 가리고 있는 경우에는 업데이트하지 않음
	if (!EVENTMANAGER->isPlayingEvent() && !_ui->isUIOn() && !_ui->UIon())
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

//그리기 전용
void playGround::render()
{	
	D2DRENDERER->BeginRender(D2D1::ColorF::Black);
	{

		//=================================================

		SCENEMANAGER->render();
		EFFECTMANAGER->render();
		OBJECTMANAGER->render();
		TIMEMANAGER->render();
		_ui->render();
		//_enemyManager->render();

		// 상태에 따른 마우스 변경 처리
		if (EVENTMANAGER->isPlayingEvent() || _ui->isUIOn() || SCENEMANAGER->getCurrentSceneName() == "title" || SCENEMANAGER->getCurrentSceneName() == "maptool")
		{
			IMAGEMANAGER->findImage("cursor normal")->render(Vector2(_ptMouse));
		}
		else if (_player->mouseCheck())
		{
			IMAGEMANAGER->findImage("cursor melee")->render(Vector2(_ptMouse));
		}
		else
		{
			IMAGEMANAGER->findImage("cursor throw")->render(Vector2(_ptMouse));
		}

		//=============================================
	}
	D2DRENDERER->EndRender();
}
