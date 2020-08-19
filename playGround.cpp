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


	// ============== 이펙트 넣는 법! =================
	// 이펙트 사용: VK_F8 쪽 확인
	IMAGEMANAGER->addFrameImage("test", L"images/test.png", 4, 2);
	// addEffect(이펙트 이름, 이미지 이름, fps, elapsedTime, 버퍼(여러 개 동시에 쓸 거면 적당히 잡기), 크기(scale))
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
		// ============== 이펙트 회전해서 사용하는 법! =================
		// play(이펙트 이름, 위치, 위치, 앵글값)
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

	// 이벤트 재생 중에는 업데이트하지 않음
	// TODO: UI 켜져 있을 때 화면 멈춰야 하므로 조건 추가
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

//그리기 전용
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
