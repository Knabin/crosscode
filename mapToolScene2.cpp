#include "stdafx.h"
#include "mapToolScene2.h"
#include "button.h"

HRESULT mapToolScene2::init()
{
	_controlMode = NOWMODE::NONE;

	CAMERA->setCameraMode(CAMERASTATE::NONE);

	_test = true;

	_nowIndex.x = _nowIndex.y = _changeIndex.x = _changeIndex.y = 9;

	_sampleStart.x = _sampleStart.y = _sampleEnd.x = _sampleEnd.y = -1;
	_drawStart.x = _drawStart.y = _drawEnd.x = _drawEnd.y = -1;
	_testViewIndex.x = _testViewIndex.y = 0;

	_isStayKeyDown = false;

	// 전체 타일 출력할 새로운 buffer 선언
	_mapBuffer = IMAGEMANAGER->addImage("mapBuffer", "images/tilenull.bmp", MAXTILEX * SIZE, MAXTILEY * SIZE, false, RGB(0,0,0));

	// ========== rect 초기화 ==========
	_editUiRc.set(0, 0, 600, 850);
	_editUiRc.setCenter(WINSIZEX - _editUiRc.getSize().x * 0.5f, WINSIZEY * 0.5f);

	_mapViewRc.set(0, 0, 1104, 912);
	_mapViewRc.setLeftTop(50, 130);
	_clippingPoint.x = 0;
	_clippingPoint.y = 0;

	_terrainRc.set(0, 0, 132, 57);
	_objectRc.set(0, 0, 132, 57);
	_enemyRc.set(0, 0, 132, 57);
	_typeRc.set(0, 0, 132, 57);
	_plusRc.set(0, 0, 90, 72);
	_minusRc.set(0, 0, 90, 72);

	_terrainRc.setLeftTop(_editUiRc.left + 6, _editUiRc.top + 5);
	_objectRc.setLeftTop(_terrainRc.right, _terrainRc.top);
	_enemyRc.setLeftTop(_objectRc.right, _objectRc.top);
	_typeRc.setLeftTop(_enemyRc.right, _enemyRc.top);
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

	// 버튼 이미지
	IMAGEMANAGER->addFrameImage("saveload", "images/buttons_saveload.bmp", 132, 126, 1, 2, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("exit", "images/buttons_editexit.bmp", 66, 62, 1, 1, true, RGB(255, 0, 255));

	// ui 전체 이미지
	_uiImage = IMAGEMANAGER->addImage("edit ui", "images/ui_edit.bmp", 600, 850, true, RGB(255, 0, 255));

	// 샘플 이미지
	_terrainImage[PAGE_ONE] = IMAGEMANAGER->addFrameImage("terrain", "images/tiletest.bmp", 512, 576, 16, 18, true, RGB(255, 0, 255));
	_terrainImageBig[PAGE_ONE] = IMAGEMANAGER->addFrameImage("terrain b", "images/tiletestbig.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	
	// 빈 타일
	IMAGEMANAGER->addImage("tile null", "images/tilenull.bmp", 48, 48, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("tile change", "images/tilechange.bmp", SIZE * MAXTILEX, SIZE * MAXTILEY, false, RGB(0, 0, 0));

	// 오더 버튼 이미지
	IMAGEMANAGER->addFrameImage("type", "images/buttons_type.bmp", 1024, 575, 2, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tile type", "images/typetile.bmp", 48, 240, 1, 5, true, RGB(255, 0, 255));

	// 버튼 추가
	button* save = new button();
	save->init("saveload", WINSIZEX / 2 - 100, 66, 0, 0, bind(&mapToolScene2::saveMap, this));
	save->setName("save button");

	button* load = new button();
	load->init("saveload", WINSIZEX / 2 + 100, 66, 0, 1, bind(&mapToolScene2::loadMap, this));
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
	_testRc.set(WINSIZEX / 2-50, WINSIZEY - 100, 100, 50);
	_testRc2.set(WINSIZEX / 2+50, WINSIZEY - 100, 100, 50);

	redrawMap();

	return S_OK;
}

void mapToolScene2::release()
{
}

void mapToolScene2::update()
{
	forTesting();

	_ptMouseAbs.x = _ptMouse.x + CAMERA->getRect().left;
	_ptMouseAbs.y = _ptMouse.y + CAMERA->getRect().top;

	_testSelectIndex.x = (_ptMouse.x + _clippingPoint.x - _mapViewRc.left) / SIZE;
	_testSelectIndex.y = (_ptMouse.y + _clippingPoint.y - _mapViewRc.top) / SIZE;

	if (_testSelectIndex.x < 0) _testSelectIndex.x = 0;
	else if (_testSelectIndex.x >= MAXTILEX) _testSelectIndex.x = MAXTILEX - 1;
	else if (_testSelectIndex.x > _testViewMaxIndex.x) 
		_testSelectIndex.x = _testViewMaxIndex.x;

	if (_testSelectIndex.y < 0) _testSelectIndex.y = 0;
	else if (_testSelectIndex.y >= MAXTILEY) _testSelectIndex.y = MAXTILEY - 1;
	else if (_testSelectIndex.y > _testViewMaxIndex.y) 
		_testSelectIndex.y = _testViewMaxIndex.y;

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

	switch (_controlMode)
	{
	case NOWMODE::NONE:
		checkMapSize();
		break;
	case NOWMODE::MAPSIZE:
		changeMapSize();
		break;
	case NOWMODE::EDIT:
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
	_uiImage->render(getMemDC(), _editUiRc.left, _editUiRc.top);
	_mapViewRc.render(getMemDC());

	switch (_editMode)
	{
	case EDITMODE::TERRAIN:
		_terrainImage[_page]->render(getMemDC(), _sampleRc.left, _sampleRc.top);
		break;
	case EDITMODE::OBJECT:
		break;
	case EDITMODE::ENEMY:
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
	
	drawMap();

	if (_controlMode == NOWMODE::MAPSIZE)
	{
		int width;
		int height;

		if (_testSelectIndex.x >= _vTiles[0].size() && _testSelectIndex.y >= _vTiles.size())
		{
			width = _vTiles[_nowIndex.y][_nowIndex.x]->getRect().right - _clippingPoint.x + (_testSelectIndex.x - _nowIndex.x) * SIZE;
			height = _vTiles[_nowIndex.y][_nowIndex.x]->getRect().bottom - _clippingPoint.y + (_testSelectIndex.y - _nowIndex.y) * SIZE;
		}
		else if (_testSelectIndex.x >= _vTiles[0].size())
		{
			width = _vTiles[_testSelectIndex.y][_nowIndex.x]->getRect().right - _clippingPoint.x + (_testSelectIndex.x - _nowIndex.x) * SIZE;
			height = _vTiles[_testSelectIndex.y][_nowIndex.x]->getRect().bottom - _clippingPoint.y;
		}
		else if (_testSelectIndex.y >= _vTiles.size())
		{
			width = _vTiles[_nowIndex.y][_testSelectIndex.x]->getRect().right - _clippingPoint.x;
			height = _vTiles[_nowIndex.y][_testSelectIndex.x]->getRect().bottom - _clippingPoint.y + (_testSelectIndex.y - _nowIndex.y) * SIZE;
		}
		else
		{
			width = _vTiles[_testSelectIndex.y][_testSelectIndex.x]->getRect().right - _clippingPoint.x;
			height = _vTiles[_testSelectIndex.y][_testSelectIndex.x]->getRect().bottom - _clippingPoint.y;
		}

		//if (_testSelectIndex.x >= _vTiles[0].size())
		//	width = _vTiles[_nowIndex.y][_nowIndex.x]->getRect().right - _clippingPoint.x + (_testSelectIndex.x - _nowIndex.x) * SIZE;
		//else width = _vTiles[_testSelectIndex.y][_testSelectIndex.x]->getRect().right - _clippingPoint.x;

		//if (_testSelectIndex.y >= _vTiles.size())
		//	height = _vTiles[_nowIndex.y][_nowIndex.x]->getRect().bottom - _clippingPoint.y + (_testSelectIndex.y - _nowIndex.y) * SIZE;
		//else height = _vTiles[_testSelectIndex.y][_testSelectIndex.x]->getRect().bottom - _clippingPoint.y;

		IMAGEMANAGER->findImage("tile change")->alphaRender(getMemDC(),
			_mapViewRc.left, _mapViewRc.top, 0, 0, width, height, 100);
	}
	char str[10];
	sprintf_s(str, "%d, %d", _testSelectIndex.x, _testSelectIndex.y);
	TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 10, str, strlen(str));
}

void mapToolScene2::forTesting()
{
	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (_vTiles[i][j]->getRect().right < _clippingPoint.x || _vTiles[i][j]->getRect().bottom < _clippingPoint.y) continue;
			_testViewIndex.x = j;
			_testViewIndex.y = i;
			_testViewLastIndex.x = _testViewMaxIndex.x = j + MAXMAPTOOLX;
			_testViewLastIndex.y = _testViewMaxIndex.y = i + MAXMAPTOOLY;
			if (_testViewLastIndex.x > _nowIndex.x) _testViewLastIndex.x = _nowIndex.x;
			if (_testViewLastIndex.y > _nowIndex.y) _testViewLastIndex.y = _nowIndex.y;
			return;
		}
	}

	
}

void mapToolScene2::checkMapSize()
{
	if (_testSelectIndex.x == _nowIndex.x && _testSelectIndex.y == _nowIndex.y)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_testSelectStartIndex.x = _testSelectIndex.x;
			_testSelectStartIndex.y = _testSelectIndex.y;
			_controlMode = NOWMODE::MAPSIZE;
		}
	}
}

void mapToolScene2::changeMapSize()
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		// 놓으면 해야 할 것
		// 놓았을 때 사이즈만큼 늘리거나 줄여야 함
		// 우선 늘려야 하는지 줄여야 하는지 체크하고
		// for문 돌면서 체크하고
		// 맵 다시 그리기
		_test = false;
		POINT newIndex = { _testSelectIndex.x, _testSelectIndex.y };

		// X축이 늘어난 경우
		if (_testSelectStartIndex.x < _testSelectIndex.x)
		{
			for (int i = 0; i <= _nowIndex.y; ++i)
			{
				for (int j = 0; j < _testSelectIndex.x - _testSelectStartIndex.x; ++j)
				{
					tile* t = new tile();
					t->setTileRc(_vTiles[i].size() * SIZE, i * SIZE);
					_vTiles[i].push_back(t);
				}
			}
			_nowIndex.x += _testSelectIndex.x - _testSelectStartIndex.x;
		}
		// X축이 줄어든 경우
		else if (_testSelectStartIndex.x > _testSelectIndex.x)
		{
			for (int i = 0; i <= _nowIndex.y; ++i)
			{
				for (int j = 0; j < _testSelectStartIndex.x - _testSelectIndex.x; ++j)
				{
					_vTiles[i][_vTiles[i].size() - 1]->release();
					SAFE_DELETE(_vTiles[i][_vTiles[i].size() - 1]);
					_vTiles[i].pop_back();
				}
			}
			_nowIndex.x += _testSelectIndex.x - _testSelectStartIndex.x;
		}

		// Y축이 늘어난 경우
		if (_testSelectStartIndex.y < _testSelectIndex.y)
		{
			for (int i = 0; i < _testSelectIndex.y - _testSelectStartIndex.y; ++i)
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
			_nowIndex.y += _testSelectIndex.y - _testSelectStartIndex.y;
		}

		// Y축이 줄어든 경우
		else if (_testSelectStartIndex.y > _testSelectIndex.y)
		{
			for (int i = 0; i < _testSelectStartIndex.y - _testSelectIndex.y; ++i)
			{
				for (int j = 0; j <= _nowIndex.x; ++j)
				{
					_vTiles[_vTiles.size() - 1][j]->release();
					SAFE_DELETE(_vTiles[_vTiles.size() - 1][j]);
				}
				_vTiles[_vTiles.size() - 1].clear();
				_vTiles.pop_back();
			}
			_nowIndex.y += _testSelectIndex.y - _testSelectStartIndex.y;
		}

		_controlMode = NOWMODE::NONE;
		redrawMap();
	}
}

void mapToolScene2::moveMapView()
{
}

void mapToolScene2::selectUiButton()
{
	// TODO: EDIT MODE 바뀔 때마다 select rect랑 index 비워 줘야 함
	if (PtInRect(&_editUiRc.getRect(), _ptMouse))
	{
		_controlMode = NOWMODE::EDIT;
	}

	// Terrain 버튼
	if (PtInRect(&_terrainRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_editMode = EDITMODE::TERRAIN;
			_penMode = PENMODE::PLUS;
		}
	}

	// Object 버튼
	if (PtInRect(&_objectRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_editMode = EDITMODE::OBJECT;
			_penMode = PENMODE::PLUS;
		}
	}

	// Enemy 버튼
	if (PtInRect(&_enemyRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_editMode = EDITMODE::ENEMY;
			_penMode = PENMODE::PLUS;
		}
	}

	// Type 버튼
	if (PtInRect(&_typeRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_editMode = EDITMODE::TYPE;
			_penMode = PENMODE::PLUS;
			_selectType = 0;
		}
	}

	// 연필 버튼
	if (PtInRect(&_plusRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_penMode = PENMODE::PLUS;
			if (_editMode == EDITMODE::TYPE) _selectType = 0;
		}
	}

	// 지우개 버튼
	if (PtInRect(&_minusRc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_penMode = PENMODE::MINUS;
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
					_penMode = PENMODE::PLUS;
					_selectType = i;
					break;
				}
			}
		}
	}

}


void mapToolScene2::saveMap()
{
}

void mapToolScene2::loadMap()
{
}

void mapToolScene2::startEdit()
{
}

void mapToolScene2::endEdit()
{
}

void mapToolScene2::drawMap()
{
	_mapBuffer->render(getMemDC(), _mapViewRc.left, _mapViewRc.top, _clippingPoint.x, _clippingPoint.y, _mapViewRc.getWidth(), _mapViewRc.getHeight());
}

void mapToolScene2::redrawMap()
{
	IMAGEMANAGER->deleteImage("mapBuffer");
	_mapBuffer = IMAGEMANAGER->addImage("mapBuffer", "images/tilenull.bmp", MAXTILEX * SIZE, MAXTILEY * SIZE, false, RGB(0, 0, 0));

	for (int i = 0; i <= _nowIndex.y; ++i)
	{
		for (int j = 0; j <= _nowIndex.x; ++j)
		{
			if (_vTiles[i][j]->getTerrainX() != -1)
				_terrainImageBig[_vTiles[i][j]->getTerrainType()]->frameRender(getMapBufferDC(), _vTiles[i][j]->getRect().left, _vTiles[i][j]->getRect().top, _vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());
			else
				_vTiles[i][j]->getRect().render(getMapBufferDC());
		}
	}
}
