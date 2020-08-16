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
	bulletCollision();
}

void collisionManager::render()
{
}

void collisionManager::playerCollision()
{
	
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

void collisionManager::bulletCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);

	for (int i = 0; i < temp.size(); i++)
	{
		meerkat* m = dynamic_cast<meerkat*>(temp[i]);
		if (m == NULL) continue;
		// 미어캣의 getBullets() 반환 -> bullets 포인터
		// => 인데 지섭이가 쓴 건 bullets 포인터에 0번째 방에 접근하라  m->getBullets()[i] << 여기서 윈도우가 뭐지??? 왜 포인터의 0번방에 접근하라 그러지?????? 이 상황이었던것임~~
		// 이거 어케 끊어

		// bullets의 getvEnemyBullet() 반환 -> 구조체의 벡터
		// 됏네!!!!!!!!

		vector<tagBullet> bullet = m->getBullets()->getvEnemyBullet();
		if (bullet.size() == NULL) continue;		// 이거는 이제 필요 없겠다 아래 j for문이 bullet.size()만큼 돌아가니까
		for (int j = 0; j < bullet.size(); ++j)
		{
			//cout << m->getBullets()->getvEnemyBullet()[j].position.x << endl;
			if (isCollision(_player->getRect(), m->getBullets()->getvEnemyBullet()[j].rc))//미어캣의 총알이 플레이어 렉트에 충돌했으면
			{
				m->getBullets()->remove(j);//해당 총알의 벡터를 삭제
				break;
			}
		}
		/*
		지금 위에 i로 돌아가는 for문은 해당 "에너미"에 접근하기 위한 거잖아
		근데 그 i를 
		ㅋㅋㅋㅋㅋㅋ
		for문을 한번 더 돌려야지

		*/
	}
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
