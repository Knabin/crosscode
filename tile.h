#pragma once
#include "gameObject.h"

#define SIZE 48
#define MAXTILEX 50
#define MAXTILEY 50
#define MAXMAPTOOLX 23
#define MAXMAPTOOLY 19

#define SAMPLESIZE 32
#define SAMPLENUMX 16
#define SAMPLENUMY 18

enum class ORDER : int
{
	ZERO,			// ¶³¾îÁú ¼ö ÀÖ´Â °÷(¹°, ÇÏ´Ã µî)
	ONE,			// 1Ãþ(±âº»)
	TWO,			// 2Ãþ
	THREE,			// 3Ãþ
	NONE,			// ÀÌµ¿ ºÒ°¡´É
	END
};

class tile : public gameObject
{
private:
	int _terrainType;
	int _objectType;

	int _terrainX;
	int _terrainY;
	int _objectX;
	int _objectY;

	int _pageNum;

	ORDER _order;

public:
	tile();

	void setTiles(int terX, int terY, int objX, int objY, int order);
	void setTiles(int terX, int terY, int objX, int objY, int pageNum, int order);

	bool canView() {
		if (CAMERA->getRect().left < _rc.right &&
			CAMERA->getRect().right > _rc.left &&
			CAMERA->getRect().top < _rc.bottom &&
			CAMERA->getRect().bottom > _rc.top) return true;
		return false;
	}

	bool canView(floatRect rc)
	{
		if (rc.left < _rc.right && rc.right > _rc.left &&
			rc.top < _rc.bottom && rc.bottom > _rc.top) return true;
		return false;
	}

	virtual void render();

	// ======== getter / setter ========

	int getTerrainType() { return _terrainType; }
	void setTerrainType(int type) { _terrainType = type; }

	int getTerrainX() { return _terrainX; }
	void setTerrainX(int x) { _terrainX = x; }

	int getTerrainY() { return _terrainY; }
	void setTerrainY(int y) { _terrainY = y; }

	int getObjectX() { return _objectX; }
	void setObjectX(int x) { _objectX = x; }

	int getObjectY() { return _objectY; }
	void setObjectY(int y) { _objectY = y; }

	int getOrderIndex() { return (int)_order; }
	void setOrder(ORDER order) { _order = order; }

	int getPageNum() { return _pageNum; }
	void setPageNum(int page) { _pageNum = page; }

	void setTileRc(int left, int top) { _rc = RectMake(left, top, SIZE, SIZE); }


};

