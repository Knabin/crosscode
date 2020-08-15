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

	//���� bmp�̹��� ����

	IMAGEMANAGER->addImage("��������", "images/boss/center_body.bmp", 975, 675, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�������������", "images/boss/center_move.bmp", 14625, 675, 15, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��������", "images/boss/bottom.bmp", 492, 261, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ҹ�1", "images/boss/bottom_first.bmp", 1350, 69, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ҹ�2", "images/boss/bottom_second.bmp", 750, 69, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ҹ�3", "images/boss/bottom_third.bmp", 600, 69, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����", "images/boss/left_arm.bmp", 300, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޼�", "images/boss/left_hand.bmp", 450, 600, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�޼հ���", "images/boss/left_hand_attack.bmp", 21000, 450, 40, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������", "images/boss/right_arm.bmp", 300, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/boss/right_hand.bmp", 375, 480, true, RGB(255, 0, 255));

	//================================================================================================================================================================//

	//���� ���� ����

	_Center._x = WINSIZEX / 2 - 95;
	_Center._y = WINSIZEY / 2 + 150;
	_Center._angle = 0;

	_Center._center.x = WINSIZEX / 2 - 95;
	_Center._center.y = WINSIZEY / 2 + 150;
	_Center._centerMeter = 100;

	_Center._speed = 2.0f;

	_Center._rectBody.set(_Center._x + 210, _Center._y + 200, 615, 400);

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

	_LeftArm._rectBody.set(_LeftArm._center.x, _LeftArm._center.y, 10, 10);

	//================================================================================================================================================================//

	//�޼� ����

	_LeftHand._x = _LeftArm._x - 100;
	_LeftHand._y = _LeftArm._y + 100;
	_LeftHand._angle = 0;

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;
	_LeftHand._centerMeter = 150;


	//�޼� ���� ��Ʈ ����

	_LeftHand._rectBody.set(_LeftHand._center.x, _LeftHand._center.y, 10, 10);

	//================================================================================================================================================================//

	//������ ����

	_RightArm._x = _Center._x + 395;
	_RightArm._y = _Center._y + 275;
	_RightArm._angle = 0;

	_RightArm._center.x = _Center._x + 395;
	_RightArm._center.y = _Center._y + 275;
	_RightArm._centerMeter = 270;


	//������ ���� ��Ʈ ����

	_RightArm._rectBody.set(_RightArm._center.x, _RightArm._center.y, 10, 10);

	//================================================================================================================================================================//

	//������ ����

	_RightHand._x = _RightArm._x + 100;
	_RightHand._y = _RightArm._y + 100;
	_RightHand._angle = 0;

	_RightHand._center.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightHand._center.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;
	_RightHand._centerMeter = 150;


	//������ ���� ��Ʈ ����
	_RightHand._rectBody.set(_RightHand._center.x + 200, _RightHand._center.y + 200, 10, 10);

	//================================================================================================================================================================//

	//���� ����

	_Bottom._x = _Center._x + 162;
	_Bottom._y = _Center._y + 450;

	_Bottom._rectBody.set(_Bottom._x + 50, _Bottom._y, 150, 80);

	//================================================================================================================================================================//


	return S_OK;
}

void boss::release()
{

	ReleaseDC(_hWnd, getMemDC());
}

void boss::update()
{


	 

	
	_Center._rectBody.set(_Center._x + 210, _Center._y + 200, 615, 400);

	_Center._centerEnd.x = cosf(_Center._angle) * _Center._centerMeter + _Center._center.x;
	_Center._centerEnd.y = -sinf(_Center._angle) * _Center._centerMeter + _Center._center.y;

	_Bottom._rectBody.set(_Bottom._x + 50, _Bottom._y, 150, 80);
	
	IMAGEMANAGER->findImage("�������ҹ�1")->setFrameY(0);

	if (_protectFrameCount % 5 == 0)
	{
		if (_protectCurrentFrameX > IMAGEMANAGER->findImage("�������ҹ�1")->getMaxFrameX()) _protectCurrentFrameX = 0;
		IMAGEMANAGER->findImage("�������ҹ�1")->setFrameX(_protectCurrentFrameX);
		_protectCurrentFrameX++;
		_protectFrameCount = 0;
	}
	

	//================================================================================================================================================================//

	
	//����, �޼� �ǽð� ������Ʈ

	_LeftArm._rectBody.set(_LeftArm._center.x, _LeftArm._center.y, 10, 10);
	_LeftHand._rectBody.set(_LeftHand._center.x, _LeftHand._center.y, 10, 10);

	_LeftArm._centerEnd.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftArm._centerEnd.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._centerEnd.x = sinf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.x;
	_LeftHand._centerEnd.y = cosf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.y;

	//================================================================================================================================================================//

	//������, ������ �ǽð� ������Ʈ

	_RightArm._rectBody.set(_RightArm._center.x, _RightArm._center.y, 10, 10);
	_RightHand._rectBody.set(_RightHand._center.x , _RightHand._center.y , 10, 10);

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


}

void boss::bossDraw()
{

	IMAGEMANAGER->findImage("��������")->render(getMemDC(), _Bottom._rectBody.left - 173, _Bottom._rectBody.top - 50);

	IMAGEMANAGER->findImage("�������ҹ�1")->frameRender(getMemDC(), _Bottom._rectBody.left, _Bottom._rectBody.top + 35);

	//IMAGEMANAGER->findImage("����")->rotateRender(getMemDC(), _LeftHand._rectBody.left + 100, _LeftHand._rectBody.top - 75, _LeftArm._angle);
	//IMAGEMANAGER->findImage("������")->rotateRender(getMemDC(), _RightHand._rectBody.left - 100, _RightHand._rectBody.top - 75, _RightArm._angle);


	if (_bossState == CENTER_ATTACK_READY || _bossState == CENTER_ATTACK || _bossState == CENTER_ATTACK_END)
	{
		IMAGEMANAGER->findImage("�������������")->frameRender(getMemDC(), _Center._x - 200, _Center._y - 75);
	}

	//IMAGEMANAGER->findImage("��������")->rotateRender(getMemDC(), _Center._x + 210, _Center._y + 140, _Center._angle);
	

	//_Bottom._rectBody.render(getMemDC());





}

