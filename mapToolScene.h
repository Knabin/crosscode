#pragma once
#include "scene.h"
#include "tile.h"

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

enum class PAGE : int
{
	ONE,
	TWO,
	THREE,
	FOUR,
	END
};

class mapCamera : public gameObject
{
public:
	void move(float x, float y)
	{
		float moveX = x;
		float moveY = y;
		if ((_x + _rc.getWidth() * 0.5f >= CAMERA->getMapWidth() && x > 0) || (_x - _rc.getWidth() * 0.5f <= 0 && x < 0)) moveX = 0;
		if ((_y + _rc.getHeight() * 0.5f >= CAMERA->getMapHeight() && y > 0) || (_y - _rc.getHeight() * 0.5f <= 0 && y < 0)) moveY = 0;
		_rc.move(moveX, moveY); 
		_x = _rc.getCenter().x;
		_y = _rc.getCenter().y;
	}
};

class mapUi : public gameObject
{
private:
	image* _image;
	image* _terrain;
	floatRect _terrainRc;
	floatRect _objectRc;
	floatRect _enemyRc;
	floatRect _typeRc;
	floatRect _plusRc;
	floatRect _minusRc;

	floatRect _sampleRc;
	floatRect _sampleViewRc;

	floatRect _typeRcs[5];
	int _selectType;

	EDITMODE _editMode;
	PENMODE _penMode;
	PAGE _page;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void renderRelative(float x, float y);

	void setSampleViewRc(floatRect& rc) { _sampleViewRc = rc; }
	

	floatRect& getSampleRc() { return _sampleRc; }
	ORDER getTileType() { return (ORDER)_selectType; }
	EDITMODE& getEditMode() { return _editMode; }
	void setPenMode(PENMODE mode) { _penMode = mode; }
	PENMODE& getPenMode() { return _penMode; }
	PAGE& getPage() { return _page; }
};

class mapToolScene : public scene
{
private:
	vector<vector<tile *>> _vTiles;
	tile _sampleTiles[SAMPLENUMY][SAMPLENUMX];
	mapCamera* _cameraControl;
	mapUi* _editUi;
	NOWMODE _mode;

	POINT _ptMouseAbs;

	int _nowIndexX;
	int _nowIndexY;

	int _changeSizeX;
	int _changeSizeY;

	floatRect _tileViewRc;

	floatRect _sampleViewRc;
	int _sampleStartX;
	int _sampleStartY;
	int _sampleEndX;
	int _sampleEndY;

	bool _isStayKeyDown;
	floatRect _drawViewRc;
	int _drawStartX;
	int _drawStartY;
	int _drawEndX;
	int _drawEndY;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void saveMap();
	void loadMap();
	void startEdit();
	void endEdit();
	
	void drawMap();
};

