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

	icethrowerCollision();		//¾óÀ½Èð»Ñ¸®±â Ãæµ¹		
	mineCollision();			//Áö·Ú Ãæµ¹
	stoneCollision();			//¹ÙÀ§ Ãæµ¹
	flameCollision();			//È­¿° Ãæµ¹
	iceguideCollision();		//»ÏÁ·¾óÀ½ Ãæµ¹
	bossHandCollision();		//ÇÃ·¹ÀÌ¾î ÃÑ¾Ë°ú º¸½º ÆÈ Ãæµ¹		

	//bossMineCollision();
	bossBulletCollision();
	bossAttackCollision();

	newMineCollision();
	//newBossMineCollision();

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
				_player->setAttackCollision(true);

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
	/*
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
					EFFECTMANAGER->play("Æø¹ßÀÌÆåÆ®", CAMERA->getRelativeVector2(Vector2(spider->getMineVector()[k]._x, spider->getMineVector()[k]._y)), 0);
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
					EFFECTMANAGER->play("Æø¹ßÀÌÆåÆ®", CAMERA->getRelativeVector2(Vector2(spider->getMineVector()[y]._x, spider->getMineVector()[y]._y)), 0);
					spider->collision2(y, _player->getBullet()->getVPlayerBullet()[p].angle);
					_player->getBullet()->remove(p);
					break;
				}
			}
		}		

	}
	*/


	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "mine");

	for (int i = 0; i < temp.size(); i++)
	{

		mine* spider = dynamic_cast<mine*>(temp[i]);

		for (int k = 0; k < spider->getMineVector().size(); k++)
		{

			if (isCollision(_player->getRect(), spider->getMineVector()[k]._rc))
			{
				EFFECTMANAGER->play("Æø¹ßÀÌÆåÆ®", CAMERA->getRelativeVector2(Vector2(spider->getMineVector()[k]._x, spider->getMineVector()[k]._y)), 0);
				_player->damage(spider->getMineVector()[k]._damage);
				_player->setAttackCollision(true);

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


				break;

			}



		}

		for (int s = 0; s < spider->getMine2Vector().size(); s++)
		{

			if (isCollision(_player->getRect(), spider->getMine2Vector()[s]._rc))
			{
				EFFECTMANAGER->play("Æø¹ßÀÌÆåÆ®", CAMERA->getRelativeVector2(Vector2(spider->getMine2Vector()[s]._x, spider->getMine2Vector()[s]._y)), 0);
				_player->damage(spider->getMine2Vector()[s]._damage);
				_player->setAttackCollision(true);

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


				break;

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
				_player->setAttackCollision(true);

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
				_player->setAttackCollision(true);

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
				_player->setAttackCollision(true);

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
				SOUNDMANAGER->play("hit", 0.6f);
				EFFECTMANAGER->play("player bulletRemoveEffect",
					CAMERA->getRelativeVector2(_player->getBullet()->getVPlayerBullet()[j].position).x + 20,
					CAMERA->getRelativeVector2(_player->getBullet()->getVPlayerBullet()[j].position).y);
				_player->getBullet()->remove(j);
				break;
			}

			if (isCollision(hand->getLeftHandRect(), _player->getBullet()->getVPlayerBullet()[j].rc))
			{
				SOUNDMANAGER->play("hit", 0.6f);
				EFFECTMANAGER->play("player bulletRemoveEffect",
					CAMERA->getRelativeVector2(_player->getBullet()->getVPlayerBullet()[j].position).x + 20,
					CAMERA->getRelativeVector2(_player->getBullet()->getVPlayerBullet()[j].position).y);
				_player->getBullet()->remove(j);
				break;
			}

		}

	}
}

void bossCollision::bossMineCollision()
{

	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "mine");


	for (int i = 0; i < temp.size(); i++)
	{
		mine* spider = dynamic_cast<mine*>(temp[i]);

		vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");

		for (int d = 0; d < temp.size(); d++)
		{
			boss* b = dynamic_cast<boss*>(temp[d]);

			if (spider->getDropTrue1() && spider->getDropTrue2() && spider->getDropTrue3() && spider->getDropTrue4() && spider->getDropTrue5() && spider->getDropTrue6())
			{
				for (int a = 0; a < spider->getMineVector().size(); a++)
				{

					if (isCollision(spider->getMineVector()[a]._rc, b->getRightWall()))
					{
						spider->setCollision(false);
						//spider->mineRemove(a);
						break;
					}
					if (isCollision(spider->getMineVector()[a]._rc, b->getLeftWall()))
					{
						spider->setCollision(false);
						//spider->mineRemove(a);
						break;
					}
					if (isCollision(spider->getMineVector()[a]._rc, b->getBottomWall()))
					{
						spider->setCollision(false);
						//spider->mineRemove(a);
						break;
					}
					if (isCollision(spider->getMineVector()[a]._rc, b->getBottomRect()))
					{
						spider->setCollision(false);
						//spider->mineRemove(a);
						break;
					}




				}

				for (int c = 0; c < spider->getMine2Vector().size(); c++)
				{
					if (isCollision(spider->getMine2Vector()[c]._rc, b->getRightWall()))
					{
						spider->setCollision2(false);
						//spider->mineRemove2(c);
						break;
					}
					if (isCollision(spider->getMine2Vector()[c]._rc, b->getLeftWall()))
					{
						spider->setCollision2(false);
						//spider->mineRemove2(c);
						break;
					}
					if (isCollision(spider->getMine2Vector()[c]._rc, b->getBottomWall()))
					{
						spider->setCollision2(false);
						//spider->mineRemove2(c);
						break;
					}
					if (isCollision(spider->getMine2Vector()[c]._rc, b->getBottomRect()))
					{
						spider->setCollision(false);
						//spider->mineRemove2(c);
						break;
					}


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
				if (hand->getBossState() == STUN || hand->getBossState() == STUN2 || hand->getBossState() == STUN3)
				{
					hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower() * 2.5f);
				}
				else
				{
					hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower());
				}
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
				if (hand->getBossState() == STUN || hand->getBossState() == STUN2 || hand->getBossState() == STUN3)
				{
					hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower() * 5);
				}
				else
				{
					hand->setBossHp(hand->getBossHp() - _player->getPlayerAttackPower() * 2);
				}
				hand->setBossCollision(true);
			}

		
		}

		
	}


}

void bossCollision::newMineCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "mine");

	for (int i = 0; i < temp.size(); i++)
	{
		mine* spider = dynamic_cast<mine*>(temp[i]);

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{

			if (isCollision(_player->getBullet()->getVPlayerBullet()[j].rc, spider->getMineVector().begin()->_rc))
			{

				spider->collision(_player->getBullet()->getVPlayerBullet()[j].angle);
				_player->getBullet()->remove(j);
				break;
			}

			if (isCollision(_player->getBullet()->getVPlayerBullet()[j].rc, (spider->getMineVector().begin() + 1)->_rc))
			{

				spider->collision2(_player->getBullet()->getVPlayerBullet()[j].angle);
				_player->getBullet()->remove(j);
				break;
			}

			if (isCollision(_player->getBullet()->getVPlayerBullet()[j].rc, (spider->getMineVector().begin() + 2)->_rc))
			{

				spider->collision3(_player->getBullet()->getVPlayerBullet()[j].angle);
				_player->getBullet()->remove(j);
				break;
			}

			if (isCollision(_player->getBullet()->getVPlayerBullet()[j].rc, spider->getMine2Vector().begin()->_rc))
			{

				spider->collision4(_player->getBullet()->getVPlayerBullet()[j].angle);
				_player->getBullet()->remove(j);
				break;
			}

			if (isCollision(_player->getBullet()->getVPlayerBullet()[j].rc, (spider->getMine2Vector().begin() + 1)->_rc))
			{

				spider->collision5(_player->getBullet()->getVPlayerBullet()[j].angle);
				_player->getBullet()->remove(j);
				break;
			}

			if (isCollision(_player->getBullet()->getVPlayerBullet()[j].rc, (spider->getMine2Vector().begin() + 2)->_rc))
			{

				spider->collision6(_player->getBullet()->getVPlayerBullet()[j].angle);
				_player->getBullet()->remove(j);
				break;
			}


		}


	}

}

void bossCollision::newBossMineCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::BOSS, "mine");

	for (int i = 0; i < temp.size(); i++)
	{
		mine* spider = dynamic_cast<mine*>(temp[i]);

		vector<gameObject*> temp2 = OBJECTMANAGER->findObjects(objectType::BOSS, "boss");

		for (int d = 0; d < temp2.size(); d++)
		{
			boss* bottom = dynamic_cast<boss*>(temp[d]);

			if (spider->getDropTrue1() && spider->getDropTrue2() && spider->getDropTrue3() && spider->getDropTrue4() && spider->getDropTrue5() && spider->getDropTrue6())
			{
				if (isCollision(bottom->getBottomRect(), spider->getMineVector().begin()->_rc))
				{
					spider->setCollision(false);
					break;

				}

				if (isCollision(bottom->getBottomRect(), (spider->getMineVector().begin() + 1)->_rc))
				{
					spider->setCollision2(false);
					break;

				}

				if (isCollision(bottom->getBottomRect(), (spider->getMineVector().begin() + 2)->_rc))
				{
					spider->setCollision3(false);
					break;

				}

				if (isCollision(bottom->getBottomRect(), spider->getMine2Vector().begin()->_rc))
				{
					spider->setCollision4(false);
					break;

				}

				if (isCollision(bottom->getBottomRect(), (spider->getMine2Vector().begin() + 1)->_rc))
				{
					spider->setCollision5(false);
					break;

				}

				if (isCollision(bottom->getBottomRect(), (spider->getMine2Vector().begin() + 2)->_rc))
				{
					spider->setCollision6(false);
					break;

				}
			}

		}

	}
}

