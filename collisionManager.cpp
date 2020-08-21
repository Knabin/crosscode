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
	enemyCollision();//에너미끼리 충돌
	buffaloCollision();//버팔로랑 플레이어 충돌처리
	hedgehagCollision();//고슴도치랑 플레이어 충돌처리
	meerkatCollision();//미어캣이랑 플레이어 충돌처리
	bulletCollision();//미어캣의 총알이랑 플레이어 충돌처리
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
			if (isCollision(_player->getRect(), b->getEnemyAttackRect()))//플레이어렉트에 버팔로 공격렉트가 충돌했으면
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
			if (isCollision(b->getRect(), _player->getPlayerAttackRect()))//버팔로 렉트에 플레이어 공격렉트가 충돌했으면
			{
				b->setEnemyHP(_player->getPlayerAttackPower());//에너미한테 데미지
				_player->setPlayerAttackRectRemove();//플레이어공격 렉트삭제
			}
		}

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)//플레이어 원거리 공격이 버팔로한테 맞으면
		{
			if (isCollision(b->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))
			{
				b->setEnemyHP(_player->getPlayerAttackPower());
				_player->getBullet()->remove(j);
			}
		}

		//플레이어 렉트와 에너미 렉트가 충돌시 플레이어를 밀어내기
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

			if (interW > interH)//수직충돌(위아래)
			{
				//위에서 부딪혔을때
				if (rcInter.top == rcHold.top)
				{
					_player->setPlayerY(_player->getRect().getCenter().y - interH);
				}
				//아래에서 부딪혔을때
				else if (rcInter.bottom == rcHold.bottom)
				{
					_player->setPlayerY(_player->getRect().getCenter().y + interH);
				}
			}
			else//양옆에서 충돌했을때
			{
				//왼족에서 충돌했을때
				if (rcInter.left == rcHold.left)
				{
					_player->setPlayerX(_player->getRect().getCenter().x - interW);
				}
				//오른쪽에서 충돌했을때
				else if (rcInter.right == rcHold.right)
				{
					_player->setPlayerX(_player->getRect().getCenter().x + interW);
				}
			}
		}
		//플레이어 렉트와 에너미 렉트가 충돌시 플레이어를 밀어내기
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
			if (isCollision(h->getRect(), _player->getPlayerAttackRect()))//고슴도치 렉트에 플레이어 공격렉트가 충돌시
			{
				if (!h->getEnemyIsAttack())
				{
					if (h->getEnemyAngle() * (180 / PI) >= 135 && h->getEnemyAngle() * (180 / PI) <= 225)//왼쪽
					{
						h->setEnemyDirection(ENEMY_LEFT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 90 && h->getEnemyAngle() * (180 / PI) <= 135)//왼쪽위
					{
						h->setEnemyDirection(ENEMY_UP_LEFT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 45 && h->getEnemyAngle() * (180 / PI) <= 90)//오른쪽위
					{
						h->setEnemyDirection(ENEMY_UP_RIGHT_HIT);
					}

					if ((h->getEnemyAngle() * (180 / PI) <= 45 && h->getEnemyAngle() * (180 / PI) >= 0) ||//오른쪽
						(h->getEnemyAngle() * (180 / PI) <= 360 && h->getEnemyAngle() * (180 / PI) >= 315))
					{
						h->setEnemyDirection(ENEMY_RIGHT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 270 && h->getEnemyAngle() * (180 / PI) <= 315)//아래오른쪽
					{
						h->setEnemyDirection(ENEMY_DOWN_RIGHT_HIT);
					}

					if (h->getEnemyAngle() * (180 / PI) >= 225 && h->getEnemyAngle() * (180 / PI) <= 270)//아래왼쪽
					{
						h->setEnemyDirection(ENEMY_DOWN_LEFT_HIT);
					}
				}
				h->setEnemyHP(_player->getPlayerAttackPower());//에너미한테 데미지
				_player->setPlayerAttackRectRemove();//플레이어공격 렉트삭제
			}
		}

		//플레이어 렉트와 에너미 렉트가 충돌시 플레이어를 밀어내기
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

			if (!h->getEnemyIsAttack())//에너미가 공격상태가 아닐경우에만 충돌처리
			{
				if (interW > interH)//수직충돌(위아래)
				{
					//위에서 부딪혔을때
					if (rcInter.top == rcHold.top)
					{
						//_player->setPlayerY(_player->getRect().getCenter().y - interH);
						h->setEnemyY(h->getRect().getCenter().y - interH);
					}
					//아래에서 부딪혔을때
					else if (rcInter.bottom == rcHold.bottom)
					{
						//_player->setPlayerY(_player->getRect().getCenter().y + interH);
						h->setEnemyY(h->getRect().getCenter().y + interH);
					}
				}
				else//양옆에서 충돌했을때
				{
					//왼족에서 충돌했을때
					if (rcInter.left == rcHold.left)
					{
						//_player->setPlayerX(_player->getRect().getCenter().x - interW);
						h->setEnemyX(h->getRect().getCenter().x - interW);
					}
					//오른쪽에서 충돌했을때
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
		//플레이어 렉트와 에너미 렉트가 충돌시 플레이어를 밀어내기
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
			if (isCollision(m->getRect(), _player->getPlayerAttackRect()))//미어캣 렉트에 플레이어 공격렉트가 충돌시
			{
				if (m->getEnemyDirection() != ENEMY_TUNNEL_MOVE)
				{
					if (!m->getEnemyIsAttack())
					{
						if (m->getEnemyAngle() * (180 / PI) >= 135 && m->getEnemyAngle() * (180 / PI) <= 225)//왼쪽
						{
							m->setEnemyDirection(ENEMY_LEFT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 90 && m->getEnemyAngle() * (180 / PI) <= 135)//왼쪽위
						{
							m->setEnemyDirection(ENEMY_UP_LEFT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 45 && m->getEnemyAngle() * (180 / PI) <= 90)//오른쪽위
						{
							m->setEnemyDirection(ENEMY_UP_RIGHT_HIT);
						}

						if ((m->getEnemyAngle() * (180 / PI) <= 45 && m->getEnemyAngle() * (180 / PI) >= 0) ||//오른쪽
							(m->getEnemyAngle() * (180 / PI) <= 360 && m->getEnemyAngle() * (180 / PI) >= 315))
						{
							m->setEnemyDirection(ENEMY_RIGHT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 270 && m->getEnemyAngle() * (180 / PI) <= 315)//아래오른쪽
						{
							m->setEnemyDirection(ENEMY_DOWN_RIGHT_HIT);
						}

						if (m->getEnemyAngle() * (180 / PI) >= 225 && m->getEnemyAngle() * (180 / PI) <= 270)//아래왼쪽
						{
							m->setEnemyDirection(ENEMY_DOWN_LEFT_HIT);
						}
					}
					m->setEnemyHP(_player->getPlayerAttackPower());//에너미한테 데미지
					_player->setPlayerAttackRectRemove();//플레이어공격 렉트삭제
				}
			}
		}

		if (m->getEnemyAttackRect().getSize().x != 0 && m->getEnemyAttackRect().getSize().y != 0)
		{
			if (isCollision(_player->getRect(), m->getEnemyAttackRect()))//플레이어렉트에 미어캣 공격렉트가 충돌했으면
			{
				_player->setPlayerPlusX(cosf(m->getEnemyAngle()) * 10.0f);
				_player->setPlayerPlusY(-sinf(m->getEnemyAngle()) * 10.0f);
				m->setIsAttack(false);
			}
		}

		//플레이어 렉트와 에너미 렉트가 충돌시 플레이어를 밀어내기
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

			if (m->getEnemyDirection() != ENEMY_TUNNEL_MOVE)//미어캣이 땅속에 있는 상태가 아닐경우에만 충돌처리
			{
				if (interW > interH)//수직충돌(위아래)
				{
					//위에서 부딪혔을때
					if (rcInter.top == rcHold.top)
					{
						_player->setPlayerY(_player->getRect().getCenter().y - interH);
					}
					//아래에서 부딪혔을때
					else if (rcInter.bottom == rcHold.bottom)
					{
						_player->setPlayerY(_player->getRect().getCenter().y + interH);
					}
				}
				else//양옆에서 충돌했을때
				{
					//왼족에서 충돌했을때
					if (rcInter.left == rcHold.left)
					{
						_player->setPlayerX(_player->getRect().getCenter().x - interW);
					}
					//오른쪽에서 충돌했을때
					else if (rcInter.right == rcHold.right)
					{
						_player->setPlayerX(_player->getRect().getCenter().x + interW);
					}
				}
			}
		}
		//플레이어 렉트와 에너미 렉트가 충돌시 플레이어를 밀어내기
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
			if (isCollision(_player->getRect(), m->getBullets()->getvEnemyBullet()[j].rc))//미어캣의 총알이 플레이어 렉트에 충돌했으면
			{
				EFFECTMANAGER->play("enemyMeerkatBallEffect", CAMERA->getRelativeVector2(m->getBullets()->getvEnemyBullet()[j].position).x + 25, CAMERA->getRelativeVector2(m->getBullets()->getvEnemyBullet()[j].position).y + 25);
				m->getBullets()->remove(j);//해당 총알의 벡터를 삭제
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

		//에너미 렉트와 에너미 렉트가 충돌시 에너미 밀어내기
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

					if (interW > interH)//수직충돌(위아래)
					{
						if (rcInter.top == rcHold.top)//위에서 충돌
						{
							e2->setEnemyY(e2->getRect().getCenter().y - interH);
						}
						//아래에서 충돌
						else if (rcInter.bottom == rcHold.bottom)
						{
							e2->setEnemyY(e2->getRect().getCenter().y + interH);
						}
					}
					else//양옆에서 충돌
					{
						if (rcInter.left == rcHold.left)//왼쪽에서 충돌
						{
							e2->setEnemyX(e2->getRect().getCenter().x - interW);
						}

						else if (rcInter.right == rcHold.right)//오른쪽에서 충돌
						{
							e2->setEnemyX(e2->getRect().getCenter().x + interW);
						}
					}
				}
			}
		}
		//에너미 렉트와 에너미 렉트가 충돌시 에너미 밀어내기
	}
}
