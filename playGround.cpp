#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init();

	_player = new player();
	_player->init();
	_player->setIsActive(true);
	OBJECTMANAGER->addObject(objectType::Player, _player);

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	OBJECTMANAGER->update();
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	OBJECTMANAGER->render();

	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}
