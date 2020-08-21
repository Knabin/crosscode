#include "stdafx.h"
#include "collisionManager.h"
#include "player.h"
#include "enemy.h"
#include "meerkat.h"
#include "buffalo.h"
#include "hedgehag.h"
#include "bullets.h"
#include "bullet.h"

HRESULT collisionManager::init()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	_count = 0;
	_pushOut = false;

	return S_OK;
}

void collisionManager::release()
{
}

void collisionManager::update()
{
	enemyCollision();//���ʹ̳��� �浹
	buffaloCollision();//���ȷζ� �÷��̾� �浹ó��
	hedgehagCollision();//����ġ�� �÷��̾� �浹ó��
	meerkatCollision();//�̾�Ĺ�̶� �÷��̾� �浹ó��
	bulletCollision();//�̾�Ĺ�� �Ѿ��̶� �÷��̾� �浹ó��
}

void collisionManager::render()
{
}

void collisionManager::buffaloCollision()
{

	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::ENEMY, "buffalo");

	for (int i = 0; i < temp.size(); i++)
	{
		buffalo* b = dynamic_cast<buffalo*>(temp[i]);
		if (b == NULL) continue;
		if (b->getEnemyAttackRect().getSize().x != 0 && b->getEnemyAttackRect().getSize().y != 0)
		{
			if (isCollision(_player->getRect(), b->getEnemyAttackRect()))//�÷��̾Ʈ�� ���ȷ� ���ݷ�Ʈ�� �浹������
			{
				_pushOut = true;

				if (b->getEnemyDirection() == ENEMY_UP_LEFT_ATTACK)
				{
					b->setEnemyDirection(ENEMY_UP_LEFT_IDLE);
				}

				if (b->getEnemyDirection() == ENEMY_UP_RIGHT_ATTACK)
				{
					b->setEnemyDirection(ENEMY_UP_RIGHT_IDLE);
				}

				if (b->getEnemyDirection() == ENEMY_LEFT_ATTACK)
				{
					b->setEnemyDirection(ENEMY_LEFT_IDLE);
				}

				if (b->getEnemyDirection() == ENEMY_RIGHT_ATTACK)
				{
					b->setEnemyDirection(ENEMY_RIGHT_IDLE);
				}

				if (b->getEnemyDirection() == ENEMY_DOWN_LEFT_ATTACK)
				{
					b->setEnemyDirection(ENEMY_DOWN_LEFT_IDLE);
				}

				if (b->getEnemyDirection() == ENEMY_DOWN_RIGHT_ATTACK)
				{
					b->setEnemyDirection(ENEMY_DOWN_RIGHT_IDLE);
				}

				b->setIsAttack(false);
			}
		}

		if (_pushOut)
		{
			_player->setPlayerPlusX(cosf(b->getEnemyAngle()) * 10.0f);
			_player->setPlayerPlusY(-sinf(b->getEnemyAngle()) * 10.0f);

			_count++;
			if (_count % 10 == 0)
			{
				_pushOut = false;
				_count = 0;
			}
		}

		if (_player->getPlayerAttackRect().getSize().x != 0 && _player->getPlayerAttackRect().getSize().y != 0)
		{
			if (isCollision(b->getRect(), _player->getPlayerAttackRect()))//���ȷ� ��Ʈ�� �÷��̾� ���ݷ�Ʈ�� �浹������
			{
				b->setEnemyHP(_player->getPlayerAttackPower());//���ʹ����� ������
				_player->setPlayerAttackRectRemove();//�÷��̾���� ��Ʈ����
			}
		}

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)//�÷��̾� ���Ÿ� ������ ���ȷ����� ������
		{
			if (isCollision(b->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))
			{
				b->setEnemyHP(_player->getPlayerAttackPower());
				_player->getBullet()->remove(j);
			}
		}

		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(b->getRect().left);
		rcHold.right = FLOAT_TO_INT(b->getRect().right);
		rcHold.top = FLOAT_TO_INT(b->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(b->getRect().bottom);

		RECT rcMove;
		rcMove.left = FLOAT_TO_INT(_player->getRect().left);
		rcMove.right = FLOAT_TO_INT(_player->getRect().right);
		rcMove.top = FLOAT_TO_INT(_player->getRect().top);
		rcMove.bottom = FLOAT_TO_INT(_player->getRect().bottom);

		if (IntersectRect(&rcInter, &rcHold, &rcMove))
		{
			int interW = rcInter.right - rcInter.left;
			int interH = rcInter.bottom - rcInter.top;

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
		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
	}

}

void collisionManager::hedgehagCollision()
{

	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::ENEMY, "hedgehag");

	for (int i = 0; i < temp.size(); i++)
	{
		hedgehag* h = dynamic_cast<hedgehag*>(temp[i]);
		if (h == NULL) continue;
		if (_player->getPlayerAttackRect().getSize().x != 0 && _player->getPlayerAttackRect().getSize().y != 0)
		{
			if (isCollision(h->getRect(), _player->getPlayerAttackRect()))//����ġ ��Ʈ�� �÷��̾� ���ݷ�Ʈ�� �浹��
			{
				if (!h->getEnemyIsAttack())
				{
					if (h->getEnemyAngle() * (180 / PI) >= 135 && h->getEnemyAngle() * (180 / PI) <= 225)//����
					{
						h->setEnemyDirection(ENEMY_LEFT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 90 && h->getEnemyAngle() * (180 / PI) <= 135)//������
					{
						h->setEnemyDirection(ENEMY_UP_LEFT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 45 && h->getEnemyAngle() * (180 / PI) <= 90)//��������
					{
						h->setEnemyDirection(ENEMY_UP_RIGHT_HIT);
					}

					if ((h->getEnemyAngle() * (180 / PI) <= 45 && h->getEnemyAngle() * (180 / PI) >= 0) ||//������
						(h->getEnemyAngle() * (180 / PI) <= 360 && h->getEnemyAngle() * (180 / PI) >= 315))
					{
						h->setEnemyDirection(ENEMY_RIGHT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 270 && h->getEnemyAngle() * (180 / PI) <= 315)//�Ʒ�������
					{
						h->setEnemyDirection(ENEMY_DOWN_RIGHT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 225 && h->getEnemyAngle() * (180 / PI) <= 270)//�Ʒ�����
					{
						h->setEnemyDirection(ENEMY_DOWN_LEFT_HIT);
					}
				}
				h->setEnemyHP(_player->getPlayerAttackPower());//���ʹ����� ������
				_player->setPlayerAttackRectRemove();//�÷��̾���� ��Ʈ����
			}
		}

		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(_player->getRect().left);
		rcHold.right = FLOAT_TO_INT(_player->getRect().right);
		rcHold.top = FLOAT_TO_INT(_player->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(_player->getRect().bottom);

		RECT rcMove;
		rcMove.left = FLOAT_TO_INT(h->getRect().left);
		rcMove.right = FLOAT_TO_INT(h->getRect().right);
		rcMove.top = FLOAT_TO_INT(h->getRect().top);
		rcMove.bottom = FLOAT_TO_INT(h->getRect().bottom);

		if (IntersectRect(&rcInter, &rcHold, &rcMove))
		{
			interW = rcInter.right - rcInter.left;
			interH = rcInter.bottom - rcInter.top;

			if (!h->getEnemyIsAttack())//���ʹ̰� ���ݻ��°� �ƴҰ�쿡�� �浹ó��
			{
				if (interW > interH)//�����浹(���Ʒ�)
				{
					//������ �ε�������
					if (rcInter.top == rcHold.top)
					{
						//_player->setPlayerY(_player->getRect().getCenter().y - interH);
						h->setEnemyY(h->getRect().getCenter().y - interH);
					}
					//�Ʒ����� �ε�������
					else if (rcInter.bottom == rcHold.bottom)
					{
						//_player->setPlayerY(_player->getRect().getCenter().y + interH);
						h->setEnemyY(h->getRect().getCenter().y + interH);
					}
				}
				else//�翷���� �浹������
				{
					//�������� �浹������
					if (rcInter.left == rcHold.left)
					{
						//_player->setPlayerX(_player->getRect().getCenter().x - interW);
						h->setEnemyX(h->getRect().getCenter().x - interW);
					}
					//�����ʿ��� �浹������
					else if (rcInter.right == rcHold.right)
					{
						//_player->setPlayerX(_player->getRect().getCenter().x + interW);
						h->setEnemyX(h->getRect().getCenter().x + interW);
					}
				}

				if (h->getPosition().x >= _player->getRect().left &&
					h->getPosition().x <= _player->getRect().right &&
					h->getPosition().y >= _player->getRect().top &&
					h->getPosition().y <= _player->getRect().bottom)
				{
					if (h->getPosition().x <= _player->getPosition().x)
					{
						h->setEnemyX(h->getPosition().x - interW);
					}
					else if (h->getPosition().x >= _player->getPosition().x)
					{
						h->setEnemyX(h->getPosition().x + interW);
					}
					if (h->getPosition().y <= _player->getPosition().y)
					{
						h->setEnemyY(h->getPosition().y - interH);
					}
					else if (h->getPosition().y >= _player->getPosition().y)
					{
						h->setEnemyY(h->getPosition().y + interH);
					}
				}
			}
			else
			{
				_count++;
				if (_count <= 3)
				{
					_player->setPlayerPlusX(cosf(h->getEnemyAngle()) * 10.0f);
					_player->setPlayerPlusY(-sinf(h->getEnemyAngle()) * 10.0f);
				}
				else
				{
					_count = 0;
				}
			}
		}
		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
	}

}

void collisionManager::meerkatCollision()
{

	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::ENEMY, "meerkat");

	for (int i = 0; i < temp.size(); i++)
	{
		meerkat* m = dynamic_cast<meerkat*>(temp[i]);
		if (_player->getPlayerAttackRect().getSize().x != 0 && _player->getPlayerAttackRect().getSize().y != 0)
		{
			if (isCollision(m->getRect(), _player->getPlayerAttackRect()))//�̾�Ĺ ��Ʈ�� �÷��̾� ���ݷ�Ʈ�� �浹��
			{
				if (m->getEnemyDirection() != ENEMY_TUNNEL_MOVE)
				{
					if (!m->getEnemyIsAttack())
					{
						if (m->getEnemyAngle() * (180 / PI) >= 135 && m->getEnemyAngle() * (180 / PI) <= 225)//����
						{
							m->setEnemyDirection(ENEMY_LEFT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 90 && m->getEnemyAngle() * (180 / PI) <= 135)//������
						{
							m->setEnemyDirection(ENEMY_UP_LEFT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 45 && m->getEnemyAngle() * (180 / PI) <= 90)//��������
						{
							m->setEnemyDirection(ENEMY_UP_RIGHT_HIT);
						}

						if ((m->getEnemyAngle() * (180 / PI) <= 45 && m->getEnemyAngle() * (180 / PI) >= 0) ||//������
							(m->getEnemyAngle() * (180 / PI) <= 360 && m->getEnemyAngle() * (180 / PI) >= 315))
						{
							m->setEnemyDirection(ENEMY_RIGHT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 270 && m->getEnemyAngle() * (180 / PI) <= 315)//�Ʒ�������
						{
							m->setEnemyDirection(ENEMY_DOWN_RIGHT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 225 && m->getEnemyAngle() * (180 / PI) <= 270)//�Ʒ�����
						{
							m->setEnemyDirection(ENEMY_DOWN_LEFT_HIT);
						}
					}
					m->setEnemyHP(_player->getPlayerAttackPower());//���ʹ����� ������
					_player->setPlayerAttackRectRemove();//�÷��̾���� ��Ʈ����
				}
			}
		}

		if (m->getEnemyAttackRect().getSize().x != 0 && m->getEnemyAttackRect().getSize().y != 0)
		{
			if (isCollision(_player->getRect(), m->getEnemyAttackRect()))//�÷��̾Ʈ�� �̾�Ĺ ���ݷ�Ʈ�� �浹������
			{
				_player->setPlayerPlusX(cosf(m->getEnemyAngle()) * 10.0f);
				_player->setPlayerPlusY(-sinf(m->getEnemyAngle()) * 10.0f);
				m->setIsAttack(false);
			}
		}

		//�÷��̾� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� �÷��̾ �о��
		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(m->getRect().left);
		rcHold.right = FLOAT_TO_INT(m->getRect().right);
		rcHold.top = FLOAT_TO_INT(m->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(m->getRect().bottom);

		RECT rcMove;
		rcMove.left = FLOAT_TO_INT(_player->getRect().left);
		rcMove.right = FLOAT_TO_INT(_player->getRect().right);
		rcMove.top = FLOAT_TO_INT(_player->getRect().top);
		rcMove.bottom = FLOAT_TO_INT(_player->getRect().bottom);

		if (IntersectRect(&rcInter, &rcHold, &rcMove))
		{
			int interW = rcInter.right - rcInter.left;
			int interH = rcInter.bottom - rcInter.top;

			if (m->getEnemyDirection() != ENEMY_TUNNEL_MOVE)//�̾�Ĺ�� ���ӿ� �ִ� ���°� �ƴҰ�쿡�� �浹ó��
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

}

void collisionManager::bulletCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < temp.size(); i++)
	{
		meerkat* m = dynamic_cast<meerkat*>(temp[i]);
		if (m == NULL) continue;

		vector<tagBullet> bullet = m->getBullets()->getvEnemyBullet();
		if (bullet.size() == NULL) continue;
		for (int j = 0; j < bullet.size(); ++j)
		{
			if (isCollision(_player->getRect(), m->getBullets()->getvEnemyBullet()[j].rc))//�̾�Ĺ�� �Ѿ��� �÷��̾� ��Ʈ�� �浹������
			{
				EFFECTMANAGER->play("enemyMeerkatBallEffect", CAMERA->getRelativeVector2(m->getBullets()->getvEnemyBullet()[j].position).x + 25, CAMERA->getRelativeVector2(m->getBullets()->getvEnemyBullet()[j].position).y + 25);
				m->getBullets()->remove(j);//�ش� �Ѿ��� ���͸� ����
				break;
			}
		}
	}
}

void collisionManager::enemyCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);

		//���ʹ� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� ���ʹ� �о��
		RECT rcInter;

		RECT rcHold;

		RECT rcMove;

		for (int j = 0; j < temp.size(); j++)
		{
			enemy* e2 = dynamic_cast<enemy*>(temp[j]);

			if (i == j) continue;

			rcHold.left = FLOAT_TO_INT(e->getRect().left);
			rcHold.right = FLOAT_TO_INT(e->getRect().right);
			rcHold.top = FLOAT_TO_INT(e->getRect().top);
			rcHold.bottom = FLOAT_TO_INT(e->getRect().bottom);

			rcMove.left = FLOAT_TO_INT(e2->getRect().left);
			rcMove.right = FLOAT_TO_INT(e2->getRect().right);
			rcMove.top = FLOAT_TO_INT(e2->getRect().top);
			rcMove.bottom = FLOAT_TO_INT(e2->getRect().bottom);

			if (e->getEnemyIsAttack())
			{
				if (IntersectRect(&rcInter, &rcHold, &rcMove))
				{
					int interW = rcInter.right - rcInter.left;
					int interH = rcInter.bottom - rcInter.top;

					if (interW > interH)//�����浹(���Ʒ�)
					{
						if (rcInter.top == rcHold.top)//������ �浹
						{
							e2->setEnemyY(e2->getRect().getCenter().y - interH);
						}
						//�Ʒ����� �浹
						else if (rcInter.bottom == rcHold.bottom)
						{
							e2->setEnemyY(e2->getRect().getCenter().y + interH);
						}
					}
					else//�翷���� �浹
					{
						if (rcInter.left == rcHold.left)//���ʿ��� �浹
						{
							e2->setEnemyX(e2->getRect().getCenter().x - interW);
						}

						else if (rcInter.right == rcHold.right)//�����ʿ��� �浹
						{
							e2->setEnemyX(e2->getRect().getCenter().x + interW);
						}
					}
				}
			}
		}
		//���ʹ� ��Ʈ�� ���ʹ� ��Ʈ�� �浹�� ���ʹ� �о��
	}
}
