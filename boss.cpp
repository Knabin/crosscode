#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init()
{

	_currentFrameX, _currentFrameY, _frameCount = 0;
	_protectCurrentFrameX, _protectCurrentFrameY, _protectFrameCount = 0;
	_moveCount = 0;
	_motionDelay = 0;
	_icethrowerDelay = 0;
	_mineAttackCount = 0;

	//================================================================================================================================================================//

	//���� png�̹��� ����

	IMAGEMANAGER->addImage("��������", L"images/boss/center_body.png");

	IMAGEMANAGER->addFrameImage("�������������", L"images/boss/center_move.png", 15, 1);

	IMAGEMANAGER->addImage("��������", L"images/boss/bottom.png");
	IMAGEMANAGER->addFrameImage("�������ҹ�1", L"images/boss/bottom_first.png", 9, 1);
	IMAGEMANAGER->addFrameImage("�������ҹ�2", L"images/boss/bottom_second.png", 5, 1);
	IMAGEMANAGER->addFrameImage("�������ҹ�3", L"images/boss/bottom_third.png", 4, 1);

	IMAGEMANAGER->addImage("����", L"images/boss/left_arm.png");
	IMAGEMANAGER->addImage("�޼�", L"images/boss/left_hand.png");

	IMAGEMANAGER->addFrameImage("�޼հ���", L"images/boss/left_hand_attack.png", 20, 2);

	IMAGEMANAGER->addImage("������", L"images/boss/right_arm.png");
	IMAGEMANAGER->addImage("������", L"images/boss/right_hand.png");

	//================================================================================================================================================================//

	//���� ���� ����
	_Center._x = (WINSIZEX / 2 - 85);
	_Center._y = (WINSIZEY / 2 - 175);
	_Center._angle = 0;

	_Center._center.x = (WINSIZEX / 2 - 85);
	_Center._center.y = (WINSIZEY / 2 - 175);
	_Center._centerMeter = 100;

	_Center._speed = 2.0f;

	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(600, 400), pivot::CENTER);

	//_bossState = APPEARANCE;
	//_bossState = STOP;
	_bossState = ICETHROWER_READY1;
	//_bossState = MINE_READY;

	//================================================================================================================================================================//

	//���� ����

	_LeftArm._x = (_Center._x - 125) + 100;
	_LeftArm._y = (_Center._y + 25);
	_LeftArm._angle = PI2 - (PI / 4);
	_LeftArm._realAngle = PI2 - (PI / 4);

	_LeftArm._center.x = (_Center._x - 125) + 100;
	_LeftArm._center.y = (_Center._y + 25);
	_LeftArm._centerMeter = 170;


	//���� ���� ��Ʈ ����

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//�޼� ����

	_LeftHand._x = _LeftArm._x - 100;
	_LeftHand._y = _LeftArm._y + 100;
	_LeftHand._angle = PI2 - (PI / 4);
	_LeftHand._realAngle = PI2 - (PI / 4);

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;
	_LeftHand._centerMeter = 170;


	//�޼� ���� ��Ʈ ����

	_LeftHand._rectBody.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//������ ����

	_RightArm._x = (_Center._x + 545) - 100;
	_RightArm._y = (_Center._y + 25);
	_RightArm._angle = PI2 - (PI / 4);
	_RightArm._realAngle = PI2 - (PI / 4);

	_RightArm._center.x = (_Center._x + 545) - 100;
	_RightArm._center.y = (_Center._y + 25);
	_RightArm._centerMeter = 170;


	//������ ���� ��Ʈ ����

	_RightArm._rectBody.update(Vector2(_RightArm._center.x, _RightArm._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//������ ����

	_RightHand._x = _RightArm._x + 100;
	_RightHand._y = _RightArm._y + 100;
	_RightHand._angle = PI2 - (PI / 4);
	_RightHand._realAngle = PI2 - (PI / 4);

	_RightHand._center.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightHand._center.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;
	_RightHand._centerMeter = 170;


	//������ ���� ��Ʈ ����
	_RightHand._rectBody.update(Vector2(_RightHand._center.x, _RightHand._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//���� ����

	_Bottom._x = _Center._x + 160;
	_Bottom._y = _Center._y + 450;

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 70), pivot::CENTER);

	//================================================================================================================================================================//

	_icethrower = new icethrower;
	_icethrower->init(_Center._x, _Center._y + 650);

	_mine = new mine;
	_mine->init(_Center._x + 115 , _Center._y + 50);



	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	_icethrower->update();

	_mine->update();

	_frameCount++;

	_protectFrameCount++;

	bossMove();

	bossState();

	fireCollision();

	//================================================================================================================================================================//

	_icethrower->update();

	_mine->update();

}

void boss::render()
{

	_icethrower->render();

	//================================================================================================================================================================//

	bossDraw();

	_mine->render(_Center._x + 115, _Center._y + 50);

}

void boss::bossState()
{
	//��� �ൿ ������ 
	//������ ��� ��Ʈ ������ 
	//��� ������ �������� �� �ߵ��մϴ�.

	switch (_bossState)
	{
		/*
	case APPEARANCE:
	{
		_appearanceCount++;

		//BossDownMove2();

		if (_appearanceCount < 10)
		{
			//test1();

			_Center._angle += 0.003f;

		}
		if (_appearanceCount >= 10)
		{
			//test2();

			_Center._angle -= 0.003f;

		}

		if (_appearanceCount >= 29)
		{
			//test3();

			_Center._angle += 0.003f * 2;

		}
		if (_appearanceCount >= 38)
		{
			_appearanceCount = 0;
		}

		if (WINSIZEY / 2 - 600 < _Center._y)
		{

			_bossState = LEFTHAND_ATTACK_READY;
		}

	}
	break;
	*/

	case MOVEUP:
	case MOVEDOWN:
	case STOP:
	{


	}
	break;

	//�޼� ���������� �߻� ���


	case ICETHROWER_READY1:
	{

		_RightArm._angle -= 0.012f;
		_RightHand._angle -= 0.012f;
		_RightArm._realAngle += 0.6f;
		_RightHand._realAngle += 1.2f;

		_LeftArm._angle -= 0.024f;
		_LeftHand._angle -= 0.032f;
		_LeftArm._realAngle += 1.2f;
		_LeftHand._realAngle += 0.8f;


		_Center._angle += 0.2f;

		if (_LeftHand._rectBody.top < _Center._y + 100)
		{
			_motionDelay++;

			if (_motionDelay < 20)
			{
				_RightArm._angle += 0.012f;
				_RightHand._angle += 0.012f;
				_RightArm._realAngle -= 0.6f;
				_RightHand._realAngle -= 1.2f;

				_LeftArm._angle += 0.024f;
				_LeftHand._angle += 0.032f;
				_LeftArm._realAngle -= 1.2f;
				_LeftHand._realAngle -= 0.8f;

				_Center._angle -= 0.2f;
			}

			if (_motionDelay >= 20)
			{
				_motionDelay = 0;
				_bossState = ICETHROWER_READY2;
			}
		}
	}
	break;

	case ICETHROWER_READY2:
	{
		_LeftArm._center.x += 1.5f;
		_LeftArm._center.y += 2.0f;


		_RightArm._angle += 0.012f;
		_RightHand._angle += 0.012f;
		_RightArm._realAngle -= 0.6f;
		_RightHand._realAngle -= 1.2f;


		_LeftArm._angle += 0.024f;
		_LeftHand._angle += 0.032f;
		_LeftArm._realAngle -= 1.2f;
		_LeftHand._realAngle -= 0.8f;


		_Center._angle -= 0.2f;

		if (_RightHand._rectBody.top < _Center._y + 50)
		{
			_bossState = ICETHROWER;
		}

	}
	break;

	case ICETHROWER:
	{
		_icethrowerDelay++;

		if (_icethrowerDelay % 5 == 0)
		{
			_icethrower->fire();

		}
		

		if (_frameCount % 3 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("�޼հ���")->getMaxFrameX())
			{
				_currentFrameX = 0;
				_currentFrameY++;
			}
			if (_currentFrameY >= IMAGEMANAGER->findImage("�޼հ���")->getMaxFrameY())
			{
				_currentFrameY = 0;
				_bossState = ICETHROWER_END;
			}
			_bossLeftHandAttackFrameX = _currentFrameX;
			_bossLeftHandAttackFrameY = _currentFrameY;
			_currentFrameX++;
			_frameCount = 0;
		}		
	}
	break;

	case ICETHROWER_END:
	{
		_icethrowerDelay = 0;

		_LeftArm._center.x -= 1.5f;
		_LeftArm._center.y -= 2.0f;


		_RightArm._angle -= 0.012f;
		_RightHand._angle -= 0.012f;
		_RightArm._realAngle += 0.6f;
		_RightHand._realAngle += 1.2f;


		_LeftArm._angle -= 0.016f;
		_LeftHand._angle -= 0.024f;
		_LeftArm._realAngle += 0.8f;
		_LeftHand._realAngle += 0.6f;

		_Center._angle += 0.15f;

		if (_RightHand._rectBody.top >= _LeftHand._rectBody.top - 22)
		{
			_bossState = MINE_READY;
		}
		
	}
	break;


	//���� ���� ��ô ���


	case MINE_READY:
	{		
		moveUp();

		if (_moveCount >= 64 || _Center._y < WINSIZEY / 2 - 275)
		{			
			_moveCount = 0;
			_bossState = MINE_READY2;
		}
		
	}
	break;

	case MINE_READY2:
	{

		_LeftArm._angle -= 0.01f ;
		_RightArm._angle += 0.01f ;
		_LeftHand._angle -= 0.025f ;
		_RightHand._angle += 0.025f ;
		_LeftArm._realAngle += 0.6f ;
		_RightArm._realAngle -= 0.6f ;
		_LeftHand._realAngle += 1.5f;
		_RightHand._realAngle -= 1.5f;

		if (_LeftHand._rectBody.left < WINSIZEX / 2 - 280)
		{
			_bossState = MINE;
		}

	}
	break;


	case MINE:
	{
		
		_bossCenterMoveFrameY = 0;

		
		if (_frameCount % 9 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("�������������")->getMaxFrameX())
			{
				_currentFrameX = 0;
				_bossState = MINE_END;
			}

			if (_currentFrameX >= 7)
			{
				_mineAttackCount++;
				if (_mineAttackCount % 2 == 0)
				{
					_mine->fire();
				}
			}
			_bossCenterMoveFrameX = _currentFrameX;
			_currentFrameX++;
			_frameCount = 0;

		}
		
	}
	break;

	case MINE_END:
	{

		_LeftArm._angle += 0.01f;
		_RightArm._angle -= 0.01f;
		_LeftHand._angle += 0.025f;
		_RightHand._angle -= 0.025f;
		_LeftArm._realAngle -= 0.6f;
		_RightArm._realAngle += 0.6f;
		_LeftHand._realAngle -= 1.5f;
		_RightHand._realAngle += 1.5f;

		if (_LeftHand._rectBody.left > WINSIZEX / 2 - 265)
		{
			_bossState = MINE_END2;
		}

	}
	break;


	case MINE_END2:
	{
		moveDown();

		if (_moveCount >= 64 || _Center._y > WINSIZEY / 2 - 175)
		{
			_moveCount = 0;
			_bossState = STOP;
		}

	}
	break;

	}
}

void boss::bossMove()
{

	//================================================================================================================================================================//

	//����, ���� �ǽð� ������Ʈ

	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(600, 400), pivot::CENTER);

	_Center._centerEnd.x = cosf(_Center._angle) * _Center._centerMeter + _Center._center.x;
	_Center._centerEnd.y = -sinf(_Center._angle) * _Center._centerMeter + _Center._center.y;

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 70), pivot::CENTER);

	//���� �� ������

	_bossShieldOneFrameY = 0;

	if (_protectFrameCount % 5 == 0)
	{
		if (_protectCurrentFrameX >= IMAGEMANAGER->findImage("�������ҹ�1")->getMaxFrameX())
		{
			_protectCurrentFrameX = 0;
		}
		_bossShieldOneFrameX = _protectCurrentFrameX;
		_protectCurrentFrameX++;
		_protectFrameCount = 0;
	}

	//================================================================================================================================================================//


	//����, �޼� �ǽð� ������Ʈ

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(50, 50), pivot::CENTER);
	_LeftHand._rectBody.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(50, 50), pivot::CENTER);

	_LeftArm._centerEnd.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftArm._centerEnd.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._centerEnd.x = sinf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.x;
	_LeftHand._centerEnd.y = cosf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.y;

	//================================================================================================================================================================//

	//������, ������ �ǽð� ������Ʈ

	_RightArm._rectBody.update(Vector2(_RightArm._center.x, _RightArm._center.y), Vector2(50, 50), pivot::CENTER);
	_RightHand._rectBody.update(Vector2(_RightHand._center.x, _RightHand._center.y), Vector2(50, 50), pivot::CENTER);

	_RightHand._center.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightHand._center.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;

	_RightArm._centerEnd.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightArm._centerEnd.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;

	_RightHand._centerEnd.x = cosf(_RightHand._angle) * _RightHand._centerMeter + _RightArm._centerEnd.x;
	_RightHand._centerEnd.y = -sinf(_RightHand._angle) * _RightHand._centerMeter + _RightArm._centerEnd.y;
}

void boss::bossDraw()
{
	// ~~~~���� �ּ�~~~~ �а� ���� �ʿ� ������ ���켼��
	// ���� ����!!! left���� ���̳ʽ��ϴ� ������ � ���� �𸣰ھ ���ͷ� ���� �� �� �����
	// ������ �����ϴ� �Ŷ�� floatRect�� getCenter()�� �����ϱ� �ٶ�!
	// ex) �̹���->render(CAMERA->getRelativeVector2(_Bottom._rectBody.getCenter()));

	//���� �����̴� ���Ȱ� ����� ���� x,y �� �������� ����
	//�� �ܴ� rect left,top�� ������ �߽��ϴ�.


	//����
	IMAGEMANAGER->findImage("��������")->render(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left - 175, _Bottom._rectBody.top - 60)));

	IMAGEMANAGER->findImage("�������ҹ�1")->frameRender(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left + 75, _Bottom._rectBody.top + 60)),
		_bossShieldOneFrameX, _bossShieldOneFrameY);


	//����
	IMAGEMANAGER->findImage("����")->setAngle(_LeftArm._realAngle);
	IMAGEMANAGER->findImage("����")->render(CAMERA->getRelativeVector2(Vector2(_LeftArm._centerEnd.x - 225, _LeftArm._centerEnd.y - 75)));
	IMAGEMANAGER->findImage("������")->setAngle(_RightArm._realAngle);
	IMAGEMANAGER->findImage("������")->render(CAMERA->getRelativeVector2(Vector2(_RightArm._centerEnd.x - 100, _RightArm._centerEnd.y - 75)));


	//����
	if (_bossState == MINE)
	{
		IMAGEMANAGER->findImage("�������������")->frameRender(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left + 296, _Center._rectBody.top + 144)),
			_bossCenterMoveFrameX, _bossCenterMoveFrameY);
	}
	else
	{
		IMAGEMANAGER->findImage("��������")->setAngle(_Center._angle);
		IMAGEMANAGER->findImage("��������")->render(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left - 191, _Center._rectBody.top - 193)));
	}
	

	//������
	IMAGEMANAGER->findImage("������")->setAngle(_RightHand._realAngle);
	IMAGEMANAGER->findImage("������")->render(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x - 200, _RightHand._centerEnd.y - 50)));


	//�޼�
	if (_bossState == ICETHROWER)
	{
		IMAGEMANAGER->findImage("�޼հ���")->frameRender(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 50, _LeftHand._centerEnd.y + 225)),
		_bossLeftHandAttackFrameX, _bossLeftHandAttackFrameY);
	}
	else
	{
		IMAGEMANAGER->findImage("�޼�")->setAngle(_LeftHand._realAngle);
		IMAGEMANAGER->findImage("�޼�")->render(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 250, _LeftHand._centerEnd.y - 100)));
	}

	//================================================================================================================================================================//

	//��ġ Ȯ�ο� ����, ���� ��Ʈ

	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_Center._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_Bottom._rectBody));

	//��ġ Ȯ�ο� ���, ���� ���� ��Ʈ

	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_LeftArm._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_RightArm._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_LeftHand._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_RightHand._rectBody));


	//��ġ Ȯ�ο� ���, ���� ����

	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_LeftArm._center.x, _LeftArm._center.y))),
		(CAMERA->getRelativeVector2(Vector2(_LeftArm._centerEnd.x, _LeftArm._centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);

	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_RightArm._center.x, _RightArm._center.y))),
		(CAMERA->getRelativeVector2(Vector2(_RightArm._centerEnd.x, _RightArm._centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);

	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_LeftHand._center.x, _LeftHand._center.y))),
		(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x, _LeftHand._centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);

	D2DRENDERER->DrawLine((CAMERA->getRelativeVector2(Vector2(_RightHand._center.x, _RightHand._center.y))),
		(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x, _RightHand._centerEnd.y))),
		D2D1::ColorF::Black, 1, 2.0f);

}

void boss::moveUp()
{

	_moveCount++;

	_Center._y -= 2.0f;
	_LeftArm._center.y -= 2.0f;
	_LeftHand._center.y -= 2.0f;
	_RightArm._center.y -= 2.0f;
	_RightHand._center.y -= 2.0f;
	_Bottom._y -= 2.0f;

	if (_moveCount < 17)
	{	
		_LeftArm._angle += 0.01f / 10;
		_LeftHand._angle += 0.001f / 10;
		_RightArm._angle += 0.01f / 10;
		_RightHand._angle += 0.001f / 10;
		_LeftArm._center.x += 0.5f;
		_LeftArm._center.y += 1.0f;
		_RightArm._center.x -= 0.5f;
		_RightArm._center.y -= 1.0f;
		_Center._angle -= 0.1f;
	}

	
	if (_moveCount >= 17 && _moveCount < 48)
	{
		_LeftArm._angle -= 0.01f / 10;
		_LeftHand._angle -= 0.001f / 10;
		_RightArm._angle -= 0.01f / 10;
		_RightHand._angle -= 0.001f / 10;
		_LeftArm._center.x -= 0.5f;
		_LeftArm._center.y -= 1.0f;
		_RightArm._center.x += 0.5f;
		_RightArm._center.y += 1.0f;
		_Center._angle += 0.1f;

	}
	
	if (_moveCount >= 48 && _moveCount < 64)
	{
		_LeftArm._angle += 0.01f / 10;
		_LeftHand._angle += 0.001f / 10;
		_RightArm._angle += 0.01f / 10;
		_RightHand._angle += 0.001f / 10;
		_LeftArm._center.x += 0.5f;
		_LeftArm._center.y += 1.0f;
		_RightArm._center.x -= 0.5f;
		_RightArm._center.y -= 1.0f;
		_Center._angle -= 0.1f;
	}
	
	if (_moveCount >= 64)
	{
		_moveCount = 0;

	}
	
}

void boss::moveDown()
{
	_moveCount++;

	_Center._y += 2.0f;
	_LeftArm._center.y += 2.0f;
	_LeftHand._center.y += 2.0f;
	_RightArm._center.y += 2.0f;
	_RightHand._center.y += 2.0f;
	_Bottom._y += 2.0f;

	if (_moveCount < 17)
	{
		_LeftArm._angle -= 0.01f / 10;
		_LeftHand._angle -= 0.001f / 10;
		_RightArm._angle -= 0.01f / 10;
		_RightHand._angle -= 0.001f / 10;
		_LeftArm._center.x -= 0.5f;
		_LeftArm._center.y -= 1.0f;
		_RightArm._center.x += 0.5f;
		_RightArm._center.y += 1.0f;
		_Center._angle += 0.1f;
	}


	if (_moveCount >= 17 && _moveCount < 48)
	{
		_LeftArm._angle += 0.01f / 10;
		_LeftHand._angle += 0.001f / 10;
		_RightArm._angle += 0.01f / 10;
		_RightHand._angle += 0.001f / 10;
		_LeftArm._center.x += 0.5f;
		_LeftArm._center.y += 1.0f;
		_RightArm._center.x -= 0.5f;
		_RightArm._center.y -= 1.0f;
		_Center._angle -= 0.1f;

	}

	if (_moveCount >= 48 && _moveCount < 64)
	{
		_LeftArm._angle -= 0.01f / 10;
		_LeftHand._angle -= 0.001f / 10;
		_RightArm._angle -= 0.01f / 10;
		_RightHand._angle -= 0.001f / 10;
		_LeftArm._center.x -= 0.5f;
		_LeftArm._center.y -= 1.0f;
		_RightArm._center.x += 0.5f;
		_RightArm._center.y += 1.0f;
		_Center._angle += 0.1f;
	}

	if (_moveCount >= 64)
	{
		_moveCount = 0;

	}
}

void boss::fireCollision()
{

	for (int i = 0; i < _icethrower->getIcethrowerVector().size(); i++)
	{

		if (WINSIZEY + 1600 < _icethrower->getIcethrowerVector()[i]._rc.top)
		{
			_icethrower->removeFire(i);
			break;
		}

	}

}



