#pragma once
#include "gameObject.h"

#define SIZE 48
#define MAXTILEX 100
#define MAXTILEY 100
#define MAXMAPTOOLX 23
#define MAXMAPTOOLY 19

#define SAMPLESIZE 32
#define SAMPLENUMX 16
#define SAMPLENUMY 18

enum class ORDER : int
{
	ZERO,			// 떨어질 수 있는 곳(물, 하늘 등)
	ONE,			// 1층(기본)
	TWO,			// 2층
	THREE,			// 3층
	BORDER,			// 2층 모서리(Z-ORDER용)
	BORDER2,		// 갈 수 있는 모서리
	NONE,			// 이동 불가능
	END
};

enum
{
	NONE,
	AUTOTILE1,
	AUTOTILE2,
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

	int _terrainImageNum;
	int _objectImageNum;

	ORDER _order;

	bool _isOpen;

	tile* _parentTile;

	float _totalCost;		//F
	float _costFromStart;	//G
	float _costToGoal;		//H

	int _idX;
	int _idY;

	bool _player;
	bool _enemy;
	bool _start;

public:
	tile();

	void setTiles(int terX, int terY, int objX, int objY, int order);
	void setTiles(int terX, int terY, int objX, int objY, int pageNum, int objPagenum, int order);

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
	void checkTerrainType()
	{
		switch (_terrainImageNum)
		{
		case 0:
			_terrainType = NONE;
			break;
		case 1:
			if (_terrainX >= 8 && _terrainX < 12 && _terrainY >= 0 && _terrainY <= 3)
				_terrainType = AUTOTILE1;
			else if (_terrainX >= 12 && _terrainX <= 15 && _terrainY >= 0 && _terrainY <= 3)
				_terrainType = AUTOTILE2;
			else
				_terrainType = NONE;
			break;
		case 2:
			_terrainType = NONE;
			break;
		}
	}

	// ======== getter / setter ========

	int getTerrainType() { return _terrainType; }
	void setTerrainType(int type) { _terrainType = type; }

	int getTerrainX() { return _terrainX; }
	void setTerrainX(int x) { _terrainX = x; this->checkTerrainType(); }

	int getTerrainY() { return _terrainY; }
	void setTerrainY(int y) { _terrainY = y; this->checkTerrainType(); }

	int getObjectX() { return _objectX; }
	void setObjectX(int x) { _objectX = x; }

	int getObjectY() { return _objectY; }
	void setObjectY(int y) { _objectY = y; }

	int getOrderIndex() { return (int)_order; }
	void setOrder(ORDER order) { _order = order; }

	int getTerrainImageNum() { return _terrainImageNum; }
	void setTerrainImageNum(int imageNum) { _terrainImageNum = imageNum; }

	int getObjectImageNum() { return _objectImageNum; }
	void setObjectImageNum(int imageNum) { _objectImageNum = imageNum; }

	void setTileRc(int left, int top) { _rc = RectMake(left, top, SIZE, SIZE); }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }

	void setParentTile(tile* t) { _parentTile = t; }
	tile* getParentTile() { return _parentTile; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setIdX(int x) { _idX = x; }
	int getIdX() { return _idX; }
	void setIdY(int y) { _idY = y; }
	int getIdY() { return _idY; }

	void setPlayer(bool player) { _player = player; }
	bool getPlayer() { return _player; }
	void setEnemy(bool enemy) { _enemy = enemy; }
	bool getEnemy() { return _enemy; }
	void setStart(bool Start) { _start = Start; }
	bool getStart() { return _start; }
};

