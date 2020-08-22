#include "stdafx.h"
#include "bossCollision.h"
#include "icethrower.h"
#include "stoneshower.h"
#include "flamethrower.h"
#include "iceguide.h"

bossCollision::bossCollision()
{
}

bossCollision::~bossCollision()
{
}

HRESULT bossCollision::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	return S_OK;
}

void bossCollision::release()
{
}

void bossCollision::update()
{


	icethrowerCollision();		//얼음흩뿌리기 충돌
	stoneCollision();			//바위 충돌
	flameCollision();			//화염 충돌
	iceguideCollision();		//뾰족얼음 충돌

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
