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
	collision();//�÷��̾�� ���ʹ� �浹ó��
}

void collisionManager::render()
{
}

void collisionManager::collision()
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

		//���ʹ� ���ݷ�Ʈ�� �÷��̾ �浹��
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
		//���ʹ� ���ݷ�Ʈ�� �÷��̾ �浹��

		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
		/*
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
		*/
	}
}
