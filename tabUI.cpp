#include "stdafx.h"
#include "tabUI.h"
#include "player.h"

HRESULT tabUI::init()
{
	_invenIndex = 0;
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	IMAGEMANAGER->addImage("menu", L"images/menu/menu.png");
	IMAGEMANAGER->addImage("equip", L"images/equip/eq.png");
	IMAGEMANAGER->addImage("eq_armL", L"images/equip/eq_armL.png");
	IMAGEMANAGER->addImage("eq_armR", L"images/equip/eq_armR.png");
	IMAGEMANAGER->addImage("eq_belt", L"images/equip/eq_belt.png");
	IMAGEMANAGER->addImage("eq_foot", L"images/equip/eq_foot.png");
	IMAGEMANAGER->addImage("eq_head", L"images/equip/eq_head.png");
	IMAGEMANAGER->addImage("eq_select", L"images/equip/eq_select.png");
	IMAGEMANAGER->addImage("eq_ui", L"images/equip/eq_ui.png");

	IMAGEMANAGER->addImage("inven1", L"images/menu/inven1.png");
	IMAGEMANAGER->addImage("inven2", L"images/menu/inven2.png");
	IMAGEMANAGER->addImage("inven3", L"images/menu/inven3.png");
	IMAGEMANAGER->addImage("inven4", L"images/menu/inven4.png");
	IMAGEMANAGER->addImage("inven5", L"images/menu/inven5.png");
	IMAGEMANAGER->addImage("inven6", L"images/menu/inven6.png");
	IMAGEMANAGER->addImage("inven7", L"images/menu/inven7.png");
	
	IMAGEMANAGER->addImage("save", L"images/menu/save.png");
	IMAGEMANAGER->addImage("stat", L"images/menu/stat.png");

	IMAGEMANAGER->addFrameImage("button_menu", L"images/menu/button_menu.png", 1,4);
	IMAGEMANAGER->addImage("button_menu_back", L"images/menu/button_menu_back.png");

	IMAGEMANAGER->addFrameImage("invenList", L"images/menu/invenList.png", 7, 1);




	_on = false;

	_hpRC.update(Vector2(125, 44), Vector2(158, 10), pivot::LEFTTOP);
	_expRC.update(Vector2(125, 60), Vector2(158, 5), pivot::LEFTTOP);
	_hp = 165;
	_exp = 162;
	_eq = _iv = _sv = _st = false;
	
	
	button* btnEquip = new button();
	btnEquip->init("button_menu", 1636, 389, 0, 0, 0, 0, bind(&tabUI::inEquip, this));
	btnEquip->setName("equip");
	btnEquip->setIsActive(false);

	button* btnInventory = new button();
	btnInventory->init("button_menu", 1610, 490, 0, 1, 0, 1, bind(&tabUI::inInven, this));
	btnInventory->setName("inventory");
	btnInventory->setIsActive(false);

	button* btnStat = new button();
	btnStat->init("button_menu", 1610, 592, 0, 2, 0, 2, bind(&tabUI::inStat, this));
	btnStat->setName("stat");
	btnStat->setIsActive(false);

	button* btnSave = new button();
	btnSave->init("button_menu", 1636, 693, 0, 3, 0, 3, bind(&tabUI::inSave, this));
	btnSave->setName("save");
	btnSave->setIsActive(false);

	button* btnMenuExit = new button();
	btnMenuExit->init("button_menu_back", 1810, 36, 0, 0, 0, 0, bind(&tabUI::outMenu, this));
	btnMenuExit->setName("menuexit");
	btnMenuExit->setIsActive(false);

	OBJECTMANAGER->addObject(objectType::UI, btnEquip);
	OBJECTMANAGER->addObject(objectType::UI, btnInventory);
	OBJECTMANAGER->addObject(objectType::UI, btnStat);
	OBJECTMANAGER->addObject(objectType::UI, btnSave);
	OBJECTMANAGER->addObject(objectType::UI, btnMenuExit);

	int s = 767;
	int x = 90;
	int y = 130;

	button* btnInventory1 = new button();
	btnInventory1->init("invenList", s + x, y, 0, 0, 0, 0, bind(&tabUI::InventoryList, this));
	btnInventory1->setName("inven1");
	btnInventory1->setIsActive(false);

	button* btnInventory2 = new button();
	btnInventory2->init("invenList",  s + x*2, y, 1, 0, 1, 0, bind(&tabUI::InventoryList, this));
	btnInventory2->setName("inven2");
	btnInventory2->setIsActive(false);

	button* btnInventory3 = new button();
	btnInventory3->init("invenList", s + x*3, y, 2, 0, 2, 0, bind(&tabUI::InventoryList, this));
	btnInventory3->setName("inven3");
	btnInventory3->setIsActive(false);

	button* btnInventory4 = new button();
	btnInventory4->init("invenList", s + x*4, y, 3, 0, 3, 0, bind(&tabUI::InventoryList, this));
	btnInventory4->setName("inven4");
	btnInventory4->setIsActive(false);

	button* btnInventory5 = new button();
	btnInventory5->init("invenList", s + x*5, y, 4, 0, 4, 0, bind(&tabUI::InventoryList, this));
	btnInventory5->setName("inven5");
	btnInventory5->setIsActive(false);

	button* btnInventory6 = new button();
	btnInventory6->init("invenList", s + x*6, y, 5, 0, 5, 0, bind(&tabUI::InventoryList, this));
	btnInventory6->setName("inven6");
	btnInventory6->setIsActive(false);

	button* btnInventory7 = new button();
	btnInventory7->init("invenList", s + x*7, y, 6, 0, 6, 0, bind(&tabUI::InventoryList, this));
	btnInventory7->setName("inven7");
	btnInventory7->setIsActive(false);



	OBJECTMANAGER->addObject(objectType::UI, btnInventory1);
	OBJECTMANAGER->addObject(objectType::UI, btnInventory2);
	OBJECTMANAGER->addObject(objectType::UI, btnInventory3);
	OBJECTMANAGER->addObject(objectType::UI, btnInventory4);
	OBJECTMANAGER->addObject(objectType::UI, btnInventory5);
	OBJECTMANAGER->addObject(objectType::UI, btnInventory6);
	OBJECTMANAGER->addObject(objectType::UI, btnInventory7);

	OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(1215, 130));
	OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(1215 + 94, 130));
	OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(1215 + 94 * 2, 130));
	OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(1215 + 94 * 3, 130));
	OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1216 + 94 * 4, 130));
	OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1216 + 94 * 5, 130));

	for (int i = 0; i < 5; i++)
	{
		_eqRect[i].update(Vector2(1223,248+128*i), Vector2(IMAGEMANAGER->findImage("eq_ui")->getWidth() * 0.85f, IMAGEMANAGER->findImage("eq_ui")->getHeight() * 0.85f), pivot::LEFTTOP);
	}

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

		if (!_eq && !_iv && !_sv && !_st && !_eqSelect)
		{
			OBJECTMANAGER->findObject(objectType::UI, "equip")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inventory")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "stat")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "save")->setIsActive(true);
		}
		OBJECTMANAGER->findObject(objectType::UI, "menuexit")->setIsActive(true);
	}
	else
	{
		OBJECTMANAGER->findObject(objectType::UI, "equip")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inventory")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "stat")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "save")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "menuexit")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(false);
	}

	if (_on == false)
	{
		_eq = false;
		_iv = false;
		_sv = false;
		_st = false;
		_eqSelect = false;
		_invenIndex = 0;
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(1215, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(1215 + 94, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(1215 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(1215 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1216 + 94 * 4, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1216 + 94 * 5, 130));
	}

	if (_iv)
	{
		switch (_invenIndex)
		{
		case 0:
			OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(false);
			OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(true);
			break;
		case 1:
			OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(false);
			OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(true);
			break;
		case 2:
			OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(false);
			OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(true);
			break;
		case 3:
			OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(false);
			OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(true);
			break;
		case 4:
			OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(false);
			OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(true);
			break;
		case 5:
			OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(false);
			OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(true);
			break;
		case 6:
			OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(false);
			break;
		}
	}

	if (_eq)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_eqRect[i].getRect(), _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_eq = false;
					_eqSelect = true;
				}
				break;
			}
		}
	}

	if (_on)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) || KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			outMenu();
		}
	}


	if (_hp < 0)
		_hp = 0;
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
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_eqRect[i].getRect(), _ptMouse))
			{
				switch (i)
				{
				case 0:
					IMAGEMANAGER->findImage("eq_head")->render(Vector2(0, 0));
					break;
				case 1:
					IMAGEMANAGER->findImage("eq_armR")->render(Vector2(0, 0));
					break;
				case 2:
					IMAGEMANAGER->findImage("eq_armL")->render(Vector2(0, 0));
					break;
				case 3:
					IMAGEMANAGER->findImage("eq_belt")->render(Vector2(0, 0));
					break;
				case 4:
					IMAGEMANAGER->findImage("eq_foot")->render(Vector2(0, 0));
					break;
				}
			}
		}
	}

	if (_eqSelect)
	{
		IMAGEMANAGER->findImage("eq_select")->render(Vector2(0, 0));
	}
	
		

	if (_iv)
	{
		switch (_invenIndex)
		{
		case 0:
			IMAGEMANAGER->findImage("inven1")->render(Vector2(0, 0));
			break;
		case 1:
			IMAGEMANAGER->findImage("inven2")->render(Vector2(0, 0));
			break;
		case 2:
			IMAGEMANAGER->findImage("inven3")->render(Vector2(0, 0));
			break;
		case 3:
			IMAGEMANAGER->findImage("inven4")->render(Vector2(0, 0));
			break;
		case 4:
			IMAGEMANAGER->findImage("inven5")->render(Vector2(0, 0));
			break;
		case 5:
			IMAGEMANAGER->findImage("inven6")->render(Vector2(0, 0));
			break;
		case 6:
			IMAGEMANAGER->findImage("inven7")->render(Vector2(0, 0));
			break;
		}
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

	OBJECTMANAGER->findObject(objectType::UI, "equip")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "inventory")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "stat")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "save")->setIsActive(false);
}
void tabUI::inInven()
{
	_eq = false;
	_iv = true;
	_sv = false;
	_st = false;

	OBJECTMANAGER->findObject(objectType::UI, "equip")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "inventory")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "stat")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "save")->setIsActive(false);
}
void tabUI::inSave()
{
	_eq = false;
	_iv = false;
	_sv = true;
	_st = false;

	OBJECTMANAGER->findObject(objectType::UI, "equip")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "inventory")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "stat")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "save")->setIsActive(false);
}
void tabUI::inStat()
{
	_eq = false;
	_iv = false;
	_sv = false;
	_st = true;

	OBJECTMANAGER->findObject(objectType::UI, "equip")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "inventory")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "stat")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "save")->setIsActive(false);
}
void tabUI::outMenu()
{
	if (_on == true && !_eq && !_iv && !_sv && !_st && !_eqSelect)
	{
		_on = false;
	}

	if (_eq == true)
	{
		_eq = false;
	}

	if (_eqSelect == true)
	{
		_eqSelect = false;
		_eq = true;
	}
	
	if (_iv == true)
	{
		_iv = false;
		OBJECTMANAGER->findObject(objectType::UI, "inven1")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(1215, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(1215 + 94, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(1215 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(1215 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1216 + 94 * 4, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1216 + 94 * 5, 130));
		_invenIndex = 0;
	}

	if (_sv == true)
	{
		_sv = false;
	}

	if (_st == true)
	{
		_st = false;
	}
	
}

void tabUI::InventoryList()
{
	vector<floatRect> rc;
	int k = 0;
	for (int i = 0; i < 7; ++i)
	{
		char str[20];
		sprintf_s(str, "inven%d", i+1);
		rc.push_back(OBJECTMANAGER->findObject(objectType::UI, str)->getRect());

		if (PtInRect(&rc[i].getRect(), _ptMouse))
		{
			k = i;
			break;
		}
	}

	_invenIndex = k;

	rc.clear();

	switch (_invenIndex)
	{
	case 0:
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(1215, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(1215 + 94, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(1215 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(1215 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1216 + 94 * 4, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1216 + 94 * 5, 130));
		break;
	case 1:
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(1309 , 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(1309 + 94, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(1309 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1310 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1310 + 94 * 4, 130));
		break;
	case 2:
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(952 , 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(1309 + 94, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(1309 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1310 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1310 + 94 * 4, 130));
		break;
	case 3:
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(952, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(952 + 94, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(1309 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1310 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1310 + 94 * 4, 130));
		break;
	case 4:
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(952, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(952 + 94, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(952 + 94*2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(1310 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1310 + 94 * 4, 130));
		break;
	case 5:
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(952, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(952 + 94 , 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(952 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(952 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven7")->setPosition(Vector2(1310 + 94 * 4, 130));
		break;
	case 6:
		OBJECTMANAGER->findObject(objectType::UI, "inven2")->setPosition(Vector2(952, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven3")->setPosition(Vector2(952 + 94 * 1, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven4")->setPosition(Vector2(952 + 94 * 2, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven5")->setPosition(Vector2(952 + 94 * 3, 130));
		OBJECTMANAGER->findObject(objectType::UI, "inven6")->setPosition(Vector2(952 + 94 * 4, 130));
		break;
	}
}

void tabUI::equipSelect()
{

}