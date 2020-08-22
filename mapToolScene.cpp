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

	// ========== 각종 rect 초기화 ==========
	_editUiRc.update(Vector2((float)WINSIZEX - 300, WINSIZEY * 0.5f), Vector2(600, 850), pivot::CENTER);

	_mapViewRc.update(Vector2(50, 130), Vector2(1104, 912), pivot::LEFTTOP);

	_clippingPoint.x = 0;
	_clippingPoint.y = 0;

	for (int i = 0; i < 4; ++i)
	{
		_editButtonRc[i].update(Vector2(0, 0), Vector2(132, 57), pivot::LEFTTOP);
		_numButtonObjRc[i].update(Vector2(0, 0), Vector2(147, 52), pivot::LEFTTOP);
	}

	for (int i = 0; i < 3; ++i)
	{

		_numButtonRc[i].update(Vector2(0, 0), Vector2(192, 52), pivot::LEFTTOP);
	}

	_editButtonRc[0].set(Vector2(_editUiRc.left + 6, _editUiRc.top), pivot::LEFTTOP);
	_editButtonRc[1].set(Vector2(_editButtonRc[0].right, _editButtonRc[0].top), pivot::LEFTTOP);
	_editButtonRc[2].set(Vector2(_editButtonRc[1].right, _editButtonRc[1].top), pivot::LEFTTOP);
	_editButtonRc[3].set(Vector2(_editButtonRc[2].right, _editButtonRc[2].top), pivot::LEFTTOP);
	_numButtonRc[0].set(Vector2(_editButtonRc[0].left, _editButtonRc[0].bottom + 8), pivot::LEFTTOP);
	_numButtonRc[1].set(Vector2(_numButtonRc[0].right, _editButtonRc[0].bottom + 8), pivot::LEFTTOP);
	_numButtonRc[2].set(Vector2(_numButtonRc[1].right, _editButtonRc[0].bottom + 8), pivot::LEFTTOP);
	_numButtonObjRc[0].set(Vector2(_editButtonRc[0].left, _editButtonRc[0].bottom + 8), pivot::LEFTTOP);
	_numButtonObjRc[1].set(Vector2(_numButtonObjRc[0].right, _editButtonRc[0].bottom + 8), pivot::LEFTTOP);
	_numButtonObjRc[2].set(Vector2(_numButtonObjRc[1].right, _editButtonRc[0].bottom + 8), pivot::LEFTTOP);
	_numButtonObjRc[3].set(Vector2(_numButtonObjRc[2].right, _editButtonRc[0].bottom + 8), pivot::LEFTTOP);

	_plusRc.update(Vector2(_editUiRc.left, _editUiRc.bottom - 72), Vector2(90, 72), pivot::LEFTTOP);
	_minusRc.update(Vector2(_plusRc.right, _plusRc.top), Vector2(90, 72), pivot::LEFTTOP);

	_sampleRc.update(Vector2(_editUiRc.getCenter().x, _editUiRc.getCenter().y + 20), Vector2(512, 576), pivot::CENTER);

	for (int i = 0; i < 7; ++i)
	{
		_typeRcs[i].update(Vector2(_sampleRc.left, i == 0 ? _sampleRc.top : _typeRcs[i - 1].bottom), Vector2(512, 83), pivot::LEFTTOP);
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



	// ui 전체 이미지
	_uiImage = IMAGEMANAGER->findImage("edit ui");

	// 샘플 이미지
	_terrainImage[TERRAIN_ONE] = IMAGEMANAGER->addImage("terrain1", L"images/tile/terrain1_s.png");
	//_terrainImage[TERRAIN_ONE] = IMAGEMANAGER->addFrameImage("terrain1", L"images/tile/terrain1_s.png", 16, 18);
	_terrainImageBig[TERRAIN_ONE] = IMAGEMANAGER->addFrameImage("terrain1 b", L"images/tile/terrain1.png", 16, 18);
	_terrainImage[TERRAIN_TWO] = IMAGEMANAGER->addImage("terrain2", L"images/tile/terrain2_s.png");
	_terrainImageBig[TERRAIN_TWO] = IMAGEMANAGER->addFrameImage("terrain2 b", L"images/tile/terrain2.png", 16, 18);
	_terrainImage[TERRAIN_THREE] = IMAGEMANAGER->addImage("terrain3", L"images/tile/terrain3_s.png");
	_terrainImageBig[TERRAIN_THREE] = IMAGEMANAGER->addFrameImage("terrain3 b", L"images/tile/terrain3.png", 16, 18);

	_objectImage[OBJECT_ONE] = IMAGEMANAGER->addImage("object1", L"images/tile/object1_s.png");
	_objectImageBig[OBJECT_ONE] = IMAGEMANAGER->addFrameImage("object1 b", L"images/tile/object1.png", 16, 18);
	_objectImage[OBJECT_TWO] = IMAGEMANAGER->addImage("object2", L"images/tile/object2_s.png");
	_objectImageBig[OBJECT_TWO] = IMAGEMANAGER->addFrameImage("object2 b", L"images/tile/object2.png", 16, 18);
	_objectImage[OBJECT_THREE] = IMAGEMANAGER->addImage("object3", L"images/tile/object3_s.png");
	_objectImageBig[OBJECT_THREE] = IMAGEMANAGER->addFrameImage("object3 b", L"images/tile/object3.png", 16, 18);
	_objectImage[OBJECT_FOUR] = IMAGEMANAGER->addImage("object4", L"images/tile/object4_s.png");
	_objectImageBig[OBJECT_FOUR] = IMAGEMANAGER->addFrameImage("object4 b", L"images/tile/object4.png", 16, 18);

	_enemyImage = IMAGEMANAGER->addImage("enemy", L"images/tile/tile_enemy.png");
	_enemyImageBig = IMAGEMANAGER->addFrameImage("enemy b", L"images/tile/tile_enemy_big.png", 16, 18);

	IMAGEMANAGER->addFrameImage("foothold prev", L"images/tile/footholdpreview.png", 1, 1);
	
	// 빈 타일
	IMAGEMANAGER->addImage("tile null", L"images/tile/tilenull.png");

	// 오더 버튼 이미지
	IMAGEMANAGER->addFrameImage("type", L"images/maptool/button_type.png", 2, 7);
	_typeImage = IMAGEMANAGER->addFrameImage("tile type", L"images/tile/typetile.png", 1, 7);

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
		_sampleTiles[i].getRect().update(Vector2(_sampleRc.left + SAMPLESIZE * (i % SAMPLENUMX),
			_sampleRc.top + SAMPLESIZE * (i / SAMPLENUMX)), Vector2(SAMPLESIZE, SAMPLESIZE), pivot::LEFTTOP);
	}

	// 오토타일 설정
	{
		vector<POINT> v;
		v.push_back({ 8,0 });
		v.push_back({ 8,3 });
		v.push_back({ 11,0 });
		v.push_back({ 11,3 });
		v.push_back({ 9,0 });
		v.push_back({ 9,3 });
		v.push_back({ 10,0 });
		v.push_back({ 10,3 });
		v.push_back({ 8,1 });
		v.push_back({ 8,2 });
		v.push_back({ 11,1 });
		v.push_back({ 11,2 });
		v.push_back({ 9,1 });
		v.push_back({ 9,2 });
		v.push_back({ 10,1 });
		v.push_back({ 10,2 });
		_vAutoIndexs.push_back(v);
	}

	{
		vector<POINT> v;
		v.push_back({ 12,0 });
		v.push_back({ 12,3 });
		v.push_back({ 15,0 });
		v.push_back({ 15,3 });
		v.push_back({ 13,0 });
		v.push_back({ 13,3 });
		v.push_back({ 14,0 });
		v.push_back({ 14,3 });
		v.push_back({ 12,1 });
		v.push_back({ 12,2 });
		v.push_back({ 15,1 });
		v.push_back({ 15,2 });
		v.push_back({ 13,1 });
		v.push_back({ 13,2 });
		v.push_back({ 14,1 });
		v.push_back({ 14,2 });
		_vAutoIndexs.push_back(v);
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
			//delete(_vTiles[i][j]);
			//_vTiles[i][j]->release();
			//SAFE_DELETE(_vTiles[i][j]);
		}
		_vTiles[i].clear();
	}
	_vTiles.clear();

	OBJECTMANAGER->findObject(objectType::UI, "save button")->setIsAlive(false);
	OBJECTMANAGER->findObject(objectType::UI, "load button")->setIsAlive(false);
	OBJECTMANAGER->findObject(objectType::UI, "back title button")->setIsAlive(false);
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
	IMAGEMANAGER->findImage("map bg")->render(Vector2(0, 0));
	_uiImage->render(Vector2(_editUiRc.left, _editUiRc.top), 1.0f);
	//D2DRENDERER->DrawRotationFillRectangle(_sampleRc, D2D1::ColorF::Red, 0);
	//D2DRENDERER->DrawRotationFillRectangle(_mapViewRc, D2D1::ColorF::White, 0);
	IMAGEMANAGER->findImage("map bg2")->render(Vector2(_mapViewRc.left, _mapViewRc.top));
	redrawMap();
	switch (_editMode)
	{
	case EDITMODE::TERRAIN:
		for (int i = 0; i < 3; ++i)
		{
			if (_page == i)
				IMAGEMANAGER->findImage("numbutton")->frameRender(Vector2(_numButtonRc[i].getCenter()), 1, i);
			else IMAGEMANAGER->findImage("numbutton")->frameRender(Vector2(_numButtonRc[i].getCenter()), 0, i);
		}
		_terrainImage[_page]->render(Vector2(_sampleRc.left, _sampleRc.top));
		renderSelectTile();
		break;
	case EDITMODE::OBJECT:
		for (int i = 0; i < 4; ++i)
		{
			if (_page == i)
				IMAGEMANAGER->findImage("numobj")->frameRender(Vector2(_numButtonObjRc[i].getCenter()), 1, i);
			else IMAGEMANAGER->findImage("numobj")->frameRender(Vector2(_numButtonObjRc[i].getCenter()), 0, i);
		}
		_objectImage[_page]->render(Vector2(_sampleRc.left, _sampleRc.top));
		renderSelectTile();
		break;
	case EDITMODE::ENEMY:
		_enemyImage->render(Vector2(_sampleRc.left, _sampleRc.top));
		renderSelectTile();
		break;
	case EDITMODE::TYPE:
		for (int i = 0; i < 7; ++i)
		{
			if (_selectType == i)
				IMAGEMANAGER->findImage("type")->frameRender(Vector2(_typeRcs[i].getCenter()), 1, i);
			else
				IMAGEMANAGER->findImage("type")->frameRender(Vector2(_typeRcs[i].getCenter()), 0, i);
		}
		break;
	}
	
	for (int i = 0; i < (int)EDITMODE::END; ++i)
	{
		if ((int)_editMode == i && _penMode == PENMODE::PLUS)
			IMAGEMANAGER->findImage("editmode")->frameRender(Vector2(_editButtonRc[i].getCenter()), 1, i);
		else
			IMAGEMANAGER->findImage("editmode")->frameRender(Vector2(_editButtonRc[i].getCenter()), 0, i);
	}
	renderChangeMap();

	renderPreviewTile();

	// 마우스를 기준으로 현재 가리키고 있는 인덱스 출력
	if (PtInRect(&_mapViewRc.getRect(), _ptMouse))
	{
		char str[100];
		sprintf_s(str, "[%d, %d]", _selectIndex.x, _selectIndex.y);
		string str2 = str;
		wstring str3;
		str3.assign(str2.begin(), str2.end());
		D2DRENDERER->RenderText(_ptMouse.x - 50, _ptMouse.y - 30, str3, 20);
	}

	D2DRENDERER->DrawLine(Vector2(_clippingPoint.x, 0.f), Vector2(_clippingPoint.x, (float)WINSIZEY), D2D1::ColorF::Red, 5.f);
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
				_sampleViewRc.update(Vector2(_sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().left, _sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().top),
					Vector2((_sampleEnd.x - _sampleStart.x + 1) * SAMPLESIZE, (_sampleEnd.y - _sampleStart.y + 1) * SAMPLESIZE), pivot::LEFTTOP);
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
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainImageNum(_page);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainX(_sampleStart.x);
										_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainY(_sampleStart.y);
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
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainImageNum(_page);
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainX(_sampleStart.x + j);
									_vTiles[_drawStart.y + i][_drawStart.x + j]->setTerrainY(_sampleStart.y + i);
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
			if (_sampleStart.x != -1)
			{
				_sampleViewRc.update(Vector2(_sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().left, _sampleTiles[_sampleStart.y * SAMPLENUMX + _sampleStart.x].getRect().top),
					Vector2((_sampleEnd.x - _sampleStart.x + 1) * SAMPLESIZE, (_sampleEnd.y - _sampleStart.y + 1) * SAMPLESIZE), pivot::LEFTTOP);
			}
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
		checkMapIndex();
		redrawMap();
		_controlMode = NOWMODE::NONE;
	}
}

void mapToolScene::moveMapView()
{
	if (KEYMANAGER->isStayKeyDown('D') && _clippingPoint.x + 4 <= MAXTILEX * SIZE - _mapViewRc.GetWidth())
	{
		_clippingPoint.x += 48;
	}

	if (KEYMANAGER->isStayKeyDown('A') && _clippingPoint.x - 4 >= 0)
	{
		_clippingPoint.x -= 48;
	}
	if (KEYMANAGER->isStayKeyDown('W') && _clippingPoint.y - 4 >= 0)
	{
		_clippingPoint.y -= 48;
	}
	if (KEYMANAGER->isStayKeyDown('S') && _clippingPoint.y + 4 <= MAXTILEY * SIZE - _mapViewRc.GetHeight())
	{
		_clippingPoint.y += 48;
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
		for (int i = 0; i < 7; ++i)
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

		D2DRENDERER->DrawRotationFillRectangle(
			floatRect(_mapViewRc.left, _mapViewRc.top, (_selectIndex.x + 1) * SIZE + _mapViewRc.left - _clippingPoint.x, (_selectIndex.y + 1) * SIZE + _mapViewRc.top - _clippingPoint.y),
			D2D1::ColorF::LightSkyBlue, 0
		);
	}
}

void mapToolScene::renderSelectTile()
{
	if (_sampleViewRc.left > _editUiRc.left)
	{
		D2DRENDERER->DrawRectangle(_sampleViewRc, D2DRenderer::DefaultBrush::Green, 2.0f);
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

				image* img = IMAGEMANAGER->findImage("vendor");

				int width = 0;
				int height = 0;
				int frameX = _sampleStart.x % 3;

				switch (_sampleStart.y)
				{
				case 0:
					if (_sampleStart.x <= 2)
					{
						img = IMAGEMANAGER->findImage("vendor");
					}
					else
					{
						img = IMAGEMANAGER->findImage("door prev");
						width = SIZE * 0.5f;
					}
					break;
				case 1:
					if (_sampleStart.x <= 2)
					{
						img = IMAGEMANAGER->findImage("tree");
						height = SIZE * 2.5f;
					}
					else
					{
						img = IMAGEMANAGER->findImage("grass");
						height = SIZE * 0.5f;
					}
					break;
				case 2:
					img = IMAGEMANAGER->findImage("button prev");
					height = SIZE * 0.5f;
					break;
				case 3:
					img = IMAGEMANAGER->findImage("button2 prev");
					height = SIZE * 0.5f;
					break;
				case 4:
					img = IMAGEMANAGER->findImage("destruct");
					width = SIZE * 0.5f;
					break;
				case 5:
					if (_sampleStart.x == 0)
					{
						img = IMAGEMANAGER->findImage("wall prev");
					}
					else if (_sampleStart.x == 1)
					{
						img = IMAGEMANAGER->findImage("wall2 prev");
					}
					else if (_sampleStart.x == 2)
					{
						img = IMAGEMANAGER->findImage("wall3 prev");
					}
					else if (_sampleStart.x == 3)
					{
						img = IMAGEMANAGER->findImage("wall4 prev");
						width = SIZE * 0.5f;
					}
					frameX = 0;
					break;
				case 6:
					img = IMAGEMANAGER->findImage("roof");
					break;
				case 7:
					img = IMAGEMANAGER->findImage("foothold prev");
					break;
				}
				
				
				for (int i = 0; i <= abs(_drawEnd.y - _drawStart.y); ++i)
				{
					for (int j = 0; j <= abs(_drawEnd.x - _drawStart.x); ++j)
					{
						if (_penMode == PENMODE::PLUS)
						{
							img->setAlpha(0.7f);
							img->frameRender(Vector2(_vTiles[drawY + i][drawX + j]->getRect().getCenter()) 
								+ Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint - Vector2(width,height),
								frameX, 0);
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
							{
								_terrainImageBig[_page]->setAlpha(0.7f);
								_terrainImageBig[_page]->frameRender(
									(Vector2(_vTiles[_drawStart.y + i][_drawStart.x + j]->getRect().getCenter())
										+ Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint), 
									_sampleStart.x + j, _sampleStart.y + i);
							}
							else
							{
								_objectImageBig[_page]->setAlpha(0.7f);
								_objectImageBig[_page]->frameRender(
									(Vector2(_vTiles[_drawStart.y + i][_drawStart.x + j]->getRect().getCenter())
										+ Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint),
									_sampleStart.x + j, _sampleStart.y + i);
							}
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
							if (_editMode == EDITMODE::TERRAIN)
							{
								_terrainImageBig[_page]->setAlpha(0.7f);
								_terrainImageBig[_page]->frameRender(
									(Vector2(_vTiles[drawY + i][drawX + j]->getRect().getCenter())
										+ Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint),
									_sampleStart.x, _sampleStart.y);
							}
							else
							{
								_objectImageBig[_page]->setAlpha(0.7f);
								_objectImageBig[_page]->frameRender(
									(Vector2(_vTiles[drawY + i][drawX + j]->getRect().getCenter())
									+ Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint),
									_sampleStart.x, _sampleStart.y);
							}
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
				_enemyImageBig->setAlpha(0.7f);
				_enemyImageBig->frameRender(
					(Vector2(_vTiles[_drawStart.y][_drawStart.x]->getRect().getCenter())
						+ Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint),
					_sampleStart.x, _sampleStart.y);
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
	_sampleViewRc.update(Vector2(0, 0), Vector2(0, 0), pivot::LEFTTOP);
}


void mapToolScene::saveMap()
{
	ShowCursor(true);
	OPENFILENAME ofn = { 0 };
	char filePathSize[1028] = "";

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
	WriteFile(file, &_nowIndex.x, sizeof(int), &write, NULL);
	WriteFile(file, &_nowIndex.y, sizeof(int), &write, NULL);

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			int terX = _vTiles[i][j]->getTerrainX();
			int terY = _vTiles[i][j]->getTerrainY();
			int objX = _vTiles[i][j]->getObjectX();
			int objY = _vTiles[i][j]->getObjectY();
			int terN = _vTiles[i][j]->getTerrainImageNum();
			int objN = _vTiles[i][j]->getObjectImageNum();
			int order = _vTiles[i][j]->getOrderIndex();

			WriteFile(file, &terX, sizeof(int), &write, NULL);
			WriteFile(file, &terY, sizeof(int), &write, NULL);
			WriteFile(file, &objX, sizeof(int), &write, NULL);
			WriteFile(file, &objY, sizeof(int), &write, NULL);
			WriteFile(file, &terN, sizeof(int), &write, NULL);
			WriteFile(file, &objN, sizeof(int), &write, NULL);
			WriteFile(file, &order, sizeof(int), &write, NULL);
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

	int size = _vEnemies.size();
	WriteFile(file, &size, sizeof(int), &write, NULL);

	for (int i = 0; i < _vEnemies.size(); ++i)
	{
		int tileX = _vEnemies[i].tileX;
		int tileY = _vEnemies[i].tileY;
		int frameX = _vEnemies[i].frameX;
		int frameY = _vEnemies[i].frameY;
		int enemyType = _vEnemies[i].enemyType;

		WriteFile(file, &tileX, sizeof(int), &write, NULL);
		WriteFile(file, &tileY, sizeof(int), &write, NULL);
		WriteFile(file, &frameX, sizeof(int), &write, NULL);
		WriteFile(file, &frameY, sizeof(int), &write, NULL);
		WriteFile(file, &enemyType, sizeof(int), &write, NULL);
	}

	CloseHandle(file);
	ShowCursor(false);
}

void mapToolScene::loadMap()
{
	ShowCursor(true);
	OPENFILENAME ofn = { 0 };
	char filePathSize[1028] = "";
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

	for (int i = 0; i < _vTiles.size(); ++i)
	{
		for (int j = 0; j < _vTiles[i].size(); ++j)
		{
			if(_vTiles[i][j] != nullptr) _vTiles[i][j]->release();
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

	ReadFile(file, &_nowIndex.x, sizeof(int), &read, NULL);
	ReadFile(file, &_nowIndex.y, sizeof(int), &read, NULL);

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		vector<tile *> v;
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			tile* t = new tile();
			ZeroMemory(t, sizeof(tile));

			int terX;
			int terY;
			int objX;
			int objY;
			int terN;
			int objN;
			int order;

			ReadFile(file, &terX, sizeof(int), &read, NULL);
			ReadFile(file, &terY, sizeof(int), &read, NULL);
			ReadFile(file, &objX, sizeof(int), &read, NULL);
			ReadFile(file, &objY, sizeof(int), &read, NULL);
			ReadFile(file, &terN, sizeof(int), &read, NULL);
			ReadFile(file, &objN, sizeof(int), &read, NULL);
			ReadFile(file, &order, sizeof(int), &read, NULL);

			t->setTiles(terX, terY, objX, objY, terN, objN, order);
			t->setTileRc(j * SIZE, i * SIZE);
			v.push_back(t);

			if (objX != -1 && objY != -1 && objN == 3)
			{
				tagObject obj = { j, i, objX, objY, objN, (objX > 2) ? 1 : 0 };
				_mObject.insert(make_pair(tagPoint{ j, i }, obj));
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

	int maxNum = 0;
	ReadFile(file, &maxNum, sizeof(int), &read, NULL);

	_vEnemies.clear();

	for (int i = 0; i < maxNum; ++i)
	{
		int tileX;
		int tileY;
		int frameX;
		int frameY;
		int enemyType;

		ReadFile(file, &tileX, sizeof(int), &read, NULL);
		ReadFile(file, &tileY, sizeof(int), &read, NULL);
		ReadFile(file, &frameX, sizeof(int), &read, NULL);
		ReadFile(file, &frameY, sizeof(int), &read, NULL);
		ReadFile(file, &enemyType, sizeof(int), &read, NULL);

		tagEnemy enemy = { tileX, tileY, frameX, frameY, enemyType };
		_vEnemies.push_back(enemy);
	}

	CloseHandle(file);
	_clippingPoint = Vector2(0, 0);

	redrawMap();
	ShowCursor(false);
}

void mapToolScene::checkAutoTile(int indexX, int indexY)
{
	int autoIndex = 0;
	int type = _vTiles[indexY][indexX]->getTerrainType();

	// 상단
	if (indexY != 0)
	{
		if (_vTiles[indexY - 1][indexX]->getTerrainType() == type)
		autoIndex += 1 << AUTO_T;
	}

	// 좌측
	if (indexX != 0)
	{
		if (_vTiles[indexY][indexX - 1]->getTerrainType() == type)
		autoIndex += 1 << AUTO_L;
	}

	// 우측
	if (indexX != _nowIndex.x)
	{
		if (_vTiles[indexY][indexX + 1]->getTerrainType() == type)
		autoIndex += 1 << AUTO_R;
	}

	// 하단
	if (indexY != _nowIndex.y)
	{
		if (_vTiles[indexY + 1][indexX]->getTerrainType() == type)
		autoIndex += 1 << AUTO_B;
	}

	// 타일 설정

	_vTiles[indexY][indexX]->setTerrainX(_vAutoIndexs[type - 1][autoIndex].x);
	_vTiles[indexY][indexX]->setTerrainY(_vAutoIndexs[type - 1][autoIndex].y);
}

void mapToolScene::redrawMap()
{
	checkMapIndex();
	//for (int i = 0; i <= _nowIndex.y; ++i)
	for(int i = 0; i <= _viewLastIndex.y; ++i)
	{
		for (int j = 0; j <= _viewLastIndex.x; ++j)
		//for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (_vTiles[i][j]->getRect().getCenter().x < _clippingPoint.x ||
				_vTiles[i][j]->getRect().getCenter().x > _clippingPoint.x + _mapViewRc.getSize().x ||
				_vTiles[i][j]->getRect().getCenter().y < _clippingPoint.y ||
				_vTiles[i][j]->getRect().getCenter().y > _clippingPoint.y + _mapViewRc.getSize().y) continue;

			if (_vTiles[i][j]->getTerrainX() != -1)
			{
				if (_vTiles[i][j]->getTerrainType() > 0)
					checkAutoTile(j, i);
				_terrainImageBig[_vTiles[i][j]->getTerrainImageNum()]->frameRender(
					Vector2(_vTiles[i][j]->getRect().getCenter()) + Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
			}
			else
			{
				IMAGEMANAGER->findImage("tile null")->render(
					Vector2(_vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top) + Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint);
			}


			// 오브젝트가 있는 경우
			if (_vTiles[i][j]->getObjectX() != -1)
			{
				if (_vTiles[i][j]->getObjectImageNum() != 3)
				{
					// 일반 오브젝트인 경우
					_objectImageBig[_vTiles[i][j]->getObjectImageNum()]->frameRender(
						Vector2(_vTiles[i][j]->getRect().getCenter()) + Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint, _vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
				}
			}		
		}
	}

	// 에너미 렌더
	for (int i = 0; i < _vEnemies.size(); ++i)
	{
		if (_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().getCenter().x < _clippingPoint.x ||
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().getCenter().x > _clippingPoint.x + _mapViewRc.getSize().x ||
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().getCenter().y < _clippingPoint.y ||
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().getCenter().y > _clippingPoint.y + _mapViewRc.getSize().y) continue;

		_enemyImageBig->frameRender(Vector2(
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->getRect().getCenter()) + Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint,
			_vEnemies[i].frameX, _vEnemies[i].frameY);
	}

	// 오브젝트 렌더
	_miObject = _mObject.begin();
	for (; _miObject != _mObject.end(); ++_miObject)
	{
		if (_vTiles[_miObject->second.tileY][_miObject->second.tileX]->getRect().getCenter().x < _clippingPoint.x ||
			_vTiles[_miObject->second.tileY][_miObject->second.tileX]->getRect().getCenter().x > _clippingPoint.x + _mapViewRc.getSize().x ||
			_vTiles[_miObject->second.tileY][_miObject->second.tileX]->getRect().getCenter().y < _clippingPoint.y ||
			_vTiles[_miObject->second.tileY][_miObject->second.tileX]->getRect().getCenter().y > _clippingPoint.y + _mapViewRc.getSize().y) continue;

		int width = 0;
		int height = 0;
		int frameX = _miObject->second.frameX;

		image* img = IMAGEMANAGER->findImage("vendor");

		switch (_miObject->second.frameY)
		{
		case 0:
			if (_miObject->second.frameX <= 2)
			{
				img = IMAGEMANAGER->findImage("vendor");
			}
			else
			{
				img = IMAGEMANAGER->findImage("door prev");
				width = SIZE * 0.5f;
				frameX -= 3;
			}
			break;
		case 1:
			if (_miObject->second.frameX <= 2)
			{
				img = IMAGEMANAGER->findImage("tree");
				height = SIZE * 2.5f;
			}
			else
			{
				img = IMAGEMANAGER->findImage("grass");
				height = SIZE * 0.5f;
				frameX -= 3;
			}
			break;
		case 2:
			img = IMAGEMANAGER->findImage("button prev");
			height = SIZE * 0.5f;
			break;
		case 3:
			img = IMAGEMANAGER->findImage("button2 prev");
			height = SIZE * 0.5f;
			break;
		case 4:
			img = IMAGEMANAGER->findImage("destruct");
			width = SIZE * 0.5f;
			break;
		case 5:
			if (_miObject->second.frameX == 0)
			{
				img = IMAGEMANAGER->findImage("wall prev");
				frameX = 0;
			}
			else if (_miObject->second.frameX == 1)
			{
				img = IMAGEMANAGER->findImage("wall2 prev");
				frameX = 0;
			}
			else if (_miObject->second.frameX == 2)
			{
				img = IMAGEMANAGER->findImage("wall3 prev");
				frameX = 0;
			}
			else if (_miObject->second.frameX == 3)
			{
				img = IMAGEMANAGER->findImage("wall4 prev");
				frameX = 0;
				width = SIZE * 0.5f;
			}
			break;
		case 6:
			img = IMAGEMANAGER->findImage("roof");
			break;
		case 7:
			img = IMAGEMANAGER->findImage("foothold prev");
			break;
		}
		img->frameRender(
			Vector2(_vTiles[_miObject->second.tileY][_miObject->second.tileX]->getRect().getCenter()) + Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint - Vector2(width, height),
			frameX, 0);
	}

	if (_editMode != EDITMODE::TYPE) return;
	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (_vTiles[i][j]->getRect().getCenter().x < _clippingPoint.x ||
				_vTiles[i][j]->getRect().getCenter().x > _clippingPoint.x + _mapViewRc.getSize().x ||
				_vTiles[i][j]->getRect().getCenter().y < _clippingPoint.y ||
				_vTiles[i][j]->getRect().getCenter().y > _clippingPoint.y + _mapViewRc.getSize().y) continue;
				_typeImage->frameRender(
					Vector2(_vTiles[i][j]->getRect().getCenter()) + Vector2(_mapViewRc.left, _mapViewRc.top) - _clippingPoint
					, 0, _vTiles[i][j]->getOrderIndex());
		}
	}
}

void mapToolScene::backToTitle()
{
	SCENEMANAGER->loadScene(L"title");
}