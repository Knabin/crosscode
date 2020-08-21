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
			if (isCollision(p->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//�÷��̾��� ��Ʈ�� �����纮 ��Ʈ�� �浹������
			{
				if (!_player->getBullet()->getVPlayerBullet()[j].nomal)
				{
					_player->getBullet()->setPlayerBullet(j, _player->getBullet()->getVPlayerBullet()[j].angle + PI);
				}
				else
				{
					_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˷�Ʈ�� ����
					break;
				}
			}
		}

		//�÷��̾Ʈ�� �����纮 ��Ʈ�� �浹������ �÷��̾� ��Ʈ�� �о������ ���� ���
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

			if (interW > interH)//���Ʒ����� �浹������
			{
				if (rcInter.top == rcHold.top)//������ �浹������
				{
					_player->setPlayerY(_player->getRect().getCenter().y - interH);
				}
				else if (rcInter.bottom == rcHold.bottom)//�Ʒ����� �浹������
				{
					_player->setPlayerY(_player->getRect().getCenter().y + interH);
				}
			}
			else//�翷���� �浹������
			{
				if (rcInter.left == rcHold.left)//���ʿ��� �浹������
				{
					_player->setPlayerX(_player->getRect().getCenter().x - interW);
				}
				else if (rcInter.right == rcHold.right)
				{
					_player->setPlayerX(_player->getRect().getCenter().x + interW);
				}
			}
		}
		//�÷��̾Ʈ�� �����纮 ��Ʈ�� �浹������ �÷��̾� ��Ʈ�� �о������ ���� ���
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

			if (interW > interH)//���Ʒ����� �浹������
			{
				if (rcInter.top == rcHold.top)//������ �浹������
				{
					_player->setPlayerY(_player->getRect().getCenter().y - interH);
				}
				else if (rcInter.bottom == rcHold.bottom)//�Ʒ����� �浹������
				{
					_player->setPlayerY(_player->getRect().getCenter().y + interH);
				}
			}
			else//�翷���� �浹������
			{
				if (rcInter.left == rcHold.left)//���ʿ��� �浹������
				{
					_player->setPlayerX(_player->getRect().getCenter().x - interW);
				}
				else if (rcInter.right == rcHold.right)//�����ʿ��� �浹������
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

		if (_puzzleTabButtonCollision)//ž��ư�� �÷��̾��� ���ݷ�Ʈ�� �浹���ߴٸ�
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

			if (_puzzleTabButtonCollision)//ž��ư�� �÷��̾��� ���ݷ�Ʈ�� �浹���ߴٸ�
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
