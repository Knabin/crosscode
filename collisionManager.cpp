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
	enemyCollision();//에너미렉트에 플레이어 렉트가 충돌시
	playerCollision();//플레이어렉트에 에너미 렉트가 충돌시
}

void collisionManager::render()
{
}

void collisionManager::playerCollision()
{
	//에너미 공격렉트랑 플레이어가 충돌시
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);
		if (isCollision(_player->getRect(), e->getEnemyAttackRect()))//에너미 공격렉트와 플레이어 렉트가 충돌했으면
		{
			_count++;
			if (_count % 10 == 0)//충돌한 이후 에너미의 공격 상태값을 변경하기까지의 딜레이
			{
				_count = 0;//딜레이 초기화
				//_player->setPlayerHP(e->getEnemyAttackPower());//에너미의 공격력 만큼 플레이어에게 데미지주기
			}
			e->setEnemyAttackRect();//에너미의 공격렉트 제거
		}

		//플레이어 렉트와 에너미 렉트가 충돌시 플레이어를 밀어내기
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

			if (!e->getEnemyIsAttack())//에너미가 공격상태가 아닐경우에만 충돌처리
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
	//에너미 공격렉트랑 플레이어가 충돌시
}

void collisionManager::enemyCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);

		//에너미 렉트랑 플레이어의 공격렉트랑 충돌시
		if (isCollision(e->getRect(), _player->getPlayerAttackRect()))//에너미렉트랑 플레이어 공격렉트랑 충돌시
		{
			if (e->getEnemyAngle() * (180 / PI) >= 135 && e->getEnemyAngle() * (180 / PI) <= 225 && !e->getEnemyIsAttack())//왼쪽
			{
				e->setEnemyDirection(ENEMY_LEFT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 90 && e->getEnemyAngle() * (180 / PI) <= 135 && !e->getEnemyIsAttack())//왼쪽위
			{
				e->setEnemyDirection(ENEMY_UP_LEFT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 45 && e->getEnemyAngle() * (180 / PI) <= 90 && !e->getEnemyIsAttack())//오른쪽위
			{
				e->setEnemyDirection(ENEMY_UP_RIGHT_HIT);
			}

			if ((e->getEnemyAngle() * (180 / PI) <= 45 && e->getEnemyAngle() * (180 / PI) >= 0) && !e->getEnemyIsAttack() ||//오른쪽
				(e->getEnemyAngle() * (180 / PI) <= 360 && e->getEnemyAngle() * (180 / PI) >= 315) && !e->getEnemyIsAttack())
			{
				e->setEnemyDirection(ENEMY_RIGHT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 270 && e->getEnemyAngle() * (180 / PI) <= 315 && !e->getEnemyIsAttack())//아래오른쪽
			{
				e->setEnemyDirection(ENEMY_DOWN_RIGHT_HIT);
			}

			if (e->getEnemyAngle() * (180 / PI) >= 225 && e->getEnemyAngle() * (180 / PI) <= 270 && !e->getEnemyIsAttack())//아래왼쪽
			{
				e->setEnemyDirection(ENEMY_DOWN_LEFT_HIT);
			}

			e->setEnemyHP(_player->getPlayerAttackPower());//에너미한테 데미지
			_player->setPlayerAttackRectRemove();//플레이어공격 렉트삭제
		}


		//에너미 렉트와 에너미 렉트가 충돌시 에너미 밀어내기
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

					if (interW2 > interH2)//수직충돌(위아래)
					{
						if (rcInter2.top == rcHold2.top)//위에서 충돌
						{
							e2->setEnemyY(e2->getRect().getCenter().y - interH2);
						}
						//아래에서 충돌
						else if (rcInter2.bottom == rcHold2.bottom)
						{
							e2->setEnemyY(e2->getRect().getCenter().y + interH2);
						}
					}
					else//양옆에서 충돌
					{
						if (rcInter2.left == rcHold2.left)//왼쪽에서 충돌
						{
							e2->setEnemyX(e2->getRect().getCenter().x - interW2);
						}

						else if (rcInter2.right == rcHold2.right)//오른쪽에서 충돌
						{
							e2->setEnemyX(e2->getRect().getCenter().x + interW2);
						}
					}
				}
			}
		}
		//에너미 렉트와 에너미 렉트가 충돌시 에너미 밀어내기

	}
}
