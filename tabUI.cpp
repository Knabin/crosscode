#include "stdafx.h"
#include "tabUI.h"
#include "player.h"
#include "inventory.h"
#include <codecvt>

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
	IMAGEMANAGER->addImage("save slot", L"images/menu/save_slot.png");
	IMAGEMANAGER->addImage("stat", L"images/menu/stat.png");

	IMAGEMANAGER->addFrameImage("button_menu", L"images/menu/button_menu.png", 1,4);
	IMAGEMANAGER->addImage("button_menu_back", L"images/menu/button_menu_back.png");

	IMAGEMANAGER->addFrameImage("invenList", L"images/menu/invenList.png", 7, 1);

	IMAGEMANAGER->addImage("inven01", L"images/menu/inven01.png");
	IMAGEMANAGER->addImage("inven02", L"images/menu/inven02.png");
	IMAGEMANAGER->addImage("inven03", L"images/menu/inven03.png");
	IMAGEMANAGER->addImage("inven04", L"images/menu/inven04.png");
	IMAGEMANAGER->addImage("inven05", L"images/menu/inven05.png");
	IMAGEMANAGER->addImage("inven06", L"images/menu/inven06.png");
	IMAGEMANAGER->addImage("inven07", L"images/menu/inven07.png");
	
	IMAGEMANAGER->addFrameImage("weapon", L"images/equip/weapon.png", 4, 1);
	IMAGEMANAGER->addFrameImage("eq_effect", L"images/equip/eq_eff.png", 5, 1);

	EFFECTMANAGER->addEffect("eq_effect", "eq_effect", 1, 0.3f, 1, 0.74f);

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

	//¿Â∫Ò √ ±‚ º≥¡§
	for (int i = 0; i < 5; i++)
	{
		_equip[i] = 99999;
	}
	
	for (int i = 0; i < 5; ++i)
	{
		//200 216
		_saveSlot[i].rc.update(Vector2(203, 215 + i * 135), Vector2(IMAGEMANAGER->findImage("save slot")->getSize()), pivot::LEFTTOP);
		_saveSlot[i].fileName = "data/crosscode" + to_string(i) + ".data";
	}
	loadData();


	_item = new item;
	_item->init();
	

	_time = 0;
	_timeCount = 0;
	_eqSelectNum = 0;
	return S_OK;
}

void tabUI::release()
{
}

void tabUI::update()
{
	_timeCount++;
	if (_timeCount > 59)
	{
		_time++;
		_timeCount = 0;
	}
	

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if(_on) SOUNDMANAGER->play("button cancel");
		else SOUNDMANAGER->play("button ok");
		_on = _on == false ? true : false;
	}
	if (_on)
	{
		_hp = (float)_player->getPlayerHP() / (float)_player->getPlayerMaxHP() * 165;
		_exp = (float)_player->getPlayerEXP() / (float)_player->getPlayerNextEXP() * 162;

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
		if (_player->getPlayerHP() >= _player->getPlayerMaxHP())
		{
			_player->setPlayerHP(_player->getPlayerMaxHP());
		}

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
					_equipList = i;

					_equipItemNum.clear();

					_eqSelectNum = 0;
					for (int j = 0; j < _vIv.size(); ++j)
					{
						SOUNDMANAGER->play("button ok");
						switch (i)
						{
						case 0:
							if (_vIv[j].type == L"∏”∏Æ")
							{
								_eqSelectNum++;
								int num = _vIv[j].itemNum;
								_equipItemNum.push_back(num);
							}
							break;
						case 1:
						case 2:
							if (_vIv[j].type == L"∆»")
							{
								_eqSelectNum++;
								int num = _vIv[j].itemNum;
								_equipItemNum.push_back(num);
							}
							break;
						case 3:
							if (_vIv[j].type == L"∏ˆ≈Î")
							{
								_eqSelectNum++;
								int num = _vIv[j].itemNum;
								_equipItemNum.push_back(num);
							}
							break;
						case 4:
							if (_vIv[j].type == L"¥Ÿ∏Æ")
							{
								_eqSelectNum++;
								int num = _vIv[j].itemNum;
								_equipItemNum.push_back(num);
							}
							break;
						}

					}
				}
				break;
			}
		}
	}

	if (_equipList)
	{
		if (_player->getPlayerHP() >= _player->getPlayerMaxHP())
		{
			_player->setPlayerHP(_player->getPlayerMaxHP());
		}
	}

	
	if (_on)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) || KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			outMenu();
		}
	}


	//ºº¿Ã∫Í ¡∏
	if (_sv)
	{
		// æÓ∂≤ ∑∫∆Æ º±≈√«ﬂ¥¬¡ˆ
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_saveSlot[i].rc.getRect(), _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0 && !_saveSlot[i].isSaved)
					{
						// forπÆ ∞≈≤Ÿ∑Œ µπ∏Èº≠ πÿø° ∫Òæ˙¥¬¡ˆ √º≈©
						for (int j = 4; j >= 0; --j)
						{
							if (!_saveSlot[j].isSaved)
							{
								SOUNDMANAGER->play("button ok");
								saveData(j);
								loadData();
								break;
							}
						}
					}
					else
					{
						SOUNDMANAGER->play("button ok");
						saveData(i);
						loadData();
						break;
					}
				}
			}
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


		wstring Num = to_wstring(_player->getPlayerEXP());
		D2DRENDERER->RenderText(600, 182, Num, 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerNextEXP());
		D2DRENDERER->RenderText(680, 182, Num, 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerHP());
		D2DRENDERER->RenderText(350, 152, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerLEVEL());
		D2DRENDERER->RenderText(300, 80, Num, 50, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerMaxHP());
		D2DRENDERER->RenderText(440, 98, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerAtk());
		D2DRENDERER->RenderText(592, 98, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerDef());
		D2DRENDERER->RenderText(730, 98, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerCri());
		D2DRENDERER->RenderText(868, 98, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");


		for (int i = 0; i < _player->getPlayerSP(); ++i)
		{
			floatRect rc;
			rc.update(Vector2(508 + 16 * i, 162), Vector2(10, 17), pivot::LEFTTOP);
			D2DRENDERER->DrawRotationFillRectangle(rc, D2D1::ColorF::DeepSkyBlue, 0);
		}

		Num = to_wstring(_inven->getMoney());
		D2DRENDERER->RenderText(120, 980, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		char str[256];
		sprintf_s(str, "%02d : %02d", _time / 60, _time % 60);
		string ss;
		ss = str;

		wstring sstr;
		sstr.assign(ss.begin(), ss.end());
		Num = to_wstring(_time);
		D2DRENDERER->RenderText(155, 1025, sstr, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
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

		for (int i = 0; i < 5; ++i)
		{
			if (_equip[i] != 99999)
			{
				switch (i)
				{
					case 0:
					{
						IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 290), 0, 0);

						itemObject it = _item->getItemInfo(L"∏”∏Æ", _equip[0]);
						D2DRENDERER->RenderText(1380, 264, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						break; 
					}
					case 1:
					{
						IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 418), 1, 0);
						itemObject it = _item->getItemInfo(L"∆»", _equip[1]);
						D2DRENDERER->RenderText(1380, 392, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						break;
					}
					case 2:
					{
						IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 546), 1, 0);
						itemObject it = _item->getItemInfo(L"∆»", _equip[2]);
						D2DRENDERER->RenderText(1380, 520, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						break;
					}
					case 3:
					{
						IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 674), 2, 0);
						itemObject it = _item->getItemInfo(L"∏ˆ≈Î", _equip[3]);
						D2DRENDERER->RenderText(1380, 648, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						break;
					}
					case 4:
					{
						IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 802), 3, 0);
						itemObject it = _item->getItemInfo(L"¥Ÿ∏Æ", _equip[4]);
						D2DRENDERER->RenderText(1380, 776, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						break;
					}
				}

			}
		}
		
	}

	if (_eqSelect)
	{

		IMAGEMANAGER->findImage("eq_select")->render(Vector2(0, 0));
		
		//¿Â∫Ò «•Ω√
		switch (_equipList)
		{
			case 0:
			{
				itemObject it = _item->getItemInfo(L"∏”∏Æ", _equip[0]);
				IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 178), 0, 0);
				D2DRENDERER->RenderText(1380, 152, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				int list = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type != L"∏”∏Æ") continue;
					IMAGEMANAGER->findImage("inven03")->render(Vector2(1270, 275 + 75 * list), 1.1f);
					itemObject it = _item->getItemInfo(L"∏”∏Æ", _vIv[i].itemNum);
					D2DRENDERER->RenderText(1350, 285 + 75 * list, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num = to_wstring(_vIv[i].count);
					D2DRENDERER->RenderText(1750, 285 + 75 * list, Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					list++;
				}
				break;
			}
			case 1:
			{
				itemObject it = _item->getItemInfo(L"∆»", _equip[1]);
				IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 178), 1, 0);
				D2DRENDERER->RenderText(1380, 152, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				int list = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type != L"∆»") continue;
					IMAGEMANAGER->findImage("inven02")->render(Vector2(1270, 275 + 75 * list), 1.1f);
					itemObject it = _item->getItemInfo(L"∆»", _vIv[i].itemNum);
					D2DRENDERER->RenderText(1350, 285 + 75 * list, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num = to_wstring(_vIv[i].count);
					D2DRENDERER->RenderText(1750, 285 + 75 * list, Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					list++;
				}
				break;
			}
			case 2:
			{
				itemObject it = _item->getItemInfo(L"∆»", _equip[2]);
				IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 178), 1, 0);
				D2DRENDERER->RenderText(1380, 152, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				int list = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type != L"∆»") continue;
					IMAGEMANAGER->findImage("inven02")->render(Vector2(1270, 275 + 75 * list), 1.1f);
					itemObject it = _item->getItemInfo(L"∆»", _vIv[i].itemNum);
					D2DRENDERER->RenderText(1350, 285 + 75 * list, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num = to_wstring(_vIv[i].count);
					D2DRENDERER->RenderText(1750, 285 + 75 * list, Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					list++;
				}
				break;
			}
			case 3:
			{
				itemObject it = _item->getItemInfo(L"∏ˆ≈Î", _equip[3]);
				IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 178), 2, 0);
				D2DRENDERER->RenderText(1380, 152, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				int list = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type != L"∏ˆ≈Î") continue;
					IMAGEMANAGER->findImage("inven04")->render(Vector2(1270, 275 + 75 * list), 1.1f);
					itemObject it = _item->getItemInfo(L"∏ˆ≈Î", _vIv[i].itemNum);
					D2DRENDERER->RenderText(1350, 285 + 75 * list, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num = to_wstring(_vIv[i].count);
					D2DRENDERER->RenderText(1750, 285 + 75 * list, Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					list++;
				}
				break;
			}
			case 4:
			{
				itemObject it = _item->getItemInfo(L"¥Ÿ∏Æ", _equip[4]);
				IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 178), 3, 0);
				D2DRENDERER->RenderText(1380, 152, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				
				int list = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type != L"¥Ÿ∏Æ") continue;
					IMAGEMANAGER->findImage("inven05")->render(Vector2(1270, 275 + 75 * list), 1.1f);
					itemObject it = _item->getItemInfo(L"¥Ÿ∏Æ", _vIv[i].itemNum);
					D2DRENDERER->RenderText(1350, 285 + 75 * list, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num = to_wstring(_vIv[i].count);
					D2DRENDERER->RenderText(1750, 285 + 75 * list, Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					list++;
				}
				break;
			}
		}

		//¿Â∫Ò ¿Œ∫• ∏ÆΩ∫∆Æ ¡§∫∏
		for (int i = 0; i < _eqSelectNum; ++i)
		{
			floatRect rc;
			rc.update(Vector2(1270, 275 + 75 * i), Vector2((float)IMAGEMANAGER->findImage("inven03")->getWidth(), (float)IMAGEMANAGER->findImage("inven03")->getHeight()), pivot::LEFTTOP);

			switch (_equipList)
			{
			case 0:
			{
				itemObject it = _item->getItemInfo(L"∏”∏Æ", _equipItemNum[i]);
				if (PtInRect(&rc.getRect(), _ptMouse))
				{
					int x = 420;
					int y = 110;
					int d = 49;
					wstring Num1 = to_wstring(it.hp);
					D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num2 = to_wstring(it.atk);
					D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num3 = to_wstring(it.def);
					D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num4 = to_wstring(it.crt);
					D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num5 = to_wstring(it.fireR);
					D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num6 = to_wstring(it.iceR);
					D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num7 = to_wstring(it.electricR);
					D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					wstring Num8 = to_wstring(it.psycoR);
					D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_inven->deleteItem(L"∏”∏Æ", _equipItemNum[i]);
						if (_equip[0] != 99999)
						{
							it = _item->getItemInfo(L"∏”∏Æ", _equip[0]);
							_inven->getItem(L"∏”∏Æ", _equip[0]);
							_player->setPlayerMaxHP(_player->getPlayerMaxHP() - it.hp);
							_player->setPlayerAtk(_player->getPlayerAtk() - it.atk);
							_player->setPlayerDef(_player->getPlayerDef() - it.def);
							_player->setPlayerCri(_player->getPlayerCri() - it.crt);
							_player->setPlayerFR(_player->getPlayerFR() - it.fireR);
							_player->setPlayerIR(_player->getPlayerIR() - it.iceR);
							_player->setPlayerER(_player->getPlayerER() - it.electricR);
							_player->setPlayerPR(_player->getPlayerPR() - it.psycoR);
						}

						it = _item->getItemInfo(L"∏”∏Æ", _equipItemNum[i]);
						_player->setPlayerMaxHP(_player->getPlayerMaxHP() + it.hp);
						_player->setPlayerAtk(_player->getPlayerAtk() + it.atk);
						_player->setPlayerDef(_player->getPlayerDef() + it.def);
						_player->setPlayerCri(_player->getPlayerCri() + it.crt);
						_player->setPlayerFR(_player->getPlayerFR() + it.fireR);
						_player->setPlayerIR(_player->getPlayerIR() + it.iceR);
						_player->setPlayerER(_player->getPlayerER() + it.electricR);
						_player->setPlayerPR(_player->getPlayerPR() + it.psycoR);

						_equip[0] = _equipItemNum[i];
						EFFECTMANAGER->play("eq_effect", Vector2(1025, 222), 0, 0.7f);
						outMenu();
					}
				}
				break;
			}
			case 1:
			case 2:
			{itemObject it = _item->getItemInfo(L"∆»", _equipItemNum[_eqSelectNum - 1]);
			if (PtInRect(&rc.getRect(), _ptMouse))
			{
				int x = 420;
				int y = 110;
				int d = 49;
				wstring Num1 = to_wstring(it.hp);
				D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num2 = to_wstring(it.atk);
				D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num3 = to_wstring(it.def);
				D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num4 = to_wstring(it.crt);
				D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num5 = to_wstring(it.fireR);
				D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num6 = to_wstring(it.iceR);
				D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num7 = to_wstring(it.electricR);
				D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num8 = to_wstring(it.psycoR);
				D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_inven->deleteItem(L"∆»", _equipItemNum[i]);
					if (_equip[_equipList] != 99999)
					{
						it = _item->getItemInfo(L"∆»", _equip[_equipList]);
						_inven->getItem(L"∆»", _equip[_equipList]);
						_player->setPlayerMaxHP(_player->getPlayerMaxHP() - it.hp);
						_player->setPlayerAtk(_player->getPlayerAtk() - it.atk);
						_player->setPlayerDef(_player->getPlayerDef() - it.def);
						_player->setPlayerCri(_player->getPlayerCri() - it.crt);
						_player->setPlayerFR(_player->getPlayerFR() - it.fireR);
						_player->setPlayerIR(_player->getPlayerIR() - it.iceR);
						_player->setPlayerER(_player->getPlayerER() - it.electricR);
						_player->setPlayerPR(_player->getPlayerPR() - it.psycoR);
					}

					it = _item->getItemInfo(L"∆»", _equipItemNum[i]);
					_player->setPlayerMaxHP(_player->getPlayerMaxHP() + it.hp);
					_player->setPlayerAtk(_player->getPlayerAtk() + it.atk);
					_player->setPlayerDef(_player->getPlayerDef() + it.def);
					_player->setPlayerCri(_player->getPlayerCri() + it.crt);
					_player->setPlayerFR(_player->getPlayerFR() + it.fireR);
					_player->setPlayerIR(_player->getPlayerIR() + it.iceR);
					_player->setPlayerER(_player->getPlayerER() + it.electricR);
					_player->setPlayerPR(_player->getPlayerPR() + it.psycoR);

					_equip[_equipList] = _equipItemNum[i];

					switch (_equipList)
					{
					case 1:
						EFFECTMANAGER->play("eq_effect", Vector2(879, 533), 0, 0.7f);
						break;
					case 2:
						EFFECTMANAGER->play("eq_effect", Vector2(1166, 533), 0, 0.7f);
						break;
					}
					outMenu();
				}
			}
			break;
			}

			case 3:
			{itemObject it = _item->getItemInfo(L"∏ˆ≈Î", _equipItemNum[_eqSelectNum - 1]);
			if (PtInRect(&rc.getRect(), _ptMouse))
			{
				int x = 420;
				int y = 110;
				int d = 49;
				wstring Num1 = to_wstring(it.hp);
				D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num2 = to_wstring(it.atk);
				D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num3 = to_wstring(it.def);
				D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num4 = to_wstring(it.crt);
				D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num5 = to_wstring(it.fireR);
				D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num6 = to_wstring(it.iceR);
				D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num7 = to_wstring(it.electricR);
				D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num8 = to_wstring(it.psycoR);
				D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_inven->deleteItem(L"∏ˆ≈Î", _equipItemNum[i]);
					if (_equip[_equipList] != 99999)
					{
						it = _item->getItemInfo(L"∏ˆ≈Î", _equip[_equipList]);
						_inven->getItem(L"∏ˆ≈Î", _equip[_equipList]);
						_player->setPlayerMaxHP(_player->getPlayerMaxHP() - it.hp);
						_player->setPlayerAtk(_player->getPlayerAtk() - it.atk);
						_player->setPlayerDef(_player->getPlayerDef() - it.def);
						_player->setPlayerCri(_player->getPlayerCri() - it.crt);
						_player->setPlayerFR(_player->getPlayerFR() - it.fireR);
						_player->setPlayerIR(_player->getPlayerIR() - it.iceR);
						_player->setPlayerER(_player->getPlayerER() - it.electricR);
						_player->setPlayerPR(_player->getPlayerPR() - it.psycoR);
					}

					it = _item->getItemInfo(L"∏ˆ≈Î", _equipItemNum[i]);
					_player->setPlayerMaxHP(_player->getPlayerMaxHP() + it.hp);
					_player->setPlayerAtk(_player->getPlayerAtk() + it.atk);
					_player->setPlayerDef(_player->getPlayerDef() + it.def);
					_player->setPlayerCri(_player->getPlayerCri() + it.crt);
					_player->setPlayerFR(_player->getPlayerFR() + it.fireR);
					_player->setPlayerIR(_player->getPlayerIR() + it.iceR);
					_player->setPlayerER(_player->getPlayerER() + it.electricR);
					_player->setPlayerPR(_player->getPlayerPR() + it.psycoR);

					_equip[_equipList] = _equipItemNum[i];
					EFFECTMANAGER->play("eq_effect", Vector2(1024, 550), 0, 0.7f);
					outMenu();
				}
			}
			break;
			}

			case 4:
			{itemObject it = _item->getItemInfo(L"¥Ÿ∏Æ", _equipItemNum[_eqSelectNum - 1]);
			if (PtInRect(&rc.getRect(), _ptMouse))
			{
				int x = 420;
				int y = 110;
				int d = 49;
				wstring Num1 = to_wstring(it.hp);
				D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num2 = to_wstring(it.atk);
				D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num3 = to_wstring(it.def);
				D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num4 = to_wstring(it.crt);
				D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num5 = to_wstring(it.fireR);
				D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num6 = to_wstring(it.iceR);
				D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num7 = to_wstring(it.electricR);
				D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
				wstring Num8 = to_wstring(it.psycoR);
				D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_inven->deleteItem(L"¥Ÿ∏Æ", _equipItemNum[i]);
					if (_equip[_equipList] != 99999)
					{
						it = _item->getItemInfo(L"¥Ÿ∏Æ", _equip[_equipList]);
						_inven->getItem(L"¥Ÿ∏Æ", _equip[_equipList]);
						_player->setPlayerMaxHP(_player->getPlayerMaxHP() - it.hp);
						_player->setPlayerAtk(_player->getPlayerAtk() - it.atk);
						_player->setPlayerDef(_player->getPlayerDef() - it.def);
						_player->setPlayerCri(_player->getPlayerCri() - it.crt);
						_player->setPlayerFR(_player->getPlayerFR() - it.fireR);
						_player->setPlayerIR(_player->getPlayerIR() - it.iceR);
						_player->setPlayerER(_player->getPlayerER() - it.electricR);
						_player->setPlayerPR(_player->getPlayerPR() - it.psycoR);
					}

					it = _item->getItemInfo(L"¥Ÿ∏Æ", _equipItemNum[i]);
					_player->setPlayerMaxHP(_player->getPlayerMaxHP() + it.hp);
					_player->setPlayerAtk(_player->getPlayerAtk() + it.atk);
					_player->setPlayerDef(_player->getPlayerDef() + it.def);
					_player->setPlayerCri(_player->getPlayerCri() + it.crt);
					_player->setPlayerFR(_player->getPlayerFR() + it.fireR);
					_player->setPlayerIR(_player->getPlayerIR() + it.iceR);
					_player->setPlayerER(_player->getPlayerER() + it.electricR);
					_player->setPlayerPR(_player->getPlayerPR() + it.psycoR);

					_equip[_equipList] = _equipItemNum[i];
					EFFECTMANAGER->play("eq_effect", Vector2(1072, 995),0,0.7f);
					outMenu();
				}
			}
			break;
			}

			}
		}
	}

	if (_eq || _eqSelect)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (_equip[i] != 99999)
			{
				switch (i)
				{
				case 0:
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(958, 155), 0, 0);
					break;
				case 1:
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(813, 465), 1, 0);
					break;

				case 2:
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1100, 465), 1, 0);
					break;
				case 3:
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(958, 482), 2, 0);
					break;
				case 4:
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1006, 927), 3, 0);
					break;
				}

			}
		}
	}

	if (_iv)
	{
		switch (_invenIndex)
		{
		case 0:
			IMAGEMANAGER->findImage("inven1")->render(Vector2(0, 0));
			if (_vIv.size() != NULL)
			{
				int count = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type == L"º“∏")
					{
						itemObject it;
						it = _item->getItemInfo(L"º“∏", _vIv[i].itemNum);

						IMAGEMANAGER->findImage("inven01")->render(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)));

						D2DRENDERER->RenderText(770 + 570 * (count % 2), 228 + 67 * (count / 2), it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						wstring Num = to_wstring(_vIv[i].count);
						D2DRENDERER->RenderText(1150 + 570 * (count % 2), 228 + 67 * (count / 2), Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

						floatRect rc;
						rc.update(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)), Vector2((float)IMAGEMANAGER->findImage("inven02")->getWidth(), (float)IMAGEMANAGER->findImage("inven02")->getHeight()), pivot::LEFTTOP);

						if (PtInRect(&rc.getRect(), _ptMouse))
						{
							IMAGEMANAGER->findImage("eq_ui")->render(Vector2(_ptMouse), 0.6f);
							D2DRENDERER->RenderText(_ptMouse.x + 60, _ptMouse.y +3, L"√º∑¬»∏∫π:", 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num = to_wstring(it.hp);
							D2DRENDERER->RenderText(_ptMouse.x + 230, _ptMouse.y +3 , Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

							if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
							{
								_inven->deleteItem(L"º“∏", _vIv[i].itemNum);
								_player->setPlayerHP(_player->getPlayerHP() + it.hp);
							}
							
						}

						count++;
					}
				}
			}
			break;
		case 1:
			IMAGEMANAGER->findImage("inven2")->render(Vector2(0, 0));

			if (_vIv.size() != NULL)
			{
				int count = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type == L"∆»")
					{
						itemObject it;
						it = _item->getItemInfo(L"∆»",_vIv[i].itemNum);

						IMAGEMANAGER->findImage("inven02")->render(Vector2(690 + 570 * (count % 2), 220 + 67 * (count /2)));
						
						D2DRENDERER->RenderText(770 + 570 * (count % 2), 228 + 67 * (count / 2), it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						wstring Num = to_wstring(_vIv[i].count);
						D2DRENDERER->RenderText(1150 + 570 * (count % 2), 228 + 67 * (count / 2), Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						
						floatRect rc;
						rc.update(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)), Vector2((float)IMAGEMANAGER->findImage("inven02")->getWidth(), (float)IMAGEMANAGER->findImage("inven02")->getHeight()), pivot::LEFTTOP);

						if (PtInRect(&rc.getRect(), _ptMouse))
						{
							int x = 420;
							int y = 110;
							int d = 49;
							wstring Num1 = to_wstring(it.hp);
							D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num2 = to_wstring(it.atk);
							D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num3 = to_wstring(it.def);
							D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num4 = to_wstring(it.crt);
							D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num5 = to_wstring(it.fireR);
							D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num6 = to_wstring(it.iceR);
							D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num7 = to_wstring(it.electricR);
							D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num8 = to_wstring(it.psycoR);
							D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						}

						

						count++;
					}
				}
			}
			break;
		case 2:
			IMAGEMANAGER->findImage("inven3")->render(Vector2(0, 0));
			if (_vIv.size() != NULL)
			{
				int count = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type == L"∏”∏Æ")
					{
						itemObject it;
						it = _item->getItemInfo(L"∏”∏Æ", _vIv[i].itemNum);

						IMAGEMANAGER->findImage("inven03")->render(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)));

						D2DRENDERER->RenderText(770 + 570 * (count % 2), 228 + 67 * (count / 2), it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						wstring Num = to_wstring(_vIv[i].count);
						D2DRENDERER->RenderText(1150 + 570 * (count % 2), 228 + 67 * (count / 2), Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						
						floatRect rc;
						rc.update(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)), Vector2((float)IMAGEMANAGER->findImage("inven02")->getWidth(), (float)IMAGEMANAGER->findImage("inven02")->getHeight()), pivot::LEFTTOP);

						if (PtInRect(&rc.getRect(), _ptMouse))
						{
							int x = 420;
							int y = 110;
							int d = 49;
							wstring Num1 = to_wstring(it.hp);
							D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num2 = to_wstring(it.atk);
							D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num3 = to_wstring(it.def);
							D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num4 = to_wstring(it.crt);
							D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num5 = to_wstring(it.fireR);
							D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num6 = to_wstring(it.iceR);
							D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num7 = to_wstring(it.electricR);
							D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num8 = to_wstring(it.psycoR);
							D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						}
						count++;
					}
				}
			}
			break;
		case 3:
			IMAGEMANAGER->findImage("inven4")->render(Vector2(0, 0));
			if (_vIv.size() != NULL)
			{
				int count = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type == L"∏ˆ≈Î")
					{
						itemObject it;
						it = _item->getItemInfo(L"∏ˆ≈Î", _vIv[i].itemNum);

						IMAGEMANAGER->findImage("inven04")->render(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)));

						D2DRENDERER->RenderText(770 + 570 * (count % 2), 228 + 67 * (count / 2), it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						wstring Num = to_wstring(_vIv[i].count);
						D2DRENDERER->RenderText(1150 + 570 * (count % 2), 228 + 67 * (count / 2), Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

						floatRect rc;
						rc.update(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)), Vector2((float)IMAGEMANAGER->findImage("inven02")->getWidth(), (float)IMAGEMANAGER->findImage("inven02")->getHeight()), pivot::LEFTTOP);

						if (PtInRect(&rc.getRect(), _ptMouse))
						{
							int x = 420;
							int y = 110;
							int d = 49;
							wstring Num1 = to_wstring(it.hp);
							D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num2 = to_wstring(it.atk);
							D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num3 = to_wstring(it.def);
							D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num4 = to_wstring(it.crt);
							D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num5 = to_wstring(it.fireR);
							D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num6 = to_wstring(it.iceR);
							D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num7 = to_wstring(it.electricR);
							D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num8 = to_wstring(it.psycoR);
							D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						}
						count++;
					}
				}
			}
			break;
		case 4:
			IMAGEMANAGER->findImage("inven5")->render(Vector2(0, 0));
			if (_vIv.size() != NULL)
			{
				int count = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type == L"¥Ÿ∏Æ")
					{
						itemObject it;
						it = _item->getItemInfo(L"¥Ÿ∏Æ", _vIv[i].itemNum);

						IMAGEMANAGER->findImage("inven05")->render(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)));

						D2DRENDERER->RenderText(770 + 570 * (count % 2), 228 + 67 * (count / 2), it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						wstring Num = to_wstring(_vIv[i].count);
						D2DRENDERER->RenderText(1150 + 570 * (count % 2), 228 + 67 * (count / 2), Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

						floatRect rc;
						rc.update(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)), Vector2((float)IMAGEMANAGER->findImage("inven02")->getWidth(), (float)IMAGEMANAGER->findImage("inven02")->getHeight()), pivot::LEFTTOP);

						if (PtInRect(&rc.getRect(), _ptMouse))
						{
							int x = 420;
							int y = 110;
							int d = 49;
							wstring Num1 = to_wstring(it.hp);
							D2DRENDERER->RenderText(x, y, Num1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num2 = to_wstring(it.atk);
							D2DRENDERER->RenderText(x, y + d, Num2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num3 = to_wstring(it.def);
							D2DRENDERER->RenderText(x, y + d * 2, Num3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num4 = to_wstring(it.crt);
							D2DRENDERER->RenderText(x, y + d * 3, Num4, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num5 = to_wstring(it.fireR);
							D2DRENDERER->RenderText(x, y + d * 4, Num5, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num6 = to_wstring(it.iceR);
							D2DRENDERER->RenderText(x, y + d * 5, Num6, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num7 = to_wstring(it.electricR);
							D2DRENDERER->RenderText(x, y + d * 6, Num7, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
							wstring Num8 = to_wstring(it.psycoR);
							D2DRENDERER->RenderText(x, y + d * 7, Num8, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						}
						count++;
					}
				}
			}
			break;
		case 5:
			IMAGEMANAGER->findImage("inven6")->render(Vector2(0, 0));
			if (_vIv.size() != NULL)
			{
				int count = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type == L"∞≈∑°")
					{
						itemObject it;
						it = _item->getItemInfo(L"∞≈∑°", _vIv[i].itemNum);

						IMAGEMANAGER->findImage("inven06")->render(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)));

						D2DRENDERER->RenderText(770 + 570 * (count % 2), 228 + 67 * (count / 2), it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						wstring Num = to_wstring(_vIv[i].count);
						D2DRENDERER->RenderText(1150 + 570 * (count % 2), 228 + 67 * (count / 2), Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");


						count++;
					}
				}
			}
			break;
		case 6:
			IMAGEMANAGER->findImage("inven7")->render(Vector2(0, 0));
			if (_vIv.size() != NULL)
			{
				int count = 0;
				for (int i = 0; i < _vIv.size(); ++i)
				{
					if (_vIv[i].type == L"¡ﬂø‰")
					{
						itemObject it;
						it = _item->getItemInfo(L"¡ﬂø‰", _vIv[i].itemNum);

						IMAGEMANAGER->findImage("inven07")->render(Vector2(690 + 570 * (count % 2), 220 + 67 * (count / 2)));

						D2DRENDERER->RenderText(770 + 570 * (count % 2), 228 + 67 * (count / 2), it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						wstring Num = to_wstring(_vIv[i].count);
						D2DRENDERER->RenderText(1150 + 570 * (count % 2), 228 + 67 * (count / 2), Num, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
						count++;
					}
				}
			}
			break;
		}
	}
		
	if (_sv)
	{
		IMAGEMANAGER->findImage("save")->render(Vector2(0, 0));

		for (int i = 0; i < 5; ++i)
		{
			//D2DRENDERER->DrawRotationFillRectangle(_saveSlot[i].rc, D2D1::ColorF::CadetBlue, 0);
			if (_saveSlot[i].isSaved)
			{
				IMAGEMANAGER->findImage("save slot")->render(Vector2(_saveSlot[i].rc.left, _saveSlot[i].rc.top));

				// µ∑
				D2DRENDERER->RenderText(_saveSlot[i].rc.left + 1240, _saveSlot[i].rc.top + 50, to_wstring(_saveSlot[i].credit), 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				// ∑π∫ß
				D2DRENDERER->RenderText(_saveSlot[i].rc.left + 585, _saveSlot[i].rc.top + 10, to_wstring(_saveSlot[i].level), 25, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				// ∏  ¿Ã∏ß
				wstring t = _saveSlot[i].map;
				if (_saveSlot[i].map == L"town") t = L"∏∂¿ª";
				else if (_saveSlot[i].map == L"puzzle") t = L"ºˆªÛ«— ƒ¡≈◊¿Ã≥ ";
				else if (_saveSlot[i].map == L"boss") t = L"µø±º(∫∏Ω∫ ∏ )";
				else if (_saveSlot[i].map == L"mountain") t = L"∞°¿ª¿« ∫ŒªÛ";
				D2DRENDERER->RenderText(_saveSlot[i].rc.left + 560, _saveSlot[i].rc.top + 87, t, 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

				// Ω√∞£
				int m = _saveSlot[i].time / 60;
				int s = _saveSlot[i].time % 60;

				char str[256];
				sprintf_s(str, "%02d : %02d", m, s);
				string ss;
				ss = str;

				wstring sstr;
				sstr.assign(ss.begin(), ss.end());

				D2DRENDERER->RenderText(_saveSlot[i].rc.left + 1240, _saveSlot[i].rc.top + 15, sstr, 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
			}
		}
	}
	if (_st)
	{
		IMAGEMANAGER->findImage("stat")->render(Vector2(0, 0));

		_hp = (float)_player->getPlayerHP() / (float)_player->getPlayerMaxHP() * 402;
		_exp = (float)_player->getPlayerEXP() / (float)_player->getPlayerNextEXP() * 402;

		_hpRC.update(Vector2(98, 365), Vector2(_hp, 13), pivot::LEFTTOP);
		_expRC.update(Vector2(98, 493), Vector2(_exp, 13), pivot::LEFTTOP);

		if (_hp > 50)
			D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::LawnGreen, 0, 45);
		else
			D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::Red, 0, 45);

		D2DRENDERER->SkewRectangle(_expRC, D2D1::ColorF::MediumPurple, 0, 45);


		wstring Num = to_wstring(_player->getPlayerEXP());
		D2DRENDERER->RenderText(220, 443, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		wstring w = L"/";
		D2DRENDERER->RenderText(315, 443, w, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerNextEXP());
		D2DRENDERER->RenderText(360, 443, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerHP());
		D2DRENDERER->RenderText(220, 315, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		D2DRENDERER->RenderText(315, 315, w, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerMaxHP());
		D2DRENDERER->RenderText(360, 315, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		D2DRENDERER->RenderText(400, 525, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerLEVEL());
		D2DRENDERER->RenderText(440, 195, Num, 50, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerAtk());
		D2DRENDERER->RenderText(400, 570, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerDef());
		D2DRENDERER->RenderText(400, 617, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerCri());
		D2DRENDERER->RenderText(400, 665, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		Num = to_wstring(_player->getPlayerFR());
		D2DRENDERER->RenderText(400, 725, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerIR());
		D2DRENDERER->RenderText(400, 770, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerER());
		D2DRENDERER->RenderText(400, 820, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		Num = to_wstring(_player->getPlayerPR());
		D2DRENDERER->RenderText(400, 865, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");


		for (int i = 0; i < _player->getPlayerSP(); ++i)
		{
			floatRect rc;
			rc.update(Vector2(117 + 17 * i, 428), Vector2(10, 15), pivot::LEFTTOP);
			D2DRENDERER->DrawRotationFillRectangle(rc, D2D1::ColorF::DeepSkyBlue, 0);
		}

		Num = to_wstring(_inven->getMoney());
		D2DRENDERER->RenderText(120, 980, Num, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		// Ω√∞£
		char str[256];
		sprintf_s(str, "%02d : %02d", _time / 60, _time % 60);
		string ss;
		ss = str;

		wstring sstr;
		sstr.assign(ss.begin(), ss.end());

		Num = to_wstring(_time);
		D2DRENDERER->RenderText(155, 1025, sstr, 40, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		for (int i = 0; i < 5; ++i)
		{
			if (_equip[i] != 99999)
			{
				switch (i)
				{
				case 0:
				{
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 275), 0, 0);

					itemObject it = _item->getItemInfo(L"∏”∏Æ", _equip[0]);
					D2DRENDERER->RenderText(1380, 248, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					break;
				}
				case 1:
				{
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 363), 1, 0);
					itemObject it = _item->getItemInfo(L"∆»", _equip[1]);
					D2DRENDERER->RenderText(1380, 336, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					break;
				}
				case 2:
				{
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 450), 1, 0);
					itemObject it = _item->getItemInfo(L"∆»", _equip[2]);
					D2DRENDERER->RenderText(1380, 423, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					break;
				}
				case 3:
				{
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 537), 2, 0);
					itemObject it = _item->getItemInfo(L"∏ˆ≈Î", _equip[3]);
					D2DRENDERER->RenderText(1380, 510, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					break;
				}
				case 4:
				{
					IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1340, 625), 3, 0);
					itemObject it = _item->getItemInfo(L"¥Ÿ∏Æ", _equip[4]);
					D2DRENDERER->RenderText(1380, 597, it.itemName, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
					break;
				}
				}

			}
		}
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

	SOUNDMANAGER->play("button ok");
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

	SOUNDMANAGER->play("button ok");
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

	SOUNDMANAGER->play("button ok");
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

	SOUNDMANAGER->play("button ok");
}
void tabUI::outMenu()
{
	SOUNDMANAGER->play("button cancel");
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
			SOUNDMANAGER->play("button hover");
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

void tabUI::saveData(int num)
{
	HANDLE file;
	DWORD write;
	string fileName = "data/crosscode" + to_string(num) + ".data";

	file = CreateFile(fileName.c_str(), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// ================== «√∑π¿ÃæÓ ¡§∫∏ ¿˙¿Â =====================
	int hp = _player->getPlayerHP();		//«√∑π¿ÃæÓ √º∑¬
	int maxHp = _player->getPlayerMaxHP();	//«√∑π¿ÃæÓ ∏∆Ω∫ √º∑¬
	int level = _player->getPlayerLEVEL();	// «√∑π¿ÃæÓ ∑π∫ß
	int exp = _player->getPlayerEXP();		//«√∑π¿ÃæÓ ∞Ê«Ëƒ°
	int nextExp = _player->getPlayerNextEXP();//∑π∫ßæ˜ « ø‰ ∞Ê«Ëƒ°
	int atk = _player->getPlayerAtk();		//«√∑π¿ÃæÓ ∞¯∞›∑¬
	int def = _player->getPlayerDef();		//«√∑π¿ÃæÓ πÊæÓ∑¬
	int cri = _player->getPlayerCri();		//«√∑π¿ÃæÓ ≈©∏Æ∆ºƒ√
	int fr = _player->getPlayerFR();		//«√∑π¿ÃæÓ ∫“ ¿˙«◊∑¬
	int ir = _player->getPlayerIR();		//«√∑π¿ÃæÓ æÛ¿Ω ¿˙«◊∑¬
	int er = _player->getPlayerER();		//«√∑π¿ÃæÓ ¿¸±‚ ¿˙«◊∑¬
	int pr = _player->getPlayerPR();		//«√∑π¿ÃæÓ ∆ƒµø ¿˙«◊∑¬
	wstring sc = SCENEMANAGER->getCurrentSceneName();	// «ˆ¿Á ¿ßƒ°
	
	int sn = 0;
	if (sc == L"town") sn = 0;
	else if (sc == L"puzzle") sn = 1;
	else if (sc == L"mountain") sn = 2;
	else if (sc == L"boss") sn = 3;

	WriteFile(file, &hp, sizeof(int), &write, NULL);
	WriteFile(file, &maxHp, sizeof(int), &write, NULL);
	WriteFile(file, &level, sizeof(int), &write, NULL);
	WriteFile(file, &exp, sizeof(int), &write, NULL);
	WriteFile(file, &nextExp, sizeof(int), &write, NULL);
	WriteFile(file, &atk, sizeof(int), &write, NULL);
	WriteFile(file, &def, sizeof(int), &write, NULL);
	WriteFile(file, &cri, sizeof(int), &write, NULL);
	WriteFile(file, &fr, sizeof(int), &write, NULL);
	WriteFile(file, &ir, sizeof(int), &write, NULL);
	WriteFile(file, &er, sizeof(int), &write, NULL);
	WriteFile(file, &pr, sizeof(int), &write, NULL);
	WriteFile(file, &sn, sizeof(int), &write, NULL);
	// =========================================================

	// ================== ¿Ã∫•∆Æ ¡§∫∏ ¿˙¿Â =====================
	bool first = EVENTMANAGER->getFirstEvent();			// ≈∏øÓ √π π¯¬∞ ¿Ã∫•∆Æ
	bool second = EVENTMANAGER->getSecondEvent();		// ≈∏øÓ µŒ π¯¬∞ ¿Ã∫•∆Æ
	bool puzzle = EVENTMANAGER->getPuzzleEvent();		// ∆€¡Ò ≈¨∏ÆæÓ ¿Ã∫•∆Æ
	bool bossf = EVENTMANAGER->getBossFirstEvent();		// ∫∏Ω∫ √π π¯¬∞ ¿Ã∫•∆Æ
	bool bosss = EVENTMANAGER->getBossSecondEvent();	// ∫∏Ω∫ µŒ π¯¬∞ ¿Ã∫•∆Æ

	WriteFile(file, &first, sizeof(bool), &write, NULL);
	WriteFile(file, &second, sizeof(bool), &write, NULL);
	WriteFile(file, &puzzle, sizeof(bool), &write, NULL);
	WriteFile(file, &bossf, sizeof(bool), &write, NULL);
	WriteFile(file, &bosss, sizeof(bool), &write, NULL);
	// =======================================================

	// ================== ¿Œ∫•≈‰∏Æ ¿˙¿Â =====================
	
	int ivSize = _vIv.size();	// ¿Œ∫•≈‰∏Æ ∫§≈Õ¥¬ ªÁ¿Ã¡Ó ¿˙¿Â « ø‰

	WriteFile(file, &ivSize, sizeof(int), &write, NULL);

	for (int i = 0; i < _vIv.size(); ++i)
	{
		//¿Œ∫•≈‰∏Æ ∫§≈Õ
		//wstring type = _vIv[i].type;		//æ∆¿Ã≈€ ¡æ∑˘ wstring
		//int num = _vIv[i].itemNum;	//æ∆¿Ã≈€ π¯»£ int
		//int count = _vIv[i].count;		//æ∆¿Ã≈€ ∞πºˆ int

		//WriteFile(file, &type, 128, &write, NULL);
		//WriteFile(file, &num, sizeof(int), &write, NULL);
		//WriteFile(file, &count, sizeof(int), &write, NULL);

		WriteFile(file, &_vIv[i], sizeof(invenObject), &write, NULL);
	}
	// =======================================================

	// ================== ¿Â∫Ò ¿˙¿Â =====================
	//¿Â∫Ò πËø≠ 1.∏”∏Æ 2.∆» 3.∆» 4.∏ˆ≈Î 5.¥Ÿ∏Æ
	for (int i = 0; i < 5; ++i)
	{
		int eq = _equip[i];
		WriteFile(file, &eq, sizeof(int), &write, NULL);
	}
	// =======================================================

	// ================== ±‚≈∏ ¿˙¿Â =====================
	//µ∑
	int money = _inven->getMoney();
	WriteFile(file, &money, sizeof(int), &write, NULL);

	//Ω√∞£
	_time;
	WriteFile(file, &_time, sizeof(int), &write, NULL);
	// =======================================================

	CloseHandle(file);
}

void tabUI::loadData()
{
	
	for (int i = 4; i >= 0; --i)
	{
		HANDLE file = CreateFile(_saveSlot[i].fileName.c_str(), GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		// ∏∏æ‡ø° ¡§∫∏∞° ¿÷¥Ÿ∏È? πﬁæ∆øÕº≠ ¿˙¿Â »ƒ render √≥∏Æ
		if (file != INVALID_HANDLE_VALUE)
		{
			DWORD read;

			int hp, maxHp, level, exp, nextExp, atk, def, cri, fr, ir, er, pr, sn;

			ReadFile(file, &hp, sizeof(int), &read, NULL);
			ReadFile(file, &maxHp, sizeof(int), &read, NULL);
			ReadFile(file, &level, sizeof(int), &read, NULL);
			ReadFile(file, &exp, sizeof(int), &read, NULL);
			ReadFile(file, &nextExp, sizeof(int), &read, NULL);
			ReadFile(file, &atk, sizeof(int), &read, NULL);
			ReadFile(file, &def, sizeof(int), &read, NULL);
			ReadFile(file, &cri, sizeof(int), &read, NULL);
			ReadFile(file, &fr, sizeof(int), &read, NULL);
			ReadFile(file, &ir, sizeof(int), &read, NULL);
			ReadFile(file, &er, sizeof(int), &read, NULL);
			ReadFile(file, &pr, sizeof(int), &read, NULL);
			ReadFile(file, &sn, sizeof(int), &read, NULL);

			bool first, second, puzzle, bossf, bosss;
			ReadFile(file, &first, sizeof(bool), &read, NULL);
			ReadFile(file, &second, sizeof(bool), &read, NULL);
			ReadFile(file, &puzzle, sizeof(bool), &read, NULL);
			ReadFile(file, &bossf, sizeof(bool), &read, NULL);
			ReadFile(file, &bosss, sizeof(bool), &read, NULL);

			int ivSize;
			ReadFile(file, &ivSize, sizeof(int), &read, NULL);

			for (int i = 0; i < ivSize; ++i)
			{
				//wstring type;
				//int num, count;

				//ReadFile(file, &type, 128, &read, NULL);
				//ReadFile(file, &num, sizeof(int), &read, NULL);
				//ReadFile(file, &count, sizeof(int), &read, NULL);

				invenObject o;
				ReadFile(file, &o, sizeof(invenObject), &read, NULL);
			}

			for (int i = 0; i < 5; ++i)
			{
				int eq;
				ReadFile(file, &eq, sizeof(int), &read, NULL);
			}

			int money, time;
			ReadFile(file, &money, sizeof(int), &read, NULL);
			ReadFile(file, &time, sizeof(int), &read, NULL);

			_saveSlot[i].level = level;
			_saveSlot[i].time = time;
			_saveSlot[i].credit = money;

			wstring sc = L"town";
			if (sn == 0)  sc = L"town";
			else if (sn == 1)  sc = L"puzzle";
			else if (sn == 2)  sc = L"mountain";
			else if (sn == 3)  sc = L"boss";
			_saveSlot[i].map = sc;
			_saveSlot[i].isSaved = true;
		}
		else
			_saveSlot[i].isSaved = false;

		CloseHandle(file);
	}

	for (int i = 0; i < 5; ++i)
	{
		if (!_saveSlot[i].isSaved)
		{
			if(i == 0)
				_saveSlot[i].rc.update(Vector2(203, 215 + i * 135), Vector2(IMAGEMANAGER->findImage("save slot")->getSize()), pivot::LEFTTOP);
			else
				_saveSlot[i].rc.update(Vector2(203, (int)_saveSlot[i - 1].rc.bottom), Vector2(0, 0), pivot::LEFTTOP);
		}
		else {
			if (i == 0)
				_saveSlot[i].rc.update(Vector2(203, 215), Vector2(IMAGEMANAGER->findImage("save slot")->getSize()), pivot::LEFTTOP);
			else
				_saveSlot[i].rc.update(Vector2(203, (int)_saveSlot[i - 1].rc.bottom), Vector2(IMAGEMANAGER->findImage("save slot")->getSize()), pivot::LEFTTOP);
		}
	}
}
