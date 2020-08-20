#include "stdafx.h"
#include "aStar.h"
#include "player.h"
#include "scene.h"
#include "enemy.h"

HRESULT aStar::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	_vEnemy = OBJECTMANAGER->getObjectList(objectType::ENEMY);
	_totalSize = _opensize =
		_stack = _maxX = _maxY = 0;
	_move = false;
	
	_scene = SCENEMANAGER->getCurrentScene();

	return S_OK;
}

void aStar::setTiles()
{
	_vTotalList.clear();
	if (_scene->getTiles().size() == 0) return;

	_maxX = _scene->getTiles()[0].size() - 1;
	//_maxX = _scene->getTiles()[0].size(); 원본
	_maxY = _scene->getTiles().size() - 1;
	//_maxY = _scene->getTiles().size(); 원본
	for (int i = 0; i < _maxY; ++i)
	{
		for (int j = 0; j < _maxX; j++)
		{
			_scene->getTiles()[i][j]->setIdX(j);
			_scene->getTiles()[i][j]->setIdY(i);
			_vTotalList.push_back(_scene->getTiles()[i][j]);
		}
	}

	_totalSize = _vTotalList.size();

	for (int i = 0; i < _totalSize; ++i)
	{
		_vTotalList[i]->setEnemy(false);
		_vTotalList[i]->setPlayer(false);
		_vTotalList[i]->setStart(false);
		_startTile = NULL;
		_endTile = NULL;
		_currentTile = NULL;
		if (_vTotalList[i]->getOrderIndex() == 6 || _vTotalList[i]->getOrderIndex() == 0 || _vTotalList[i]->getOrderIndex() == 7 || _vTotalList[i]->getOrderIndex() == 1)
		{
			_vTotalList[i]->setIsOpen(false);
		}
		else
		{
			_vTotalList[i]->setIsOpen(true);
		}
	}
}

void aStar::pathFinder(tile* currentTile)
{
	float tempTotalCost = 5000;
	tile* tempTile = NULL;
	_stack++;

	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 9; i++)
	{
		int ii = i / 3;
		int jj = i % 3;

		int k = (startY * _maxX) + startX + jj + (ii * _maxX);
		if (k < 0 || k >= _maxX * _maxY)
		{
			continue;
		}
		tile* node = _vTotalList[k];

		if (!node->getIsOpen()) continue;
		if (node->getStart()) continue;
		if (node->getOrderIndex() == 6) continue;
		if (node->getOrderIndex() == 7) continue;
		if (node->getOrderIndex() == 0) continue;
		if (node->getEnemy()) continue;
		if (node->getPlayer() && _currentTile->getStart())
		{
			_vOpenList.clear();
			_opensize = _vOpenList.size();

			break;
		}

		if (node->getOrderIndex() == 4 && _currentTile->getOrderIndex() == 1) continue;
		if (node->getOrderIndex() == 3 && _currentTile->getOrderIndex() == 1) continue;


		node->setParentTile(_currentTile);


		bool addObj = true;

		for (int i = 0; i < _opensize; ++i)
		{
			if (_vOpenList[i] == node)
			{
				addObj = false;
				break;
			}
		}

		if (!addObj) continue;

		_vOpenList.push_back(node);
		_opensize = _vOpenList.size();

	}

	for (int i = 0; i < _opensize; ++i)
	{

		int count = 0;
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) + abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		Vector2 center1 = _vOpenList[i]->getParentTile()->getRect().getCenter();
		Vector2 center2 = _vOpenList[i]->getRect().getCenter();

		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > SIZE) ? 14 : 10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];

			_vOpenList[i]->setIsOpen(false);
			continue;
		}
		_vOpenList[i]->setIsOpen(false);
	}

	if (tempTile == NULL)
	{
		_move = true;
		return;
	}
	if (tempTile == _endTile)
	{
		while (_currentTile->getParentTile() != NULL)
		{
			_vMove.push_back(_currentTile);
			_currentTile = _currentTile->getParentTile();

		}
		_move = true;
		return;
	}

	for (int i = 0; i < _opensize; ++i)
	{
		if (_vOpenList[i] == tempTile)
		{
			_vOpenList.erase(_vOpenList.begin() + i);
			_opensize = _vOpenList.size();
			break;
		}
	}

	_currentTile = tempTile;

	if (_stack > 300)
	{
		while (_currentTile->getParentTile() != NULL)
		{

			_vMove.push_back(_currentTile);

			_currentTile = _currentTile->getParentTile();
		}

		_move = true;
	}

}

vector<tile*> aStar::pathChecking(floatRect enemyRC)
{
	_vMove.clear();

	_move = false;

	for (int i = 0; i < _totalSize; ++i)
	{

		_vTotalList[i]->setIsOpen(true);
		_vTotalList[i]->setParentTile(NULL);
		for (int j = 0; j < _vEnemy.size(); ++j)
		{
			if (PtInRect(&_vTotalList[i]->getRect().getRect(), PointMake(_vEnemy[j]->getPosition().x, _vEnemy[j]->getPosition().y)))
			{
				if (_vEnemy[j]->getPosition().x == enemyRC.getCenter().x && _vEnemy[j]->getPosition().y == enemyRC.getCenter().y)
				{
					_vTotalList[i]->setStart(true);
					_currentTile = _vTotalList[i];
					_startTile = _currentTile;
					_vTotalList[i]->setIsOpen(false);

				}
				else
				{
					_vTotalList[i]->setEnemy(true);
					_vTotalList[i]->setIsOpen(false);
				}
			}
		}

		if (PtInRect(&_vTotalList[i]->getRect().getRect(), PointMake(_player->getPosition().x, _player->getRect().bottom)))
		{
			if (_vTotalList[i]->getStart())
				return _vMove;
			_vTotalList[i]->setPlayer(true);
			_endTile = _vTotalList[i];

			continue;
		}
	}

	if (_currentTile == NULL)
	{
		return _vMove;
	}

	while (_move == false)
		pathFinder(_currentTile);

	_vOpenList.clear();
	_opensize = 0;
	_stack = 0;

	_startTile->setStart(false);
	_startTile->setIsOpen(true);
	_endTile->setPlayer(false);

	int count = 0;
	for (int i = 0; i < _totalSize; i++)
	{
		if (_vTotalList[i]->getEnemy())
		{
			_vTotalList[i]->setEnemy(false);
			_vTotalList[i]->setIsOpen(true);
			count++;
		}
		if (count >= _vEnemy.size() - 1)
			break;
	}

	_startTile = NULL;
	_endTile = NULL;
	_currentTile = NULL;

	return _vMove;
}

void aStar::render()
{
	//_player->getRect().render(getMemDC());
	//for (int i = 0; i < _totalSize; ++i)
	//{
	//	char str[20];
	//	sprintf_s(str, "%d", _vTotalList[i]->getOrderIndex());
	//	//sprintf_s(str, "%d,%d,%d", _vTotalList[i]->getPlayer(), _vTotalList[i]->getStart(), _vTotalList[i]->getEnemy());
	//	//sprintf_s(str, "%d,%d", _vTotalList[i]->getIdX(), _vTotalList[i]->getIdY());
	//	TextOut(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, str, strlen(str));
	//}
}
