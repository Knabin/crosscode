#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"
#include "player.h"

HRESULT enemyManager::init()
{
	_vEnemy = OBJECTMANAGER->getObjectList(objectType::ENEMY);
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	return S_OK;
}

void enemyManager::update()
{
	_vEnemy = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		cout << i << endl;
		//enemy* e = dynamic_cast<enemy*>(_vEnemy[i]);
	}
}
