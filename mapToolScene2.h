#pragma once
#include "tile.h"
#include "scene.h"

enum class NOWMODE : int
{
	NONE,
	MAPSIZE,
	EDIT,
	END
};

enum class EDITMODE : int
{
	TERRAIN,
	OBJECT,
	ENEMY,
	TYPE,
	END
};

enum class PENMODE : int
{
	PLUS,
	MINUS,
	END
};

enum
{
	PAGE_ONE,
	PAGE_TWO,
	PAGE_THREE,
	PAGE_FOUR,
	PAGE_END,
};

class mapToolScene2 : public scene
{
private:
	vector<vector<tile *>> _vTiles;
	tile _sampleTiles[SAMPLENUMX * SAMPLENUMY];
	image* _mapBuffer;
	image* _uiImage;
	image* _terrainImage[PAGE_END];
	image* _terrainImageBig[PAGE_END];
	image* _objectImage[PAGE_END];
	image* _enemyImage;

	floatRect _mapViewRc;
	floatRect _editUiRc;
	floatRect _terrainRc;
	floatRect _objectRc;
	floatRect _enemyRc;
	floatRect _typeRc;
	floatRect _plusRc;
	floatRect _minusRc;

	floatRect _typeRcs[5];
	int _selectType;

	NOWMODE _controlMode;
	EDITMODE _editMode;
	PENMODE _penMode;
	int _page;

	// 마우스 절대 좌표(필요 없을 것 같음)
	POINT _ptMouseAbs;
	// 클리핑 좌표
	POINT _clippingPoint;

	// 현재 위치
	POINT _nowIndex;
	// 사이즈 변경
	POINT _changeIndex;
	floatRect _changeRc;

	// sample 관련 변수
	floatRect _sampleRc;
	floatRect _sampleViewRc;
	POINT _sampleStart;
	POINT _sampleEnd;

	// 그려지는 곳 관련 변수
	bool _isStayKeyDown;
	floatRect _drawViewRc;
	POINT _drawStart;
	POINT _drawEnd;


	// 테스트용
	bool _test;
	POINT _testViewIndex;			// 지금 현재 화면에 존재하는 TILE의 최소 인덱스(좌측 상단)
	POINT _testViewLastIndex;		// 지금 현재 화면에 존재하는 TILE의 최대 인덱스(존재하는 TILE들 중 우측 하단)
	POINT _testViewMaxIndex;		// 지금 현재 화면에서 볼 수 있는 TILE의 최대 인덱스(우측 하단)
	POINT _testSelectIndex;			// 지금 마우스가 클릭하고 있는 TILE의 인덱스
	POINT _testSelectStartIndex;	// 선택 시작된 TILE의 인덱스

	floatRect _testRc;
	floatRect _testRc2;

public:
	HDC getMapBufferDC() { return _mapBuffer->getMemDC(); }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void forTesting();
	void checkMapSize();
	void changeMapSize();
	void moveMapView();
	void selectUiButton();

	void saveMap();
	void loadMap();
	void startEdit();
	void endEdit();

	void drawMap();
	void redrawMap();
};

