#include "stdafx.h"
#include "mapToolScene.h"
#include "button.h"
#include <commdlg.h>

HRESULT mapToolScene::init()
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
	_mapBuffer = IMAGEMANAGER->addImage("mapBuffer", "images/tile/tilenull.bmp", MAXTILEX * SIZE, MAXTILEY * SIZE, false, RGB(0,0,0));

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
		_numButtonObjRc[i].set(0, 0, 147, 52);
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
	_numButtonObjRc[0].setLeftTop(_editButtonRc[0].left, _editButtonRc[0].bottom + 8);
	_numButtonObjRc[1].setLeftTop(_numButtonObjRc[0].right, _editButtonRc[0].bottom + 8);
	_numButtonObjRc[2].setLeftTop(_numButtonObjRc[1].right, _editButtonRc[0].bottom + 8);
	_numButtonObjRc[3].setLeftTop(_numButtonObjRc[2].right, _editButtonRc[0].bottom + 8);

	_plusRc.setLeftTop(_editUiRc.left, _editUiRc.bottom - 72);
	_minusRc.setLeftTop(_plusRc.right, _plusRc.top);

	_sampleRc.set(0, 0, 512, 576);
	_sampleRc.setCenter(_editUiRc.getCenter().x, _editUiRc.getCenter().y + 20);

	for (int i = 0; i < 6; ++i)
	{
		_typeRcs[i].set(0, 0, 512, 96);
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
	_page = TERRAIN_ONE;

	// 배경 이미지
	IMAGEMANAGER->addImage("map bg", "images/maptool/map_bg.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("map bg2", "images/maptool/map_back.bmp", 1200, 1200, false, RGB(0, 0, 0));

	// 버튼 이미지
	IMAGEMANAGER->addFrameImage("saveload", "images/maptool/button_saveload.bmp", 264, 126, 2, 2, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("editmode", "images/maptool/button_menu.bmp", 264, 248, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("numbutton", "images/maptool/button_num.bmp", 392, 156, 2, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("numobj", "images/maptool/button_numobj.bmp", 294, 208, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("backtotitle", "images/maptool/button_backtotitle.bmp", 486, 72, 1, 1, true, RGB(255, 0, 255));

	// ui 전체 이미지
	_uiImage = IMAGEMANAGER->addImage("edit ui", "images/maptool/ui_edit.bmp", 600, 850, true, RGB(255, 0, 255));

	// 샘플 이미지
	_terrainImage[TERRAIN_ONE] = IMAGEMANAGER->addFrameImage("terrain1", "images/tile/terrain1_s.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_terrainImageBig[TERRAIN_ONE] = IMAGEMANAGER->addFrameImage("terrain1 b", "images/tile/terrain1.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_terrainImage[TERRAIN_TWO] = IMAGEMANAGER->addFrameImage("terrain2", "images/tile/terrain2_s.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_terrainImageBig[TERRAIN_TWO] = IMAGEMANAGER->addFrameImage("terrain2 b", "images/tile/terrain2.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_terrainImage[TERRAIN_THREE] = IMAGEMANAGER->addFrameImage("terrain3", "images/tile/terrain3_s.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_terrainImageBig[TERRAIN_THREE] = IMAGEMANAGER->addFrameImage("terrain3 b", "images/tile/terrain3.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));

	_objectImage[OBJECT_ONE] = IMAGEMANAGER->addFrameImage("object1", "images/tile/object1_s.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_objectImageBig[OBJECT_ONE] = IMAGEMANAGER->addFrameImage("object1 b", "images/tile/object1.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_objectImage[OBJECT_TWO] = IMAGEMANAGER->addFrameImage("object2", "images/tile/object2_s.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_objectImageBig[OBJECT_TWO] = IMAGEMANAGER->addFrameImage("object2 b", "images/tile/object2.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_objectImage[OBJECT_THREE] = IMAGEMANAGER->addFrameImage("object3", "images/tile/object3_s.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_objectImageBig[OBJECT_THREE] = IMAGEMANAGER->addFrameImage("object3 b", "images/tile/object3.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_objectImage[OBJECT_FOUR] = IMAGEMANAGER->addFrameImage("object4", "images/tile/object4_s.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_objectImageBig[OBJECT_FOUR] = IMAGEMANAGER->addFrameImage("object4 b", "images/tile/object4.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));

	_enemyImage = IMAGEMANAGER->addFrameImage("enemy", "images/tile/tile_enemy.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_enemyImageBig = IMAGEMANAGER->addFrameImage("enemy b", "images/tile/tile_enemy_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("vendor", "images/object/vendor.bmp", 720, 288, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door prev", "images/tile/doorpreview.bmp", 288, 144, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "images/object/tree.bmp", 720, 288, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grass", "images/object/grass.bmp", 432, 96, 3, 1, true, RGB(255, 0, 255));
	
	// 빈 타일
	IMAGEMANAGER->addImage("tile null", "images/tile/tilenull.bmp", 48, 48, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("tile change", "images/tile/tilechange.bmp", SIZE * MAXTILEX, SIZE * MAXTILEY, false, RGB(0, 0, 0));

	// 오더 버튼 이미지
	IMAGEMANAGER->addFrameImage("type", "images/maptool/button_type.bmp", 1024, 576, 2, 6, true, RGB(255, 0, 255));
	_typeImage = IMAGEMANAGER->addFrameImage("tile type", "images/tile/typetile.bmp", 48, 288, 1, 6, true, RGB(255, 0, 255));

	// 버튼 추가
	button* save = new button();
	save->init("saveload", WINSIZEX / 2 - 100, 66, 0, 0, 1, 0, bind(&mapToolScene::saveMap, this));
	save->setName("save button");

	button* load = new button();
	load->init("saveload", WINSIZEX / 2 + 100, 66, 0, 1, 1, 1, bind(&mapToolScene::loadMap, this));
	load->setName("load button");

	button* backToTitle = new button();
	backToTitle->init("backtotitle", WINSIZEX - 300, WINSIZEY - 55, 0, 0, 0, 0, bind(&mapToolScene::backToTitle, this));
	backToTitle->setName("back title button");

	OBJECTMANAGER->addObject(objectType::UI, save);
	OBJECTMANAGER->addObject(objectType::UI, load);
	OBJECTMANAGER->addObject(objectType::UI, backToTitle);

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

void mapToolScene::release()
{
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
}

void mapToolScene::update()
{
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

void mapToolScene::render()
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
		for (int i = 0; i < 4; ++i)
		{
			if (_page == i)
				IMAGEMANAGER->findImage("numobj")->frameRender(getMemDC(), _numButtonObjRc[i].left, _numButtonObjRc[i].top, 1, i);
			else IMAGEMANAGER->findImage("numobj")->frameRender(getMemDC(), _numButtonObjRc[i].left, _numButtonObjRc[i].top, 0, i);
		}
		_objectImage[_page]->render(getMemDC(), _sampleRc.left, _sampleRc.top);
		renderSelectTile();
		break;
	case EDITMODE::ENEMY:
		_enemyImage->render(getMemDC(), _sampleRc.left, _sampleRc.top);
		renderSelectTile();
		break;
	case EDITMODE::TYPE:
		for (int i = 0; i < 6; ++i)
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

void mapToolScene::checkMapIndex()
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

void mapToolScene::checkMapSize()
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

void mapToolScene::checkSelectSample()
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
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _page != 3)
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
			if (_sampleStart.x != -1 && _sampleStart.y != -1)
			{
				_sampleViewRc.set(0, 0, (_sampleEnd.x - _sampleStart.x + 1) * SAMPLESIZE, (_sampleEnd.y - _sampleStart.y + 1) * SAMPLESIZE);
				_sampleViewRc.setLeftTop(_sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().left, _sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().top);
			}
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
					if (_page == 3)
					{
						_drawStart.x = (_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
						_drawStart.y = (_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;
						_drawEnd.x = (_selectIndex.x > _nowIndex.x) ? _nowIndex.x : _selectIndex.x;
						_drawEnd.y = (_selectIndex.y > _nowIndex.y) ? _nowIndex.y : _selectIndex.y;
					}

					else if (_sampleStart.x != _sampleEnd.x || _sampleStart.y != _sampleEnd.y)
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
									int page = _penMode == PENMODE::PLUS ? _page : 0;
									if (_editMode == EDITMODE::TERRAIN)
									{
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainX(_sampleStart.x);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainY(_sampleStart.y);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainImageNum(_page);
									}
									else if (_editMode == EDITMODE::OBJECT)
									{
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectX(_sampleStart.x);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectY(_sampleStart.y);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectImageNum(_page);
									}
								}
							}
							if (_page == 3)
							{
								if (_penMode == PENMODE::PLUS)
								{
									bool b = true;
									_miObject = _mObject.find(tagPoint{_drawStart.x, _drawStart.y});
									
									//// 찾았으면
									if (_miObject != _mObject.end())
									{
										_miObject->second.frameX = _sampleStart.x;
										_miObject->second.frameY = _sampleStart.y;
										_miObject->second.pageNum = _page;
										_miObject->second.objectType = (_sampleStart.x > 2) ? 1 : 0;
									}
									else
									{
										tagObject obj = { _drawStart.x, _drawStart.y, _sampleStart.x, _sampleStart.y, _page, (_sampleStart.x > 2) ? 1 : 0 };
										_mObject.insert(make_pair(tagPoint{_drawStart.x, _drawStart.y}, obj));
									}
									
									if (_sampleStart.y == 0 && _sampleStart.x <= 2) setVendor();
								}
								else
								{
									_miObject = _mObject.find(tagPoint{ _drawStart.x, _drawStart.y });

									// 찾았으면
									if (_miObject != _mObject.end())
									{
										_mObject.erase(_miObject);
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
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainImageNum(_page);
								}
								else if (_editMode == EDITMODE::OBJECT)
								{
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectX(_sampleStart.x + j);
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectY(_sampleStart.y + i);
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setObjectImageNum(_page);
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

void mapToolScene::changeMapSize()
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

void mapToolScene::moveMapView()
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

void mapToolScene::selectUiButton()
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

				if (i == 0 || i == 1)	// terrain or object
					_page = 0;
				else if (i == 3)		// type(order)
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

	for (int i = 0; i < 4; ++i)
	{
		if (_editMode != EDITMODE::OBJECT) break;
		if (PtInRect(&_numButtonObjRc[i].getRect(), _ptMouse))
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
		for (int i = 0; i < 6; ++i)
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

void mapToolScene::setVendor()
{
	int dx = _drawStart.x - 2;
	int dy = _drawStart.y;
	if (dx < 0) dx = 0;
	if (dy < 0) dy = 0;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			_vTiles[dy + i][dx + j]->setOrder(ORDER::NONE);
			if (dx + j >= _nowIndex.x) break;
		}
		if (dy + i >= _nowIndex.y) break;
	}
}

void mapToolScene::renderChangeMap()
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

void mapToolScene::renderSelectTile()
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

void mapToolScene::renderPreviewTile()
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
			if (_page == 3)
			{
				if (_drawStart.x == -1 && _drawStart.y == -1) return;

				int drawX = _drawStart.x;
				int drawY = _drawStart.y;

				if (_drawStart.x > _drawEnd.x) drawX = _drawEnd.x;
				if (_drawStart.y > _drawEnd.y) drawY = _drawEnd.y;

				image* img = img = IMAGEMANAGER->findImage("vendor");

				int width = 0;
				int height = 0;

				if (_sampleStart.y == 0)
				{
					if (_sampleStart.x <= 2)
					{
						img = IMAGEMANAGER->findImage("vendor");
						width = SIZE * 2;
						height = SIZE * 2;
					}
					else
					{
						img = IMAGEMANAGER->findImage("door prev");
						height = SIZE;
					}
				}
				else
				{
					if (_sampleStart.x <= 2)
					{
						img = IMAGEMANAGER->findImage("tree");
						width = SIZE * 2;
						height = SIZE * 5;
					}
					else
					{
						img = IMAGEMANAGER->findImage("grass");
						width = SIZE;
						height = SIZE;
					}
				}

				for (int i = 0; i <= abs(_drawEnd.y - _drawStart.y); ++i)
				{
					for (int j = 0; j <= abs(_drawEnd.x - _drawStart.x); ++j)
					{
						if (_penMode == PENMODE::PLUS)
						{
							img->alphaFrameRender(getMemDC(),
									_vTiles[drawY + i][drawX + j]->getRect().left + _mapViewRc.left - _clippingPoint.x - width,
									_vTiles[drawY + i][drawX + j]->getRect().top + _mapViewRc.top - _clippingPoint.y - height,
									_sampleStart.x % 3, 0, 150);
						}
						if (drawX + j + 1 > _viewLastIndex.x) break;
					}
					if (drawY + i + 1 > _viewLastIndex.y) break;
				}

			}
			else if (!_isStayKeyDown)
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
								_objectImageBig[_page]->alphaFrameRender(getMemDC(),
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
							_objectImageBig[_page]->alphaFrameRender(getMemDC(),
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

void mapToolScene::resetSample()
{
	_sampleStart.x = _sampleStart.y = _sampleEnd.x = _sampleEnd.y = -1;
	_sampleViewRc.set(0, 0, 0, 0);
}


void mapToolScene::saveMap()
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
			sprintf_s(str, "%d,%d,%d,%d,%d,%d,%d\n",
			_vTiles[i][j]->getTerrainX(),
			_vTiles[i][j]->getTerrainY(),
			_vTiles[i][j]->getObjectX(),
			_vTiles[i][j]->getObjectY(),
			_vTiles[i][j]->getTerrainImageNum(),
			_vTiles[i][j]->getObjectImageNum(),
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

	string name = token;

	// enemy 저장
	string s = "../enemy/";
	s += name;

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

	// 상호작용하는 object 저장
	/*s = "../object/";
	s += name;

	file = CreateFile(TEXT(s.c_str()), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "object number: %d\n", _vObject.size());
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < _vObject.size(); ++i)
	{
		ZeroMemory(str, sizeof(str));
		sprintf_s(str, "%d,%d,%d,%d,%d,%d\n",
			_vObject[i].tileX,
			_vObject[i].tileY,
			_vObject[i].frameX,
			_vObject[i].frameY,
			_vObject[i].pageNum,
			_vObject[i].objectType);
		WriteFile(file, str, strlen(str), &write, NULL);
	}

	CloseHandle(file);*/
}

void mapToolScene::loadMap()
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
	_mObject.clear();

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
				int tx = -1, ty = -1, ox = -1, oy = -1, pn = 0, on = 0, oi = 0;
				sscanf_s(tok, "%d,%d,%d,%d,%d,%d,%d", &tx, &ty, &ox, &oy, &pn, &on, &oi);

				tile * t = new tile();
				t->setTiles(tx, ty, ox, oy, pn, on, oi);
				t->setTileRc(j * SIZE, i * SIZE);
				v.push_back(t);

				if (ox != -1 && oy != -1 && on == 3)
				{
					tagObject obj = { j, i, ox, oy, on, (ox > 2) ? 1 : 0 };
					_mObject.insert(make_pair(tagPoint{ j, i }, obj));
				}

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

	string name = token;

	char str2[500];

	string s = "../enemy/";
	s += name;

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

	_vEnemies.clear();

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
	/*
	char str3[500];

	s = "../object/";
	s += name;

	file = CreateFile(TEXT(s.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//if (file == INVALID_HANDLE_VALUE)
	//	return;

	ReadFile(file, str3, strlen(str3), &read, NULL);

	int maxNum2 = 0;

	context = NULL;
	tok = strtok_s(str3, "\n", &context);
	sscanf_s(tok, "object number: %d", &maxNum2);
	tok = strtok_s(NULL, "\n", &context);

	_vObject.clear();

	for (int i = 0; i < maxNum2; ++i)
	{
		if (tok != NULL)
		{
			int tx = -1, ty = -1, fx = -1, fy = -1, pn = 0, ot = 0;
			sscanf_s(tok, "%d,%d,%d,%d,%d", &tx, &ty, &fx, &fy, &pn, &ot);

			tagObject obj = { tx, ty, fx, fy, pn, ot };
			_vObject.push_back(obj);
			tok = strtok_s(NULL, "\n", &context);
		}
	}

	CloseHandle(file); */

	redrawMap();
}

bool mapToolScene::isAutoTile(int frameX, int frameY, int page)
{
	switch (page)
	{
	case 0:
		// 초록초록
		break;
	case 1:
		// 마을
		break;
	case 2:
		// 보스
		break;
	}
	return false;
}

void mapToolScene::autotile()
{
}

void mapToolScene::drawMap()
{
	_mapBuffer->render(getMemDC(), _mapViewRc.left, _mapViewRc.top, _clippingPoint.x, _clippingPoint.y, _mapViewRc.getWidth(), _mapViewRc.getHeight());
}

void mapToolScene::redrawMap()
{
	StretchBlt(getMapBufferDC(), 0, 0, _mapBuffer->getWidth(), _mapBuffer->getHeight(), IMAGEMANAGER->findImage("map bg2")->getMemDC(), 0, 0, 1200, 1200, SRCCOPY);

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (_vTiles[i][j]->getTerrainX() != -1)
				_terrainImageBig[_vTiles[i][j]->getTerrainImageNum()]->frameRender(getMapBufferDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
			else
				_vTiles[i][j]->getRect().render(getMapBufferDC());

			// 오브젝트가 있는 경우
			if (_vTiles[i][j]->getObjectX() != -1)
			{
				if (_vTiles[i][j]->getObjectImageNum() != 3)
				{
					// 일반 오브젝트인 경우
					_objectImageBig[_vTiles[i][j]->getObjectImageNum()]->frameRender(getMapBufferDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
				}
				else
				{
					// 클래스화 시킬 오브젝트인 경우
					int width = 0;
					int height = 0;
					int frameX = _vTiles[i][j]->getObjectX();
					int frameY = _vTiles[i][j]->getObjectY();

					image* img = IMAGEMANAGER->findImage("vendor");

					switch (frameX % 3)
					{
					case 0:
						if (frameY == 0)
						{
							// 상인
							img = IMAGEMANAGER->findImage("vendor");
							width = SIZE * 2;
							height = SIZE * 2;
						}
						else
						{
							// 나무
							img = IMAGEMANAGER->findImage("tree");
							width = SIZE * 2;
							height = SIZE * 5;
						}
						break;
					case 1:
						if (frameY == 0)
						{
							// 문
							img = IMAGEMANAGER->findImage("door prev");
							height = SIZE;
						}
						else
						{
							// 풀
							img = IMAGEMANAGER->findImage("grass");
							width = SIZE;
							height = SIZE;
						}
						frameX -= 3;
						break;
					}
					img->frameRender(getMapBufferDC(),
						_vTiles[i][j]->getRect().left - width,
						_vTiles[i][j]->getRect().top - height,
						frameX, 0);
				}
			}		
		}
	}

	for (int i = 0; i < _vEnemies.size(); ++i)
	{
		_enemyImageBig->frameRender(getMapBufferDC(),
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().left,
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().top,
			_vEnemies[i].frameX, _vEnemies[i].frameY);
	}

	_miObject = _mObject.begin();
	for (; _miObject != _mObject.end(); ++_miObject)
	{
		int width = 0;
		int height = 0;
		int frameX = _miObject->second.frameX;

		image* img = IMAGEMANAGER->findImage("vendor");

		switch (_miObject->second.objectType)
		{
		case 0:
			if (_miObject->second.frameY == 0)
			{
				img = IMAGEMANAGER->findImage("vendor");
				width = SIZE * 2;
				height = SIZE * 2;
			}
			else
			{
				// 나무
				img = IMAGEMANAGER->findImage("tree");
				width = SIZE * 2;
				height = SIZE * 5;
			}
			break;
		case 1:
			if (_miObject->second.frameY == 0)
			{
				// 문
				img = IMAGEMANAGER->findImage("door prev");
				height = SIZE;
			}
			else
			{
				// 풀
				img = IMAGEMANAGER->findImage("grass");
				width = SIZE;
				height = SIZE;
			}
			frameX -= 3;
			break;
		}
		img->frameRender(getMapBufferDC(),
			_vTiles[_miObject->second.tileY][_miObject->second.tileX]->getRect().left - width,
			_vTiles[_miObject->second.tileY][_miObject->second.tileX]->getRect().top - height,
			frameX, 0);
	}

	if (_editMode != EDITMODE::TYPE) return;
	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
				_typeImage->frameRender(getMapBufferDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, 0, _vTiles[i][j]->getOrderIndex());
		}
	}
}

void mapToolScene::backToTitle()
{
	SCENEMANAGER->loadScene("title");
}