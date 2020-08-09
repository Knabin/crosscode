#include "stdafx.h"
#include "hedgehag.h"

HRESULT hedgehag::init()
{
	_rc.set(0, 0, 120, 99);

	_image = IMAGEMANAGER->addFrameImage("hed", "images/hed.bmp", 1203, 693, 10, 7, true, RGB(255, 0, 255));
	int play[] = { 40, 41 };
	_test_ani = new animation;
	_test_ani->init(1203, 693, 120, 99);
	_test_ani->setPlayFrame(play, 2, true);
	_test_ani->setFPS(1);
	_test_ani->start();

	return S_OK;
}

void hedgehag::release()
{
}

void hedgehag::update()
{
	_test_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
}

void hedgehag::render()
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _test_ani);
}
