#pragma once
#include "tile.h"
#include "gameNode.h"
class aStar :public gameNode
{
private:
	class scene* _scene;
	

	//��ü Ÿ���� ���� ����
	vector<tile*>			_vTotalList;

	//�� �� �ִ� Ÿ���� ���� ����
	vector<tile*>			_vOpenList;

	//������ ����
	vector<tile*>			 _vMove;

	tile* _startTile;			//���� Ÿ��
	tile* _endTile;			//�� Ÿ��
	tile* _currentTile;		//���� Ÿ��(���)

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

