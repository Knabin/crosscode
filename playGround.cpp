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

//�ʱ�ȭ �Լ�
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

	SCENEMANAGER->addScene("title", new titleScene());			// Ÿ��Ʋ ��
	SCENEMANAGER->addScene("maptool", new mapToolScene());		// ���� ��
	SCENEMANAGER->addScene("test", new testScene());			// �׽�Ʈ��(�� ���� ��ư)
	SCENEMANAGER->addScene("test2", new testScene2());			// �׽�Ʈ��(���� �ҷ����� ��ư)
	SCENEMANAGER->addScene("boss", new bossTestScene());		// �׽�Ʈ��(�ɼ� ��ư)
	SCENEMANAGER->loadScene("title");

	_test = false;

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

	SCENEMANAGER->update();
	OBJECTMANAGER->update();
	CAMERA->update();
	_ui->update();

	_collisionManager->update();
	_enemyManager->update();

	//vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::Monster);
}

//�׸��� ����
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
