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
	IMAGEMANAGER->addImage("얼음", "images/boss/right_hand.bmp",375, 480, true, RGB(255, 0, 255));

	_currentFrameX, _currentFrameY, _frameCount = 0;
	_protectCurrentFrameX, _protectCurrentFrameY, _protectFrameCount = 0;
	_appearanceCount = 0;
	_attackCount = 0;
	_attackEndCount = 0;
	_fireskill1Time = 0;
	_mineAttackCount = 0;





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
	IMAGEMANAGER->findImage("얼음")->rotateRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, 2);

}
