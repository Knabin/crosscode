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
	enemyDead();//���ʹ� ���
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

		if (e->getEnemyHP() <= 0)//���ʹ� ü���� 0���ϰ� �Ǹ�
		{
			_count++;
			if (_count % 5 == 0)
			{
				e->setEnemyIsActive(false);//���ʹ� ����
				_count = 0;
			}
		}
	}
}
