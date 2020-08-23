#include "stdafx.h"
#include "bossHPBar.h"

HRESULT bossHPBar::init()
{
	return S_OK;
}

void bossHPBar::release()
{
}

void bossHPBar::update()
{
	_rc.update(Vector2(155, 1007), Vector2(_HP, 20), pivot::LEFTTOP);
}

void bossHPBar::render()
{
	IMAGEMANAGER->findImage("bossHpbar")->render(Vector2(57, 1000));

	if (_HP >= 0)
	{
		D2DRENDERER->SkewRectangle(_rc, D2D1::ColorF::Red, 0, 135);
	}
}
