#include "stdafx.h"
#include "bossCollision.h"
#include "icethrower.h"
#include "mine.h"
#include "stoneshower.h"
#include "flamethrower.h"
#include "iceguide.h"
#include "boss.h"
#include "bullet.h"

bossCollision::bossCollision()
{
}

bossCollision::~bossCollision()
{
}

HRESULT bossCollision::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	_collisionCount = 0;



	return S_OK;
}

void bossCollision::release()
{
}

void bossCollision::update()
{

	icethrowerCollision();		//������Ѹ��� �浹		
	mineCollision();			//���� �浹
	stoneCollision();			//���� �浹
	flameCollision();			//ȭ�� �浹
	iceguideCollision();		//�������� �浹
	bossHandCollision();		//�÷��̾� �Ѿ˰� ���� �� �浹				
	//bossMineCollision();
	bossBulletCollision();

	vector<gameObject*> temp10 = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");

	for (int i = 0; i < temp10.size(); i++)
	{
		boss* b = dynamic_cast<boss*>(temp10[i]);
		if (b->getBossCollision())
		{
			_collisionCount++;
			if (_collisionCount % 40 == 0)
			{
				b->setBossCollision(false);
				_collisionCount = 0;
			}
		}
	}


}

void bossCollision::render()
{
}

void bossCollision::icethrowerCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "icethrower");

	for (int i = 0; i < temp.size(); i++)
	{
		icethrower* attack1 = dynamic_cast<icethrower*>(temp[i]);

		for (int j = 0; j < attack1->getIcethrowerVector().size(); j++)
		{
			if (isCollision(_player->getRect(), attack1->getIcethrowerVector()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack1->getIcethrowerVector()[j]._damage);
				attack1->removeFire(j);
				break;
			}
		}
	}	
}

void bossCollision::mineCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "mine");

	for (int i = 0; i < temp.size(); i++)
	{
		mine* spider = dynamic_cast<mine*>(temp[i]);

		
		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			for (int k = 0; k < spider->getMineVector().size(); k++)
			{
				if (isCollision(spider->getMineVector()[k]._rc, _player->getBullet()->getVPlayerBullet()[j].rc))
				{


					spider->collision(k, _player->getBullet()->getVPlayerBullet()[j].angle);
					_player->getBullet()->remove(j);
					break;
				
				}
			}	
		}
		

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			for (int y = 0; y < spider->getMine2Vector().size(); y++)
			{
				if (isCollision(spider->getMine2Vector()[y]._rc, _player->getBullet()->getVPlayerBullet()[j].rc))
				{

					spider->collision2(y, _player->getBullet()->getVPlayerBullet()[j].angle);
					_player->getBullet()->remove(j);
					break;
				}
			}
		}
	}
}

void bossCollision::stoneCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "stoneshower");

	for (int i = 0; i < temp.size(); i++)
	{
		stoneshower* attack2 = dynamic_cast<stoneshower*>(temp[i]);

		for (int j = 0; j < attack2->getStoneVector().size(); j++)
		{
			if (isCollision(_player->getRect(), attack2->getStoneVector()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack2->getStoneVector()[j]._damage);
				attack2->removeFire(j);
				break;
			}
		}
	}
}

void bossCollision::flameCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "flamethrower");

	for (int i = 0; i < temp.size(); i++)
	{
		flamethrower* attack3 = dynamic_cast<flamethrower*>(temp[i]);

		for (int j = 0; j < attack3->getFlameVector().size(); j++)
		{
			if (isCollision(_player->getRect(), attack3->getFlameVector()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack3->getFlameVector()[j]._damage);
				attack3->removeFire(j);
				break;
			}
		}
	}

}

void bossCollision::iceguideCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "iceguide");

	for (int i = 0; i < temp.size(); i++)
	{
		iceguide* attack4 = dynamic_cast<iceguide*>(temp[i]);

		for (int j = 0; j < attack4->getIceguideVector().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack4->getIceguideVector()[j]._damage);
				attack4->removeFire1(j);
				break;
			}
		}


		for (int j = 0; j < attack4->getIceguideVector2().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector2()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack4->getIceguideVector2()[j]._damage);
				attack4->removeFire2(j);
				break;
			}
		}

		for (int j = 0; j < attack4->getIceguideVector3().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector3()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack4->getIceguideVector3()[j]._damage);
				attack4->removeFire3(j);
				break;
			}
		}

		for (int j = 0; j < attack4->getIceguideVector4().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector4()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack4->getIceguideVector4()[j]._damage);
				attack4->removeFire4(j);
				break;
			}
		}


		for (int j = 0; j < attack4->getIceguideVector5().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector5()[j]._rc))
			{
				if (_player->getDirection() == PLAYERDIRECTION::TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_TOP)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::RIGHT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}
				if (_player->getDirection() == PLAYERDIRECTION::LEFT_BOTTOM)
				{
					_player->setState(PLAYERSTATE::BE_ATTACKED);
				}

				_player->setPlayerHP(_player->getPlayerHP() - attack4->getIceguideVector5()[j]._damage);
				attack4->removeFire5(j);
				break;
			}
		}

	}


}

void bossCollision::bossHandCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");

	for (int i = 0; i < temp.size(); i++)
	{
		boss* hand = dynamic_cast<boss*>(temp[i]);

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			if (isCollision(hand->getRightHandRect(), _player->getBullet()->getVPlayerBullet()[j].rc))
			{
				_player->getBullet()->remove(j);
				break;
			}

			if (isCollision(hand->getLeftHandRect(), _player->getBullet()->getVPlayerBullet()[j].rc))
			{
				_player->getBullet()->remove(j);
				break;
			}

		}
	}
}

void bossCollision::bossMineCollision()
{

	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "mine");
	vector<gameObject*> temp2 = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");


	for (int i = 0; i < temp.size(); i++)
	{
		mine* spider = dynamic_cast<mine*>(temp[i]);

		for (int j = 0; j < temp2.size(); j++)
		{
			boss* hand = dynamic_cast<boss*>(temp[j]);

			for (int k = 0; k < spider->getMineVector().size(); k++)
			{
				if (isCollision(spider->getMineVector()[k]._rc, hand->getBottomRect()))
				{
					//spider->mineRemove(k); 
					//break;

				}
			}


			for (int z = 0; z < spider->getMine2Vector().size(); z++)
			{
				if (isCollision(spider->getMine2Vector()[z]._rc, hand->getBottomRect()))
				{
					//spider->mineRemove2(z);
					//break;

				}
			}


		}
	}






}

void bossCollision::bossBulletCollision()
{

	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");

	for (int i = 0; i < temp.size(); i++)
	{
		boss* hand = dynamic_cast<boss*>(temp[i]);

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			if (isCollision(hand->getBottomRect(), _player->getBullet()->getVPlayerBullet()[j].rc))
			{
				hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower());
				_player->getBullet()->remove(j);
				break;
			}

		}

		if (isCollision(hand->getBottomRect(), _player->getPlayerAttackRect()))
		{
			hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower());

		}
	}
}

