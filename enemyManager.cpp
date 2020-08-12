#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{
	_as = new aStar;

	_count = 0;

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	enemyDead();//에너미 사망
}

void enemyManager::render()
{
}

void enemyManager::enemyDead()
{
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::Monster);

	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);

		cout << e->getEnemyHP() << endl;

		if (e->getEnemyHP() <= 0)//에너미 체력이 0이하가 되면
		{
			_count++;
			if (_count % 5 == 0)
			{
				e->setEnemyIsActive(false);//에너미 삭제
				_count = 0;
			}
		}
	}
}
