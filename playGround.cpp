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

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}
