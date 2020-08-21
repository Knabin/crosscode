#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"
#include "player.h"

HRESULT enemyManager::init()
{
	_sc = SCENEMANAGER->getCurrentScene();
	_as = new aStar;

	_vEnemy = OBJECTMANAGER->getObjectList(objectType::ENEMY);
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	_time = _index = 0;
	_count = 0;

	return S_OK;
}

void enemyManager::update()
{
	_time++;
	_vEnemy = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	if (_sc != SCENEMANAGER->getCurrentScene() && _vEnemy.size() > 0)
	{
		_sc = SCENEMANAGER->getCurrentScene();
		_as->init();
		_as->setTiles();
	}

	if (_time % 10 == 0 && _vEnemy.size() != NULL)
	{
		enemy* e = dynamic_cast<enemy*>(_vEnemy[_index]);
		if (e->getEnemyHP() < 100 && !e->getEnemyIsAttack() && e->getMove().size() == NULL)
		{
			e->setMove(_as->pathChecking(e->getRect()));
		}
		_time = 0;
		_index++;
		if (_index >= _vEnemy.size())
			_index = 0;

	}

	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		enemy* e = dynamic_cast<enemy*>(_vEnemy[i]);

		if (e->getMove().size() != NULL)
			for (int j = 0; j < _vEnemy.size(); j++)
			{
				if (i == j) continue;
				if (PtInRect(&e->getMove()[e->getMove().size() - 1]->getRect().getRect(), PointMake(_vEnemy[j]->getRect().getCenter().x, _vEnemy[j]->getRect().getCenter().y)))
				{
					e->clearMove();
					e->setMove(_as->pathChecking(e->getRect()));
					break;
				}
			}
	}


	enemyDead();//에너미 사망
}

void enemyManager::render()
{
	_as->render();
}

void enemyManager::enemyDead()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(_vEnemy[i]);
		if (e->getEnemyHP() <= 0)//에너미의 현재 체력이 0이하가 되면
		{

			_count++;
			if (_count % 5 == 0)
			{
				e->setIsAlive(false);//에너미 삭제
				//OBJECTMANAGER->removeObject(objectType::ENEMY, e);
				// 이거 켜면 터짐??? 잠만
				//_vEnemy.erase(_vEnemy.begin() + i);
				_player->setPlayerEXP(10);
				
				_count = 0;

				break;
			}



		}
	}

	if (_index >= _vEnemy.size())
		_index = 0;
}
