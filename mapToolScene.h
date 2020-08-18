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

	// UI ���� RECT
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

	// Ŭ���� ��ǥ
	Vector2 _clippingPoint;

	// ���� ��ġ
	POINT _nowIndex;

	// sample ���� ����
	floatRect _sampleRc;
	floatRect _sampleViewRc;
	POINT _sampleStart;
	POINT _sampleEnd;

	// �׷����� �� ���� ����
	bool _isStayKeyDown;
	floatRect _drawViewRc;
	POINT _drawStart;
	POINT _drawEnd;


	// �� ������ ���� ���� ����
	POINT _viewIndex;			// ���� ���� ȭ�鿡 �����ϴ� TILE�� �ּ� �ε���(���� ���)
	POINT _viewLastIndex;		// ���� ���� ȭ�鿡 �����ϴ� TILE�� �ִ� �ε���(�����ϴ� TILE�� �� ���� �ϴ�)
	POINT _viewMaxIndex;		// ���� ���� ȭ�鿡�� �� �� �ִ� TILE�� �ִ� �ε���(���� �ϴ�)
	POINT _selectIndex;			// ���� ���콺�� Ŭ���ϰ� �ִ� TILE�� �ε���
	POINT _selectStartIndex;	// ���õ��� ��� TILE�� �ε���

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

