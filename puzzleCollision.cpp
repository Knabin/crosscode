#include "stdafx.h"
#include "puzzleCollision.h"
#include "puzzleTabButton.h"
#include "puzzleDestruct.h"
#include "puzzleBlueWall.h"
#include "puzzleOrangeWall.h"
#include "foothold.h"
#include "bullet.h"
#include "iEvent.h"

HRESULT puzzleCollision::init()
{
	SOUNDMANAGER->addSound("counter", "sounds/object/counter.ogg", false, false);
	SOUNDMANAGER->addSound("ore-destructible", "sounds/object/ore-destructible.ogg", false, false);

	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	_count = 0;

	for (int i = 0; i < 6; i++)
	{
		_puzzleTabButtonCollision[i] = false;
		_puzzleComplete[i] = false;
	}

	return S_OK;
}

void puzzleCollision::release()
{
}

void puzzleCollision::update()
{
	puzzleBlueWallCollision();//블루벽에 플레이어의 충전된 총알이 충돌시 반사 + 플레이어가 블루벽에 밀려나게 하기위한 함수
	puzzleOrangeWallCollision();//오렌지벽이랑 플레이어 렉트가 충돌하면 플레이어를 밀어나게 하기위한 함수
	puzzleTabButtonCollision();//탑버튼이 플레이어의 총알공격렉트 + 근접공격 렉트에 충돌되면 벽을 내려가게 하기위한 함수
	puzzleDestructCollision();//플레이어의 총알공격렉트 + 근접공격렉트가 충돌되면 벽HP가 깍이고 벽HP가 0이되면 이펙트를 발생하고 렉트를 제거하기 위한 함수
	puzzleComplete();//탑버튼이 모두 충돌됬고 탑버튼들의 프레임재생도 모두 끝났다면 발판상태를 트루로 바꿔주기 위한 함수
}

void puzzleCollision::puzzleBlueWallCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleBlueWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleBlueWall* p = dynamic_cast<puzzleBlueWall*>(temp[i]);//모든 블루벽

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			if (p->getRect().getSize().x != 0 && p->getRect().getSize().y != 0)
			{
				if (isCollision(p->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//플레이어의 총알렉트랑 블루벽 렉트랑 충돌했으면
				{
					if (!_player->getBullet()->getVPlayerBullet()[j].nomal)//플레이어의 총알이 충전된 상태이면
					{
						_player->getBullet()->setPlayerBullet(j, _player->getBullet()->getVPlayerBullet()[j].angle + PI);//플레이어의 총알 반사
					}
					else//플레이어의 총알이 충전된 총알이 아니면
					{
						_player->getBullet()->remove(j);//플레이어의 총알렉트를 삭제
						break;
					}
				}
			}
		}

		//플레이어렉트랑 블루벽 렉트랑 충돌했을때 플레이어 렉트를 밀어버리기 위한 기능
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
		//플레이어렉트랑 블루벽 렉트랑 충돌했을때 플레이어 렉트를 밀어버리기 위한 기능
	}
}

void puzzleCollision::puzzleOrangeWallCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleOrangeWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleOrangeWall* p = dynamic_cast<puzzleOrangeWall*>(temp[i]);//오렌지벽

		//오렌지벽 렉트랑 플레이어 렉트가 충돌하면 플레이어 렉트를 밀어버리기 위한 코드
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
		//오렌지벽 렉트랑 플레이어 렉트가 충돌하면 플레이어 렉트를 밀어버리기 위한 코드
	}
}

void puzzleCollision::puzzleTabButtonCollision()
{
	vector<gameObject*> topButtonTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleTabButton");
	vector<gameObject*> blueWallTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleBlueWall");
	vector<gameObject*> orangeTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleOrangeWall");


	for (int i = 0; i < topButtonTemp.size(); i++)
	{
		puzzleTabButton* allButtonP = dynamic_cast<puzzleTabButton*>(topButtonTemp[i]);//해당 충돌된 탑버튼이 몇번째 방인지 알기위한 모든 탑버튼
		puzzleTabButton* buttonP1 = dynamic_cast<puzzleTabButton*>(topButtonTemp[1]);//1번째 탑버튼
		puzzleTabButton* buttonP2 = dynamic_cast<puzzleTabButton*>(topButtonTemp[5]);//2번째 탑버튼
		puzzleTabButton* buttonP3 = dynamic_cast<puzzleTabButton*>(topButtonTemp[2]);//3번째 탑버튼
		puzzleTabButton* buttonP4 = dynamic_cast<puzzleTabButton*>(topButtonTemp[0]);//위쪽 컨테이너 탑버튼
		puzzleTabButton* buttonP5 = dynamic_cast<puzzleTabButton*>(topButtonTemp[3]);//아래쪽 컨테이너 탑버튼
		puzzleTabButton* buttonP6 = dynamic_cast<puzzleTabButton*>(topButtonTemp[4]);//근접공격용 탑버튼

		puzzleBlueWall* blueP = dynamic_cast<puzzleBlueWall*>(blueWallTemp[0]);//1번째 블루벽
		puzzleOrangeWall* orangeP1 = dynamic_cast<puzzleOrangeWall*>(orangeTemp[1]);//1번째 오렌지벽

		if (buttonP1->getRect().getSize().x != 0 && buttonP1->getRect().getSize().y != 0)
		{
			if (isCollision(buttonP1->getRect(), _player->getPlayerAttackRect()))//1번째 탑버튼 렉트에 플레이어 근접공격 렉트가 충돌하면
			{
				if (!SOUNDMANAGER->isPlaySound("counter"))
				{
					SOUNDMANAGER->play("counter", 1.0f);
				}

				_puzzleTabButtonCollision[0] = true;
				buttonP1->setRect(RectMakePivot(Vector2(buttonP1->getRect().getCenter().x, buttonP1->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//1번째 탑버튼 렉트크기 0으로 변경
			}
		}


		if (buttonP6->getRect().getSize().x != 0 && buttonP6->getRect().getSize().y != 0)
		{
			if (isCollision(buttonP6->getRect(), _player->getPlayerAttackRect()))//상자에 둘러쌓인 탑버튼렉트에 플레이어의 근접공격 렉트가 충돌했으면
			{
				if (!SOUNDMANAGER->isPlaySound("counter"))
				{
					SOUNDMANAGER->play("counter", 1.0f);
				}

				_puzzleTabButtonCollision[5] = true;
				buttonP6->setRect(RectMakePivot(Vector2(buttonP6->getRect().getCenter().x, buttonP6->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//상자에 둘러쌓인 탑버튼 렉트크기 0으로 변경
			}
		}


		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)//플레이어의 총알벡터 사이즈만큼 for문
		{
			if (buttonP1->getRect().getSize().x != 0 && buttonP1->getRect().getSize().y != 0)
			{
				if (isCollision(buttonP1->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//1번째 탑버튼렉트랑 플레이어의 총알렉트가 충돌하면
				{
					if (!SOUNDMANAGER->isPlaySound("counter"))
					{
						SOUNDMANAGER->play("counter", 1.0f);
					}

					_puzzleTabButtonCollision[0] = true;//1번째 탑버튼이 충돌했다는 bool값 트루
					buttonP1->setRect(RectMakePivot(Vector2(buttonP1->getRect().getCenter().x, buttonP1->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//1번째 탑버튼 렉트크기 0으로 변경
					_player->getBullet()->remove(j);//플레이어의 총알벡터 삭제
					iPlayerTurn* i2 = new iPlayerTurn(0);
					iCameraMove* i = new iCameraMove(blueP, 1.5f);
					SOUNDMANAGER->play("barrier");
					EVENTMANAGER->addEvent(i2);
					EVENTMANAGER->addEvent(i);
					break;
				}
			}

			if (buttonP2->getRect().getSize().x != 0 && buttonP2->getRect().getSize().y != 0)
			{
				if (isCollision(buttonP2->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//2번째 탑버튼 렉트에 플레이어의 총알렉트가 충돌했으면
				{
					if (!SOUNDMANAGER->isPlaySound("counter"))
					{
						SOUNDMANAGER->play("counter", 1.0f);
					}

					_puzzleTabButtonCollision[1] = true;//2번째 탑버튼이 충돌했다는 bool값 트루
					buttonP2->setRect(RectMakePivot(Vector2(buttonP2->getRect().getCenter().x, buttonP2->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//2번째 탑버튼 렉트크기 0으로 변경
					_player->getBullet()->remove(j);//플레이어의 총알벡터 삭제
					iCameraMove* i = new iCameraMove(orangeP1, 1.5f);
					iPlayerTurn* i2 = new iPlayerTurn(4);
					SOUNDMANAGER->play("barrier");
					EVENTMANAGER->addEvent(i2);
					EVENTMANAGER->addEvent(i);
					break;
				}
			}

					if (buttonP3->getRect().getSize().x != 0 && buttonP3->getRect().getSize().y != 0)
					{
						if (isCollision(buttonP3->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//3번째 탑버튼 렉트에 플레이어의 총알렉트가 충돌했으면
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[2] = true;//3번째 탑버튼이 충돌했다는 bool값 트루
							buttonP3->setRect(RectMakePivot(Vector2(buttonP3->getRect().getCenter().x, buttonP3->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//3번째 탑버튼 렉트크기 0으로 변경
							_player->getBullet()->remove(j);//플레이어의 총알벡터 삭제
							break;
						}
					}

					if (buttonP4->getRect().getSize().x != 0 && buttonP4->getRect().getSize().y != 0)
					{
						if (isCollision(buttonP4->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//위쪽 컨테이너 탑버튼에 플레이어의 총알렉트가 충돌했으면
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[3] = true;//위쪽 컨테이너 탑버튼이 충돌했다는 bool값 트루
							buttonP4->setRect(RectMakePivot(Vector2(buttonP4->getRect().getCenter().x, buttonP4->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//위쪽 컨테이너 탑버튼 렉트크기 0으로 변경
							_player->getBullet()->remove(j);//플레이어의 총알벡터 삭제
							break;
						}
					}


					if (buttonP5->getRect().getSize().x != 0 && buttonP5->getRect().getSize().y != 0)
					{
						if (isCollision(buttonP5->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//아래쪽 컨테이너 탑버튼에 플레이어의 총알렉트가 충돌했으면
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[4] = true;//아래쪽 컨테이너 탑버튼이 충돌했다는 bool값 트루
							buttonP5->setRect(RectMakePivot(Vector2(buttonP5->getRect().getCenter().x, buttonP5->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//아래쪽 컨테이너 탑버튼 렉트크기 0으로 변경
							_player->getBullet()->remove(j);//플레이어의 총알벡터 삭제
							break;
						}
					}


					if (buttonP6->getRect().getSize().x != 0 && buttonP6->getRect().getSize().y != 0)
					{
						if (isCollision(buttonP6->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//상자에 둘러쌓인 탑버튼에 플레이어의 총알렉트가 충돌했으면
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[5] = true;
							buttonP6->setRect(RectMakePivot(Vector2(buttonP6->getRect().getCenter().x, buttonP6->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//상자에 둘러쌓인 탑버튼 렉트크기 0으로 변경
							_player->getBullet()->remove(j);//플레이어의 총알벡터 삭제
							break;
						}
					}
				}

				if (_puzzleTabButtonCollision[0])//1번째 탑버튼이 충돌됬으면
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP1->getFrameX() < buttonP1->getImage()->getMaxFrameX() - 1)//1번째 탑버튼이 충돌했을때 x프레임을 몇까지 증가되게 할건지 정해줄 조건문
						{
							buttonP1->setFrameX(buttonP1->getFrameX() + 1);//1번째 탑버튼 프레임 재생
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[1])//2번째 탑버튼이 충돌됬으면
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP2->getFrameX() < buttonP2->getImage()->getMaxFrameX() - 1)//2번째 탑버튼이 충돌했을때 x프레임을 몇까지 증가되게 할건지 정해줄 조건문
						{
							buttonP2->setFrameX(buttonP2->getFrameX() + 1);//2번째 탑버튼 프레임 재생
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[2])//3번째 탑버튼이 충돌됬으면
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP3->getFrameX() < buttonP3->getImage()->getMaxFrameX() - 1)//3번째 탑버튼이 충돌했을때 x프레임을 몇까지 증가되게 할건지 정해줄 조건문
						{
							buttonP3->setFrameX(buttonP3->getFrameX() + 1);//3번째 탑버튼 프레임 재생
						}

						if (buttonP3->getFrameX() >= buttonP3->getImage()->getMaxFrameX() - 1)//3번째 탑버튼의 프레임이 마지막에 도달했으면
						{
							_puzzleComplete[2] = true;
							_puzzleTabButtonCollision[2] = false;
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[3])//위쪽 컨테이너 탑버튼이 충돌됬으면
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP4->getFrameX() < buttonP4->getImage()->getMaxFrameX() - 1)//위쪽 컨테이너 탑버튼이 충돌했을때 x프레임을 몇까지 증가되게 할건지 정해줄 조건문
						{
							buttonP4->setFrameX(buttonP4->getFrameX() + 1);//위쪽 컨테이너 탑버튼 프레임 재생
						}

						if (buttonP4->getFrameX() >= buttonP4->getImage()->getMaxFrameX() - 1)//위쪽 컨테이너 탑버튼의 프레임이 마지막에 도달했으면
						{
							_puzzleComplete[3] = true;
							_puzzleTabButtonCollision[3] = false;
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[4])//아래쪽 컨테이너 탑버튼이 충돌됬으면
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP5->getFrameX() < buttonP5->getImage()->getMaxFrameX() - 1)//아래쪽 컨테이너 탑버튼이 충돌했을때 x프레임을 몇까지 증가되게 할건지 정해줄 조건문
						{
							buttonP5->setFrameX(buttonP5->getFrameX() + 1);//아래쪽 컨테이너 탑버튼 프레임 재생
						}

						if (buttonP5->getFrameX() >= buttonP5->getImage()->getMaxFrameX() - 1)//아래쪽 컨테이너 탑버튼의 프레임이 마지막에 도달했으면
						{
							_puzzleComplete[4] = true;
							_puzzleTabButtonCollision[4] = false;
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[5])//상자에 둘러쌓인 탑버튼이 충돌됬으면
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP6->getFrameX() < buttonP6->getImage()->getMaxFrameX() - 1)//상자에 둘러쌓인 탑버튼이 충돌했을때 x프레임을 몇까지 증가되게 할건지 정해줄 조건문
						{
							buttonP6->setFrameX(buttonP6->getFrameX() + 1);//상자에 둘러쌓인 탑버튼 프레임 재생
						}

						if (buttonP6->getFrameX() >= buttonP6->getImage()->getMaxFrameX() - 1)//상자에 둘러쌓인 탑버튼의 프레임이 마지막에 도달했으면
						{
							_puzzleComplete[5] = true;
							_puzzleTabButtonCollision[5] = false;
						}
						_count = 0;
					}
				}


				//1번째 탑버튼이 충돌처리 되서 프레임이 끝났으면

				if (_puzzleTabButtonCollision[0])//1번째 탑버튼이 충돌됬으면
				{
					if (buttonP1->getFrameX() >= buttonP1->getImage()->getMaxFrameX() - 1)//1번째 탑버튼의 프레임이 끝났다면
					{
						_count++;
						if (_count % 15 == 0)
						{
							if (blueP->getFrameX() < blueP->getImage()->getMaxFrameX() - 1)//1번째 블루벽의 프레임을 마지막 프레임까지 증가시키기 위한 조건
							{
								blueP->setFrameX(blueP->getFrameX() + 1);
							}

							if (blueP->getFrameX() >= blueP->getImage()->getMaxFrameX() - 1)//1번째 블루벽의 프레임이 마지막에 도달했다면
							{
								blueP->setRect(RectMakePivot(Vector2(blueP->getRect().getCenter().x, blueP->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//1번째 블루벽의 렉트크기0으로 변경
								_puzzleComplete[0] = true;
								_puzzleTabButtonCollision[0] = false;
							}
							_count = 0;
						}
					}
				}
				//위에 코드는 1번째 탑버튼이 충돌되면 1번째 블루벽의 프레임을 재생시키고 렉트를 제거시키기 위한 코드


				//2번째 탑버튼이 충돌처리 되서 프레임이 끝났으면

				if (_puzzleTabButtonCollision[1])//2번째 탑버튼이 충돌됬으면
				{
					if (buttonP2->getFrameX() >= buttonP2->getImage()->getMaxFrameX() - 1)//2번째 탑버튼의 프레임이 끝났다면
					{
						_count++;
						if (_count % 15 == 0)
						{
							if (orangeP1->getFrameX() < orangeP1->getImage()->getMaxFrameX() - 1)//1번째 오렌지벽 프레임이 멕스 프레임보다 작으면
							{
								orangeP1->setFrameX(orangeP1->getFrameX() + 1);//오렌지벽 프레임 증가
							}

							if (orangeP1->getFrameX() >= orangeP1->getImage()->getMaxFrameX() - 1)//1번째 오렌지벽의 프레임이 마지막에 도달했다면
							{
								orangeP1->setRect(RectMakePivot(Vector2(orangeP1->getRect().getCenter().x, orangeP1->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//오렌지벽 렉트크기 0으로 변경
								_puzzleComplete[1] = true;
								_puzzleTabButtonCollision[1] = false;
							}
							_count = 0;
						}
					}
				}
				//위에 코드는 2번째 탑버튼이 충돌처리 되면 1번째 오렌지벽의 프레임을 재생시키고 렉트를 제거시키기 위한 코드


				//탑버튼 렉트랑 플레이어 렉트랑 충돌시 플레이어를 밀어내기 위한 코드
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
				//탑버튼 렉트랑 플레이어 렉트랑 충돌시 플레이어를 밀어내기 위한 코드
			}
}

void puzzleCollision::puzzleDestructCollision()
{
	vector<gameObject*> destructTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleDestruct");

	for (int i = 0; i < destructTemp.size(); i++)
	{
		puzzleDestruct* d = dynamic_cast<puzzleDestruct*>(destructTemp[i]);

		if (d->getRect().getSize().x != 0 && d->getRect().getSize().y != 0)
		{
			if (isCollision(d->getRect(), _player->getPlayerAttackRect()))//벽에 플레이어의 근접공격 렉트가 충돌하면
			{
				if (!SOUNDMANAGER->isPlaySound("ore-destructible"))
				{
					SOUNDMANAGER->play("ore-destructible", 0.5f);
				}

				if (d->getHP() > 0)
				{
					d->setHP(_player->getPlayerAttackPower());//플레이어의 공격력 만큼 데미지 주기
				}
			}
		}


		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)//플레이어의 총알렉트 벡터사이즈만큼 for문
		{
			if (d->getRect().getSize().x != 0 && d->getRect().getSize().y != 0)
			{
				if (isCollision(d->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//벽에 플레이어의 총알렉트가 충돌하면
				{
					if (!SOUNDMANAGER->isPlaySound("ore-destructible"))
					{
						SOUNDMANAGER->play("ore-destructible", 0.5f);
					}

					if (d->getHP() > 0)
					{
						d->setHP(50);//플레이어의 공격력 만큼 데미지 주기
						_player->getBullet()->remove(j);//플레이어의 총알 벡터 삭제
						break;
					}
				}
			}
		}


		//벽 렉트랑 플레이어 렉트랑 충돌시 플레이어를 밀어내기 위한 코드
		RECT rcInter;

		RECT rcHold;
		rcHold.left = FLOAT_TO_INT(d->getRect().left);
		rcHold.right = FLOAT_TO_INT(d->getRect().right);
		rcHold.top = FLOAT_TO_INT(d->getRect().top);
		rcHold.bottom = FLOAT_TO_INT(d->getRect().bottom);

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
		//벽 렉트랑 플레이어 렉트랑 충돌시 플레이어를 밀어내기 위한 코드
	}
}

void puzzleCollision::puzzleComplete()
{
	vector<gameObject*> footholdTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "foothold");

	for (int i = 0; i < footholdTemp.size(); i++)
	{
		foothold* footholdP = dynamic_cast<foothold*>(footholdTemp[i]);

		if (_puzzleComplete[0] &&//모든 탑버튼들의 충돌이 끝나고 프레임 재생까지 끝났다면
			_puzzleComplete[1] &&
			_puzzleComplete[2] &&
			_puzzleComplete[3] &&
			_puzzleComplete[4] &&
			_puzzleComplete[5])
		{
			if (!footholdP->getIsOn())
			{
				SOUNDMANAGER->play("puzzle");
				iCameraMove* i = new iCameraMove(footholdP, 2.0f);
				iPlayerTurn* i2 = new iPlayerTurn(4);
				EVENTMANAGER->addEvent(i2);
				EVENTMANAGER->addEvent(i);
			}
			footholdP->setIsOn(true);//발판상태값 트루
		}
	}
}
