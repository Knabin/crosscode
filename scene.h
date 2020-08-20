#pragma once
#include "gameNode.h"
#include "tile.h"
#include "aStar.h"

class scene : public gameNode
{
public:
	typedef vector<tile*>						vTileOneLine;
	typedef vector<tile*>::iterator				viTileOneLine;
	typedef vector<vector<tile*>>				vTiles;
	typedef vector<vector<tile*>>::iterator		viTiles;
protected:
	// 해당 씬 타일 관련 변수
	vTiles _vTiles;
	viTiles _viTiles;

	aStar* _as;

	int _maxX;
	int _maxY;

	// 캐릭터 이동 위치 관련 변수
	floatPoint _previous;
	floatPoint _next;

	// 씬 이동 관련 변수
	Vector2 _nextPoint;
	string _nextScene;
	Vector2 _prevPoint;
	string _prevScene;
	bool _canMoveNextScene;

public:
	virtual ~scene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getDataFromFile(string fileName);
	void getTilesFromFile(string fileName);
	void getEnemiesFromFile(string fileName);

	vTiles& getTiles() { return _vTiles; }
};

