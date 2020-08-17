#include "stdafx.h"
#include "tabUI.h"
#include "player.h"

HRESULT tabUI::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	IMAGEMANAGER->addImage("menu", L"images/menu/menu.png");
	IMAGEMANAGER->addImage("equip", L"images/equip/eq.png");

	IMAGEMANAGER->addImage("inven1", L"images/menu/inven1.png");
	IMAGEMANAGER->addImage("inven2", L"images/menu/inven1.png");
	IMAGEMANAGER->addImage("inven3", L"images/menu/inven1.png");
	IMAGEMANAGER->addImage("inven4", L"images/menu/inven1.png");
	IMAGEMANAGER->addImage("inven5", L"images/menu/inven1.png");
	IMAGEMANAGER->addImage("inven6", L"images/menu/inven1.png");
	IMAGEMANAGER->addImage("inven7", L"images/menu/inven1.png");
	
	IMAGEMANAGER->addImage("save", L"images/menu/save.png");
	IMAGEMANAGER->addImage("stat", L"images/menu/stat.png");


	_on = false;

	_hpRC.update(Vector2(125, 44), Vector2(158, 10), pivot::LEFTTOP);
	_expRC.update(Vector2(125, 60), Vector2(158, 5), pivot::LEFTTOP);
	_hp = 165;
	_exp = 162;
	_eq = _iv = _sv = _st = false;
	_setButton = false;
	

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
	if (_on)
	{
		_hpRC.update(Vector2(298, 188), Vector2(_hp, 12), pivot::LEFTTOP);
		_expRC.update(Vector2(309, 203), Vector2(_exp, 2), pivot::LEFTTOP);

		if (!_setButton)
		{
			button* btnEquip = new button();
			btnEquip->init("buttons", 600, 500, 0, 0, 0, 0, bind(&tabUI::inEquip, this));

			button* btnInventory = new button();
			btnInventory->init("buttons", 600, 600, 0, 1, 0, 1, bind(&tabUI::inInven, this));

			button* btnStat = new button();
			btnStat->init("buttons", 600, 700, 0, 2, 0, 2, bind(&tabUI::inStat, this));

			button* btnSave = new button();
			btnSave->init("buttons", 600, 800, 0, 3, 0, 3, bind(&tabUI::inSave, this));

			button* btnMenuExit = new button();
			btnMenuExit->init("buttons", 600, 900, 0, 4, 0, 4, bind(&tabUI::outMenu, this));

			OBJECTMANAGER->addObject(objectType::UI, btnEquip);
			OBJECTMANAGER->addObject(objectType::UI, btnInventory);
			OBJECTMANAGER->addObject(objectType::UI, btnStat);
			OBJECTMANAGER->addObject(objectType::UI, btnSave);
			OBJECTMANAGER->addObject(objectType::UI, btnMenuExit);

			_setButton = true;
		}
		
	}

	if (_on == false)
	{
		_eq = false;
		_iv = false;
		_sv = false;
		_st = false;
	}

	if (_hp < 0)
		_hp = 0;

	cout << _eq << endl;
}

void tabUI::render()
{
	if (_on)
	{
		IMAGEMANAGER->findImage("menu")->render(Vector2(0, 0));
		if (_hp > 50)
			D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::LawnGreen, 0, 45);
		else
			D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::Red, 0, 45);

		D2DRENDERER->DrawRotationFillRectangle(_expRC, D2D1::ColorF::MediumPurple, 0);	
	}
	

	if (_eq)
	{
		IMAGEMANAGER->findImage("equip")->render(Vector2(0, 0));
	}
	if (_iv)
	{
		IMAGEMANAGER->findImage("inven")->render(Vector2(0, 0));
	}
	if (_sv)
	{
		IMAGEMANAGER->findImage("save")->render(Vector2(0, 0));
	}
	if (_st)
	{
		IMAGEMANAGER->findImage("stat")->render(Vector2(0, 0));
	}
}

void tabUI::inEquip()
{
	_eq = true;
	_iv = false;
	_sv = false;
	_st = false;
}
void tabUI::inInven()
{
	_eq = false;
	_iv = true;
	_sv = false;
	_st = false;
}
void tabUI::inSave()
{
	_eq = false;
	_iv = false;
	_sv = true;
	_st = false;
}
void tabUI::inStat()
{
	_eq = false;
	_iv = false;
	_sv = false;
	_st = true;
}
void tabUI::outMenu()
{
	_on = false;
	_eq = false;
	_iv = false;
	_sv = false;
	_st = false;
	_setButton = false;
}