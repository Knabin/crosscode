#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init()
{
	IMAGEMANAGER->addImage("����", "images/boss/ice1.bmp", 84, 84, true, RGB(255, 0, 255));



	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
}

void boss::render()
{
	IMAGEMANAGER->findImage("����")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);

}
