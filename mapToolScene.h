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
	int objectType;
};

class mapToolScene : public scene
{
private:
	vector<vector<tile *>> _vTiles;
	vector<tagEnemy> _vEnemies;
	vector<tagObject> _vObject;
	tile _sampleTiles[SAMPLENUMX * SAMPLENUMY];
	image* _mapBuffer;
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

	floatRect _typeRcs[6];
	int _selectType;

	NOWMODE _controlMode;
	EDITMODE _editMode;
	PENMODE _penMode;
	int _page;

	// ���콺 ���� ��ǥ
	POINT _ptMouseAbs;	
	// Ŭ���� ��ǥ
	POINT _clippingPoint;

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
	void setVendor();
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

