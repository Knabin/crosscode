#include "stdafx.h"
#include "playGround.h"
#include "titleScene.h"
//#include "mapToolScene.h"
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
	OBJECTMANAGER->addObject(objectType::Player, _player);

	_collisionManager = new collisionManager;
	_collisionManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_ui = new uiController();
	_ui->init();

	SCENEMANAGER->addScene("title", new titleScene());			// 타이틀 씬
	SCENEMANAGER->addScene("maptool", new mapToolScene());		// 맵툴 씬
	SCENEMANAGER->addScene("test", new testScene());			// 테스트용(새 게임 버튼)
	SCENEMANAGER->addScene("test2", new testScene2());			// 테스트용(게임 불러오기 버튼)
	SCENEMANAGER->addScene("boss", new bossTestScene());		// 테스트용(옵션 버튼)
	SCENEMANAGER->loadScene("title");

	_test = false;

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

	SCENEMANAGER->update();
	OBJECTMANAGER->update();
	CAMERA->update();
	_ui->update();

	_collisionManager->update();
	_enemyManager->update();

	//vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::Monster);
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, CAMERA->getMapWidth(), CAMERA->getMapHeight(), WHITENESS);
	//=================================================

	SCENEMANAGER->render();
	OBJECTMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	_ui->render();

	//=============================================
	_backBuffer->render(getHDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top, WINSIZEX, WINSIZEY);
}
