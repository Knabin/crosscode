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
	PAGE_END,
};

struct tagEnemy
{
	int tileX;
	int tileY;
	int frameX;
	int frameY;
	int enemyType;
};

class mapToolScene : public scene
{
private:
	vector<vector<tile *>> _vTiles;
	vector<tagEnemy> _vEnemies;
	tile _sampleTiles[SAMPLENUMX * SAMPLENUMY];
	image* _mapBuffer;
	image* _uiImage;
	image* _terrainImage[PAGE_END];
	image* _terrainImageBig[PAGE_END];
	image* _objectImage;
	image* _objectImageBig;
	image* _enemyImage;
	image* _enemyImageBig;
	image* _typeImage;

	// UI 관련 RECT
	floatRect _mapViewRc;
	floatRect _editUiRc;
	floatRect _editButtonRc[(int)EDITMODE::END];
	floatRect _numButtonRc[PAGE_END];
	floatRect _plusRc;
	floatRect _minusRc;

	floatRect _typeRcs[5];
	int _selectType;

	NOWMODE _controlMode;
	EDITMODE _editMode;
	PENMODE _penMode;
	int _page;

	// 마우스 절대 좌표
	POINT _ptMouseAbs;	
	// 클리핑 좌표
	POINT _clippingPoint;

	// 현재 위치
	POINT _nowIndex;

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


	// 맵 사이즈 변경 관련 변수
	POINT _viewIndex;			// 지금 현재 화면에 존재하는 TILE의 최소 인덱스(좌측 상단)
	POINT _viewLastIndex;		// 지금 현재 화면에 존재하는 TILE의 최대 인덱스(존재하는 TILE들 중 우측 하단)
	POINT _viewMaxIndex;		// 지금 현재 화면에서 볼 수 있는 TILE의 최대 인덱스(우측 하단)
	POINT _selectIndex;			// 지금 마우스가 클릭하고 있는 TILE의 인덱스
	POINT _selectStartIndex;	// 선택됐을 당시 TILE의 인덱스

public:
	HDC getMapBufferDC() { return _mapBuffer->getMemDC(); }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void checkMapIndex();
	void checkMapSize();
	void checkSelectSample();
	void changeMapSize();
	void moveMapView();
	void selectUiButton();
	void renderChangeMap();
	void renderSelectTile();
	void renderPreviewTile();
	void resetSample();

	void saveMap();
	void loadMap();
	
	void drawMap();
	void redrawMap();

	void backToTitle();
};

