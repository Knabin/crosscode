#include "stdafx.h"
#include "playGround.h"
#include "titleScene.h"
//#include "mapToolScene.h"
#include "mapToolScene2.h"
#include "testScene.h"


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
	OBJECTMANAGER->addObject(objectType::Player, _player);

	_ui = new uiController();
	_ui->init();

	SCENEMANAGER->addScene("title", new titleScene());
	SCENEMANAGER->addScene("maptool", new mapToolScene2());
	SCENEMANAGER->addScene("test", new testScene());
	SCENEMANAGER->loadScene("title");

	_test = false;

	SetCursor(LoadCursorFromFile("cursor/cursor-melee.cur"));

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	
}

//����
void playGround::update()
{
	SCENEMANAGER->update();
	OBJECTMANAGER->update();
	CAMERA->update();
	_ui->update();

}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, CAMERA->getMapWidth(), CAMERA->getMapHeight(), WHITENESS);
	//=================================================
	Rectangle(getMemDC(), CAMERA->getRect());
	SCENEMANAGER->render();
	OBJECTMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	_ui->render();


	//=============================================
	_backBuffer->render(getHDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top, WINSIZEX, WINSIZEY);
}
