#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init();

	_player = new player();
	_player->init();
	_player->setIsActive(true);
	OBJECTMANAGER->addObject(objectType::Player, _player);

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	
}

//����
void playGround::update()
{
	OBJECTMANAGER->update();
}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	OBJECTMANAGER->render();

	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}
