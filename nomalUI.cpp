#include "stdafx.h"
#include "nomalUI.h"
#include "player.h"

HRESULT nomalUI::init()
{
	IMAGEMANAGER->addImage("nomalUI", L"images/menu/nomalUI.png");
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	_hpRC.update(Vector2(125, 44), Vector2(158, 10), pivot::LEFTTOP);
	_expRC.update(Vector2(125, 60), Vector2(158, 5), pivot::LEFTTOP);
	_hp = 158;
	_exp = 157;
	return S_OK;
}

void nomalUI::release()
{
}

void nomalUI::update()
{
	_hpRC.update(Vector2(125, 44), Vector2(_hp, 10), pivot::LEFTTOP);
	_expRC.update(Vector2(135, 57), Vector2(_exp, 4), pivot::LEFTTOP);
}

void nomalUI::render()
{
	IMAGEMANAGER->findImage("nomalUI")->render(Vector2(15, 15));

	if ( _hp > 50)
		D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::LawnGreen, 0, 45);
	else 
		D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::Red, 0, 45);

	D2DRENDERER->DrawRotationFillRectangle(_expRC, D2D1::ColorF::MediumPurple, 0);

}
