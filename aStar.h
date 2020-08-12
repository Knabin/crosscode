#pragma once
#include "tile.h"
#include "gameNode.h"
class aStar :public gameNode
{
private:
	class scene* _scene;
	

	//전체 타일을 담을 벡터
	vector<tile*>			_vTotalList;

	//갈 수 있는 타일을 담을 벡터
	vector<tile*>			_vOpenList;

	//움직일 벡터
	vector<tile*>			 _vMove;

	tile* _startTile;			//시작 타일
	tile* _endTile;			//끝 타일
	tile* _currentTile;		//현재 타일(노드)

	//vector<tile*> _vEnemy;

	class player* _player;
	vector<class gameObject*> _vEnemy;

	int _totalSize;
	int _opensize;
	bool _move;
	int _stack;


	int _maxX;
	int _maxY;

	//vector<floatRect> _enemyRect;

public:
	HRESULT init();

	void setTiles();
	void pathFinder(tile* currentTile);
	//void clearEnemyRect() { _enemyRect.clear(); }
	//void enemyRectPush(floatRect enemyRC) { _enemyRect.push_back(enemyRC); }
	vector<tile*> pathChecking(floatRect enemyRC);
	void setScene(scene* s) { _scene = s; }

	int getIndexX(int i) { int idX = i % _maxX; return idX; }
	int getIndexY(int i) { int idY = i / _maxY; return idY; }

	void render();
};

