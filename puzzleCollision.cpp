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
	puzzleBlueWallCollision();//��纮�� �÷��̾��� ������ �Ѿ��� �浹�� �ݻ� + �÷��̾ ��纮�� �з����� �ϱ����� �Լ�
	puzzleOrangeWallCollision();//���������̶� �÷��̾� ��Ʈ�� �浹�ϸ� �÷��̾ �о�� �ϱ����� �Լ�
	puzzleTabButtonCollision();//ž��ư�� �÷��̾��� �Ѿ˰��ݷ�Ʈ + �������� ��Ʈ�� �浹�Ǹ� ���� �������� �ϱ����� �Լ�
	puzzleDestructCollision();//�÷��̾��� �Ѿ˰��ݷ�Ʈ + �������ݷ�Ʈ�� �浹�Ǹ� ��HP�� ���̰� ��HP�� 0�̵Ǹ� ����Ʈ�� �߻��ϰ� ��Ʈ�� �����ϱ� ���� �Լ�
	puzzleComplete();//ž��ư�� ��� �浹��� ž��ư���� ����������� ��� �����ٸ� ���ǻ��¸� Ʈ��� �ٲ��ֱ� ���� �Լ�
}

void puzzleCollision::puzzleBlueWallCollision()
{
	vector<gameObject*> temp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleBlueWall");

	for (int i = 0; i < temp.size(); i++)
	{
		puzzleBlueWall* p = dynamic_cast<puzzleBlueWall*>(temp[i]);//��� ��纮

		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)
		{
			if (p->getRect().getSize().x != 0 && p->getRect().getSize().y != 0)
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
		puzzleTabButton* buttonP3 = dynamic_cast<puzzleTabButton*>(topButtonTemp[2]);//3��° ž��ư
		puzzleTabButton* buttonP4 = dynamic_cast<puzzleTabButton*>(topButtonTemp[0]);//���� �����̳� ž��ư
		puzzleTabButton* buttonP5 = dynamic_cast<puzzleTabButton*>(topButtonTemp[3]);//�Ʒ��� �����̳� ž��ư
		puzzleTabButton* buttonP6 = dynamic_cast<puzzleTabButton*>(topButtonTemp[4]);//�������ݿ� ž��ư

		puzzleBlueWall* blueP = dynamic_cast<puzzleBlueWall*>(blueWallTemp[0]);//1��° ��纮
		puzzleOrangeWall* orangeP1 = dynamic_cast<puzzleOrangeWall*>(orangeTemp[1]);//1��° ��������

		if (buttonP1->getRect().getSize().x != 0 && buttonP1->getRect().getSize().y != 0)
		{
			if (isCollision(buttonP1->getRect(), _player->getPlayerAttackRect()))//1��° ž��ư ��Ʈ�� �÷��̾� �������� ��Ʈ�� �浹�ϸ�
			{
				if (!SOUNDMANAGER->isPlaySound("counter"))
				{
					SOUNDMANAGER->play("counter", 1.0f);
				}

				_puzzleTabButtonCollision[0] = true;
				buttonP1->setRect(RectMakePivot(Vector2(buttonP1->getRect().getCenter().x, buttonP1->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//1��° ž��ư ��Ʈũ�� 0���� ����
			}
		}


		if (buttonP6->getRect().getSize().x != 0 && buttonP6->getRect().getSize().y != 0)
		{
			if (isCollision(buttonP6->getRect(), _player->getPlayerAttackRect()))//���ڿ� �ѷ����� ž��ư��Ʈ�� �÷��̾��� �������� ��Ʈ�� �浹������
			{
				if (!SOUNDMANAGER->isPlaySound("counter"))
				{
					SOUNDMANAGER->play("counter", 1.0f);
				}

				_puzzleTabButtonCollision[5] = true;
				buttonP6->setRect(RectMakePivot(Vector2(buttonP6->getRect().getCenter().x, buttonP6->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//���ڿ� �ѷ����� ž��ư ��Ʈũ�� 0���� ����
			}
		}


		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)//�÷��̾��� �Ѿ˺��� �����ŭ for��
		{
			if (buttonP1->getRect().getSize().x != 0 && buttonP1->getRect().getSize().y != 0)
			{
				if (isCollision(buttonP1->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//1��° ž��ư��Ʈ�� �÷��̾��� �Ѿ˷�Ʈ�� �浹�ϸ�
				{
					if (!SOUNDMANAGER->isPlaySound("counter"))
					{
						SOUNDMANAGER->play("counter", 1.0f);
					}

					_puzzleTabButtonCollision[0] = true;//1��° ž��ư�� �浹�ߴٴ� bool�� Ʈ��
					buttonP1->setRect(RectMakePivot(Vector2(buttonP1->getRect().getCenter().x, buttonP1->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//1��° ž��ư ��Ʈũ�� 0���� ����
					_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˺��� ����
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
				if (isCollision(buttonP2->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//2��° ž��ư ��Ʈ�� �÷��̾��� �Ѿ˷�Ʈ�� �浹������
				{
					if (!SOUNDMANAGER->isPlaySound("counter"))
					{
						SOUNDMANAGER->play("counter", 1.0f);
					}

					_puzzleTabButtonCollision[1] = true;//2��° ž��ư�� �浹�ߴٴ� bool�� Ʈ��
					buttonP2->setRect(RectMakePivot(Vector2(buttonP2->getRect().getCenter().x, buttonP2->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//2��° ž��ư ��Ʈũ�� 0���� ����
					_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˺��� ����
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
						if (isCollision(buttonP3->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//3��° ž��ư ��Ʈ�� �÷��̾��� �Ѿ˷�Ʈ�� �浹������
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[2] = true;//3��° ž��ư�� �浹�ߴٴ� bool�� Ʈ��
							buttonP3->setRect(RectMakePivot(Vector2(buttonP3->getRect().getCenter().x, buttonP3->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//3��° ž��ư ��Ʈũ�� 0���� ����
							_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˺��� ����
							break;
						}
					}

					if (buttonP4->getRect().getSize().x != 0 && buttonP4->getRect().getSize().y != 0)
					{
						if (isCollision(buttonP4->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//���� �����̳� ž��ư�� �÷��̾��� �Ѿ˷�Ʈ�� �浹������
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[3] = true;//���� �����̳� ž��ư�� �浹�ߴٴ� bool�� Ʈ��
							buttonP4->setRect(RectMakePivot(Vector2(buttonP4->getRect().getCenter().x, buttonP4->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//���� �����̳� ž��ư ��Ʈũ�� 0���� ����
							_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˺��� ����
							break;
						}
					}


					if (buttonP5->getRect().getSize().x != 0 && buttonP5->getRect().getSize().y != 0)
					{
						if (isCollision(buttonP5->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//�Ʒ��� �����̳� ž��ư�� �÷��̾��� �Ѿ˷�Ʈ�� �浹������
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[4] = true;//�Ʒ��� �����̳� ž��ư�� �浹�ߴٴ� bool�� Ʈ��
							buttonP5->setRect(RectMakePivot(Vector2(buttonP5->getRect().getCenter().x, buttonP5->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//�Ʒ��� �����̳� ž��ư ��Ʈũ�� 0���� ����
							_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˺��� ����
							break;
						}
					}


					if (buttonP6->getRect().getSize().x != 0 && buttonP6->getRect().getSize().y != 0)
					{
						if (isCollision(buttonP6->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//���ڿ� �ѷ����� ž��ư�� �÷��̾��� �Ѿ˷�Ʈ�� �浹������
						{
							if (!SOUNDMANAGER->isPlaySound("counter"))
							{
								SOUNDMANAGER->play("counter", 1.0f);
							}

							_puzzleTabButtonCollision[5] = true;
							buttonP6->setRect(RectMakePivot(Vector2(buttonP6->getRect().getCenter().x, buttonP6->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//���ڿ� �ѷ����� ž��ư ��Ʈũ�� 0���� ����
							_player->getBullet()->remove(j);//�÷��̾��� �Ѿ˺��� ����
							break;
						}
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

				if (_puzzleTabButtonCollision[2])//3��° ž��ư�� �浹������
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP3->getFrameX() < buttonP3->getImage()->getMaxFrameX() - 1)//3��° ž��ư�� �浹������ x�������� ����� �����ǰ� �Ұ��� ������ ���ǹ�
						{
							buttonP3->setFrameX(buttonP3->getFrameX() + 1);//3��° ž��ư ������ ���
						}

						if (buttonP3->getFrameX() >= buttonP3->getImage()->getMaxFrameX() - 1)//3��° ž��ư�� �������� �������� ����������
						{
							_puzzleComplete[2] = true;
							_puzzleTabButtonCollision[2] = false;
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[3])//���� �����̳� ž��ư�� �浹������
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP4->getFrameX() < buttonP4->getImage()->getMaxFrameX() - 1)//���� �����̳� ž��ư�� �浹������ x�������� ����� �����ǰ� �Ұ��� ������ ���ǹ�
						{
							buttonP4->setFrameX(buttonP4->getFrameX() + 1);//���� �����̳� ž��ư ������ ���
						}

						if (buttonP4->getFrameX() >= buttonP4->getImage()->getMaxFrameX() - 1)//���� �����̳� ž��ư�� �������� �������� ����������
						{
							_puzzleComplete[3] = true;
							_puzzleTabButtonCollision[3] = false;
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[4])//�Ʒ��� �����̳� ž��ư�� �浹������
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP5->getFrameX() < buttonP5->getImage()->getMaxFrameX() - 1)//�Ʒ��� �����̳� ž��ư�� �浹������ x�������� ����� �����ǰ� �Ұ��� ������ ���ǹ�
						{
							buttonP5->setFrameX(buttonP5->getFrameX() + 1);//�Ʒ��� �����̳� ž��ư ������ ���
						}

						if (buttonP5->getFrameX() >= buttonP5->getImage()->getMaxFrameX() - 1)//�Ʒ��� �����̳� ž��ư�� �������� �������� ����������
						{
							_puzzleComplete[4] = true;
							_puzzleTabButtonCollision[4] = false;
						}
						_count = 0;
					}
				}

				if (_puzzleTabButtonCollision[5])//���ڿ� �ѷ����� ž��ư�� �浹������
				{
					_count++;
					if (_count % 15 == 0)
					{
						if (buttonP6->getFrameX() < buttonP6->getImage()->getMaxFrameX() - 1)//���ڿ� �ѷ����� ž��ư�� �浹������ x�������� ����� �����ǰ� �Ұ��� ������ ���ǹ�
						{
							buttonP6->setFrameX(buttonP6->getFrameX() + 1);//���ڿ� �ѷ����� ž��ư ������ ���
						}

						if (buttonP6->getFrameX() >= buttonP6->getImage()->getMaxFrameX() - 1)//���ڿ� �ѷ����� ž��ư�� �������� �������� ����������
						{
							_puzzleComplete[5] = true;
							_puzzleTabButtonCollision[5] = false;
						}
						_count = 0;
					}
				}


				//1��° ž��ư�� �浹ó�� �Ǽ� �������� ��������

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
								blueP->setRect(RectMakePivot(Vector2(blueP->getRect().getCenter().x, blueP->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//1��° ��纮�� ��Ʈũ��0���� ����
								_puzzleComplete[0] = true;
								_puzzleTabButtonCollision[0] = false;
							}
							_count = 0;
						}
					}
				}
				//���� �ڵ�� 1��° ž��ư�� �浹�Ǹ� 1��° ��纮�� �������� �����Ű�� ��Ʈ�� ���Ž�Ű�� ���� �ڵ�


				//2��° ž��ư�� �浹ó�� �Ǽ� �������� ��������

				if (_puzzleTabButtonCollision[1])//2��° ž��ư�� �浹������
				{
					if (buttonP2->getFrameX() >= buttonP2->getImage()->getMaxFrameX() - 1)//2��° ž��ư�� �������� �����ٸ�
					{
						_count++;
						if (_count % 15 == 0)
						{
							if (orangeP1->getFrameX() < orangeP1->getImage()->getMaxFrameX() - 1)//1��° �������� �������� �߽� �����Ӻ��� ������
							{
								orangeP1->setFrameX(orangeP1->getFrameX() + 1);//�������� ������ ����
							}

							if (orangeP1->getFrameX() >= orangeP1->getImage()->getMaxFrameX() - 1)//1��° ���������� �������� �������� �����ߴٸ�
							{
								orangeP1->setRect(RectMakePivot(Vector2(orangeP1->getRect().getCenter().x, orangeP1->getRect().getCenter().y), Vector2(0, 0), pivot::CENTER));//�������� ��Ʈũ�� 0���� ����
								_puzzleComplete[1] = true;
								_puzzleTabButtonCollision[1] = false;
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
	vector<gameObject*> destructTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "puzzleDestruct");

	for (int i = 0; i < destructTemp.size(); i++)
	{
		puzzleDestruct* d = dynamic_cast<puzzleDestruct*>(destructTemp[i]);

		if (d->getRect().getSize().x != 0 && d->getRect().getSize().y != 0)
		{
			if (isCollision(d->getRect(), _player->getPlayerAttackRect()))//���� �÷��̾��� �������� ��Ʈ�� �浹�ϸ�
			{
				if (!SOUNDMANAGER->isPlaySound("ore-destructible"))
				{
					SOUNDMANAGER->play("ore-destructible", 0.5f);
				}

				if (d->getHP() > 0)
				{
					d->setHP(_player->getPlayerAttackPower());//�÷��̾��� ���ݷ� ��ŭ ������ �ֱ�
				}
			}
		}


		for (int j = 0; j < _player->getBullet()->getVPlayerBullet().size(); j++)//�÷��̾��� �Ѿ˷�Ʈ ���ͻ����ŭ for��
		{
			if (d->getRect().getSize().x != 0 && d->getRect().getSize().y != 0)
			{
				if (isCollision(d->getRect(), _player->getBullet()->getVPlayerBullet()[j].rc))//���� �÷��̾��� �Ѿ˷�Ʈ�� �浹�ϸ�
				{
					if (!SOUNDMANAGER->isPlaySound("ore-destructible"))
					{
						SOUNDMANAGER->play("ore-destructible", 0.5f);
					}

					if (d->getHP() > 0)
					{
						d->setHP(50);//�÷��̾��� ���ݷ� ��ŭ ������ �ֱ�
						_player->getBullet()->remove(j);//�÷��̾��� �Ѿ� ���� ����
						break;
					}
				}
			}
		}


		//�� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�� �÷��̾ �о�� ���� �ڵ�
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
		//�� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�� �÷��̾ �о�� ���� �ڵ�
	}
}

void puzzleCollision::puzzleComplete()
{
	vector<gameObject*> footholdTemp = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "foothold");

	for (int i = 0; i < footholdTemp.size(); i++)
	{
		foothold* footholdP = dynamic_cast<foothold*>(footholdTemp[i]);

		if (_puzzleComplete[0] &&//��� ž��ư���� �浹�� ������ ������ ������� �����ٸ�
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
			footholdP->setIsOn(true);//���ǻ��°� Ʈ��
		}
	}
}
