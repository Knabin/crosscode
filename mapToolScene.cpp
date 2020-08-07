#include "stdafx.h"
#include "mapToolScene.h"
#include "button.h"
#include <commdlg.h>

HRESULT mapToolScene::init()
{
	_mode = NOWMODE::NONE;

	_nowIndexX = _changeSizeX = 9;
	_nowIndexY = _changeSizeY = 9;

	_sampleStartX = _sampleStartY = _sampleEndX = _sampleEndY = -1;
	_drawStartX = _drawStartY = _drawEndX = _drawEndY = -1;

	_isStayKeyDown = false;

	for (int i = 0; i < MAXTILEY; ++i)
	{
		vector<tile *> v;
		for (int j = 0; j < MAXTILEX; ++j)
		{
			tile * t = new tile();
			t->setTileRc(j * SIZE, i * SIZE);
			v.push_back(t);
		}
		_vTiles.push_back(v);
	}

	_cameraControl = new mapCamera;
	_cameraControl->getRect().set(0, 0, 10, 10);
	_cameraControl->setX(WINSIZEX / 2);
	_cameraControl->setY(WINSIZEY / 2);

	CAMERA->changeTarget(_cameraControl);
	CAMERA->setMapSize(SIZE * MAXTILEX, SIZE * MAXTILEY);

	IMAGEMANAGER->addFrameImage("saveload", "images/buttons_saveload.bmp", 132, 126, 1, 2, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("edit", "images/buttons_edit.bmp", 72, 269, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("edit ui", "images/ui_edit.bmp", 600, 850, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("exit", "images/buttons_editexit.bmp", 66, 62, 1, 1, true, RGB(255, 0, 255));

	button* save = new button();
	save->init("saveload", WINSIZEX / 2 - 100, 66, 0, 0, bind(&mapToolScene::saveMap, this));
	save->setName("save button");

	button* load = new button();
	load->init("saveload", WINSIZEX / 2 + 100, 66, 0, 1, bind(&mapToolScene::loadMap, this));
	load->setName("load button");

	button* edit = new button();
	edit->init("edit", WINSIZEX - 36, WINSIZEY / 2, 0, 0, bind(&mapToolScene::startEdit, this));
	edit->setName("edit button");

	OBJECTMANAGER->addObject(objectType::UI, save);
	OBJECTMANAGER->addObject(objectType::UI, load);
	OBJECTMANAGER->addObject(objectType::UI, edit);

	_editUi = new mapUi();
	_editUi->init();
	_editUi->setName("edit ui");
	_editUi->setIsActive(false);

	OBJECTMANAGER->addObject(objectType::UI, _editUi);

	button* exit = new button();
	exit->init("exit", WINSIZEX - 33, _editUi->getRect().top + 31, 0, 0, bind(&mapToolScene::endEdit, this));
	exit->setName("exit button");
	exit->setIsActive(false);

	OBJECTMANAGER->addObject(objectType::UI, exit);

	for (int i = 0; i < SAMPLENUMY; ++i)
	{
		for (int j = 0; j < SAMPLENUMX; ++j)
		{
			_sampleTiles[i][j].setTerrainX(j);
			_sampleTiles[i][j].setTerrainY(i);
			_sampleTiles[i][j].getRect().set(0, 0, SAMPLESIZE, SAMPLESIZE);
			_sampleTiles[i][j].getRect().setLeftTop(_editUi->getSampleRc().left + SAMPLESIZE * j,
				_editUi->getSampleRc().top + SAMPLESIZE * i);
		}
	}


	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{
	_ptMouseAbs.x = _ptMouse.x + CAMERA->getRect().left;
	_ptMouseAbs.y = _ptMouse.y + CAMERA->getRect().top;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || _ptMouse.x < 100)
	{
		_cameraControl->move(-3.f, 0);
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || (_ptMouse.x > WINSIZEX - 100 && !PtInRect(&_editUi->getSampleRc().getRect(), _ptMouse)))
	{
		_cameraControl->move(3.f, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) || _ptMouse.y < 100)
	{
		_cameraControl->move(0, -3.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || _ptMouse.y > WINSIZEY - 100)
	{
		_cameraControl->move(0, 3.f);
	}

	switch (_mode)
	{
	case NOWMODE::NONE:
		// 최하단 우측 RECT를 클릭하면 맵 사이즈 변경 모드로 전환한다.
		if (PtInRect(&_vTiles[_nowIndexY][_nowIndexX]->getRect().getRect(), _ptMouseAbs))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_mode = NOWMODE::MAPSIZE;
			}
		}
		break;
	case NOWMODE::MAPSIZE:
		// 맵 사이즈 변경 모드에서는 꾹 눌러서 이동하는 대로 화면에 보여질 RECT의 개수를 결정한다.
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < MAXTILEY; ++i)
			{
				for (int j = 0; j < MAXTILEX; ++j)
				{
					if (!_vTiles[i][j]->canView()) continue;
					if (PtInRect(&_vTiles[i][j]->getRect().getRect(), _ptMouseAbs))
					{
						_changeSizeX = j;
						_changeSizeY = i;
						break;
					}
				}
			}
		}
		// 마우스 좌클릭을 끝냈을 때 맵을 고정하고 기본 모드로 전환한다.
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_nowIndexX = _changeSizeX > MAXTILEX - 1 ? MAXTILEX - 1 : _changeSizeX;
			_nowIndexY = _changeSizeY > MAXTILEY - 1 ? MAXTILEY - 1 : _changeSizeY;
			_mode = NOWMODE::NONE;
		}
		break;
	case NOWMODE::EDIT:
		// 현재 상태가 지형 변경일 경우
		if (_editUi->getEditMode() == EDITMODE::TERRAIN)
		{
			if (PtInRect(&_editUi->getSampleRc().getRect(), _ptMouse))
			{
				for (int i = 0; i < SAMPLENUMY; ++i)
				{
					for (int j = 0; j < SAMPLENUMX; ++j)
					{
						if (PtInRect(&_sampleTiles[i][j].getRect().getRect(), _ptMouse))
						{
							if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
							{
								_editUi->setPenMode(PENMODE::PLUS);
								_drawStartX = _drawStartY = -1;
								_sampleStartX = _sampleEndX = j;
								_sampleStartY = _sampleEndY = i;
							}
							if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
							{
								_sampleEndX = j;
								_sampleEndY = i;
							}
							if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
							{
								_sampleEndX = j;
								_sampleEndY = i;
							}
						}
					}
				}
				if (_sampleStartX > _sampleEndX)
					swap(_sampleStartX, _sampleEndX);
				if (_sampleStartY > _sampleEndY)
					swap(_sampleStartY, _sampleEndY);
				_sampleViewRc.set(0, 0, (_sampleEndX - _sampleStartX + 1) * SAMPLESIZE, (_sampleEndY - _sampleStartY + 1) * SAMPLESIZE);
				_sampleViewRc.setLeftTop(_sampleTiles[_sampleStartY][_sampleStartX].getRect().left, _sampleTiles[_sampleStartY][_sampleStartX].getRect().top);
				_editUi->setSampleViewRc(_sampleViewRc);
			}
			else
			{
				bool b = false;
				for (int i = 0; i <= _nowIndexY; ++i)
				{
					for (int j = 0; j <= _nowIndexX; ++j)
					{
						if (!_vTiles[i][j]->canView()) continue;
						if (PtInRect(&_vTiles[i][j]->getRect().getRect(), _ptMouseAbs))
						{
							if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
							{
								_editUi->setPenMode(PENMODE::PLUS);
								_drawStartX = _drawEndX = j;
								_drawStartY = _drawEndY = i;

								if (_sampleStartX == _sampleEndX && _sampleStartY == _sampleEndY)
									_isStayKeyDown = true;
							}
							if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
							{
								if (_sampleStartX != _sampleEndX || _sampleStartY != _sampleEndY)
								{
									_drawStartX = _drawEndX = j;
									_drawStartY = _drawEndY = i;
								}
								else
								{
									_drawEndX = j;
									_drawEndY = i;
								}
							}
							if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
							{
								if (_sampleStartX == _sampleEndX && _sampleStartY == _sampleEndY)
								{
									_drawEndX = j;
									_drawEndY = i;
									_isStayKeyDown = false;
									b = true;

									if (_drawStartX > _drawEndX)
										swap(_drawStartX, _drawEndX);
									if (_drawStartY > _drawEndY)
										swap(_drawStartY, _drawEndY);
								}
							}
						}
					}
				}
				if (_drawStartX == -1 && _drawStartY == -1) break;

				if (_editUi->getPenMode() == PENMODE::MINUS) _sampleStartX = _sampleStartY = _sampleEndX = _sampleEndY = -1;

				if (_sampleStartX == _sampleEndX && _sampleStartY == _sampleEndY)
				{
					if (b)
					{
						for (int i = 0; i <= _drawEndY - _drawStartY; ++i)
						{
							for (int j = 0; j <= _drawEndX - _drawStartX; ++j)
							{
								_vTiles[_drawStartY + i][_drawStartX + j]->setTerrainX(_sampleStartX);
								_vTiles[_drawStartY + i][_drawStartX + j]->setTerrainY(_sampleStartY);
							}
						}
						_isStayKeyDown = false;
					}
				}
				else
				{
					for (int i = 0; i <= _sampleEndY - _sampleStartY; ++i)
					{
						for (int j = 0; j <= _sampleEndX - _sampleStartX; ++j)
						{
							_vTiles[_drawStartY + i][_drawStartX + j]->setTerrainX(_sampleStartX + j);
							_vTiles[_drawStartY + i][_drawStartX + j]->setTerrainY(_sampleStartY + i);
							if (_drawStartX + j + 1 > _nowIndexX) break;
						}
						if (_drawStartY + i + 1 > _nowIndexY) break;
					}
				}
			}
		}
		// 현재 상태가 타입(타일 오더) 변경일 경우
		else if (_editUi->getEditMode() == EDITMODE::TYPE)
		{
			for (int i = 0; i <= _nowIndexY; ++i)
			{
				for (int j = 0; j <= _nowIndexX; ++j)
				{
					if (PtInRect(&_vTiles[i][j]->getRect().getRect(), _ptMouseAbs))
					{
						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
						{
							_drawStartX = _drawEndX = j;
							_drawStartY = _drawEndY = i;
						}
						if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
						{
								_drawEndX = j;
								_drawEndY = i;
						}
						if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
						{
							_drawEndX = j;
							_drawEndY = i;

							if (_drawStartX > _drawEndX)
								swap(_drawStartX, _drawEndX);
							if (_drawStartY > _drawEndY)
								swap(_drawStartY, _drawEndY);
						}
					}
				}
			}

			if (_drawStartX == -1 || _drawStartY == -1) break;

			ORDER type = _editUi->getTileType();
			if (_editUi->getPenMode() == PENMODE::MINUS) type = ORDER::ONE;

			if (_drawStartX != -1 && _drawStartY != -1)
			{
				_vTiles[_drawStartY][_drawStartX]->setOrder(type);
			}
		}
		break;
	}
}

void mapToolScene::render()
{
	//_tileViewRc.render(getMemDC());
	char str[20];
	switch (_mode)
	{
	case NOWMODE::NONE:
		for (int i = 0; i <= _nowIndexY; ++i)
		{
			for (int j = 0; j <= _nowIndexX; ++j)
			{
				if (!_vTiles[i][j]->canView()) continue;
				
				if (_vTiles[i][j]->getTerrainX() != -1) 
					IMAGEMANAGER->findImage("terrain b")->frameRender(getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
				else 
					_vTiles[i][j]->getRect().render(getMemDC());
				sprintf_s(str, "(%d,%d)", j + 1, i + 1);
				TextOut(getMemDC(), _vTiles[i][j]->getRect().left + 2, _vTiles[i][j]->getRect().top + 2, str, strlen(str));
			}
		}
		break;
	case NOWMODE::EDIT:
	{
		int tempX = -1;
		int tempY = -1;
		for (int i = 0; i <= _nowIndexY; ++i)
		{
			for (int j = 0; j <= _nowIndexX; ++j)
			{
				if (!_vTiles[i][j]->canView()) continue;
				if (_vTiles[i][j]->getTerrainX() != -1 || _vTiles[i][j]->getTerrainY() != -1) 
					IMAGEMANAGER->findImage("terrain b")->frameRender(getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
				if (PtInRect(&_vTiles[i][j]->getRect().getRect(), _ptMouseAbs))
				{
					tempX = j;
					tempY = i;
				}
				if(_editUi->getEditMode() == EDITMODE::TYPE)
					IMAGEMANAGER->findImage("tile type")->frameRender(getMemDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, 0, _vTiles[i][j]->getOrderIndex());

				sprintf_s(str, "(%d,%d)", j + 1, i + 1);
				TextOut(getMemDC(), _vTiles[i][j]->getRect().left + 2, _vTiles[i][j]->getRect().top + 2, str, strlen(str));
			}
		}

		if (_editUi->getEditMode() == EDITMODE::TERRAIN)
		{
			if (!_isStayKeyDown)
			{
				if (tempX == -1 || tempY == -1) break;

				for (int i = 0; i <= _sampleEndY - _sampleStartY; ++i)
				{
					for (int j = 0; j <= _sampleEndX - _sampleStartX; ++j)
					{
						if (_editUi->getPenMode() == PENMODE::PLUS)
							IMAGEMANAGER->findImage("terrain b")->alphaFrameRender(getMemDC(), _vTiles[tempY + i][tempX + j]->getRect().left, _vTiles[tempY + i][tempX + j]->getRect().top, _sampleStartX + j, _sampleStartY + i, 150);
						if (tempX + j + 1 > _nowIndexX) break;
					}
					if (tempY + i + 1 > _nowIndexY) break;
				}
			}
			else
			{
				if (_drawStartX == -1 && _drawStartY == -1) break;

				int drawX = _drawStartX;
				int drawY = _drawStartY;

				if (_drawStartX > _drawEndX) drawX = _drawEndX;
				if (_drawStartY > _drawEndY) drawY = _drawEndY;

				for (int i = 0; i <= abs(_drawEndY - _drawStartY); ++i)
				{
					for (int j = 0; j <= abs(_drawEndX - _drawStartX); ++j)
					{
						if (_editUi->getPenMode() == PENMODE::PLUS)
							IMAGEMANAGER->findImage("terrain b")->alphaFrameRender(getMemDC(), _vTiles[drawY + i][drawX + j]->getRect().left, _vTiles[drawY + i][drawX + j]->getRect().top, _sampleStartX, _sampleStartY, 150);
						else
							IMAGEMANAGER->findImage("tile null")->alphaRender(getMemDC(), _vTiles[drawY + i][drawX + j]->getRect().left, _vTiles[drawY + i][drawX + j]->getRect().top, 150);
						if (drawX + j + 1 > _nowIndexX) break;
					}
					if (drawY + i + 1 > _nowIndexY) break;
				}
			}
		}
	}
		break;

	case NOWMODE::MAPSIZE:
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

		for (int i = 0; i <= _changeSizeY; ++i)
		{
			for (int j = 0; j <= _changeSizeX; ++j)
			{
				if (!_vTiles[i][j]->canView()) continue;
				_vTiles[i][j]->getRect().render(getMemDC());
				sprintf_s(str, "(%d,%d)", j + 1, i + 1);
				TextOut(getMemDC(), _vTiles[i][j]->getRect().left + 2, _vTiles[i][j]->getRect().top + 2, str, strlen(str));
			}
		}

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
		break;
	}

	_cameraControl->getRect().render(getMemDC());
}

void mapToolScene::saveMap()
{
	OPENFILENAME ofn = { 0 };
	char filePathSize[1028] = "";
	char str[100 + MAXTILEX * MAXTILEY * 14];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = ("타일맵 파일(*.map)");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn) == FALSE) return;

	HANDLE file;
	DWORD write;

	file = CreateFile(filePathSize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "x: %d, y: %d\n", _nowIndexX, _nowIndexY);
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i <= _nowIndexY; ++i)
	{
		for (int j = 0; j <= _nowIndexX; ++j)
		{
			ZeroMemory(str, sizeof(str));
			sprintf_s(str, "%d,%d,%d,%d,%d\n",
				_vTiles[i][j]->getTerrainX(),
				_vTiles[i][j]->getTerrainY(),
				_vTiles[i][j]->getObjectX(),
				_vTiles[i][j]->getObjectY(),
				_vTiles[i][j]->getOrderIndex());
			WriteFile(file, str, strlen(str), &write, NULL);
		}
	}

	CloseHandle(file);
}

void mapToolScene::loadMap()
{
	cout << "맵 불러오기" << endl;

	OPENFILENAME ofn = { 0 };
	char filePathSize[1028] = "";
	char str[100 + MAXTILEX * MAXTILEY * 14];
	char* context = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = ("타일맵 파일(*.map)");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == FALSE) return;

	HANDLE file;
	DWORD read;

	file = CreateFile(filePathSize, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	char* tok = strtok_s(str, "\n", &context);
	sscanf_s(tok, "x: %d, y: %d", &_nowIndexX, &_nowIndexY);
	tok = strtok_s(NULL, "\n", &context);

	for (int i = 0; i <= _nowIndexY; ++i)
	{
		for (int j = 0; j <= _nowIndexX; ++j)
		{
			if (tok != NULL)
			{
				int tx = -1, ty = -1, ox = -1, oy = -1, oi = 0;
				sscanf_s(tok, "%d,%d,%d,%d,%d", &tx, &ty, &ox, &oy, &oi);
				_vTiles[i][j]->setTiles(tx, ty, ox, oy, oi);
				tok = strtok_s(NULL, "\n", &context);
			}
		}
	}

	CloseHandle(file);
}

void mapToolScene::startEdit()
{
	if (_mode != NOWMODE::EDIT)
	{
		_sampleStartX = _sampleStartY = _sampleEndX = _sampleEndY = _drawStartX = _drawStartY = _drawEndX = _drawEndY = -1;
		_sampleViewRc.set(0, 0, 0, 0);
		_drawViewRc.set(0, 0, 0, 0);
		OBJECTMANAGER->findObject(objectType::UI, "edit button")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "edit ui")->setIsActive(true);
		OBJECTMANAGER->findObject(objectType::UI, "exit button")->setIsActive(true);
		_mode = NOWMODE::EDIT;
	}
}

void mapToolScene::endEdit()
{
	if (_mode == NOWMODE::EDIT)
	{
		_sampleStartX = _sampleStartY = _sampleEndX = _sampleEndY = _drawStartX = _drawStartY = _drawEndX = _drawEndY = -1;
		_sampleViewRc.set(0, 0, 0, 0);
		_drawViewRc.set(0, 0, 0, 0);
		OBJECTMANAGER->findObject(objectType::UI, "edit button")->setIsActive(true);
		OBJECTMANAGER->findObject(objectType::UI, "edit ui")->setIsActive(false);
		OBJECTMANAGER->findObject(objectType::UI, "exit button")->setIsActive(false);
		_mode = NOWMODE::NONE;
	}
}

void mapToolScene::drawMap()
{
}

HRESULT mapUi::init()
{
	_image = IMAGEMANAGER->findImage("edit ui");
	_terrain = IMAGEMANAGER->addFrameImage("terrain", "images/tiletest.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("terrain b", "images/tiletestbig.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tile null", "images/tilenull.bmp", 48, 48, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("type", "images/buttons_type.bmp", 1024, 575, 2, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tile type", "images/typetile.bmp", 48, 240, 1, 5, true, RGB(255, 0, 255));
	_rc.set(0, 0, 600, 850);
	_rc.setCenter(WINSIZEX - _rc.getSize().x * 0.5f, WINSIZEY * 0.5f);

	_terrainRc.set(0, 0, 132, 57);
	_objectRc.set(0, 0, 132, 57);
	_enemyRc.set(0, 0, 132, 57);
	_typeRc.set(0, 0, 132, 57);
	_plusRc.set(0, 0, 90, 72);
	_minusRc.set(0, 0, 90, 72);

	_terrainRc.setLeftTop(_rc.left + 6, _rc.top + 5);
	_objectRc.setLeftTop(_terrainRc.right, _terrainRc.top);
	_enemyRc.setLeftTop(_objectRc.right, _objectRc.top);
	_typeRc.setLeftTop(_enemyRc.right, _enemyRc.top);
	_plusRc.setLeftTop(_rc.left, _rc.bottom - 72);
	_minusRc.setLeftTop(_plusRc.right, _plusRc.top);

	_editMode = EDITMODE::TERRAIN;
	_penMode = PENMODE::PLUS;
	_page = PAGE::ONE;

	_sampleRc.set(0, 0, 512, 576);
	_sampleRc.setCenter(_rc.getCenter().x, _rc.getCenter().y + 20);

	for (int i = 0; i < 5; ++i)
	{
		_typeRcs[i].set(0, 0, 512, 115);
		_typeRcs[i].setLeftTop(_sampleRc.left, i == 0 ? _sampleRc.top : _typeRcs[i - 1].bottom);
	}

	return S_OK;
}

void mapUi::release()
{
}

void mapUi::update()
{
	if (PtInRect(&_terrainRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			cout << "지형 클릭" << endl;
			_editMode = EDITMODE::TERRAIN;
		}
	}
	else if (PtInRect(&_objectRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			cout << "오브젝트 클릭" << endl;
			_editMode = EDITMODE::OBJECT;
		}
	}
	else if (PtInRect(&_enemyRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			cout << "에너미 클릭" << endl;
			_editMode = EDITMODE::ENEMY;
		}
	}
	else if (PtInRect(&_typeRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			cout << "타입 클릭" << endl;
			_editMode = EDITMODE::TYPE;
			_selectType = 0;
		}
	}
	else if (PtInRect(&_plusRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			cout << "플러스 펜" << endl;
			_penMode = PENMODE::PLUS;
			if (_editMode == EDITMODE::TYPE) _selectType = 0;
		}
	}
	else if (PtInRect(&_minusRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			cout << "마이너스 펜" << endl;
			_penMode = PENMODE::MINUS;
			if (_editMode == EDITMODE::TYPE) _selectType = -1;
		}
	}

	switch (_editMode)
	{
	case EDITMODE::TERRAIN:
		break;
	case EDITMODE::OBJECT:
		break;
	case EDITMODE::ENEMY:
		break;
	case EDITMODE::TYPE:
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_typeRcs[i].getRect(), _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_penMode = PENMODE::PLUS;
					_selectType = i;
					break;
				}
			}
		}
		break;
	case EDITMODE::END:
		break;
	default:
		break;
	}
}

void mapUi::render()
{
	
}

void mapUi::renderRelative(float x, float y)
{
	_image->render(getMemDC(), x + _rc.left, y + _rc.top);
	switch (_editMode)
	{
	case EDITMODE::TERRAIN:
		_terrain->render(getMemDC(), x + _sampleRc.left, y + _sampleRc.top);
		break;
	case EDITMODE::OBJECT:
		break;
	case EDITMODE::ENEMY:
		break;
	case EDITMODE::TYPE:
		for (int i = 0; i < 5; ++i)
		{
			if (_selectType == i)
				IMAGEMANAGER->findImage("type")->frameRender(getMemDC(), x + _typeRcs[i].left, y + _typeRcs[i].top, 1, i);
			else
				IMAGEMANAGER->findImage("type")->frameRender(getMemDC(), x + _typeRcs[i].left, y + _typeRcs[i].top, 0, i);
		}
		break;
	case EDITMODE::END:
		break;
	default:
		break;
	}
	if (_sampleViewRc.getRect().left > 0 && _penMode == PENMODE::PLUS && _editMode != EDITMODE::TYPE)
	{
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HPEN pen = (HPEN)CreatePen(PS_SOLID, 3, RGB(0, 255, 100));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		_sampleViewRc.render(getMemDC(), x, y);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
		SelectObject(getMemDC(), oldPen);
		DeleteObject(pen);
	}
	_rc.render(getMemDC());
}
