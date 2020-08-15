#include "stdafx.h"
#include "nomalUI.h"
#include "player.h"

HRESULT nomalUI::init()
{
	IMAGEMANAGER->addImage("nomalUI", L"images/menu/nomalUI.png");
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	//_hp = _player.

	_hp = 160;
	_exp = 158;
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
	IMAGEMANAGER->findImage("nomalUI")->render(Vector2(15, 15));

	int ltX = CAMERA->getRect().left + 117;
	int tY = CAMERA->getRect().top + 43;
	int rtX = ltX + _hp;
	int rbX = rtX + 12 ;
	int bY = CAMERA->getRect().top + 53;
	int lbX = ltX+ 12;

	/*HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	POINT polygon[5] = { ltX,tY,rtX ,tY,rbX,bY,lbX,bY,ltX,tY };
	Polygon(getMemDC(), polygon, 5);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	HBRUSH brush1 = CreateSolidBrush(RGB(243, 0, 243));
	HBRUSH oldBrush1 = (HBRUSH)SelectObject(getMemDC(), brush1);
	RectangleMake(getMemDC(), ltX +17, bY +3, _exp, 5);
	SelectObject(getMemDC(), oldBrush1);
	DeleteObject(brush1);*/
}
