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

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	
}

//����
void playGround::update()
{
}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}
