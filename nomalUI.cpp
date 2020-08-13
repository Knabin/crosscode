#include "stdafx.h"
#include "nomalUI.h"
#include "player.h"

HRESULT nomalUI::init()
{
	IMAGEMANAGER->addImage("nomalUI", "images/menu/nomalUI.bmp", 400, 108, true, RGB(255, 0, 255));
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	//_hp = _player.

	_hp = 160;
	return S_OK;
}

void nomalUI::release()
{
}

void nomalUI::update()
{

}

void nomalUI::render()
{
	IMAGEMANAGER->findImage("nomalUI")->render(getMemDC(),CAMERA->getRect().left + 15, CAMERA->getRect().top + 15);

	int ltX = 117;
	int tY = 43;
	int rtX = ltX + _hp;
	int rbX = rtX + 12 ;
	int bY = 53;
	int lbX = ltX+ 12;



	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	POINT polygon[5] = { ltX,tY,rtX ,tY,rbX,bY,lbX,bY,ltX,tY };
	Polygon(getMemDC(), polygon, 5);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);
}
