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

	for (int i = 0; i < 6; i++)
	{
		_puzzleTabButtonCollision[i] = false;
	}

	return S_OK;
}

void puzzleCollision::release()
{
}

void puzzleCollision::update()
{
	puzzleBlueWallCollision();//��纮�� �÷��̾��� ������ �Ѿ��� �浹�� �ݻ� + �÷��̾ ��纮�� �з����� �ϱ����� �Լ�
	puzzleOrangeWallCollision();//���������̶� �÷��̾� ��Ʈ�� �浹�ϸ� �÷��̾ �о�� �ϱ����� �Լ�
	puzzleComboButtonCollision();//�÷��̾��� �Ѿ˷�Ʈ + �������� ��Ʈ�� �浹�Ҷ� �ܽð��ȿ� ������ �浹�Ǹ� ���������� �����ϱ� ���� �Լ�
	puzzleTabButtonCollision();//ž��ư�� �÷��̾��� �Ѿ˰��ݷ�Ʈ + �������� ��Ʈ�� �浹�Ǹ� ���� �������� �ϱ����� �Լ�
	puzzleDestructCollision();//�÷��̾��� �Ѿ˰��ݷ�Ʈ + �������ݷ�Ʈ�� �浹�Ǹ� ��HP�� ���̰� ��HP�� 0�̵Ǹ� �������� �������ְ� ��Ʈ�� �����ϱ� ���� �Լ�
}

void puzzleCollision::puzzleBlueWallCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleBlueWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleBlueWall* p = dynamic_cast<puzzleBlueWall*>(temp[i]);//��� ��纮

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			if (isCollision(p->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//�÷��̾��� �Ѿ˷�Ʈ�� ��纮 ��Ʈ�� �浹������
			{
				if (!_player->getBullet()->getVPlayerBullet()[j].nomal)//�÷��̾��� �Ѿ��� ������ �����̸�
				{
					_player->getBullet()->setPlayerBullet(j, _player->getBullet()->getVPlayerBullet()[j].angle + PI);//�÷��̾��� �Ѿ� �ݻ�
				}
				else//�÷��̾��� �Ѿ��� ������ �Ѿ��� �ƴϸ�
				{
					_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˷�Ʈ�� ����
					break;
				}
			}
		}

		//�÷��̾Ʈ�� ��纮 ��Ʈ�� �浹������ �÷��̾� ��Ʈ�� �о������ ���� ���
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
		//�÷��̾Ʈ�� ��纮 ��Ʈ�� �浹������ �÷��̾� ��Ʈ�� �о������ ���� ���
	}
}

void puzzleCollision::puzzleOrangeWallCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleOrangeWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleOrangeWall* p = dynamic_cast<puzzleOrangeWall*>(temp[i]);//��������

		//�������� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�ϸ� �÷��̾� ��Ʈ�� �о������ ���� �ڵ�
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
		//�������� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�ϸ� �÷��̾� ��Ʈ�� �о������ ���� �ڵ�
	}
}

void puzzleCollision::puzzleComboButtonCollision()
{
}


void puzzleCollision::puzzleTabButtonCollision()
{
	vector<gameObject*> topButtonTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleTabButton");
	vector<gameObject*> blueWallTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleBlueWall");
	vector<gameObject*> orangeTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleOrangeWall");

	for (int i = 0; i < topButtonTemp.size(); i++)
	{
		puzzleTabButton* allButtonP = dynamic_cast<puzzleTabButton*>(topButtonTemp[i]);//�ش� �浹�� ž��ư�� ���° ������ �˱����� ��� ž��ư
		puzzleTabButton* buttonP1 = dynamic_cast<puzzleTabButton*>(topButtonTemp[1]);//1��° ž��ư
		puzzleTabButton* buttonP2 = dynamic_cast<puzzleTabButton*>(topButtonTemp[5]);//2��° ž��ư

		if (isCollision(buttonP1->getRect(), _player->getPlayerAttackRect()))//1��° ž��ư ��Ʈ�� �÷��̾� �������� ��Ʈ�� �浹�ϸ�
		{
			_puzzleTabButtonCollision[0] = true;
			buttonP1->setRect(RectMakePivot(Vector2(0, 0), Vector2(0, 0), pivot::CENTER));//1��° ž��ư ��Ʈũ�� 0���� ����
		}

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)//�÷��̾��� �Ѿ˺��� �����ŭ for��
		{
			if (isCollision(buttonP1->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//1��° ž��ư��Ʈ�� �÷��̾��� �Ѿ˷�Ʈ�� �浹�ϸ�
			{
				_puzzleTabButtonCollision[0] = true;//1��° ž��ư�� �浹�ߴٴ� bool�� Ʈ��
				buttonP1->setRect(RectMakePivot(Vector2(0, 0), Vector2(0, 0), pivot::CENTER));//1��° ž��ư ��Ʈũ�� 0���� ����
				_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˷�Ʈ ����
				break;
			}


			if (isCollision(buttonP2->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//2��° ž��ư ��Ʈ�� �÷��̾��� �Ѿ˷�Ʈ�� �浹������
			{
				_puzzleTabButtonCollision[1] = true;//2��° ž��ư�� �浹�ߴٴ� bool�� Ʈ��
				buttonP2->setRect(RectMakePivot(Vector2(0, 0), Vector2(0, 0), pivot::CENTER));//2��° ž��ư ��Ʈũ�� 0���� ����
				_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˷�Ʈ ����
				break;
			}
		}

		if (_puzzleTabButtonCollision[0])//1��° ž��ư�� �浹������
		{
			_count++;
			if (_count % 15 == 0)
			{
				if (buttonP1->getFrameX() < buttonP1->getImage()->getMaxFrameX() - 1)//1��° ž��ư�� �浹������ x�������� ����� �����ǰ� �Ұ��� ������ ���ǹ�
				{
					buttonP1->setFrameX(buttonP1->getFrameX() + 1);//1��° ž��ư ������ ���
				}
				_count = 0;
			}
		}

		if (_puzzleTabButtonCollision[1])//2��° ž��ư�� �浹������
		{
			_count++;
			if (_count % 15 == 0)
			{
				if (buttonP2->getFrameX() < buttonP2->getImage()->getMaxFrameX() - 1)//2��° ž��ư�� �浹������ x�������� ����� �����ǰ� �Ұ��� ������ ���ǹ�
				{
					buttonP2->setFrameX(buttonP2->getFrameX() + 1);//2��° ž��ư ������ ���
				}
				_count = 0;
			}
		}


		//1��° ž��ư�� �浹ó�� �Ǽ� �������� ��������
		puzzleBlueWall* blueP = dynamic_cast<puzzleBlueWall*>(blueWallTemp[0]);//1��° ��纮

		if (_puzzleTabButtonCollision[0])//1��° ž��ư�� �浹������
		{
			if (buttonP1->getFrameX() >= buttonP1->getImage()->getMaxFrameX() - 1)//1��° ž��ư�� �������� �����ٸ�
			{
				_count++;
				if (_count % 15 == 0)
				{
					if (blueP->getFrameX() < blueP->getImage()->getMaxFrameX() - 1)//1��° ��纮�� �������� ������ �����ӱ��� ������Ű�� ���� ����
					{
						blueP->setFrameX(blueP->getFrameX() + 1);
					}

					if (blueP->getFrameX() >= blueP->getImage()->getMaxFrameX() - 1)//1��° ��纮�� �������� �������� �����ߴٸ�
					{
						blueP->setRect(RectMakePivot(Vector2(0, 0), Vector2(0, 0), pivot::CENTER));//1��° ��纮�� ��Ʈũ��0���� ����
					}
					_count = 0;
				}
			}
		}
		//���� �ڵ�� 1��° ž��ư�� �浹�Ǹ� 1��° ��纮�� �������� �����Ű�� ��Ʈ�� ���Ž�Ű�� ���� �ڵ�


		//2��° ž��ư�� �浹ó�� �Ǽ� �������� ��������
		puzzleOrangeWall* orangeP1 = dynamic_cast<puzzleOrangeWall*>(orangeTemp[1]);//1��° ��������
		puzzleOrangeWall* orangeP2 = dynamic_cast<puzzleOrangeWall*>(orangeTemp[0]);//2��° ��������

		if (_puzzleTabButtonCollision[1])//2��° ž��ư�� �浹������
		{
			if (buttonP2->getFrameX() >= buttonP2->getImage()->getMaxFrameX() - 1)//2��° ž��ư�� �������� �����ٸ�
			{
				_count++;
				if (_count % 15 == 0)
				{
					if (orangeP1->getFrameX() < orangeP1->getImage()->getMaxFrameX())//ù��° �������� �������� �߽� �����Ӻ��� ������
					{
						orangeP1->setFrameX(orangeP1->getFrameX() + 1);//�������� ������ ����
					}

					if (orangeP1->getFrameX() >= orangeP1->getImage()->getMaxFrameX() - 1)//2��° ���������� �������� �������� �����ߴٸ�
					{
						orangeP1->setRect(RectMakePivot(Vector2(0, 0), Vector2(0, 0), pivot::CENTER));//�������� ��Ʈũ�� 0���� ����
					}
					_count = 0;
				}
			}
		}
		//���� �ڵ�� 2��° ž��ư�� �浹ó�� �Ǹ� 1��° ���������� �������� �����Ű�� ��Ʈ�� ���Ž�Ű�� ���� �ڵ�


		//ž��ư ��Ʈ�� �÷��̾� ��Ʈ�� �浹�� �÷��̾ �о�� ���� �ڵ�
		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(allButtonP->getRect().left);
		rcHold.right = FLOAT_TO_INT(allButtonP->getRect().right);
		rcHold.top = FLOAT_TO_INT(allButtonP->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(allButtonP->getRect().bottom);

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
		//ž��ư ��Ʈ�� �÷��̾� ��Ʈ�� �浹�� �÷��̾ �о�� ���� �ڵ�
	}
}

void puzzleCollision::puzzleDestructCollision()
{
}
