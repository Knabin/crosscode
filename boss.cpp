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
	_appearanceCount = 0;
	_attackCount = 0;
	_attackEndCount = 0;
	_fireskill1Time = 0;
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

	//IMAGEMANAGER->addFrameImage("�޼հ���", L"images/boss/left_hand_attack.png", 39, 1);

	IMAGEMANAGER->addImage("������", L"images/boss/right_arm.png");
	IMAGEMANAGER->addImage("������", L"images/boss/right_hand.png");

	//================================================================================================================================================================//

	//���� ���� ����

	_Center._x = WINSIZEX / 2 - 95;
	_Center._y = WINSIZEY / 2 + 150;
	_Center._angle = 0;

	_Center._center.x = WINSIZEX / 2 - 95;
	_Center._center.y = WINSIZEY / 2 + 150;
	_Center._centerMeter = 100;

	_Center._speed = 2.0f;

	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(615, 400), pivot::CENTER);

	//_bossState = APPEARANCE;
	_bossState = STOP;
	//_bossState = LEFTHAND_ATTACK_READY;
	//_bossState = CENTER_ATTACK_READY;

	//================================================================================================================================================================//

	//���� ����

	_LeftArm._x = _Center._x - 245;
	_LeftArm._y = _Center._y + 5;
	_LeftArm._angle = 0;

	_LeftArm._center.x = _Center._x - 245;
	_LeftArm._center.y = _Center._y + 5;
	_LeftArm._centerMeter = 270;


	//���� ���� ��Ʈ ����

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(10, 10), pivot::CENTER);

	//================================================================================================================================================================//

	//�޼� ����

	_LeftHand._x = _LeftArm._x - 100;
	_LeftHand._y = _LeftArm._y + 100;
	_LeftHand._angle = 0;

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;
	_LeftHand._centerMeter = 150;


	//�޼� ���� ��Ʈ ����

	_LeftHand._rectBody.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(10, 10), pivot::CENTER);

	//================================================================================================================================================================//

	//������ ����

	_RightArm._x = _Center._x + 395;
	_RightArm._y = _Center._y + 275;
	_RightArm._angle = 0;

	_RightArm._center.x = _Center._x + 395;
	_RightArm._center.y = _Center._y + 275;
	_RightArm._centerMeter = 270;


	//������ ���� ��Ʈ ����

	_RightArm._rectBody.update(Vector2(_RightArm._center.x, _RightArm._center.y), Vector2(10, 10), pivot::CENTER);

	//================================================================================================================================================================//

	//������ ����

	_RightHand._x = _RightArm._x + 100;
	_RightHand._y = _RightArm._y + 100;
	_RightHand._angle = 0;

	_RightHand._center.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightHand._center.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;
	_RightHand._centerMeter = 150;


	//������ ���� ��Ʈ ����
	_RightHand._rectBody.update(Vector2(_RightHand._center.x + 200, _RightHand._center.y + 200), Vector2(10, 10), pivot::CENTER);

	//================================================================================================================================================================//

	//���� ����

	_Bottom._x = _Center._x + 162;
	_Bottom._y = _Center._y + 450;

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 80), pivot::CENTER);

	//================================================================================================================================================================//


	return S_OK;
}

void boss::release()
{
}

void boss::update()
{

	//================================================================================================================================================================//

	
	//����, ���� �ǽð� ������Ʈ

	
	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(615, 400), pivot::CENTER);

	_Center._centerEnd.x = cosf(_Center._angle) * _Center._centerMeter + _Center._center.x;
	_Center._centerEnd.y = -sinf(_Center._angle) * _Center._centerMeter + _Center._center.y;

	_Center._angle += 0.02f;

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 80), pivot::CENTER);

	_bossShieldOneFrameY = 0;

	if (_protectFrameCount % 5 == 0)
	{
		if (_protectCurrentFrameX >= IMAGEMANAGER->findImage("�������ҹ�1")->getMaxFrameX()) _protectCurrentFrameX = 0;
		_bossShieldOneFrameX = _protectCurrentFrameX;
		_protectCurrentFrameX++;
		_protectFrameCount = 0;
	}
	

	//================================================================================================================================================================//

	
	//����, �޼� �ǽð� ������Ʈ

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(10, 10), pivot::CENTER);
	_LeftHand._rectBody.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(10, 10), pivot::CENTER);

	_LeftArm._centerEnd.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftArm._centerEnd.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._centerEnd.x = sinf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.x;
	_LeftHand._centerEnd.y = cosf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.y;

	//================================================================================================================================================================//

	//������, ������ �ǽð� ������Ʈ

	_RightArm._rectBody.update(Vector2(_RightArm._center.x, _RightArm._center.y), Vector2(10, 10), pivot::CENTER);
	_RightHand._rectBody.update(Vector2(_RightHand._center.x + 200, _RightHand._center.y + 200), Vector2(10, 10), pivot::CENTER);

	_RightHand._center.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightHand._center.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;

	_RightArm._centerEnd.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightArm._centerEnd.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;

	_RightHand._centerEnd.x = cosf(_RightHand._angle) * _RightHand._centerMeter + _RightArm._centerEnd.x;
	_RightHand._centerEnd.y = -sinf(_RightHand._angle) * _RightHand._centerMeter + _RightArm._centerEnd.y;

	//================================================================================================================================================================//
	
	_frameCount++;
	_protectFrameCount++;
	_fireskill1Time++;
	//BossMove();
	  bossState();
	//================================================================================================================================================================//

	  
	//collision();

	 

}

void boss::render()
{

	bossDraw();

	
	/*
	_LeftArm._rectBody.render(getMemDC());

	_LeftHand._rectBody.render(getMemDC());

	_RightArm._rectBody.render(getMemDC());

	_RightHand._rectBody.render(getMemDC());

	LineMake(getMemDC(), _LeftArm._center.x, _LeftArm._center.y, _LeftArm._centerEnd.x, _LeftArm._centerEnd.y);

	LineMake(getMemDC(), _LeftHand._center.x, _LeftHand._center.y, _LeftHand._centerEnd.x, _LeftHand._centerEnd.y);

	LineMake(getMemDC(), _RightArm._center.x, _RightArm._center.y, _RightArm._centerEnd.x, _RightArm._centerEnd.y);

	LineMake(getMemDC(), _RightHand._center.x, _RightHand._center.y, _RightHand._centerEnd.x, _RightHand._centerEnd.y);
	*/
}

void boss::bossState()
{
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


	case LEFTHAND_ATTACK_READY:
	{
		_appearanceCount = 0;
		_attackCount++;
		_attackEndCount = 0;

		if (_attackCount < 50)
		{
			_RightArm._angle += 0.002f;
			_RightHand._angle += 0.002f;
			_LeftArm._angle += 0.002f * 2;
			_LeftHand._angle += 0.002f * 2;
			_Center._angle += 0.001f;

			_RightArm._center.x -= 0.5f;
			_RightArm._center.y -= 0.5f;

			_LeftArm._center.x += 0.5f;
			_LeftArm._center.y += 0.5f;
		}

		if (_attackCount >= 50)
		{

			_LeftArm._angle += 0.002f * 2;
			_LeftHand._angle += 0.002f * 2;
			_RightArm._angle += 0.002f;
			_RightHand._angle += 0.002f;
			_Center._angle += 0.001f;

			_LeftArm._center.y += 0.5f;
			_LeftArm._center.x -= 0.5f;
		}

		if (_attackCount >= 75)
		{
			_attackCount = 0;
			_bossState = LEFTHAND_ATTACK;
		}

	}
	break;

	case LEFTHAND_ATTACK:
	{
		_attackCount = 0;

		/*
		if (_fireskill1Time % 3 == 0)
		{
			_BossAttack->attackFire();

		}
		*/

		/*
		IMAGEMANAGER->findImage("�޼հ���")->setFrameY(0);

		if (_frameCount % 2 == 0)
		{
			if (_currentFrameX > IMAGEMANAGER->findImage("�޼հ���")->getMaxFrameX())
			{
				_bossState = LEFTHAND_ATTACK_END;
			}
			IMAGEMANAGER->findImage("�޼հ���")->setFrameX(_currentFrameX);
			_currentFrameX++;
			_frameCount = 0;
		}
		*/

	}
	break;

	case LEFTHAND_ATTACK_END:
	{

		_currentFrameX = 0;
		_attackEndCount++;

		if (_attackEndCount < 5)
		{
			_LeftArm._angle -= 0.02f * 2;
			_LeftHand._angle -= 0.02f * 2;
			_RightArm._angle -= 0.02f;
			_RightHand._angle -= 0.02f;
			_Center._angle -= 0.01f;

			_LeftArm._center.y -= 2;
			_LeftArm._center.x += 2;
		}

		if (_attackEndCount >= 5)
		{
			_RightArm._angle -= 0.02f;
			_RightHand._angle -= 0.02f;
			_LeftArm._angle -= 0.02f * 2;
			_LeftHand._angle -= 0.02f * 2;
			_Center._angle -= 0.01f;

			_RightArm._center.x += 2;
			_RightArm._center.y += 2;

			_LeftArm._center.x -= 2;
			_LeftArm._center.y -= 2;

		}

		if (_attackEndCount >= 15)
		{
			_attackEndCount = 0;
			_bossState = STOP;

		}

	}
	break;


	//���� ���� ��ô ���

	case CENTER_ATTACK_READY:
	{

		_LeftArm._angle += 0.005f * 6;
		_RightArm._angle -= 0.005f * 6;
		_LeftHand._angle += 0.015f * 6;
		_RightHand._angle -= 0.015f * 6;

		if (_LeftHand._rectBody.right > WINSIZEX / 2 - 450)
		{

			_bossState = CENTER_ATTACK;
		}

		/*
		IMAGEMANAGER->findImage("�������������")->setFrameY(0);

		if (_frameCount % 4 == 0)
		{
			if (_currentFrameX > IMAGEMANAGER->findImage("�������������")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			IMAGEMANAGER->findImage("�������������")->setFrameX(_currentFrameX);
			_currentFrameX++;
			_frameCount = 0;

		}
		*/
	}
	break;

	case CENTER_ATTACK:
	{
		/*
		IMAGEMANAGER->findImage("�������������")->setFrameY(0);

		if (_frameCount % 4 == 0)
		{
			if (_currentFrameX > IMAGEMANAGER->findImage("�������������")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			IMAGEMANAGER->findImage("�������������")->setFrameX(_currentFrameX);
			_currentFrameX++;
			_frameCount = 0;

		}
		*/

		_LeftHand._centerEnd.y -= 25;
		_RightHand._centerEnd.y -= 25;
		_Center._y += 0.5f;
		_LeftArm._angle -= 0.005f * 12;
		_RightArm._angle += 0.005f * 12;
		_LeftHand._angle -= 0.015f * 12;
		_RightHand._angle += 0.015f * 12;

		if (_LeftHand._rectBody.right < WINSIZEX / 2 - 625)
		{
			_bossState = CENTER_ATTACK_END;

		}
	}
	break;

	case CENTER_ATTACK_END:
	{
		_mineAttackCount++;

		_LeftHand._centerEnd.x -= 15;
		_RightHand._centerEnd.x += 15;
		_LeftHand._centerEnd.y += 15;
		_RightHand._centerEnd.y += 15;

		if (_mineAttackCount % 30 == 0)
		{
			//_Mine->MineFire();

		}
	}
	break;

	}
}

void boss::bossDraw()
{
	// ~~~~���� �ּ�~~~~ �а� ���� �ʿ� ������ ���켼��
	// ���� ����!!! left���� ���̳ʽ��ϴ� ������ � ���� �𸣰ھ ���ͷ� ���� �� �� �����
	// ������ �����ϴ� �Ŷ�� floatRect�� getCenter()�� �����ϱ� �ٶ�!
	// ex) �̹���->render(CAMERA->getRelativeVector2(_Bottom._rectBody.getCenter()));


	IMAGEMANAGER->findImage("��������")->render(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left - 173, _Bottom._rectBody.top - 50)));

	IMAGEMANAGER->findImage("�������ҹ�1")->frameRender(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left, _Bottom._rectBody.top + 35)), 
		_bossShieldOneFrameX, _bossShieldOneFrameY);

	//IMAGEMANAGER->findImage("����")->rotateRender(getMemDC(), _LeftHand._rectBody.left + 100, _LeftHand._rectBody.top - 75, _LeftArm._angle);
	//IMAGEMANAGER->findImage("������")->rotateRender(getMemDC(), _RightHand._rectBody.left - 100, _RightHand._rectBody.top - 75, _RightArm._angle);


	if (_bossState == CENTER_ATTACK_READY || _bossState == CENTER_ATTACK || _bossState == CENTER_ATTACK_END)
	{
		//IMAGEMANAGER->findImage("�������������")->frameRender(Vector2(_Center._x - 200, _Center._y - 75), );
	}

	IMAGEMANAGER->findImage("��������")->setAngle(_Center._angle);
	IMAGEMANAGER->findImage("��������")->render(CAMERA->getRelativeVector2(Vector2(_Center._x + 210, _Center._y + 140)));
	

	//_Bottom._rectBody.render(getMemDC());

	/*
	if (_Center._BossState == IDLE || _Center._BossState == APPEARANCE || _Center._BossState == MOVEDOWN || _Center._BossState == MOVEUP || _Center._BossState == LEFTHAND_ATTACK_END || _Center._BossState == LEFTHAND_ATTACK_READY)
	{
		_LeftHand._Image->RotateRender(getMemDC(), _LeftHand._centerEnd.x + 75, _LeftHand._centerEnd.y, _LeftHand._angle + 25);
	}
	*/
	//IMAGEMANAGER->findImage("�޼�")->rotateRender(getMemDC(), _LeftHand._centerEnd.x + 25, _LeftHand._centerEnd.y + 75, _LeftHand._angle);
//	IMAGEMANAGER->findImage("������")->rotateRender(getMemDC(), _RightHand._centerEnd.x - 175, _RightHand._centerEnd.y + 200, _RightHand._angle);

	if (_bossState == LEFTHAND_ATTACK)
	{
		//IMAGEMANAGER->findImage("�޼հ���")->frameRender(getMemDC(), _LeftHand._centerEnd.x - 175, _LeftHand._centerEnd.y - 200);
	}
	else
	{
		//_LeftHand._Image->RotateRender(getMemDC(), _LeftHand._centerEnd.x + 75, _LeftHand._centerEnd.y, _LeftHand._angle + 25);
	}



}

