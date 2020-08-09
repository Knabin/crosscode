#include "stdafx.h"
#include "mapToolScene2.h"
#include "button.h"
#include <commdlg.h>

HRESULT mapToolScene2::init()
{
	_controlMode = NOWMODE::NONE;

	CAMERA->setCameraMode(CAMERASTATE::NONE);

	_nowIndex.x = 22;
	_nowIndex.y = 18;

	_sampleStart.x = _sampleStart.y = _sampleEnd.x = _sampleEnd.y = -1;
	_drawStart.x = _drawStart.y = _drawEnd.x = _drawEnd.y = -1;
	_viewIndex.x = _viewIndex.y = 0;

	_isStayKeyDown = false;

	// 전체 타일 출력할 새로운 buffer 선언
	_mapBuffer = IMAGEMANAGER->addImage("mapBuffer", "images/tilenull.bmp", MAXTILEX * SIZE, MAXTILEY * SIZE, false, RGB(0,0,0));

	// ========== 각종 rect 초기화 ==========
	_editUiRc.set(0, 0, 600, 850);
	_editUiRc.setCenter(WINSIZEX - _editUiRc.getSize().x * 0.5f, WINSIZEY * 0.5f);

	_mapViewRc.set(0, 0, 1104, 912);
	_mapViewRc.setLeftTop(50, 130);
	_clippingPoint.x = 0;
	_clippingPoint.y = 0;

	for (int i = 0; i < 4; ++i)
	{
		_editButtonRc[i].set(0, 0, 132, 57);
	}

	for (int i = 0; i < 3; ++i)
	{
		_numButtonRc[i].set(0, 0, 192, 52);
	}

	_plusRc.set(0, 0, 90, 72);
	_minusRc.set(0, 0, 90, 72);

	_editButtonRc[0].setLeftTop(_editUiRc.left + 6, _editUiRc.top);
	_editButtonRc[1].setLeftTop(_editButtonRc[0].right, _editButtonRc[0].top);
	_editButtonRc[2].setLeftTop(_editButtonRc[1].right, _editButtonRc[1].top);
	_editButtonRc[3].setLeftTop(_editButtonRc[2].right, _editButtonRc[2].top);
	_numButtonRc[0].setLeftTop(_editButtonRc[0].left, _editButtonRc[0].bottom + 8);
	_numButtonRc[1].setLeftTop(_numButtonRc[0].right, _editButtonRc[0].bottom + 8);
	_numButtonRc[2].setLeftTop(_numButtonRc[1].right, _editButtonRc[0].bottom + 8);

	_plusRc.setLeftTop(_editUiRc.left, _editUiRc.bottom - 72);
	_minusRc.setLeftTop(_plusRc.right, _plusRc.top);

	_sampleRc.set(0, 0, 512, 576);
	_sampleRc.setCenter(_editUiRc.getCenter().x, _editUiRc.getCenter().y + 20);

	for (int i = 0; i < 5; ++i)
	{
		_typeRcs[i].set(0, 0, 512, 115);
		_typeRcs[i].setLeftTop(_sampleRc.left, i == 0 ? _sampleRc.top : _typeRcs[i - 1].bottom);
	}
	// ===============================

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		vector<tile *> v;
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			tile *t = new tile();
			t->setTileRc(j * SIZE, i * SIZE);
			v.push_back(t);
		}
		_vTiles.push_back(v);
	}

	_editMode = EDITMODE::TERRAIN;
	_penMode = PENMODE::PLUS;
	_page = PAGE_ONE;

	// 배경 이미지
	IMAGEMANAGER->addImage("map bg", "images/map_bg.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("map bg2", "images/map_back.bmp", 1200, 1200, false, RGB(0, 0, 0));

	// 버튼 이미지
	IMAGEMANAGER->addFrameImage("saveload", "images/buttons_saveload.bmp", 264, 126, 2, 2, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("editmode", "images/buttons_menu.bmp", 264, 248, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("numbutton", "images/buttons_num.bmp", 392, 156, 2, 3, true, RGB(255, 0, 255));

	// ui 전체 이미지
	_uiImage = IMAGEMANAGER->addImage("edit ui", "images/ui_edit.bmp", 600, 850, true, RGB(255, 0, 255));

	// 샘플 이미지
	_terrainImage[PAGE_ONE] = IMAGEMANAGER->addFrameImage("terrain1", "images/tile1.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_terrainImageBig[PAGE_ONE] = IMAGEMANAGER->addFrameImage("terrain1 b", "images/tile1_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_terrainImage[PAGE_TWO] = IMAGEMANAGER->addFrameImage("terrain2", "images/tile2.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_terrainImageBig[PAGE_TWO] = IMAGEMANAGER->addFrameImage("terrain2 b", "images/tile2_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_terrainImage[PAGE_THREE] = IMAGEMANAGER->addFrameImage("terrain3", "images/tile3.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_terrainImageBig[PAGE_THREE] = IMAGEMANAGER->addFrameImage("terrain3 b", "images/tile3_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));

	_objectImage = IMAGEMANAGER->addFrameImage("object", "images/tile_object.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_objectImageBig = IMAGEMANAGER->addFrameImage("object b", "images/tile_object_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_enemyImage = IMAGEMANAGER->addFrameImage("enemy", "images/tile_enemy.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_enemyImageBig = IMAGEMANAGER->addFrameImage("enemy b", "images/tile_enemy_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	
	// 빈 타일
	IMAGEMANAGER->addImage("tile null", "images/tilenull.bmp", 48, 48, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("tile change", "images/tilechange.bmp", SIZE * MAXTILEX, SIZE * MAXTILEY, false, RGB(0, 0, 0));

	// 오더 버튼 이미지
	IMAGEMANAGER->addFrameImage("type", "images/buttons_type.bmp", 1024, 575, 2, 5, true, RGB(255, 0, 255));
	_typeImage = IMAGEMANAGER->addFrameImage("tile type", "images/typetile.bmp", 48, 240, 1, 5, true, RGB(255, 0, 255));

	// 버튼 추가
	button* save = new button();
	save->init("saveload", WINSIZEX / 2 - 100, 66, 0, 0, 1, 0, bind(&mapToolScene2::saveMap, this));
	save->setName("save button");

	button* load = new button();
	load->init("saveload", WINSIZEX / 2 + 100, 66, 0, 1, 1, 1, bind(&mapToolScene2::loadMap, this));
	load->setName("load button");

	OBJECTMANAGER->addObject(objectType::UI, save);
	OBJECTMANAGER->addObject(objectType::UI, load);

	for (int i = 0; i < SAMPLENUMX * SAMPLENUMY; ++i)
	{
		_sampleTiles[i].setTerrainX(i % SAMPLENUMX);
		_sampleTiles[i].setTerrainY(i / SAMPLENUMX);
		_sampleTiles[i].getRect().set(0, 0, SAMPLESIZE, SAMPLESIZE);
		_sampleTiles[i].getRect().setLeftTop(_sampleRc.left + SAMPLESIZE * (i % SAMPLENUMX),
			_sampleRc.top + SAMPLESIZE * (i / SAMPLENUMX));
	}

	redrawMap();

	return S_OK;
}

void mapToolScene2::release()
{
}

void mapToolScene2::update()
{
	_ptMouseAbs.x = _ptMouse.x + CAMERA->getRect().left;
	_ptMouseAbs.y = _ptMouse.y + CAMERA->getRect().top;

	checkMapIndex();
	moveMapView();

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_controlMode = NOWMODE::NONE;
		resetSample();
	}

	switch (_controlMode)
	{
	case NOWMODE::NONE:
		checkMapSize();
		break;
	case NOWMODE::MAPSIZE:
		changeMapSize();
		break;
	case NOWMODE::EDIT:
		checkSelectSample();
		break;
	case NOWMODE::END:
		break;
	default:
		break;
	}

	if (_controlMode != NOWMODE::MAPSIZE)
		selectUiButton();
}

void mapToolScene2::render()
{
	IMAGEMANAGER->findImage("map bg")->render(getMemDC());
	_uiImage->render(getMemDC(), _editUiRc.left, _editUiRc.top);
	_mapViewRc.render(getMemDC());

	switch (_editMode)
	{
	case EDITMODE::TERRAIN:
		for (int i = 0; i < 3; ++i)
		{
			if (_page == i)
				IMAGEMANAGER->findImage("numbutton")->frameRender(getMemDC(), _numButtonRc[i].left, _numButtonRc[i].top, 1, i);
			else IMAGEMANAGER->findImage("numbutton")->frameRender(getMemDC(), _numButtonRc[i].left, _numButtonRc[i].top, 0, i);
		}
		_terrainImage[_page]->render(getMemDC(), _sampleRc.left, _sampleRc.top);
		renderSelectTile();
		break;
	case EDITMODE::OBJECT:
		_objectImage->render(getMemDC(), _sampleRc.left, _sampleRc.top);
		renderSelectTile();
		break;
	case EDITMODE::ENEMY:
		_enemyImage->render(getMemDC(), _sampleRc.left, _sampleRc.top);
		renderSelectTile();
		break;
	case EDITMODE::TYPE:
		for (int i = 0; i < 5; ++i)
		{
			if (_selectType == i)
				IMAGEMANAGER->findImage("type")->frameRender(getMemDC(), _typeRcs[i].left, _typeRcs[i].top, 1, i);
			else
				IMAGEMANAGER->findImage("type")->frameRender(getMemDC(), _typeRcs[i].left, _typeRcs[i].top, 0, i);
		}
		break;
	}
	
	for (int i = 0; i < (int)EDITMODE::END; ++i)
	{
		if ((int)_editMode == i && _penMode == PENMODE::PLUS)
			IMAGEMANAGER->findImage("editmode")->frameRender(getMemDC(), _editButtonRc[i].left, _editButtonRc[i].top, 1, i);
		else
			IMAGEMANAGER->findImage("editmode")->frameRender(getMemDC(), _editButtonRc[i].left, _editButtonRc[i].top, 0, i);
	}

	drawMap();
	renderChangeMap();

	renderPreviewTile();

	// 마우스를 기준으로 현재 가리키고 있는 인덱스 출력
	if (PtInRect(&_mapViewRc.getRect(), _ptMouse))
	{
		COLORREF oldColor = GetTextColor(getMemDC());
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		char str[100];
		sprintf_s(str, "[%d, %d]", _selectIndex.x, _selectIndex.y);
		TextOut(getMemDC(), _ptMouse.x - 15, _ptMouse.y - 15, str, strlen(str));
		SetTextColor(getMemDC(), oldColor);
	}
}

void mapToolScene2::checkMapIndex()
{
	_selectIndex.x = (_ptMouse.x + _clippingPoint.x - _mapViewRc.left) / SIZE;
	_selectIndex.y = (_ptMouse.y + _clippingPoint.y - _mapViewRc.top) / SIZE;

	if (_selectIndex.x < 0) _selectIndex.x = 0;
	else if (_selectIndex.x >= MAXTILEX) _selectIndex.x = MAXTILEX - 1;
	else if (_selectIndex.x > _viewMaxIndex.x)
		_selectIndex.x = _viewMaxIndex.x;

	if (_selectIndex.y < 0) _selectIndex.y = 0;
	else if (_selectIndex.y >= MAXTILEY) _selectIndex.y = MAXTILEY - 1;
	else if (_selectIndex.y > _viewMaxIndex.y)
		_selectIndex.y = _viewMaxIndex.y;

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (_vTiles[i][j]->getRect().right < _clippingPoint.x || _vTiles[i][j]->getRect().bottom < _clippingPoint.y) continue;
			_viewIndex.x = j;
			_viewIndex.y = i;
			_viewLastIndex.x = _viewMaxIndex.x = j + MAXMAPTOOLX;
			_viewLastIndex.y = _viewMaxIndex.y = i + MAXMAPTOOLY;
			if (_viewLastIndex.x > _nowIndex.x) _viewLastIndex.x = _nowIndex.x;
			if (_viewLastIndex.y > _nowIndex.y) _viewLastIndex.y = _nowIndex.y;
			return;
		}
	}
}

void mapToolScene2::checkMapSize()
{
	if (_selectIndex.x == _nowIndex.x && _selectIndex.y == _nowIndex.y)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_selectStartIndex.x = _selectIndex.x;
			_selectStartIndex.y = _selectIndex.y;
			_controlMode = NOWMODE::MAPSIZE;
		}
	}
}

void mapToolScene2::checkSelectSample()
{
	switch (_editMode)
	{
	case EDITMODE::TERRAIN:
	case EDITMODE::OBJECT:
		// 샘플 고르는 중
		if (PtInRect(&_sampleRc.getRect(), _ptMouse))
		{
			for (int i = 0; i < SAMPLENUMX * SAMPLENUMY; ++i)
			{
				if (PtInRect(&_sampleTiles[i].getRect().getRect(), _ptMouse))
				{
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_penMode = PENMODE::PLUS;
						_drawStart.x = _drawStart.y = -1;
						_sampleStart.x = _sampleEnd.x = i % SAMPLENUMX;
						_sampleStart.y = _sampleEnd.y = i / SAMPLENUMX;
					}
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					{
						_sampleEnd.x = i % SAMPLENUMX;
						_sampleEnd.y = i / SAMPLENUMX;
					}
				}
			}
			if (_sampleStart.x > _sampleEnd.x)
				swap(_sampleStart.x, _sampleEnd.x);
			if (_sampleStart.y > _sampleEnd.y)
				swap(_sampleStart.y, _sampleEnd.y);
			_sampleViewRc.set(0, 0, (_sampleEnd.x - _sampleStart.x + 1) * SAMPLESIZE, (_sampleEnd.y - _sampleStart.y + 1) * SAMPLESIZE);
			_sampleViewRc.setLeftTop(_sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().left, _sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().top);
		}
		// 지형 그리는 중
		else
		{
			bool b = false;

			// 만약에 selectIndex를 클릭했다면
			if (PtInRect(&_mapViewRc.getRect(), _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_drawStart.x = _drawEnd.x = 
						(_selectIndex.x < _viewIndex.x) ? _viewIndex.x :
						(_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
					_drawStart.y = _drawEnd.y = 
						(_selectIndex.y < _viewIndex.y) ? _viewIndex.y :
						(_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;

					if (_sampleStart.x == _sampleEnd.x && _sampleStart.y == _sampleEnd.y)
						_isStayKeyDown = true;
				}
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					if (_sampleStart.x != _sampleEnd.x || _sampleStart.y != _sampleEnd.y)
					{
						_drawStart.x = 
							(_selectIndex.x < _viewIndex.x) ? _viewIndex.x : 
							(_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
						_drawStart.y = 
							(_selectIndex.y < _viewIndex.y) ? _viewIndex.y :
							(_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;
					}
					_drawEnd.x = (_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
					_drawEnd.y = (_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;

				}

				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
				{
					if (_sampleStart.x == _sampleEnd.x && _sampleStart.y == _sampleEnd.y)
					{
						_isStayKeyDown = false;
						b = true;

						if (_drawStart.x > _drawEnd.x)
							swap(_drawStart.x, _drawEnd.x);
						if (_drawStart.y > _drawEnd.y)
							swap(_drawStart.y, _drawEnd.y);
					}

					if (_drawStart.x == -1 && _drawStart.y == -1) break;

					if (_penMode == PENMODE::MINUS) _sampleStart = _sampleEnd = { -1,-1 };
					else if (_sampleStart.x == -1) return;

					if (_sampleStart.x == _sampleEnd.x && _sampleStart.y == _sampleEnd.y)
					{
						if (b)
						{
							for (int i = 0; i <= _drawEnd.y - _drawStart.y; ++i)
							{
								for (int j = 0; j <= _drawEnd.x - _drawStart.x; ++j)
								{
									if (_editMode == EDITMODE::TERRAIN)
									{
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainX(_sampleStart.x);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainY(_sampleStart.y);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setPageNum(_page);
									}
									else if (_editMode == EDITMODE::OBJECT)
									{
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectX(_sampleStart.x);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectY(_sampleStart.y);
									}
								}
							}
							_isStayKeyDown = false;
						}
					}
					else
					{
						for (int i = 0; i <= _sampleEnd.y - _sampleStart.y; ++i)
						{
							for (int j = 0; j <= _sampleEnd.x - _sampleStart.x; ++j)
							{
								if (_editMode == EDITMODE::TERRAIN)
								{
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainX(_sampleStart.x + j);
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainY(_sampleStart.y + i);
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setPageNum(_page);
								}
								else if (_editMode == EDITMODE::OBJECT)
								{
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectX(_sampleStart.x + j);
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectY(_sampleStart.y + i);
								}
								if (_drawStart.x + j + 1 > _nowIndex.x) break;
							}
							if (_drawStart.y + i + 1 > _nowIndex.y) break;
						}
					}
					_drawStart = _drawEnd = { -1, -1 };
					redrawMap();
				}
			}
		}
		break;
	case EDITMODE::ENEMY:
		if (PtInRect(&_sampleRc.getRect(), _ptMouse))
		{
			for (int i = 0; i < SAMPLENUMX * SAMPLENUMY; ++i)
			{
				if (PtInRect(&_sampleTiles[i].getRect().getRect(), _ptMouse))
				{
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_penMode = PENMODE::PLUS;
						_drawStart.x = _drawStart.y = -1;
						_sampleStart.x = _sampleEnd.x = i % SAMPLENUMX;
						_sampleStart.y = _sampleEnd.y = i / SAMPLENUMX;
					}
				}
			}
			_sampleViewRc.set(0, 0, (_sampleEnd.x - _sampleStart.x + 1) * SAMPLESIZE, (_sampleEnd.y - _sampleStart.y + 1) * SAMPLESIZE);
			_sampleViewRc.setLeftTop(_sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().left, _sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().top);
		}
		else
		{
			if (PtInRect(&_mapViewRc.getRect(), _ptMouse))
			{
				_drawStart.x = _drawEnd.x =
					(_selectIndex.x < _viewIndex.x) ? _viewIndex.x :
					(_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
				_drawStart.y = _drawEnd.y =
					(_selectIndex.y < _viewIndex.y) ? _viewIndex.y :
					(_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;

				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
				{
					if (_drawStart.x == -1 && _drawStart.y == -1) break;
					
					if (_penMode == PENMODE::PLUS)
					{
						if (_sampleStart.x == -1) return;
						tagEnemy enemy;
						enemy.tileX = _drawStart.x;
						enemy.tileY = _drawStart.y;
						enemy.frameX = _sampleStart.x;
						enemy.frameY = _sampleStart.y;
						enemy.enemyType = _sampleStart.x;
						_vEnemies.push_back(enemy);
					}
					else
					{
						for (int i = 0; i < _vEnemies.size(); ++i)
						{
							if (_vEnemies[i].tileX != _drawStart.x) continue;
							if (_vEnemies[i].tileY != _drawStart.y) continue;
							_vEnemies.erase(_vEnemies.begin() + i);
							break;
						}
					}

					_drawStart = _drawEnd = { -1, -1 };
					redrawMap();
				}
			}
		}
		break;
	case EDITMODE::TYPE:
		if (PtInRect(&_mapViewRc.getRect(), _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_drawStart.x = _drawEnd.x =
					(_selectIndex.x < _viewIndex.x) ? _viewIndex.x :
					(_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
				_drawStart.y = _drawEnd.y =
					(_selectIndex.y < _viewIndex.y) ? _viewIndex.y :
					(_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_drawEnd.x = (_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
				_drawEnd.y = (_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;

			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				if (_drawStart.x > _drawEnd.x)
					swap(_drawStart.x, _drawEnd.x);
				if (_drawStart.y > _drawEnd.y)
					swap(_drawStart.y, _drawEnd.y);

				if (_drawStart.x == -1 && _drawStart.y == -1) break;

				if (_penMode == PENMODE::MINUS) _selectType = 1;
				//_vTiles[_drawStart.y][_drawStart.x]->setOrder((ORDER)_selectType);
				if (_sampleStart.x == _sampleEnd.x && _sampleStart.y == _sampleEnd.y)
				{
					for (int i = 0; i <= _drawEnd.y - _drawStart.y; ++i)
					{
						for (int j = 0; j <= _drawEnd.x - _drawStart.x; ++j)
						{
							_vTiles[_drawStart.y + i][_drawStart.x + j]->setOrder((ORDER)_selectType);
						}
					}
				}
				_drawStart = _drawEnd = { -1, -1 };
				redrawMap();
			}
		}
		break;
	case EDITMODE::END:
		break;
	default:
		break;
	}
}

void mapToolScene2::changeMapSize()
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		POINT newIndex = { _selectIndex.x, _selectIndex.y };

		// X축이 늘어난 경우
		if (_selectStartIndex.x < _selectIndex.x)
		{
			for (int i = 0; i <= _nowIndex.y; ++i)
			{
				for (int j = 0; j < _selectIndex.x - _selectStartIndex.x; ++j)
				{
					tile* t = new tile();
					t->setTileRc(_vTiles[i].size() * SIZE, i * SIZE);
					_vTiles[i].push_back(t);
				}
			}
			_nowIndex.x += _selectIndex.x - _selectStartIndex.x;
		}
		// X축이 줄어든 경우
		else if (_selectStartIndex.x > _selectIndex.x)
		{
			for (int i = 0; i <= _nowIndex.y; ++i)
			{
				for (int j = 0; j < _selectStartIndex.x - _selectIndex.x; ++j)
				{
					_vTiles[i][_vTiles[i].size() - 1]->release();
					SAFE_DELETE(_vTiles[i][_vTiles[i].size() - 1]);
					_vTiles[i].pop_back();
				}
			}
			_nowIndex.x += _selectIndex.x - _selectStartIndex.x;

			for (int i = 0; i < _vEnemies.size(); ++i)
			{
				if (_vEnemies[i].tileX <= _nowIndex.x) continue;
				_vEnemies.erase(_vEnemies.begin() + i);
			}
		}

		// Y축이 늘어난 경우
		if (_selectStartIndex.y < _selectIndex.y)
		{
			for (int i = 0; i < _selectIndex.y - _selectStartIndex.y; ++i)
			{
				vector<tile *> v;
				for (int j = 0; j <= _nowIndex.x; ++j)
				{
					tile* t = new tile();
					t->setTileRc(j * SIZE, _vTiles.size() * SIZE);
					v.push_back(t);
				}
				_vTiles.push_back(v);
			}
			_nowIndex.y += _selectIndex.y - _selectStartIndex.y;
		}
		// Y축이 줄어든 경우
		else if (_selectStartIndex.y > _selectIndex.y)
		{
			for (int i = 0; i < _selectStartIndex.y - _selectIndex.y; ++i)
			{
				for (int j = 0; j <= _nowIndex.x; ++j)
				{
					_vTiles[_vTiles.size() - 1][j]->release();
					SAFE_DELETE(_vTiles[_vTiles.size() - 1][j]);
				}
				_vTiles[_vTiles.size() - 1].clear();
				_vTiles.pop_back();
			}
			_nowIndex.y += _selectIndex.y - _selectStartIndex.y;

			for (int i = 0; i < _vEnemies.size(); ++i)
			{
				if (_vEnemies[i].tileY <= _nowIndex.y) continue;
				_vEnemies.erase(_vEnemies.begin() + i);
			}
		}
		redrawMap();
		_controlMode = NOWMODE::NONE;
	}
}

void mapToolScene2::moveMapView()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		redrawMap();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _clippingPoint.x + 4 <= _mapBuffer->getWidth() - _mapViewRc.getWidth())
	{
		_clippingPoint.x += 4;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _clippingPoint.x - 4 >= 0)
	{
		_clippingPoint.x -= 4;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _clippingPoint.y - 4 >= 0)
	{
		_clippingPoint.y -= 4;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _clippingPoint.y + 4 <= _mapBuffer->getHeight() - _mapViewRc.getHeight())
	{
		_clippingPoint.y += 4;
	}

}

void mapToolScene2::selectUiButton()
{
	for (int i = 0; i < 4; ++i)
	{
		if (PtInRect(&_editButtonRc[i].getRect(), _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
			{
				EDITMODE prevMode = _editMode;

				_controlMode = NOWMODE::EDIT;
				_editMode = (EDITMODE)i;
				_penMode = PENMODE::PLUS;
				resetSample();

				if (prevMode == EDITMODE::TYPE || _editMode == EDITMODE::TYPE)
					redrawMap();

				if (i == 0)			// terrain
					_page = 0;
				else if (i == 3)	// type(order)
					_selectType = 0;
				break;
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (_editMode != EDITMODE::TERRAIN) break;
		if (PtInRect(&_numButtonRc[i].getRect(), _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_controlMode = NOWMODE::EDIT;	
				_page = i;
				resetSample();
				break;
			}
		}
	}

	// 연필 버튼
	if (PtInRect(&_plusRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_controlMode = NOWMODE::EDIT;
			_penMode = PENMODE::PLUS;
			if (_editMode == EDITMODE::TYPE) _selectType = 0;
		}
	}

	// 지우개 버튼
	if (PtInRect(&_minusRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_controlMode = NOWMODE::EDIT;
			_penMode = PENMODE::MINUS;
			resetSample();
			if (_editMode == EDITMODE::TYPE) _selectType = -1;
		}
	}

	if (_editMode == EDITMODE::TYPE)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_typeRcs[i].getRect(), _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_controlMode = NOWMODE::EDIT;
					_penMode = PENMODE::PLUS;
					_selectType = i;
					resetSample();
					break;
				}
			}
		}
	}
	else
	{
		if (PtInRect(&_editUiRc.getRect(), _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_controlMode = NOWMODE::EDIT;
			}
		}
	}

}

void mapToolScene2::renderChangeMap()
{
	if (_controlMode == NOWMODE::MAPSIZE)
	{
		int width;
		int height;

		if (_selectIndex.x >= _vTiles[0].size() && _selectIndex.y >= _vTiles.size())
		{
			width = _vTiles[_nowIndex.y][_nowIndex.x]->getRect().right - _clippingPoint.x + (_selectIndex.x - _nowIndex.x) * SIZE;
			height = _vTiles[_nowIndex.y][_nowIndex.x]->getRect().bottom - _clippingPoint.y + (_selectIndex.y - _nowIndex.y) * SIZE;
		}
		else if (_selectIndex.x >= _vTiles[0].size())
		{
			width = _vTiles[_selectIndex.y][_nowIndex.x]->getRect().right - _clippingPoint.x + (_selectIndex.x - _nowIndex.x) * SIZE;
			height = _vTiles[_selectIndex.y][_nowIndex.x]->getRect().bottom - _clippingPoint.y;
		}
		else if (_selectIndex.y >= _vTiles.size())
		{
			width = _vTiles[_nowIndex.y][_selectIndex.x]->getRect().right - _clippingPoint.x;
			height = _vTiles[_nowIndex.y][_selectIndex.x]->getRect().bottom - _clippingPoint.y + (_selectIndex.y - _nowIndex.y) * SIZE;
		}
		else
		{
			width = _vTiles[_selectIndex.y][_selectIndex.x]->getRect().right - _clippingPoint.x;
			height = _vTiles[_selectIndex.y][_selectIndex.x]->getRect().bottom - _clippingPoint.y;
		}

		IMAGEMANAGER->findImage("tile change")->alphaRender(getMemDC(),
			_mapViewRc.left, _mapViewRc.top, 0, 0, width, height, 100);
	}
}

void mapToolScene2::renderSelectTile()
{
	if (_sampleViewRc.left > _editUiRc.left)
	{
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HPEN pen = (HPEN)CreatePen(PS_SOLID, 3, RGB(255, 150, 0));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		_sampleViewRc.render(getMemDC());
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
		SelectObject(getMemDC(), oldPen);
		DeleteObject(pen);
	}
}

void mapToolScene2::renderPreviewTile()
{
	if (!PtInRect(&_mapViewRc.getRect(), _ptMouse) || 
		_sampleStart.x == -1 || _sampleStart.y == -1 ||
		_drawStart.x == -1 || _drawStart.x == -1)
		return;

	if (_controlMode == NOWMODE::EDIT)
	{
		switch (_editMode)
		{
		case EDITMODE::TERRAIN:
		case EDITMODE::OBJECT:
			if (!_isStayKeyDown)
			{
				for (int i = 0; i <= _sampleEnd.y - _sampleStart.y; ++i)
				{
					for (int j = 0; j <= _sampleEnd.x - _sampleStart.x; ++j)
					{
						if (_penMode == PENMODE::PLUS)
						{
							if (_editMode == EDITMODE::TERRAIN)
								_terrainImageBig[_page]->alphaFrameRender(getMemDC(),
									_vTiles[_drawEnd.y + i][_drawEnd.x + j]->getRect().left + _mapViewRc.left - _clippingPoint.x,
									_vTiles[_drawEnd.y + i][_drawEnd.x + j]->getRect().top + _mapViewRc.top - _clippingPoint.y,
									_sampleStart.x + j, _sampleStart.y + i, 150);
							else
								_objectImageBig->alphaFrameRender(getMemDC(),
									_vTiles[_drawEnd.y + i][_drawEnd.x + j]->getRect().left + _mapViewRc.left - _clippingPoint.x,
									_vTiles[_drawEnd.y + i][_drawEnd.x + j]->getRect().top + _mapViewRc.top - _clippingPoint.y,
									_sampleStart.x + j, _sampleStart.y + i, 150);
						}
						if (_drawEnd.x + j + 1 > _viewLastIndex.x) break;
					}
					if (_drawEnd.y + i + 1 > _viewLastIndex.y) break;
				}
			}
			else
			{
				if (_drawStart.x == -1 && _drawStart.y == -1) return;

				int drawX = _drawStart.x;
				int drawY = _drawStart.y;

				if (_drawStart.x > _drawEnd.x) drawX = _drawEnd.x;
				if (_drawStart.y > _drawEnd.y) drawY = _drawEnd.y;


				for (int i = 0; i <= abs(_drawEnd.y - _drawStart.y); ++i)
				{
					for (int j = 0; j <= abs(_drawEnd.x - _drawStart.x); ++j)
					{
						if (_penMode == PENMODE::PLUS)
						{
							if(_editMode == EDITMODE::TERRAIN)
								_terrainImageBig[_page]->alphaFrameRender(getMemDC(),
									_vTiles[drawY + i][drawX + j]->getRect().left + _mapViewRc.left - _clippingPoint.x,
									_vTiles[drawY + i][drawX + j]->getRect().top + _mapViewRc.top - _clippingPoint.y,
									_sampleStart.x, _sampleStart.y, 150);
							else
							_objectImageBig->alphaFrameRender(getMemDC(),
								_vTiles[drawY + i][drawX + j]->getRect().left + _mapViewRc.left - _clippingPoint.x,
								_vTiles[drawY + i][drawX + j]->getRect().top + _mapViewRc.top - _clippingPoint.y,
								_sampleStart.x, _sampleStart.y, 150);
						}
						if (drawX + j + 1 > _viewLastIndex.x) break;
					}
					if (drawY + i + 1 > _viewLastIndex.y) break;
				}
			}
			break;
		case EDITMODE::ENEMY:
			if (_penMode == PENMODE::PLUS)
			{
				_enemyImageBig->alphaFrameRender(getMemDC(),
					_vTiles[_drawStart.y][_drawStart.x]->getRect().left + _mapViewRc.left - _clippingPoint.x,
					_vTiles[_drawStart.y][_drawStart.x]->getRect().top + _mapViewRc.top - _clippingPoint.y,
					_sampleStart.x, _sampleStart.y, 150);
			}
			break;
		case EDITMODE::TYPE:
			break;
		case EDITMODE::END:
			break;
		default:
			break;
		}
	}
}

void mapToolScene2::resetSample()
{
	_sampleStart.x = _sampleStart.y = _sampleEnd.x = _sampleEnd.y = -1;
	_sampleViewRc.set(0, 0, 0, 0);
}


void mapToolScene2::saveMap()
{
	OPENFILENAME ofn = { 0 };
	char filePathSize[1028] = "";
	char str[100 + MAXTILEX * MAXTILEY * 16];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrDefExt = "map";
	ofn.lpstrFilter = ("타일맵 파일(*.map)");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn) == FALSE) return;

	HANDLE file;
	DWORD write;

	file = CreateFile(filePathSize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "x: %d, y: %d\n", _nowIndex.x, _nowIndex.y);
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			ZeroMemory(str, sizeof(str));
			sprintf_s(str, "%d,%d,%d,%d,%d,%d\n",
			_vTiles[i][j]->getTerrainX(),
			_vTiles[i][j]->getTerrainY(),
			_vTiles[i][j]->getObjectX(),
			_vTiles[i][j]->getObjectY(),
			_vTiles[i][j]->getPageNum(),
			_vTiles[i][j]->getOrderIndex());
			WriteFile(file, str, strlen(str), &write, NULL);
		}
	}

	char temp[1028];
	strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));

	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);
	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
	}

	CloseHandle(file);

	// enemy 저장
	string s = "../enemy/";
	s += token;

	file = CreateFile(TEXT(s.c_str()), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "enemy number: %d\n", _vEnemies.size());
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < _vEnemies.size(); ++i)
	{
		ZeroMemory(str, sizeof(str));
		sprintf_s(str, "%d,%d,%d,%d,%d\n",
			_vEnemies[i].tileX,
			_vEnemies[i].tileY,
			_vEnemies[i].frameX,
			_vEnemies[i].frameY,
			_vEnemies[i].enemyType);
		WriteFile(file, str, strlen(str), &write, NULL);
	}

	CloseHandle(file);
}

void mapToolScene2::loadMap()
{
	OPENFILENAME ofn = { 0 };
	char filePathSize[1028] = "";
	char str[100 + MAXTILEX * MAXTILEY * 16];
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

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			_vTiles[i][j]->release();
			SAFE_DELETE(_vTiles[i][j]);
		}
		_vTiles[i].clear();
	}
	_vTiles.clear();

	HANDLE file;
	DWORD read;

	file = CreateFile(filePathSize, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	char* tok = strtok_s(str, "\n", &context);
	sscanf_s(tok, "x: %d, y: %d", &_nowIndex.x, &_nowIndex.y);
	tok = strtok_s(NULL, "\n", &context);

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		vector<tile *> v;
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (tok != NULL)
			{
				int tx = -1, ty = -1, ox = -1, oy = -1, pn = 0, oi = 0;
				sscanf_s(tok, "%d,%d,%d,%d,%d,%d", &tx, &ty, &ox, &oy, &pn, &oi);

				tile * t = new tile();
				t->setTiles(tx, ty, ox, oy, pn, oi);
				t->setTileRc(j * SIZE, i * SIZE);
				v.push_back(t);
				tok = strtok_s(NULL, "\n", &context);
			}
		}
		_vTiles.push_back(v);
	}

	char temp[1028];
	strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));

	context = NULL;
	char* token = strtok_s(temp, "\\", &context);
	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
	}

	CloseHandle(file);


	char str2[500];

	string s = "../enemy/";
	s += token;

	file = CreateFile(TEXT(s.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	ReadFile(file, str2, strlen(str2), &read, NULL);

	int maxNum = 0;

	context = NULL;
	tok = strtok_s(str2, "\n", &context);
	sscanf_s(tok, "enemy number: %d", &maxNum);
	tok = strtok_s(NULL, "\n", &context);

	for (int i = 0; i < maxNum; ++i)
	{
		if (tok != NULL)
		{
			int tx = -1, ty = -1, fx = -1, fy = -1, et = 0;
			sscanf_s(tok, "%d,%d,%d,%d,%d", &tx, &ty, &fx, &fy, &et);

			tagEnemy enemy = { tx, ty, fx, fy, et };
			_vEnemies.push_back(enemy);
			tok = strtok_s(NULL, "\n", &context);
		}
	}

	CloseHandle(file);

	redrawMap();
}

void mapToolScene2::drawMap()
{
	_mapBuffer->render(getMemDC(), _mapViewRc.left, _mapViewRc.top, _clippingPoint.x, _clippingPoint.y, _mapViewRc.getWidth(), _mapViewRc.getHeight());
}

void mapToolScene2::redrawMap()
{
	StretchBlt(getMapBufferDC(), 0, 0, _mapBuffer->getWidth(), _mapBuffer->getHeight(), IMAGEMANAGER->findImage("map bg2")->getMemDC(), 0, 0, 1200, 1200, SRCCOPY);

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (_vTiles[i][j]->getTerrainX() != -1)
				_terrainImageBig[_vTiles[i][j]->getPageNum()]->frameRender(getMapBufferDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
			else
				_vTiles[i][j]->getRect().render(getMapBufferDC());

			if (_vTiles[i][j]->getObjectX() != -1)
				_objectImageBig->frameRender(getMapBufferDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());

			if (_editMode == EDITMODE::TYPE)
				_typeImage->frameRender(getMapBufferDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, 0, _vTiles[i][j]->getOrderIndex());
		}
	}

	for (int i = 0; i < _vEnemies.size(); ++i)
	{
		_enemyImageBig->frameRender(getMapBufferDC(),
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().left,
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().top,
			_vEnemies[i].frameX, _vEnemies[i].frameY);
	}
}
