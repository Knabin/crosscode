#include "stdafx.h"
#include "collisionManager.h"
#include "player.h"
#include "enemy.h"

HRESULT collisionManager::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	_count = 0;

	return S_OK;
}

void collisionManager::release()
{
}

void collisionManager::update()
{
	enemyCollision();//���ʹ̷�Ʈ�� �÷��̾� ��Ʈ�� �浹��
	playerCollision();//�÷��̾Ʈ�� ���ʹ� ��Ʈ�� �浹��
}

void collisionManager::render()
{
}

void collisionManager::playerCollision()
{
	//���ʹ� ���ݷ�Ʈ�� �÷��̾ �浹��
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);
		if (isCollision(_player->getRect(), e->getEnemyAttackRect()))//���ʹ� ���ݷ�Ʈ�� �÷��̾� ��Ʈ�� �浹������
		{
			_count++;
			if (_count % 10 == 0)//�浹�� ���� ���ʹ��� ���� ���°��� �����ϱ������ ������
			{
				_count = 0;//������ �ʱ�ȭ
				//_player->setPlayerHP(e->getEnemyAttackPower());//���ʹ��� ���ݷ� ��ŭ �÷��̾�� �������ֱ�
			}
			e->setEnemyAttackRect();//���ʹ��� ���ݷ�Ʈ ����
		}

		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(e->getRect().left);
		rcHold.right = FLOAT_TO_INT(e->getRect().right);
		rcHold.top = FLOAT_TO_INT(e->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(e->getRect().bottom);

		RECT rcMove;
		rcMove.left = FLOAT_TO_INT(_player->getRect().left);
		rcMove.right = FLOAT_TO_INT(_player->getRect().right);
		rcMove.top = FLOAT_TO_INT(_player->getRect().top);
		rcMove.bottom = FLOAT_TO_INT(_player->getRect().bottom);

		if (IntersectRect(&rcInter, &rcHold, &rcMove))
		{
			int interW = rcInter.right - rcInter.left;
			int interH = rcInter.bottom - rcInter.top;

			if (!e->getEnemyIsAttack())//���ʹ̰� ���ݻ��°� �ƴҰ�쿡�� �浹ó��
			{
				if (interW > interH)//�����浹(���Ʒ�)
				{
					//������ �ε�������
					if (rcInter.top == rcHold.top)
					{
						_player->setPlayerY(_player->getRect().getCenter().y - interH);
					}
					//�Ʒ����� �ε�������
					else if (rcInter.bottom == rcHold.bottom)
					{
						_player->setPlayerY(_player->getRect().getCenter().y + interH);
					}
				}
				else//�翷���� �浹������
				{
					//�������� �浹������
					if (rcInter.left == rcHold.left)
					{
						_player->setPlayerX(_player->getRect().getCenter().x - interW);
					}
					//�����ʿ��� �浹������
					else if (rcInter.right == rcHold.right)
					{
						_player->setPlayerX(_player->getRect().getCenter().x + interW);
					}
				}
			}
		}
		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
	}
	//���ʹ� ���ݷ�Ʈ�� �÷��̾ �浹��
}

void collisionManager::enemyCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);

		//���ʹ� ��Ʈ�� �÷��̾��� ���ݷ�Ʈ�� �浹��
		if (isCollision(e->getRect(), _player->getPlayerAttackRect()))//���ʹ̷�Ʈ�� �÷��̾� ���ݷ�Ʈ�� �浹��
		{
			if (e->getEnemyAngle() * (180 / PI) >= 135 && e->getEnemyAngle() * (180 / PI) <= 225 && !e->getEnemyIsAttack())//����
			{
				e->setEnemyDirection(ENEMY_LEFT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 90 && e->getEnemyAngle() * (180 / PI) <= 135 && !e->getEnemyIsAttack())//������
			{
				e->setEnemyDirection(ENEMY_UP_LEFT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 45 && e->getEnemyAngle() * (180 / PI) <= 90 && !e->getEnemyIsAttack())//��������
			{
				e->setEnemyDirection(ENEMY_UP_RIGHT_HIT);
			}

			if ((e->getEnemyAngle() * (180 / PI) <= 45 && e->getEnemyAngle() * (180 / PI) >= 0) && !e->getEnemyIsAttack() ||//������
				(e->getEnemyAngle() * (180 / PI) <= 360 && e->getEnemyAngle() * (180 / PI) >= 315) && !e->getEnemyIsAttack())
			{
				e->setEnemyDirection(ENEMY_RIGHT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 270 && e->getEnemyAngle() * (180 / PI) <= 315 && !e->getEnemyIsAttack())//�Ʒ�������
			{
				e->setEnemyDirection(ENEMY_DOWN_RIGHT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 225 && e->getEnemyAngle() * (180 / PI) <= 270 && !e->getEnemyIsAttack())//�Ʒ�����
			{
				e->setEnemyDirection(ENEMY_DOWN_LEFT_HIT);
			}

			e->setEnemyHP(_player->getPlayerAttackPower());//���ʹ����� ������
			_player->setPlayerAttackRectRemove();//�÷��̾���� ��Ʈ����
		}


		//���ʹ� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� ���ʹ� �о��
		RECT rcInter2;

		RECT rcHold2;

		RECT rcMove2;

		for (int j = 0; j < temp.size(); j++)
		{
			enemy* e2 = dynamic_cast<enemy*>(temp[j]);

			if (i == j) continue;

			rcHold2.left = FLOAT_TO_INT(e->getRect().left);
			rcHold2.right = FLOAT_TO_INT(e->getRect().right);
			rcHold2.top = FLOAT_TO_INT(e->getRect().top);
			rcHold2.bottom = FLOAT_TO_INT(e->getRect().bottom);

			rcMove2.left = FLOAT_TO_INT(e2->getRect().left);
			rcMove2.right = FLOAT_TO_INT(e2->getRect().right);
			rcMove2.top = FLOAT_TO_INT(e2->getRect().top);
			rcMove2.bottom = FLOAT_TO_INT(e2->getRect().bottom);

			if (e->getEnemyIsAttack())
			{
				if (IntersectRect(&rcInter2, &rcHold2, &rcMove2))
				{
					int interW2 = rcInter2.right - rcInter2.left;
					int interH2 = rcInter2.bottom - rcInter2.top;

					if (interW2 > interH2)//�����浹(���Ʒ�)
					{
						if (rcInter2.top == rcHold2.top)//������ �浹
						{
							e2->setEnemyY(e2->getRect().getCenter().y - interH2);
						}
						//�Ʒ����� �浹
						else if (rcInter2.bottom == rcHold2.bottom)
						{
							e2->setEnemyY(e2->getRect().getCenter().y + interH2);
						}
					}
					else//�翷���� �浹
					{
						if (rcInter2.left == rcHold2.left)//���ʿ��� �浹
						{
							e2->setEnemyX(e2->getRect().getCenter().x - interW2);
						}

						else if (rcInter2.right == rcHold2.right)//�����ʿ��� �浹
						{
							e2->setEnemyX(e2->getRect().getCenter().x + interW2);
						}
					}
				}
			}
		}
		//���ʹ� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� ���ʹ� �о��

	}
}
