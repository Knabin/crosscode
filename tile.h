#pragma once
#include "gameObject.h"

#define SIZE 48
#define MAXNUMX 50
#define MAXNUMY 50

#define SAMPLESIZE 32
#define SAMPLENUMX 16
#define SAMPLENUMY 18

enum class ORDER : int
{
	ZERO,			// ������ �� �ִ� ��(��, �ϴ� ��)
	ONE,			// 1��(�⺻)
	TWO,			// 2��
	THREE,			// 3��
	NONE,			// �̵� �Ұ���
	END
};

class tile : public gameObject
{
private:
	int _terrainX;
	int _terrainY;
	int _objectX;
	int _objectY;

	ORDER _order;

public:
	tile();

	void setTiles(int terX, int terY, int objX, int objY, int order);

	int getTerrainX() { return _terrainX; }
	void setTerrainX(int x) { _terrainX = x; }

	int getTerrainY() { return _terrainY; }
	void setTerrainY(int y) { _terrainY = y; }

	int getObjectX() { return _objectX; }
	int getObjectY() { return _objectY; }

	int getOrderIndex() { return (int)_order; }
	void setOrder(ORDER order) { _order = order; }

	void setTileRc(int left, int top) { _rc = RectMake(left, top, SIZE, SIZE); }
};

