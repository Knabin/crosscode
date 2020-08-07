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

	// ���콺 ���� ��ǥ(�ʿ� ���� �� ����)
	POINT _ptMouseAbs;
	// Ŭ���� ��ǥ
	POINT _clippingPoint;

	// ���� ��ġ
	POINT _nowIndex;
	// ������ ����
	POINT _changeIndex;
	floatRect _changeRc;

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


	// �׽�Ʈ��
	bool _test;
	POINT _testViewIndex;			// ���� ���� ȭ�鿡 �����ϴ� TILE�� �ּ� �ε���(���� ���)
	POINT _testViewLastIndex;		// ���� ���� ȭ�鿡 �����ϴ� TILE�� �ִ� �ε���(�����ϴ� TILE�� �� ���� �ϴ�)
	POINT _testViewMaxIndex;		// ���� ���� ȭ�鿡�� �� �� �ִ� TILE�� �ִ� �ε���(���� �ϴ�)
	POINT _testSelectIndex;			// ���� ���콺�� Ŭ���ϰ� �ִ� TILE�� �ε���
	POINT _testSelectStartIndex;	// ���� ���۵� TILE�� �ε���

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

