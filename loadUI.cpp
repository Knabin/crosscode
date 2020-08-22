#include "stdafx.h"
#include "loadUI.h"
#include "inventory.h"
#include "tabUI.h"
#include "player.h"
#include "inventory.h"
#include "iEvent.h"

HRESULT loadUI::init()
{
	_name = "loadUI";
	IMAGEMANAGER->addImage("load back", L"images/menu/load.png");

	OBJECTMANAGER->addObject(objectType::UI, this);
	this->setIsActive(false);

	_exit = RectMakePivot(Vector2(1700, 0), Vector2(220, 70), pivot::LEFTTOP);

	for (int i = 0; i < 5; ++i)
	{
		//200 216
		_slot[i].rc.update(Vector2(203, 215 + i * 135), Vector2(IMAGEMANAGER->findImage("save slot")->getSize()), pivot::LEFTTOP);
		_slot[i].fileName = "data/crosscode" + to_string(i) + ".data";
	}
	loadData();

	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	return S_OK;
}

void loadUI::release()
{
	this->setIsAlive(false);
}

void loadUI::update()
{
	if (SCENEMANAGER->getCurrentSceneName() != L"title")
		this->setIsActive(false);

	if (PtInRect(&_exit.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			OBJECTMANAGER->findObject(objectType::UI, "start")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "continue")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "maptool")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "option")->setIsActive(true);
			OBJECTMANAGER->findObject(objectType::UI, "exit")->setIsActive(true);

			SOUNDMANAGER->play("button cancel");
			this->setIsActive(false);
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		if (PtInRect(&_slot[i].rc.getRect(), _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_slot[i].isSaved)
				{
					load(i);
					SOUNDMANAGER->play("button ok");
					break;
				}
			}
		}
	}
}

void loadUI::render()
{
	IMAGEMANAGER->findImage("load back")->render(Vector2(0, 0));
	
	for (int i = 0; i < 5; ++i)
	{
		//D2DRENDERER->DrawRotationFillRectangle(_saveSlot[i].rc, D2D1::ColorF::CadetBlue, 0);
		if (_slot[i].isSaved)
		{
			IMAGEMANAGER->findImage("save slot")->render(Vector2(_slot[i].rc.left, _slot[i].rc.top));

			// µ·
			D2DRENDERER->RenderText(_slot[i].rc.left + 1240, _slot[i].rc.top + 50, to_wstring(_slot[i].credit), 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

			// ·¹º§
			D2DRENDERER->RenderText(_slot[i].rc.left + 585, _slot[i].rc.top + 10, to_wstring(_slot[i].level), 25, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

			// ¸Ê ÀÌ¸§
			wstring t = _slot[i].map;
			if (_slot[i].map == L"town") t = L"¸¶À»";
			else if (_slot[i].map == L"puzzle") t = L"¼ö»óÇÑ ÄÁÅ×ÀÌ³Ê";
			else if (_slot[i].map == L"boss") t = L"µ¿±¼(º¸½º ¸Ê)";
			else if (_slot[i].map == L"mountain") t = L"°¡À»ÀÇ ºÎ»ó";
			D2DRENDERER->RenderText(_slot[i].rc.left + 560, _slot[i].rc.top + 87, t, 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

			// ½Ã°£
			int m = _slot[i].time / 60;
			int s = _slot[i].time % 60;

			char str[256];
			sprintf_s(str, "%02d : %02d", m, s);
			string ss;
			ss = str;

			wstring sstr;
			sstr.assign(ss.begin(), ss.end());

			D2DRENDERER->RenderText(_slot[i].rc.left + 1240, _slot[i].rc.top + 15, sstr, 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
		}
	}
}

void loadUI::loadData()
{
	for (int i = 4; i >= 0; --i)
	{
		HANDLE file = CreateFile(_slot[i].fileName.c_str(), GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		// ¸¸¾à¿¡ Á¤º¸°¡ ÀÖ´Ù¸é? ¹Þ¾Æ¿Í¼­ ÀúÀå ÈÄ render Ã³¸®
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

			_slot[i].level = level;
			_slot[i].time = time;
			_slot[i].credit = money;

			wstring sc = L"town";
			if (sn == 0) sc = L"town";
			else if (sn == 1) sc = L"puzzle";
			else if (sn == 2) sc = L"mountain";
			else if (sn == 3) sc = L"boss";

			_slot[i].map = sc;
			_slot[i].isSaved = true;
		}
		else
			_slot[i].isSaved = false;

		CloseHandle(file);
	}

	for (int i = 0; i < 5; ++i)
	{
		if (!_slot[i].isSaved)
		{
			if (i == 0)
				_slot[i].rc.update(Vector2(203, 215), Vector2(0, 0), pivot::LEFTTOP);
			else
				_slot[i].rc.update(Vector2(203, (int)_slot[i - 1].rc.bottom), Vector2(0, 0), pivot::LEFTTOP);
		}
		else {
			if (i == 0)
				_slot[i].rc.update(Vector2(203, 215), Vector2(IMAGEMANAGER->findImage("save slot")->getSize()), pivot::LEFTTOP);
			else
				_slot[i].rc.update(Vector2(203, (int)_slot[i - 1].rc.bottom), Vector2(IMAGEMANAGER->findImage("save slot")->getSize()), pivot::LEFTTOP);
		}
	}
}

void loadUI::load(int num)
{
		HANDLE file = CreateFile(_slot[num].fileName.c_str(), GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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

		_player->setPlayerHP(hp);
		_player->setPlayerMaxHP(maxHp);
		_player->setPlayerLEVEL(level);
		_player->setPlayerEXP(exp);
		_player->setPlayerNextEXP(nextExp);
		_player->setPlayerAtk(atk);
		_player->setPlayerDef(def);
		_player->setPlayerCri(cri);
		_player->setPlayerFR(fr);
		_player->setPlayerIR(ir);
		_player->setPlayerER(er);
		_player->setPlayerPR(pr);

		bool first, second, puzzle, bossf, bosss;
		ReadFile(file, &first, sizeof(bool), &read, NULL);
		ReadFile(file, &second, sizeof(bool), &read, NULL);
		ReadFile(file, &puzzle, sizeof(bool), &read, NULL);
		ReadFile(file, &bossf, sizeof(bool), &read, NULL);
		ReadFile(file, &bosss, sizeof(bool), &read, NULL);

		EVENTMANAGER->setFirstEvent(first);
		EVENTMANAGER->setSecondEvent(second);
		EVENTMANAGER->setPuzzleEvent(puzzle);
		EVENTMANAGER->setBossFirstEvent(bossf);
		EVENTMANAGER->setBossSecondEvent(bosss);

		int ivSize;
		ReadFile(file, &ivSize, sizeof(int), &read, NULL);

		for (int i = 0; i < ivSize; ++i)
		{
			wstring type;
			int num, count;

			ReadFile(file, &type, sizeof(type), &read, NULL);
			ReadFile(file, &num, sizeof(int), &read, NULL);
			ReadFile(file, &count, sizeof(int), &read, NULL);

			for (int j = 0; j < count; ++j)
				_inv->getItem(type, num);
		}

		for (int i = 0; i < 5; ++i)
		{
			int eq;
			ReadFile(file, &eq, sizeof(int), &read, NULL);
			_tab->setEq(i, eq);
		}

		int money, time;
		ReadFile(file, &money, sizeof(int), &read, NULL);
		ReadFile(file, &time, sizeof(int), &read, NULL);

		_inv->setInvenMoney(money);
		_tab->setTime(time);

		CloseHandle(file);

		Vector2 location;

		wstring sc = L"town";
		if (sn == 0) sc = L"town";
		else if (sn == 1) sc = L"puzzle";
		else if (sn == 2) sc = L"mountain";
		else if (sn == 3) sc = L"boss";

		if (sc == L"town")
			location = (Vector2(36 * 48, 47 * 48));
		else if (sc == L"mountain")
			location = Vector2((float)76 * 48, 34.5f * 48);
		else if (sc == L"puzzle")
			location = Vector2(9 * 48, 33 * 48);
		else
			location = Vector2(1070, 1850);

		SOUNDMANAGER->stopAll("");
		iMoveScene* e = new iMoveScene(sc, location);
		EVENTMANAGER->addEvent(e);
}
