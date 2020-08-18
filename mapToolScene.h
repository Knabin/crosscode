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
	TERRAIN_ONE,
	TERRAIN_TWO,
	TERRAIN_THREE,
	TERRAIN_END,
};

enum
{
	OBJECT_ONE,
	OBJECT_TWO,
	OBJECT_THREE,
	OBJECT_FOUR,
	OBJECT_END,
};

enum
{
	AUTO_T,
	AUTO_L,
	AUTO_R,
	AUTO_B,
	AUTO_END
};

struct tagEnemy
{
	int tileX;
	int tileY;
	int frameX;
	int frameY;
	int enemyType;
};

struct tagObject
{
	int tileX;
	int tileY;
	int frameX;
	int frameY;
	int pageNum;
	int objectType;
};

struct tagPoint
{
	int x;
	int y;

	tagPoint(int px, int py)
	{
		x = px;
		y = py;
	}

public:
	bool operator()(const tagPoint& p1, const tagPoint& p2) const
	{
		if (p1.y != p2.y)
			return p1.y < p2.y;
		else
			return p1.x < p2.x;
	}
	bool operator < (const tagPoint& p1) const
	{
		if (y != p1.y)
			return y < p1.y;
		else
			return x < p1.x;
	}
};

class mapToolScene : public scene
{
private:
	vector<vector<tile *>> _vTiles;
	vector<tagEnemy> _vEnemies;
	vector<vector<POINT>> _vAutoIndexs;
	//POIN
	map<tagPoint, tagObject> _mObject;
	map<tagPoint, tagObject>::iterator _miObject;
	tile _sampleTiles[SAMPLENUMX * SAMPLENUMY];
	image* _uiImage;
	image* _terrainImage[TERRAIN_END];
	image* _terrainImageBig[TERRAIN_END];
	image* _objectImage[OBJECT_END];
	image* _objectImageBig[OBJECT_END];
	image* _enemyImage;
	image* _enemyImageBig;
	image* _typeImage;

	// UI 관련 RECT
	floatRect _mapViewRc;
	floatRect _editUiRc;
	floatRect _editButtonRc[(int)EDITMODE::END];
	floatRect _numButtonRc[TERRAIN_END];
	floatRect _numButtonObjRc[OBJECT_END];
	floatRect _plusRc;
	floatRect _minusRc;

	floatRect _typeRcs[7];
	int _selectType;

	NOWMODE _controlMode;
	EDITMODE _editMode;
	PENMODE _penMode;
	int _page;

	// 클리핑 좌표
	Vector2 _clippingPoint;

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
	void setVendor();
	void renderChangeMap();
	void renderSelectTile();
	void renderPreviewTile();
	void resetSample();

	void saveMap();
	void loadMap();
	
	void checkAutoTile(int indexX, int indexY);
	void redrawMap();

	void backToTitle();
};

