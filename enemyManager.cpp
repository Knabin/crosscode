#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"
#include "player.h"
#include "hedgehag.h"
#include "meerkat.h"
#include "buffalo.h"
#include "inventory.h"

HRESULT enemyManager::init()
{
	_sc = SCENEMANAGER->getCurrentScene();
	_as = new aStar;

	_vEnemy = OBJECTMANAGER->getObjectList(objectType::ENEMY);
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	_time = _index = 0;
	_count = 0;
	
	IMAGEMANAGER->addFrameImage("drop", L"images/object/drop.png", 11, 1);
	EFFECTMANAGER->addEffect("drop", "drop", 1, 0.5, 1, 1.5f);



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
	vector<gameObject*> hTemp = OBJECTMANAGER->findObjects(objectType::ENEMY, "hedgehag");
	vector<gameObject*> mTemp = OBJECTMANAGER->findObjects(objectType::ENEMY, "meerkat");
	vector<gameObject*> bTemp = OBJECTMANAGER->findObjects(objectType::ENEMY, "buffalo");

	//for (int i = 0; i < _vEnemy.size(); i++)
	//{
	//	enemy* e = dynamic_cast<enemy*>(_vEnemy[i]);
	//	cout << _player->getPlayerEXP() << ", 경험치" << endl;
	//	//if (e->getEnemyHP() <= 0)//에너미의 현재 체력이 0이하가 되면
	//	//{
	//	//
	//	//	_count++;
	//	//	if (_count % 5 == 0)
	//	//	{
	//	//		e->setIsAlive(false);//에너미 삭제
	//	//		
	//	//		for (int j = 0; j < hTemp.size(); j++)
	//	//		{
	//	//			hedgehag* h = dynamic_cast<hedgehag*>(hTemp[j]);
	//	//			_player->setPlayerEXP(10);
	//	//			break;
	//	//		}
	//	//		
	//	//		_count = 0;
	//	//
	//	//		break;
	//	//	}
	//	//}
	//}

	for (int i = 0; i < hTemp.size(); i++)//고슴도치
	{
		hedgehag* h = dynamic_cast<hedgehag*>(hTemp[i]);
		if (h->getEnemyHP() <= 0)
		{
			_count++;
			if (_count % 5 == 0)
			{
				h->setIsAlive(false);
				_player->setPlayerEXP(_player->getPlayerEXP() + 10);
				int r = RND->getFromIntTo(0, 2);
				float x = CAMERA->getRelativeVector2(h->getPosition()).x;
				float y = CAMERA->getRelativeVector2(h->getPosition()).y;
				switch (r)
				{
				case 0:
					_inven->getItem(L"거래", 0);

					EFFECTMANAGER->play("drop", Vector2(x, y));
					SOUNDMANAGER->play("item drop");
					break;
				case 1:
					_inven->getItem(L"거래", 5);
					
					EFFECTMANAGER->play("drop", Vector2(x,y));
					SOUNDMANAGER->play("item drop");
					break;
				default:
					break;
				}
				_inven->setMoney(RND->getFromIntTo(-300, -100));
				_count = 0;
				break;
			}
		}
	}

	for (int i = 0; i < mTemp.size(); i++)//미어캣
	{
		meerkat* m = dynamic_cast<meerkat*>(mTemp[i]);
		if (m->getEnemyHP() <= 0)
		{
			_count++;
			if (_count % 5 == 0)
			{
				m->setIsAlive(false);
				_player->setPlayerEXP(_player->getPlayerEXP() + 20);
				int r = RND->getFromIntTo(0, 2);
				float x = CAMERA->getRelativeVector2(m->getPosition()).x;
				float y = CAMERA->getRelativeVector2(m->getPosition()).y;
				switch (r)
				{
				case 0:
					_inven->getItem(L"거래", 1);

					EFFECTMANAGER->play("drop", Vector2(x, y));
					SOUNDMANAGER->play("item drop");
					break;
				case 1:
					_inven->getItem(L"거래", 4);

					EFFECTMANAGER->play("drop", Vector2(x, y));
					SOUNDMANAGER->play("item drop");
					break;
				default:
					break;
				}
				_inven->setMoney(RND->getFromIntTo(-400, -200));
				_count = 0;
				break;
			}
		}
	}

	for (int i = 0; i < bTemp.size(); i++)
	{
		buffalo* b = dynamic_cast<buffalo*>(bTemp[i]);
		if (b->getEnemyHP() <= 0)
		{
			_count++;
			if (_count % 5 == 0)
			{
				b->setIsAlive(false);
				_player->setPlayerEXP(_player->getPlayerEXP() + 30);
				int r = RND->getFromIntTo(0, 2);
				float x = CAMERA->getRelativeVector2(b->getPosition()).x;
				float y = CAMERA->getRelativeVector2(b->getPosition()).y;
				switch (r)
				{
				case 0:
					_inven->getItem(L"거래", 2);

					EFFECTMANAGER->play("drop", Vector2(x, y));
					SOUNDMANAGER->play("item drop");
					break;
				case 1:
					_inven->getItem(L"거래", 3);

					EFFECTMANAGER->play("drop", Vector2(x, y));
					SOUNDMANAGER->play("item drop");
					break;
				default:
					break;
				}
				_inven->setMoney(RND->getFromIntTo(-700, -500));
				_count = 0;
				break;
			}
		}
	}

	if (_index >= _vEnemy.size())
		_index = 0;
}
