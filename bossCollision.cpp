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

	icethrowerCollision();		//얼음흩뿌리기 충돌		
	mineCollision();			//지뢰 충돌
	stoneCollision();			//바위 충돌
	flameCollision();			//화염 충돌
	iceguideCollision();		//뾰족얼음 충돌
	bossHandCollision();		//플레이어 총알과 보스 팔 충돌		

	//bossMineCollision();
	bossBulletCollision();
	bossAttackCollision();

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

	if (_player->getAttackCollision())
	{
		_playerCollisionCount++;
		if (_playerCollisionCount % 40 == 0)
		{
			_player->setAttackCollision(false);
			_playerCollisionCount = 0;
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
				_player->damage(attack1->getIcethrowerVector()[j]._damage);

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
		

		for (int p = 0; p < _player->getBullet()->getVPlayerBullet().size(); p++)
		{
			for (int y = 0; y < spider->getMine2Vector().size(); y++)
			{
				if (isCollision(spider->getMine2Vector()[y]._rc, _player->getBullet()->getVPlayerBullet()[p].rc))
				{

					spider->collision2(y, _player->getBullet()->getVPlayerBullet()[p].angle);
					_player->getBullet()->remove(p);
					break;
				}
			}
		}






		vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");

		for (int d = 0; d < temp.size(); d++)
		{
			boss* b = dynamic_cast<boss*>(temp[d]);


			for (int a = 0; a < spider->getMineVector().size(); a++)
			{
				if (isCollision(spider->getMineVector()[a]._rc, b->getRightWall()))
				{
					spider->setCollision(false);
					spider->mineRemove(a);
					break;
				}
				if (isCollision(spider->getMineVector()[a]._rc, b->getLeftWall()))
				{
					spider->setCollision(false);
					spider->mineRemove(a);
					break;
				}
				if (isCollision(spider->getMineVector()[a]._rc, b->getBottomWall()))
				{
					spider->setCollision(false);
					spider->mineRemove(a);
					break;
				}
		


			}

			for (int c = 0; c < spider->getMine2Vector().size(); c++)
			{
				if (isCollision(spider->getMine2Vector()[c]._rc, b->getRightWall()))
				{
					spider->setCollision2(false);
					spider->mineRemove2(c);
					break;
				}
				if (isCollision(spider->getMine2Vector()[c]._rc, b->getLeftWall()))
				{
					spider->setCollision2(false);
					spider->mineRemove2(c);
					break;
				}
				if (isCollision(spider->getMine2Vector()[c]._rc, b->getBottomWall()))
				{
					spider->setCollision2(false);
					spider->mineRemove2(c);
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
				_player->damage(attack2->getStoneVector()[j]._damage);

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
				_player->damage(attack3->getFlameVector()[j]._damage);

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
				_player->damage(attack4->getIceguideVector()[j]._damage);

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


				attack4->removeFire1(j);
				break;
			}
		}


		for (int j = 0; j < attack4->getIceguideVector2().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector2()[j]._rc))
			{
				_player->damage(attack4->getIceguideVector2()[j]._damage);
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
				attack4->removeFire2(j);
				break;
			}
		}

		for (int j = 0; j < attack4->getIceguideVector3().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector3()[j]._rc))
			{
				_player->damage(attack4->getIceguideVector3()[j]._damage);
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
				attack4->removeFire3(j);
				break;
			}
		}

		for (int j = 0; j < attack4->getIceguideVector4().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector4()[j]._rc))
			{
				_player->damage(attack4->getIceguideVector4()[j]._damage);
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
				attack4->removeFire4(j);
				break;
			}
		}


		for (int j = 0; j < attack4->getIceguideVector5().size(); j++)
		{
			if (isCollision(_player->getRect(), attack4->getIceguideVector5()[j]._rc))
			{
				_player->damage(attack4->getIceguideVector5()[j]._damage);
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
				SOUNDMANAGER->play("hit", 0.6f);
				hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower());
				EFFECTMANAGER->play("player bulletRemoveEffect",
					CAMERA->getRelativeVector2(_player->getBullet()->getVPlayerBullet()[j].position).x + 20,
					CAMERA->getRelativeVector2(_player->getBullet()->getVPlayerBullet()[j].position).y);
				_player->getBullet()->remove(j);
				break;
			}

		}

	}
}

void bossCollision::bossAttackCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");

	for (int i = 0; i < temp.size(); i++)
	{
		boss* hand = dynamic_cast<boss*>(temp[i]);

	
		if (isCollision(hand->getBottomRect(), _player->getPlayerAttackRect()))
		{
			if (!hand->getBossCollision())
			{
				SOUNDMANAGER->play("hit", 0.6f);
				hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower());
				hand->setBossCollision(true);
			}

		
		}

		
	}


}

