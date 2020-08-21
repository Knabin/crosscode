#include "stdafx.h"
#include "puzzleCollision.h"
#include "puzzleTabButton.h"
#include "puzzleComboButton.h"
#include "puzzleDestruct.h"
#include "puzzleBlueWall.h"
#include "puzzleOrangeWall.h"
#include "bullet.h"

HRESULT puzzleCollision::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	_count = 0;
	_puzzleTabButtonCollision = false;

	return S_OK;
}

void puzzleCollision::release()
{
}

void puzzleCollision::update()
{
	puzzleBlueWallCollision();
	puzzleOrangeWallCollision();
	puzzleComboButtonCollision();
	puzzleTabButtonCollision();
	puzzleDestructCollision();
}

void puzzleCollision::puzzleBlueWallCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleBlueWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleBlueWall* p = dynamic_cast<puzzleBlueWall*>(temp[i]);

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			if (isCollision(p->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//플레이어의 렉트랑 퍼즐블루벽 렉트랑 충돌했으면
			{
				if (!_player->getBullet()->getVPlayerBullet()[j].nomal)
				{
					_player->getBullet()->setPlayerBullet(j, _player->getBullet()->getVPlayerBullet()[j].angle + PI);
				}
				else
				{
					_player->getBullet()->remove(j);//플레이어의 총알렉트를 삭제
					break;
				}
			}
		}

		//플레이어렉트랑 퍼즐블루벽 렉트랑 충돌했을때 플레이어 렉트를 밀어버리기 위한 기능
		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(p->getRect().left);
		rcHold.right = FLOAT_TO_INT(p->getRect().right);
		rcHold.top = FLOAT_TO_INT(p->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(p->getRect().bottom);

		RECT rcMove;
		rcMove.left = FLOAT_TO_INT(_player->getRect().left);
		rcMove.right = FLOAT_TO_INT(_player->getRect().right);
		rcMove.top = FLOAT_TO_INT(_player->getRect().top);
		rcMove.bottom = FLOAT_TO_INT(_player->getRect().bottom);

		if (IntersectRect(&rcInter, &rcHold, &rcMove))
		{
			int interW = rcInter.right - rcInter.left;
			int interH = rcInter.bottom - rcInter.top;

			if (interW > interH)//위아래에서 충돌했을때
			{
				if (rcInter.top == rcHold.top)//위에서 충돌했을때
				{
					_player->setPlayerY(_player->getRect().getCenter().y - interH);
				}
				else if (rcInter.bottom == rcHold.bottom)//아래에서 충돌했을때
				{
					_player->setPlayerY(_player->getRect().getCenter().y + interH);
				}
			}
			else//양옆에서 충돌했을때
			{
				if (rcInter.left == rcHold.left)//왼쪽에서 충돌했을때
				{
					_player->setPlayerX(_player->getRect().getCenter().x - interW);
				}
				else if (rcInter.right == rcHold.right)
				{
					_player->setPlayerX(_player->getRect().getCenter().x + interW);
				}
			}
		}
		//플레이어렉트랑 퍼즐블루벽 렉트랑 충돌했을때 플레이어 렉트를 밀어버리기 위한 기능
	}
}

void puzzleCollision::puzzleOrangeWallCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleOrangeWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleOrangeWall* p = dynamic_cast<puzzleOrangeWall*>(temp[i]);

		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(p->getRect().left);
		rcHold.right = FLOAT_TO_INT(p->getRect().right);
		rcHold.top = FLOAT_TO_INT(p->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(p->getRect().bottom);

		RECT rcMove;
		rcMove.left = FLOAT_TO_INT(_player->getRect().left);
		rcMove.right = FLOAT_TO_INT(_player->getRect().right);
		rcMove.top = FLOAT_TO_INT(_player->getRect().top);
		rcMove.bottom = FLOAT_TO_INT(_player->getRect().bottom);

		if (IntersectRect(&rcInter, &rcHold, &rcMove))
		{
			int interW = rcInter.right - rcInter.left;
			int interH = rcInter.bottom - rcInter.top;

			if (interW > interH)//위아래에서 충돌했을때
			{
				if (rcInter.top == rcHold.top)//위에서 충돌했을때
				{
					_player->setPlayerY(_player->getRect().getCenter().y - interH);
				}
				else if (rcInter.bottom == rcHold.bottom)//아래에서 충돌했을때
				{
					_player->setPlayerY(_player->getRect().getCenter().y + interH);
				}
			}
			else//양옆에서 충돌했을때
			{
				if (rcInter.left == rcHold.left)//왼쪽에서 충돌했을때
				{
					_player->setPlayerX(_player->getRect().getCenter().x - interW);
				}
				else if (rcInter.right == rcHold.right)//오른쪽에서 충돌했을때
				{
					_player->setPlayerX(_player->getRect().getCenter().x + interW);
				}
			}
		}
	}
}

void puzzleCollision::puzzleComboButtonCollision()
{
}


void puzzleCollision::puzzleTabButtonCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleTabButton");
	vector<gameObject*> blueWallTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleBlueWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleTabButton* p = dynamic_cast<puzzleTabButton*>(temp[i]);

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			if (isCollision(p->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))
			{
				_puzzleTabButtonCollision = true;
				_player->getBullet()->remove(j);
				break;
			}
		}

		if (_puzzleTabButtonCollision)//탑버튼이 플레이어의 공격렉트에 충돌당했다면
		{
			_count++;
			if (_count % 5 == 0)
			{
				if (p->getFrameX() < p->getImage()->getMaxFrameX() - 1)
				{
					p->setFrameX(p->getFrameX() + 1);
				}
				_count = 0;
			}
		}

		for (int j = 0; j < blueWallTemp.size(); j++)
		{
			puzzleBlueWall* blueP = dynamic_cast<puzzleBlueWall*>(blueWallTemp[0]);

			if (_puzzleTabButtonCollision)//탑버튼이 플레이어의 공격렉트에 충돌당했다면
			{
				if (p->getFrameX() >= p->getImage()->getMaxFrameX() - 1)
				{

				}
			}
		}
	}
}

void puzzleCollision::puzzleDestructCollision()
{
}
