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
	// 기본 y축WINSIZEY / 2 - 175
	bossInitialization();

	//_bossState = APPEARANCE;
	//_bossState = STOP;
	//_bossState = ICETHROWER_READY;
	//_bossState = MINE_READY;
	_bossState = STONESHOWER_READY;

	_dustCurrentFrameX, _dustCurrentFrameY, _dustFrameCount = 0;

	_currentFrameX, _currentFrameY, _frameCount = 0;
	_protectCurrentFrameX, _protectCurrentFrameY, _protectFrameCount = 0;
	_moveCount = 0;
	_motionDelay = 0;
	_icethrowerDelay = 0;
	_randomAttackCount = 0;
	_mineAttackDelay = 0;
	_stoneAttackDelay = 0;

	//================================================================================================================================================================//

	//보스 png이미지 선언

	IMAGEMANAGER->addImage("보스몸통", L"images/boss/center_body.png");
	IMAGEMANAGER->addImage("보스몸통우", L"images/boss/center_right.png");
	IMAGEMANAGER->addImage("보스몸통좌", L"images/boss/center_left.png");
	IMAGEMANAGER->addImage("보스몸통하", L"images/boss/center_down.png");

	IMAGEMANAGER->addFrameImage("보스몸통움직임", L"images/boss/center_move.png", 15, 1);

	IMAGEMANAGER->addImage("보스바텀", L"images/boss/bottom.png");
	IMAGEMANAGER->addFrameImage("보스바텀방어막1", L"images/boss/bottom_first.png", 9, 1);
	IMAGEMANAGER->addFrameImage("보스바텀방어막2", L"images/boss/bottom_second.png", 5, 1);
	IMAGEMANAGER->addFrameImage("보스바텀방어막3", L"images/boss/bottom_third.png", 4, 1);

	IMAGEMANAGER->addImage("왼팔", L"images/boss/left_arm.png");
	IMAGEMANAGER->addImage("왼손", L"images/boss/left_hand.png");

	IMAGEMANAGER->addFrameImage("왼손공격", L"images/boss/left_hand_attack.png", 20, 2);

	IMAGEMANAGER->addImage("오른팔", L"images/boss/right_arm.png");
	IMAGEMANAGER->addImage("오른손", L"images/boss/right_hand.png");

	IMAGEMANAGER->addFrameImage("오른손공격", L"images/boss/right_hand_attack2.png", 8, 1);

	//================================================================================================================================================================//

	//몸통

	_Center._centerMeter = 100;

	_Center._speed = 2.0f;

	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(600, 400), pivot::CENTER);

	//왼팔

	_LeftArm._centerMeter = 170;

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(50, 50), pivot::CENTER);

	//왼팔

	_LeftHand._center.x = sinf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.x;
	_LeftHand._center.y = cosf(_LeftArm._angle) * _LeftArm._centerMeter + _LeftArm._center.y;
	_LeftHand._centerMeter = 170;

	_LeftHand._rectBody.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(50, 50), pivot::CENTER);

	//오른팔

	_RightArm._centerMeter = 170;

	_RightArm._rectBody.update(Vector2(_RightArm._center.x, _RightArm._center.y), Vector2(50, 50), pivot::CENTER);

	//오른손
	
	_RightHand._center.x = cosf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.x;
	_RightHand._center.y = -sinf(_RightArm._angle) * _RightArm._centerMeter + _RightArm._center.y;
	_RightHand._centerMeter = 170;

	_RightHand._rectBody.update(Vector2(_RightHand._center.x, _RightHand._center.y), Vector2(50, 50), pivot::CENTER);

	//바텀

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 70), pivot::CENTER);
	
	//================================================================================================================================================================//

	_icethrower = new icethrower;
	_icethrower->init(_Center._x, _Center._y + 650);

	_mine = new mine;
	_mine->init(_Center._x + 115 , _Center._y + 50);

	_stoneshower = new stoneshower;
	_stoneshower->init(_Center._x + 215, _Center._y - 999);

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

	_stoneshower->update();


}

void boss::render()
{

	_icethrower->render();

	//================================================================================================================================================================//

	bossDraw();

	_mine->render(_Center._x + 115, _Center._y + 50);

	_stoneshower->render();
}

void boss::bossState()
{
	//모든 행동 패턴은 
	//보스의 어느 렉트 부위가 
	//어느 지점에 도달했을 시 발동합니다.

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
		
		_randomAttackCount++;
		bossInitialization();
		
		if (_randomAttackCount >= 200)
		{
			_randomAttackCount = 0;
			int _randomAttack;
			_randomAttack = RND->getInt(3);

			if (_randomAttack == 1)
			{
				_bossState = MINE_READY;
			}
			
			else if (_randomAttack == 2)
			{
				_bossState = STONESHOWER_READY;
			}
			
			else
			{
				_bossState = ICETHROWER_READY;
			}

		}
		
	}
	break;

	//왼손 얼음포물선 발사 모션


	case ICETHROWER_READY:
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
			if (_currentFrameX >= IMAGEMANAGER->findImage("왼손공격")->getMaxFrameX())
			{
				_currentFrameX = 0;
				_currentFrameY++;
			}
			if (_currentFrameY >= IMAGEMANAGER->findImage("왼손공격")->getMaxFrameY())
			{
				_currentFrameY = 0;
				_icethrowerDelay = 0;
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


		_RightArm._angle -= 0.012f / 1.35f;
		_RightHand._angle -= 0.012f / 1.35f;
		_RightArm._realAngle += 0.6f / 1.35f;
		_RightHand._realAngle += 1.2f / 1.35f;


		_LeftArm._angle -= 0.016f;
		_LeftHand._angle -= 0.024f;
		_LeftArm._realAngle += 0.8f;
		_LeftHand._realAngle += 0.6f;

		_Center._angle += 0.15f;

		if (_LeftHand._rectBody.left <= WINSIZEX / 2 - 243)
		{
			_bossState = STOP;
		}

	}
	break;


	//몸통 지뢰 투척 모션


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
			if (_currentFrameX >= IMAGEMANAGER->findImage("보스몸통움직임")->getMaxFrameX())
			{
				_currentFrameX = 0;
				_bossState = MINE_END;
			}

			if (_currentFrameX >= 7)
			{
				_mineAttackDelay++;
				if (_mineAttackDelay % 2 == 0)
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

		if (_LeftHand._rectBody.left > WINSIZEX / 2 - 266)
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

	case STONESHOWER_READY:
	{
		_LeftArm._angle += 0.024f;
		_LeftHand._angle += 0.016f;
		_LeftArm._realAngle -= 1.2f;
		_LeftHand._realAngle -= 0.8f;
		_LeftArm._center.y += 1.0f;
		_LeftArm._center.x += 1.0f;

		_RightArm._angle += 0.024f * 2.0f;
		_RightHand._angle += 0.016f * 2.0f;
		_RightArm._realAngle -= 1.2f * 2.0f;
		_RightHand._realAngle -= 0.8f * 2.0f;

		_Center._angle -= 0.6f;

		if (_RightHand._rectBody.top < WINSIZEY / 2 - 75)
		{
			_bossRightHandAttackFrameY = 0;

			if (_frameCount % 4 == 0)
			{

				if (_currentFrameX >= IMAGEMANAGER->findImage("오른손공격")->getMaxFrameX())
				{
					_currentFrameX++;
				}
				_bossRightHandAttackFrameX = _currentFrameX;
				_currentFrameX++;
				_frameCount = 0;
			}
		}


		if (_RightHand._rectBody.top < WINSIZEY / 2 - 200)
		{
			_bossState = STONESHOWER_READY2;
		}

		
	}
	break;
	
	case STONESHOWER_READY2:
	{

		_RightHand._realAngle += 2.0f;
		
		if (_frameCount % 4 == 0)
		{

			if (_currentFrameX >= 5)
			{
				_bossState = STONESHOWER_READY3;
			}
			_bossRightHandAttackFrameX = _currentFrameX;
			_currentFrameX++;
			_frameCount = 0;
		}
		
	}
	break;

	case STONESHOWER_READY3:
	{
		_motionDelay++;

		if (_motionDelay >= 75)
		{
			_LeftArm._angle -= 0.024f * 6.0f;
			_LeftHand._angle -= 0.016f * 6.0f;
			_LeftArm._realAngle += 1.2f * 6.0f;
			_LeftHand._realAngle += 0.8f * 6.0f;
			_LeftArm._center.y -= 1.0f * 6.0f;
			_LeftArm._center.x -= 1.0f * 6.0f;

			_RightArm._angle -= 0.024f * 19.2f;
			_RightHand._angle -= 0.016f * 19.2f;
			_RightArm._realAngle += 1.2f * 19.2f;
			_RightHand._realAngle += 0.8f * 8.8f;

			_LeftArm._center.x += 1.0f;

			_RightArm._center.x -= 2.5f;
			_RightArm._center.y += 3.5f * 6;

			_Center._angle += 0.6f;

			if (_frameCount % 3 == 0)
			{

				if (_currentFrameX >= 7)
				{
					_motionDelay = 0;
					CAMERA->shakeStart(3.f, 4.2f);
					_bossState = STONESHOWER;

					for (int i = 0; i < _stoneshower->getDustVector().size(); i++)
					{
						_stoneshower->dustTrue(i);
						break;
					}
				}
				_bossRightHandAttackFrameX = _currentFrameX;
				_currentFrameX++;
				_frameCount = 0;
				
			}
		}
	}
	break;

	case STONESHOWER:
	{
		_motionDelay++;
		_stoneAttackDelay++;

		if (_stoneAttackDelay % 8 == 0)
		{
			_stoneshower->fire();
		}

		if (_motionDelay >= 48)
		{
			for (int i = 0; i < _stoneshower->getDustVector().size(); i++)
			{
				_stoneshower->dustFalse(i);
				break;
			}
		}

		if (_motionDelay >= 250)
		{
			_motionDelay = 0;
			_stoneAttackDelay = 0;
			_bossState = STONESHOWER_END;

		}

	}
	break;


	case STONESHOWER_END:
	{		
		_bossRightHandAttackFrameX = 0;

		_LeftArm._angle += 0.003f / 9;
		_LeftHand._angle += 0.006f / 12;
		_LeftArm._realAngle -= 0.12f / 3;
		_LeftHand._realAngle -= 0.08f / 3;

		_RightArm._angle += 0.024f  /2;
		_RightHand._angle += 0.016f /2;
		_RightArm._realAngle -= 1.2f  / 2;
		_RightHand._realAngle -= 0.15f  / 2;

		_RightArm._center.x += 0.3f;
		_RightArm._center.y -= 1.5f;

		_LeftArm._center.x += 0.02f;
		_LeftArm._center.y += 0.09f;

		_Center._angle = 0;

		if (_RightHand._rectBody.top < WINSIZEY / 2 - 50)
		{
			_bossState = STOP;
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
		if (_protectCurrentFrameX >= IMAGEMANAGER->findImage("보스바텀방어막1")->getMaxFrameX())
		{
			_protectCurrentFrameX = 0;
		}
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

	//자주 움직이는 양팔과 양손은 중점 x,y 를 기준으로 렌더
	//그 외는 rect left,top에 렌더를 했습니다.

	//바텀
	IMAGEMANAGER->findImage("보스바텀")->render(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left - 175, _Bottom._rectBody.top - 60)));

	IMAGEMANAGER->findImage("보스바텀방어막1")->frameRender(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left + 75, _Bottom._rectBody.top + 60)),
		_bossShieldOneFrameX, _bossShieldOneFrameY);


	//양팔
	IMAGEMANAGER->findImage("왼팔")->setAngle(_LeftArm._realAngle);
	IMAGEMANAGER->findImage("왼팔")->render(CAMERA->getRelativeVector2(Vector2(_LeftArm._centerEnd.x - 225, _LeftArm._centerEnd.y - 75)));
	IMAGEMANAGER->findImage("오른팔")->setAngle(_RightArm._realAngle);
	IMAGEMANAGER->findImage("오른팔")->render(CAMERA->getRelativeVector2(Vector2(_RightArm._centerEnd.x - 100, _RightArm._centerEnd.y - 75)));


	//몸통
	if (_bossState == MINE)
	{
		IMAGEMANAGER->findImage("보스몸통움직임")->frameRender(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left + 296, _Center._rectBody.top + 144)),
			_bossCenterMoveFrameX, _bossCenterMoveFrameY);
	}

	else if (_bossState == STONESHOWER_READY2 || _bossState == STONESHOWER_READY3)
	{
		IMAGEMANAGER->findImage("보스몸통우")->setAngle(_Center._angle);
		IMAGEMANAGER->findImage("보스몸통우")->render(CAMERA->getRelativeVector2(Vector2((_Center._rectBody.left - 191) - 20, _Center._rectBody.top - 193)));
	}

	else if (_bossState == STONESHOWER)
	{
		IMAGEMANAGER->findImage("보스몸통하")->render(CAMERA->getRelativeVector2(Vector2((_Center._rectBody.left - 191), (_Center._rectBody.top - 193) + 25)));
	}
	else
	{
		IMAGEMANAGER->findImage("보스몸통")->setAngle(_Center._angle);
		IMAGEMANAGER->findImage("보스몸통")->render(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left - 191, _Center._rectBody.top - 193)));
	}
	

	//왼손
	if (_bossState == ICETHROWER)
	{
		IMAGEMANAGER->findImage("왼손공격")->frameRender(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 50, _LeftHand._centerEnd.y + 225)),
		_bossLeftHandAttackFrameX, _bossLeftHandAttackFrameY);
	}
	else
	{
		IMAGEMANAGER->findImage("왼손")->setAngle(_LeftHand._realAngle);
		IMAGEMANAGER->findImage("왼손")->render(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 250, _LeftHand._centerEnd.y - 100)));
	}

	//오른손
	if (_bossState == STONESHOWER_READY)
	{
		IMAGEMANAGER->findImage("오른손공격")->setAngle(_RightHand._realAngle);
		IMAGEMANAGER->findImage("오른손공격")->frameRender(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x, _RightHand._centerEnd.y + 200)),
			_bossRightHandAttackFrameX, _bossRightHandAttackFrameY);
	}
	else if (_bossState == STONESHOWER_READY2 || _bossState == STONESHOWER_READY3)
	{
		IMAGEMANAGER->findImage("오른손공격")->setAngle(_RightHand._realAngle);
		IMAGEMANAGER->findImage("오른손공격")->frameRender(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x, _RightHand._centerEnd.y - 80)),
			_bossRightHandAttackFrameX, _bossRightHandAttackFrameY);
	}
	else if (_bossState == STONESHOWER)
	{
		IMAGEMANAGER->findImage("오른손공격")->setAngle(_RightHand._realAngle);
		IMAGEMANAGER->findImage("오른손공격")->frameRender(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x, _RightHand._centerEnd.y + 200)),
			_bossRightHandAttackFrameX, _bossRightHandAttackFrameY);

	}
	else
	{
		IMAGEMANAGER->findImage("오른손")->setAngle(_RightHand._realAngle);
		IMAGEMANAGER->findImage("오른손")->render(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x - 200, _RightHand._centerEnd.y - 50)));
	}


	if (_bossState == STONESHOWER)
	{
		_stoneshower->dustDraw(_RightHand._centerEnd.x, _RightHand._centerEnd.y + 200);

	}



	//================================================================================================================================================================//


	//위치 확인용 몸통, 바텀 렉트

	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_Center._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_Bottom._rectBody));

	//위치 확인용 양손, 양팔 관절 렉트

	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_LeftArm._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_RightArm._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_LeftHand._rectBody));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_RightHand._rectBody));


	//위치 확인용 양손, 양팔 점선

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

		if (WINSIZEY + 1600 < _icethrower->getIcethrowerVector()[i]._rc.bottom)
		{
			_icethrower->removeFire(i);
			break;
		}

	}

	for (int i = 0; i < _stoneshower->getStoneVector().size(); i++)
	{
		int _randomDrop;
		_randomDrop = RND->getFromIntTo(-400, 100);

		if (WINSIZEY + 500 + (_randomDrop) < _stoneshower->getStoneVector()[i]._rc.bottom)
		{
			_stoneshower->removeFire(i);
			break;

		}

	}

}

void boss::bossInitialization()
{
	_Center._x = (WINSIZEX / 2 - 85);
	_Center._y = (WINSIZEY / 2 - 175);

	_Center._center.x = (WINSIZEX / 2 - 85);
	_Center._center.y = (WINSIZEY / 2 - 175);
	
	_LeftArm._x = (_Center._x - 125) + 100;
	_LeftArm._y = (_Center._y + 25);
	_LeftArm._angle = PI2 - (PI / 4);
	_LeftArm._realAngle = PI2 - (PI / 4);

	_LeftArm._center.x = (_Center._x - 125) + 100;
	_LeftArm._center.y = (_Center._y + 25);

	_RightArm._x = (_Center._x + 545) - 100;
	_RightArm._y = (_Center._y + 25);
	_RightArm._angle = PI2 - (PI / 4);
	_RightArm._realAngle = PI2 - (PI / 4);

	_RightArm._center.x = (_Center._x + 545) - 100;
	_RightArm._center.y = (_Center._y + 25);

	_LeftHand._x = _LeftArm._x - 100;
	_LeftHand._y = _LeftArm._y + 100;
	_LeftHand._angle = PI2 - (PI / 4);
	_LeftHand._realAngle = PI2 - (PI / 4);

	_RightHand._x = _RightArm._x + 100;
	_RightHand._y = _RightArm._y + 100;
	_RightHand._angle = PI2 - (PI / 4);
	_RightHand._realAngle = PI2 - (PI / 4);

	_Bottom._x = _Center._x + 160;
	_Bottom._y = _Center._y + 450;
	_Center._angle = 0;

}
