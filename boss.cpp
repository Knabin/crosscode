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

	//보스 png이미지 선언

	IMAGEMANAGER->addImage("보스몸통", L"images/boss/center_body.png");

	IMAGEMANAGER->addFrameImage("보스몸통움직임", L"images/boss/center_move.png", 15, 1);

	IMAGEMANAGER->addImage("보스바텀", L"images/boss/bottom.png");
	IMAGEMANAGER->addFrameImage("보스바텀방어막1", L"images/boss/bottom_first.png", 9, 1);
	IMAGEMANAGER->addFrameImage("보스바텀방어막2", L"images/boss/bottom_second.png", 5, 1);
	IMAGEMANAGER->addFrameImage("보스바텀방어막3", L"images/boss/bottom_third.png", 4, 1);

	IMAGEMANAGER->addImage("왼팔", L"images/boss/left_arm.png");
	IMAGEMANAGER->addImage("왼손", L"images/boss/left_hand.png");

	//IMAGEMANAGER->addFrameImage("왼손공격", L"images/boss/left_hand_attack.png", 39, 1);

	IMAGEMANAGER->addImage("오른팔", L"images/boss/right_arm.png");
	IMAGEMANAGER->addImage("오른손", L"images/boss/right_hand.png");

	//================================================================================================================================================================//

	//보스 몸통 선언

	_Center._x = (WINSIZEX / 2 - 85);
	_Center._y = (WINSIZEY / 2 + 450);
	_Center._angle = 0;

	_Center._center.x = (WINSIZEX / 2 - 85);
	_Center._center.y = (WINSIZEY / 2 + 450);
	_Center._centerMeter = 100;

	_Center._speed = 2.0f;

	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(600, 400), pivot::CENTER);

	//_bossState = APPEARANCE;
	//_bossState = STOP;
	_bossState = LEFTHAND_ATTACK_READY;
	//_bossState = CENTER_ATTACK_READY;

	//================================================================================================================================================================//

	//왼팔 선언

	_LeftArm._x = (_Center._x - 125) + 100;
	_LeftArm._y = (_Center._y + 25);
	_LeftArm._angle = PI2 - (PI / 4);
	_LeftArm._realAngle = PI2 - (PI / 4);

	_LeftArm._center.x = (_Center._x - 125) + 100;
	_LeftArm._center.y = (_Center._y + 25);
	_LeftArm._centerMeter = 170;


	//왼팔 관절 렉트 선언

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//왼손 선언

	_LeftHand._x = _LeftArm._x - 100;
	_LeftHand._y = _LeftArm._y + 100;
	_LeftHand._angle = PI2 - (PI / 4);
	_LeftHand._realAngle = PI2 - (PI / 4);

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;
	_LeftHand._centerMeter = 170;


	//왼손 관절 렉트 선언

	_LeftHand._rectBody.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//오른팔 선언

	_RightArm._x = (_Center._x + 545) - 100;
	_RightArm._y = (_Center._y + 25);
	_RightArm._angle = PI2 - (PI / 4);
	_RightArm._realAngle = PI2 - (PI / 4);

	_RightArm._center.x = (_Center._x + 545) - 100;
	_RightArm._center.y = (_Center._y + 25);
	_RightArm._centerMeter = 170;


	//오른팔 관절 렉트 선언

	_RightArm._rectBody.update(Vector2(_RightArm._center.x, _RightArm._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//오른손 선언

	_RightHand._x = _RightArm._x + 100;
	_RightHand._y = _RightArm._y + 100;
	_RightHand._angle = PI2 - (PI / 4);
	_RightHand._realAngle = PI2 - (PI / 4);

	_RightHand._center.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightHand._center.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;
	_RightHand._centerMeter = 170;


	//오른손 관절 렉트 선언
	_RightHand._rectBody.update(Vector2(_RightHand._center.x, _RightHand._center.y), Vector2(50, 50), pivot::CENTER);

	//================================================================================================================================================================//

	//바텀 선언

	_Bottom._x = _Center._x + 160;
	_Bottom._y = _Center._y + 450;

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 70), pivot::CENTER);

	//================================================================================================================================================================//


	return S_OK;
}

void boss::release()
{
}

void boss::update()
{

	_frameCount++;

	_protectFrameCount++;

	_fireskill1Time++;

	bossMove();

	bossState();

}

void boss::render()
{

	bossDraw();

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

	//왼손 얼음포물선 발사 모션


	case LEFTHAND_ATTACK_READY:
	{
		_appearanceCount = 0;
		_attackCount++;
		_attackEndCount = 0;

		_LeftArm._angle -= 0.001f;
		_RightArm._angle += 0.001f;

		_LeftArm._realAngle += 0.05f;
		_RightArm._realAngle -= 0.05f;

		_LeftHand._angle -= 0.001f;
		_RightHand._angle += 0.001f;

		_LeftHand._realAngle += 0.05f;
		_RightHand._realAngle -= 0.05f;
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
		IMAGEMANAGER->findImage("왼손공격")->setFrameY(0);

		if (_frameCount % 2 == 0)
		{
			if (_currentFrameX > IMAGEMANAGER->findImage("왼손공격")->getMaxFrameX())
			{
				_bossState = LEFTHAND_ATTACK_END;
			}
			IMAGEMANAGER->findImage("왼손공격")->setFrameX(_currentFrameX);
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


	//몸통 지뢰 투척 모션

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
		IMAGEMANAGER->findImage("보스몸통움직임")->setFrameY(0);

		if (_frameCount % 4 == 0)
		{
			if (_currentFrameX > IMAGEMANAGER->findImage("보스몸통움직임")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			IMAGEMANAGER->findImage("보스몸통움직임")->setFrameX(_currentFrameX);
			_currentFrameX++;
			_frameCount = 0;

		}
		*/
	}
	break;

	case CENTER_ATTACK:
	{
		/*
		IMAGEMANAGER->findImage("보스몸통움직임")->setFrameY(0);

		if (_frameCount % 4 == 0)
		{
			if (_currentFrameX > IMAGEMANAGER->findImage("보스몸통움직임")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			IMAGEMANAGER->findImage("보스몸통움직임")->setFrameX(_currentFrameX);
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

void boss::bossMove()
{

	//================================================================================================================================================================//

	//몸통, 바텀 실시간 업데이트

	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(600, 400), pivot::CENTER);

	_Center._centerEnd.x = cosf(_Center._angle) * _Center._centerMeter + _Center._center.x;
	_Center._centerEnd.y = -sinf(_Center._angle) * _Center._centerMeter + _Center._center.y;

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 70), pivot::CENTER);

	//바텀 방어막 프레임

	_bossShieldOneFrameY = 0;

	if (_protectFrameCount % 5 == 0)
	{
		if (_protectCurrentFrameX >= IMAGEMANAGER->findImage("보스바텀방어막1")->getMaxFrameX()) _protectCurrentFrameX = 0;
		_bossShieldOneFrameX = _protectCurrentFrameX;
		_protectCurrentFrameX++;
		_protectFrameCount = 0;
	}

	//================================================================================================================================================================//


	//왼팔, 왼손 실시간 업데이트

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(50, 50), pivot::CENTER);
	_LeftHand._rectBody.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(50, 50), pivot::CENTER);

	_LeftArm._centerEnd.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftArm._centerEnd.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;

	_LeftHand._centerEnd.x = sinf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.x;
	_LeftHand._centerEnd.y = cosf(_LeftHand._angle) * _LeftHand._centerMeter + _LeftArm._centerEnd.y;

	//================================================================================================================================================================//

	//오른팔, 오른손 실시간 업데이트

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
	// ~~~~나빈 주석~~~~ 읽고 나서 필요 없으면 지우세용
	// 혜성 오빠!!! left에서 마이너스하는 기준이 어떤 건지 모르겠어서 센터로 수정 안 해 놨어용
	// 중점에 렌더하는 거라면 floatRect의 getCenter()에 렌더하길 바람!
	// ex) 이미지->render(CAMERA->getRelativeVector2(_Bottom._rectBody.getCenter()));

	//보스 모든 클래스 랜더는 floatRect의 left와, top을 중점렌더로 통일


	IMAGEMANAGER->findImage("보스바텀")->render(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left - 175, _Bottom._rectBody.top - 60)));

	IMAGEMANAGER->findImage("보스바텀방어막1")->frameRender(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left + 75, _Bottom._rectBody.top + 60)),
		_bossShieldOneFrameX, _bossShieldOneFrameY);


	IMAGEMANAGER->findImage("왼팔")->setAngle(_LeftArm._realAngle);
	IMAGEMANAGER->findImage("왼팔")->render(CAMERA->getRelativeVector2(Vector2(_LeftArm._centerEnd.x - 200, _LeftArm._centerEnd.y - 75)));
	IMAGEMANAGER->findImage("오른팔")->setAngle(_RightArm._realAngle);
	IMAGEMANAGER->findImage("오른팔")->render(CAMERA->getRelativeVector2(Vector2(_RightArm._centerEnd.x - 125, _RightArm._centerEnd.y - 75)));


	if (_bossState == CENTER_ATTACK_READY || _bossState == CENTER_ATTACK || _bossState == CENTER_ATTACK_END)
	{
		//IMAGEMANAGER->findImage("보스몸통움직임")->frameRender(Vector2(_Center._x - 200, _Center._y - 75), );
	}

	IMAGEMANAGER->findImage("보스몸통")->setAngle(_Center._angle);
	IMAGEMANAGER->findImage("보스몸통")->render(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left - 184, _Center._rectBody.top - 200)));


	/*
	if (_Center._BossState == IDLE || _Center._BossState == APPEARANCE || _Center._BossState == MOVEDOWN || _Center._BossState == MOVEUP || _Center._BossState == LEFTHAND_ATTACK_END || _Center._BossState == LEFTHAND_ATTACK_READY)
	{
		_LeftHand._Image->RotateRender(getMemDC(), _LeftHand._centerEnd.x + 75, _LeftHand._centerEnd.y, _LeftHand._angle + 25);
	}
	*/

	IMAGEMANAGER->findImage("왼손")->setAngle(_LeftHand._realAngle);
	IMAGEMANAGER->findImage("왼손")->render(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 250, _LeftHand._centerEnd.y - 75)));
	IMAGEMANAGER->findImage("오른손")->setAngle(_RightHand._realAngle);
	IMAGEMANAGER->findImage("오른손")->render(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x - 200, _RightHand._centerEnd.y - 50)));

	if (_bossState == LEFTHAND_ATTACK)
	{
		//IMAGEMANAGER->findImage("왼손공격")->frameRender(getMemDC(), _LeftHand._centerEnd.x - 175, _LeftHand._centerEnd.y - 200);
	}
	else
	{
		//_LeftHand._Image->RotateRender(getMemDC(), _LeftHand._centerEnd.x + 75, _LeftHand._centerEnd.y, _LeftHand._angle + 25);
	}




	//================================================================================================================================================================//

	//양손, 양팔 관절 렉트

	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_Center._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_Bottom._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_LeftArm._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_RightArm._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_LeftHand._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_RightHand._rectBody));


	//양손, 양팔 점선

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



