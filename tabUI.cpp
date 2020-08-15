#include "stdafx.h"
#include "tabUI.h"
#include "player.h"

HRESULT tabUI::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	IMAGEMANAGER->addImage("menu", L"images/menu/menu.png");

	_on = false;

	
	_hp = 164;
	_exp = 163;

	return S_OK;
}

void tabUI::release()
{
}

void tabUI::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_on = _on == false ? true : false;
	}
}

void tabUI::render()
{
	if (_on)
	{
		IMAGEMANAGER->findImage("menu")->render(Vector2(0, 0));

		int ltX = 291;
		int tY = 187;
		int rtX = ltX + _hp;
		int rbX = rtX + 12;
		int bY = tY + 12;
		int lbX = ltX + 12;

		//HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//POINT polygon[5] = { ltX,tY,rtX ,tY,rbX,bY,lbX,bY,ltX,tY };
		//Polygon(getMemDC(), polygon, 5);
		//SelectObject(getMemDC(), oldBrush);
		//DeleteObject(brush);

		//HBRUSH brush1 = CreateSolidBrush(RGB(243, 0, 243));
		//HBRUSH oldBrush1 = (HBRUSH)SelectObject(getMemDC(), brush1);
		//RectangleMake(getMemDC(), ltX + 17, bY + 3, _exp, 5);
		//SelectObject(getMemDC(), oldBrush1);
		//DeleteObject(brush1);
	}
}
