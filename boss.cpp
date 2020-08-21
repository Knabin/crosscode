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
	// 기본 y축WINSIZEY / 2 - 675
	bossInitialization();

	_bossState = APPEARANCE;
	//_bossState = STOP;
	//_bossState = ICETHROWER_READY;
	//_bossState = MINE_READY;
	//_bossState = STONESHOWER_READY;
	//_bossState = FLAMETHROWER_READY;
	//_bossState = ICEGUIDE_READY;
	//_bossState = STUN;
	//_bossState = DEATH;
	
	_currentFrameX, _currentFrameY, _frameCount = 0;
	_protectCurrentFrameX, _protectCurrentFrameY, _protectFrameCount = 0;
	_protectCurrentFrameX2, _protectCurrentFrameY2, _protectFrameCount2 = 0;
	_protectCurrentFrameX3, _protectCurrentFrameY3, _protectFrameCount3 = 0;
	_centerFrameCount, _centerCurrentFrameX, _centerCurrentFrameY = 0;
	_moveCount = 0;
	_motionDelay = 0;
	_icethrowerDelay = 0;
	_stopCount = 0;
	_mineAttackDelay = 0;
	_stoneAttackDelay = 0;
	_flamethrowerDelay = 0;
	_effectDelay = 0;
	_chargeCount = 0;
	_iceguideDelay = 0;
	_stunCount = 0;

	_attack1, _attack2, _attack3, _attack4, _attack5 = false;

	//================================================================================================================================================================//

	//보스 png이미지 선언

	IMAGEMANAGER->addImage("보스몸통", L"images/boss/center_body.png");
	IMAGEMANAGER->addImage("보스몸통우", L"images/boss/center_right.png");
	IMAGEMANAGER->addImage("보스몸통좌", L"images/boss/center_left.png");
	IMAGEMANAGER->addImage("보스몸통하", L"images/boss/center_down.png");

	IMAGEMANAGER->addFrameImage("보스몸통움직임", L"images/boss/center_move.png", 15, 1);
	IMAGEMANAGER->addFrameImage("보스몸통움직임2", L"images/boss/center_move2.png", 10, 1);

	IMAGEMANAGER->addImage("보스바텀", L"images/boss/bottom.png");
	IMAGEMANAGER->addFrameImage("보스바텀방어막1", L"images/boss/bottom_first.png", 9, 1);
	IMAGEMANAGER->addFrameImage("보스바텀방어막2", L"images/boss/bottom_second.png", 5, 1);
	IMAGEMANAGER->addFrameImage("보스바텀방어막3", L"images/boss/bottom_third.png", 4, 1);

	IMAGEMANAGER->addImage("왼팔", L"images/boss/left_arm.png");
	IMAGEMANAGER->addImage("왼손", L"images/boss/left_hand.png");
	IMAGEMANAGER->addImage("왼손움직임3", L"images/boss/left_hand_move3.png");

	IMAGEMANAGER->addFrameImage("왼손공격", L"images/boss/left_hand_attack.png", 20, 2);
	IMAGEMANAGER->addFrameImage("왼손공격2", L"images/boss/left_hand_attack2.png", 20, 2);
	IMAGEMANAGER->addFrameImage("왼손움직임1", L"images/boss/left_hand_move.png", 4, 1);
	IMAGEMANAGER->addFrameImage("왼손움직임2", L"images/boss/left_hand_move2.png", 4, 1);

	IMAGEMANAGER->addImage("오른팔", L"images/boss/right_arm.png");
	IMAGEMANAGER->addImage("오른손", L"images/boss/right_hand.png");

	IMAGEMANAGER->addFrameImage("오른손공격", L"images/boss/right_hand_attack2.png", 8, 1);
	IMAGEMANAGER->addFrameImage("오른손공격2", L"images/boss/right_hand_attack.png", 4, 1);

	IMAGEMANAGER->addFrameImage("파괴", L"images/boss/death_effect.png", 10, 1);

	//================================================================================================================================================================//

	//몸통

	_Center._centerMeter = 100;

	_Center._speed = 2.0f;

	_Center._rectBody.update(Vector2(_Center._x + 210, _Center._y + 200), Vector2(600, 400), pivot::CENTER);

	//왼팔

	_LeftArm._centerMeter = 170;

	_LeftArm._rectBody.update(Vector2(_LeftArm._center.x, _LeftArm._center.y), Vector2(50, 50), pivot::CENTER);

	//왼손

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

	//실제 팔 렉트

	_LeftHand._rectBody2.update(Vector2(_LeftHand._center.x, _LeftHand._center.y), Vector2(250, 250), pivot::CENTER);

	_RightHand._rectBody2.update(Vector2(_RightHand._center.x, _RightHand._center.y), Vector2(250, 250), pivot::CENTER);
	
	//================================================================================================================================================================//

	for (int i = 0; i < 199; i++)
	{
		tagEffect effect;
		ZeroMemory(&effect, sizeof(effect));

		effect._size = 128.0f;
		effect._angle = PI + (PI / 2);
		effect._speed = 20.0f;
		effect._fireStart = false;
		effect._frameX = 0;
		effect._frameCount = 0;
		effect._currentFrameX = 0;

		int _randomNumber;
		_randomNumber = RND->getFromFloatTo(-300, 300);

		effect._center.x = (WINSIZEX / 2 - 85 + 200 ) + _randomNumber;
		effect._center.y = (WINSIZEY / 2 - 175 + 200 ) + _randomNumber;

		effect._centerMeter = 200;
	
		_vEffect.push_back(effect);

	}

	//================================================================================================================================================================//
	_icethrower = new icethrower;
	_icethrower->init(WINSIZEX / 2 - 85, WINSIZEY / 2 - 675 + 1150);

	_mine = new mine;
	_mine->init(WINSIZEX / 2 - 85, WINSIZEY / 2 - 675 + 550);

	_stoneshower = new stoneshower;
	_stoneshower->init(WINSIZEX / 2 - 85 + 215, WINSIZEY / 2 - 675 - 499);

	_flamethrower = new flamethrower;
	_flamethrower->init(WINSIZEX / 2 - 85 + 385, WINSIZEY / 2 - 675 + 1025);

	_iceguide = new iceguide;
	_iceguide->init(WINSIZEX / 2 - 85 + 185, WINSIZEY / 2 - 675 + 1125);

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{

	_frameCount++;

	protectFrame();

	bossMove();

	bossState();

	fireCollision();

	//================================================================================================================================================================//

	_icethrower->update();

	_mine->update();

	_stoneshower->update();

	_flamethrower->update();

	_iceguide->update();

}

void boss::render()
{

	_icethrower->render();

	_iceguide->render();

	_mine->render(_Center._x + 115, _Center._y + 50);

	bossDraw();

	_mine->explotion(_Center._x + 115, _Center._y + 50);

	_stoneshower->render();

	_flamethrower->render();

}

void boss::bossState()
{
	//모든 행동 패턴은 
	//보스의 어느 렉트 부위가 
	//어느 지점에 도달했을 시 발동합니다.

	switch (_bossState)
	{
		
	case APPEARANCE:
	{

		//CAMERA->shakeStart(5.f, 4.2f);

		moveDown();

		
		if (_Center._y == WINSIZEY / 2 - 175)
		{		
			_bossState = STOP;
		}

	}
	break;
	
	case STOP:
	{
		_currentFrameX = 0;
		_stopCount++;
		bossInitialization2();
		
		
		if (_stopCount >= 200)
		{
			if (_attack1 == false && _attack2 == false && _attack3 == false && _attack4 == false)
			{
				_stopCount = 0;
				_bossState = ICETHROWER_READY;
			}

			if (_attack1 == true && _attack2 == false && _attack3 == false && _attack4 == false)
			{
				_stopCount = 0;
				_bossState = MINE_READY;
			}

			if (_attack1 == true && _attack2 == true && _attack3 == false && _attack4 == false)
			{
				_stopCount = 0;
				_bossState = STONESHOWER_READY;
			}

			if (_attack1 == true && _attack2 == true && _attack3 == true && _attack4 == false)
			{
				_stopCount = 0;
				_bossState = FLAMETHROWER_READY;
			}

			if (_attack1 == true && _attack2 == true && _attack3 == true && _attack4 == true)
			{
				_stopCount = 0;
				_bossState = ICEGUIDE_READY;
			}

		}		
	}
	break;

	//왼손 얼음포물선 발사 모션

	case ICETHROWER_READY:
	{
		_attack1 = true;

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

			if (_motionDelay < 15)
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

			if (_motionDelay >= 15)
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


		_Center._angle -= 0.3f;

		if (_RightHand._rectBody.top < _Center._y + 50)
		{
			_bossState = ICETHROWER;
		}

	}
	break;

	case ICETHROWER:
	{
		_icethrower->angleUpdate();
		_icethrowerDelay++;
		_Center._angle += 0.042f;

		if (_icethrowerDelay % 4 == 0)
		{
			_icethrower->fire();

		}
		

		if (_frameCount % 5 == 0)
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

		_Center._angle += 0.08f;

		if (_LeftHand._rectBody.left <= WINSIZEX / 2 - 243)
		{
			_bossState = STOP;
		}

	}
	break;


	//몸통 지뢰 투척 모션


	case MINE_READY:
	{	
		_attack2 = true;

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
		_attack3 = true;

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

		_Center._angle -= 0.65f;

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

			_Center._angle += 0.65f;

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
		_Center._angle += 0.047f;

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

		if (_RightHand._rectBody.top < WINSIZEY / 2 - 50)
		{
			_bossState = STOP;
		}

	}
	break;

	case FLAMETHROWER_READY:
	{
		_attack4 = true;

		_LeftArm._center.x -= 0.2f * 1.2f;
		_LeftArm._center.y += 0.5f * 1.2f;

		_LeftArm._angle += 0.024f * 1.2f;
		_LeftHand._angle += 0.016f * 1.2f;
		_LeftArm._realAngle -= 1.2f * 1.2f;
		_LeftHand._realAngle -= 0.04f;


		_bossLeftHandMoveFrameY = 0;

		if (_frameCount % 8 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("왼손움직임2")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_bossLeftHandMoveFrameX = _currentFrameX;
			_currentFrameX++;
			_frameCount = 0;

		}


		if (_LeftHand._rectBody.right > WINSIZEX / 2 - 50)
		{
			_bossState = FLAMETHROWER_READY2;
		}


	}
	break;

	case FLAMETHROWER_READY2:
	{
		moveUp();
		
		if (_Center._y < WINSIZEY / 2 - 350)
		{
			_bossState = FLAMETHROWER_READY3;
		}

	}
	break;

	case FLAMETHROWER_READY3:
	{

		_LeftArm._center.x += 0.2f * 1.2f;
		_LeftArm._center.y -= 0.5f * 1.2f;

		_LeftArm._angle -= 0.024f * 1.2f;
		_LeftHand._angle -= 0.016f * 1.2f;
		_LeftArm._realAngle += 1.2f * 1.2f;
		_LeftHand._realAngle += 0.04f;


		_RightArm._center.y += 1.8f / 1.5f;

		_RightArm._angle -= 0.036f / 1.5f;
		_RightHand._angle -= 0.032f / 1.5f;
		_RightArm._realAngle += 1.6f / 1.5f;
		_RightHand._realAngle -= 0.004f;
		
		_RightArm._center.y += 3.8f / 1.5f;

		_RightArm._angle -= 0.036f / 1.5f;
		_RightHand._angle -= 0.032f / 1.5f;
		_RightArm._realAngle += 1.6f / 1.5f;
		_RightHand._realAngle += 0.44f / 1.5f;

		_bossRightHandAttackFrameY2 = 0;

		if (_frameCount % 10 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("오른손공격2")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_bossRightHandAttackFrameX2 = _currentFrameX;
			_currentFrameX++;
			_frameCount = 0;
		}

		if (_RightHand._rectBody.left < WINSIZEX / 2 + 325)
		{
			_bossState = FLAMETHROWER_READY4;
		}

	}
	break;

	case FLAMETHROWER_READY4:
	{
		_chargeCount++;

		if (_chargeCount >= 250)
		{
			_chargeCount = 0;
			_bossState = FLAMETHROWER;
		}
	}
	break;

	case FLAMETHROWER:
	{
		_flamethrower->angleUpdate();

		_flamethrowerDelay++;

		if (_flamethrowerDelay % 3 == 0)
		{
			_flamethrower->fire();

		}

		if (_flamethrowerDelay >= 300)
		{
			for (_flamethrower->getFlameEffectIterVector() = _flamethrower->getFlameEffectVector().begin();
				_flamethrower->getFlameEffectIterVector() != _flamethrower->getFlameEffectVector().end();
				++_flamethrower->getFlameEffectIterVector())
			{
				_flamethrower->getFlameEffectIterVector()->_fireStart = false;
			}
		}

		if (_flamethrowerDelay >= 400)
		{
			for (_flamethrower->getFlameIterVector() = _flamethrower->getFlameVector().begin();
				_flamethrower->getFlameIterVector() != _flamethrower->getFlameVector().end();
				++_flamethrower->getFlameIterVector())
			{
				
				_flamethrower->getFlameIterVector()->_fireStart = false;
				_bossState = FLAMETHROWER_END;
				
				
			}
		}	
	}
	break;

	case FLAMETHROWER_END:
	{
		
		_LeftArm._center.x -= 0.2f * 1.2f;
		_LeftArm._center.y += 0.5f * 1.2f;

		_LeftArm._angle += 0.024f * 1.2f;
		_LeftHand._angle += 0.016f * 1.2f;
		_LeftArm._realAngle -= 1.2f * 1.2f;
		_LeftHand._realAngle -= 0.04f;

		_RightArm._center.y -= 1.8f / 1.5f;

		_RightArm._angle += 0.036f / 1.5f;
		_RightHand._angle += 0.032f / 1.5f;
		_RightArm._realAngle -= 1.6f / 1.5f;
		_RightHand._realAngle += 0.004f;

		_RightArm._center.y -= 3.8f / 1.5f;
		_RightArm._center.x += 0.9f / 1.5f;

		_RightArm._angle += 0.031f / 1.5f;
		_RightHand._angle += 0.032f / 1.5f;
		_RightArm._realAngle -= 1.6f / 1.5f;
		_RightHand._realAngle -= 0.44f / 1.5f;


		if (_RightHand._rectBody.right > WINSIZEX / 2 + 490)
		{
			_bossState = FLAMETHROWER_END2;
		}


	}
	break;

	case FLAMETHROWER_END2:
	{	
		moveDown();

		if (_Center._y >= WINSIZEY / 2 - 175)
		{
			_bossState = FLAMETHROWER_END3;
		}

	}
	break;

	case FLAMETHROWER_END3:
	{
		
		_LeftArm._center.x += 0.1f * 1.2f;
		_LeftArm._center.y -= 0.7f * 1.2f;

		_LeftArm._angle -= 0.024f * 1.2f;
		_LeftHand._angle -= 0.016f * 1.2f;
		_LeftArm._realAngle += 1.2f * 1.2f;
		_LeftHand._realAngle += 0.04f;
		
		_bossLeftHandMoveFrameY2 = 0;

		if (_frameCount % 34 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("왼손움직임1")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_bossLeftHandMoveFrameX2 = _currentFrameX;
			_currentFrameX++;
			_frameCount = 0;

		}

		if (_LeftHand._rectBody.left < WINSIZEX / 2 - 245)
		{
			_bossState = STOP;
		}

	}
	break;

	case ICEGUIDE_READY:
	{

		_attack1 = false;

		_LeftArm._center.x += 1.5f / 1.5f;
		_LeftArm._center.y -= 2.0f / 1.5f;

		_LeftArm._angle -= 0.024f / 1.5f;
		_LeftHand._angle -= 0.032f / 1.5f;
		_LeftArm._realAngle += 1.2f / 1.5f;
		_LeftHand._realAngle += 0.8f / 1.5f;


		_RightArm._center.x -= 0.5f / 1.5f;
		_RightArm._center.y -= 2.0f / 1.5f;

		_RightArm._angle -= 0.024f / 1.5f;
		_RightHand._angle -= 0.032f / 1.5f;
		_RightArm._realAngle += 1.2f / 1.5f;
		_RightHand._realAngle += 0.8f / 1.5f;


		_Center._angle += 0.25f;

		_bossLeftHandMoveFrameY = 0;

		if (_frameCount % 12 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("왼손움직임2")->getMaxFrameX())
			{
			
				_currentFrameX = 0;
			}
			_bossLeftHandMoveFrameX = _currentFrameX;
			_currentFrameX++;
			_frameCount = 0;

		}

		
		if (_LeftHand._rectBody.top < WINSIZEY / 2 - 200)
		{
			_bossState = ICEGUIDE_READY2;
		}
		


	}
	break;

	case ICEGUIDE_READY2:
	{
		_motionDelay++;

		if (_motionDelay >= 100)
		{
			_LeftArm._center.x += 1.5f * 2.5f;
			_LeftArm._center.y += 2.5f * 2.5f;

			_LeftArm._angle += 0.024f * 2.5f;
			_LeftHand._angle += 0.032f * 2.5f;
			_LeftArm._realAngle -= 1.7f * 2.5f;
			_LeftHand._realAngle -= 0.5f * 2.5f;


			_RightArm._center.x -= 0.5f / 2.5f;
			_RightArm._center.y += 2.0f / 2.5f;

			_RightArm._angle += 0.024f / 2.5f;
			_RightHand._angle += 0.032f / 2.5f;
			_RightArm._realAngle -= 1.2f / 2.5f;
			_RightHand._realAngle -= 0.8f / 2.5f;



			_centerFrameCount++;

			_centerMoveFrameY = 0;

			if (_centerFrameCount % 5 == 0)
			{
				if (_centerCurrentFrameX >= IMAGEMANAGER->findImage("보스몸통움직임2")->getMaxFrameX())
				{
					_centerCurrentFrameX = 0;
				}
				_centerMoveFrameX = _centerCurrentFrameX;
				_centerCurrentFrameX++;
				_centerFrameCount = 0;
			}



			if (_frameCount % 3 == 0)
			{
				if (_currentFrameX >= IMAGEMANAGER->findImage("왼손공격2")->getMaxFrameX())
				{
					_currentFrameX = 0;
					_currentFrameY++;
				}
				if (_currentFrameY >= IMAGEMANAGER->findImage("왼손공격2")->getMaxFrameY())
				{
					_currentFrameY = 0;
					_bossState = ICEGUIDE_END;
				}
				_bossLeftHandAttackFrameX2 = _currentFrameX;
				_bossLeftHandAttackFrameY2 = _currentFrameY;
				_currentFrameX++;
				_frameCount = 0;
			}


			if (_LeftHand._rectBody.bottom > WINSIZEY / 2  + 150)
			{
				_centerFrameCount = 0;
				_bossState = ICEGUIDE;
			}


		}

	}
	break;

	case ICEGUIDE:
	{
		_iceguideDelay++;

		
		if (_iceguideDelay % 3 == 0)
		{
			_iceguide->fire();

		}
		
		_Center._angle -= 0.2f;
	
		if (_frameCount % 3 == 0)
		{
			if (_currentFrameX >= IMAGEMANAGER->findImage("왼손공격2")->getMaxFrameX())
			{
				_currentFrameX = 0;
				_currentFrameY++;
			}
			if (_currentFrameY >= IMAGEMANAGER->findImage("왼손공격2")->getMaxFrameY())
			{
				_currentFrameY = 0;
				_iceguideDelay = 0;
				_bossState = ICEGUIDE_END;
			}
			_bossLeftHandAttackFrameX2 = _currentFrameX;
			_bossLeftHandAttackFrameY2 = _currentFrameY;
			_currentFrameX++;
			_frameCount = 0;
		}

	}
	break;

	case ICEGUIDE_END:
	{
		_Center._angle += 0.12f;

		_LeftArm._center.x -= 4.30f / 2.0f;
		_LeftArm._center.y -= 3.60f / 2.0f;

		_LeftArm._angle -= 0.041f / 2.0f;
		_LeftHand._angle -= 0.048f / 2.0;
		_LeftArm._realAngle += 2.9f / 2.0f;
		_LeftHand._realAngle += 0.5f / 2.0f;


		_RightArm._center.x -= 0.1f / 1.5f;
		_RightArm._center.y += 1.9f / 1.5f;

		_RightArm._angle += 0.024f / 2.0f;
		_RightHand._angle += 0.019f / 2.0f;
		_RightArm._realAngle -= 0.7f / 2.0f;
		_RightHand._realAngle -= 0.55f / 2.0f;


		if (_LeftHand._rectBody.top < WINSIZEY / 2 - 45)
		{
			_bossState = STUN;
		}

	}
	break;

	case STUN:
	{

		_Center._y -= 0.5f * 2.0f;
		_LeftArm._center.y -= 0.5f * 2.0f;
		_LeftHand._center.y -= 0.5f * 2.0f;
		_RightArm._center.y -= 0.5f * 2.0f;
		_RightHand._center.y -= 0.5f * 2.0f;
		_Bottom._y -= 0.5f * 2.0f;

		_LeftArm._angle -= 0.01f * 2.0f;
		_RightArm._angle += 0.01f * 2.0f;
		_LeftHand._angle -= 0.025f * 2.0f;
		_RightHand._angle += 0.025f * 2.0f;
		_LeftArm._realAngle += 0.6f * 2.0f;
		_RightArm._realAngle -= 0.6f * 2.0f;
		_LeftHand._realAngle += 1.5f * 2.0f;
		_RightHand._realAngle -= 1.5f * 2.0f;



		if (_LeftHand._rectBody.left < WINSIZEX / 2 - 270)
		{
			_bossState = STUN2;
		}

	}
	break;

	case STUN2:
	{
		_stunCount++;

		if (_stunCount >= 75)
		{
			_LeftArm._center.x += 2.0f * 3.0f;
			_RightArm._center.x -= 2.0f * 3.0f;

			_LeftArm._angle += 0.01f * 3.0f;
			_RightArm._angle -= 0.01f * 3.0f;
			_LeftHand._angle += 0.025f * 3.0f;
			_RightHand._angle -= 0.025f * 3.0f;

			_LeftArm._realAngle -= 0.9f * 3.0f;
			_RightArm._realAngle += 0.9f * 3.0f;
			_LeftHand._realAngle -= 1.2f * 3.0f;
			_RightHand._realAngle += 1.2f * 3.0f;

			if (_LeftHand._rectBody.bottom > WINSIZEY / 2 - 15)
			{
				_stunCount = 0;
				_bossState = STUN3;
			}
		}

	}
	break;

	case STUN3:
	{
		_stunCount++;


		if (_stunCount >= 525)
		{
			_LeftArm._center.x -= 8.8f / 2.5f;
			_RightArm._center.x += 8.8f / 2.5f;

			_LeftArm._angle -= 0.01f / 2.5f;
			_RightArm._angle += 0.01f / 2.5f;
			_LeftHand._angle -= 0.035f / 2.5f;
			_RightHand._angle += 0.035f / 2.5f;

			_LeftArm._realAngle += 2.2f / 2.5f;
			_RightArm._realAngle -= 2.2f / 2.5f;
			_LeftHand._realAngle += 0.5f / 2.5f;
			_RightHand._realAngle -= 0.5f / 2.5f;

		}

		if (_LeftHand._rectBody.top < WINSIZEY / 2 - 65)
		{
			_stunCount = 0;
			_bossState = STUN4;
		}


	}
	break;

	case STUN4:
	{
		moveDown();

		if (_Center._y >= (WINSIZEY / 2 - 175))
		{
			_bossState = DEATH;
		}

	}
	break; 

	case DEATH:
	{
		_effectDelay++;
		effectMove();
		effectFrame();
		effectAngleMove();

		if (_effectDelay % 10 == 0)
		{
			effectFire();
		}

		if (_effectDelay >= 400)
		{
			_Center._x = (WINSIZEX / 2 - 850);
			_Center._y = (WINSIZEY / 2 - 1750);

			_Center._center.x = (WINSIZEX / 2 - 850);
			_Center._center.y = (WINSIZEY / 2 - 6750);

			_LeftArm._x = (_Center._x - 1250) + 100;
			_LeftArm._y = (_Center._y + 250);


			_LeftArm._center.x = (_Center._x - 1250) + 100;
			_LeftArm._center.y = (_Center._y + 250);

			_RightArm._x = (_Center._x + 5450) - 100;
			_RightArm._y = (_Center._y + 250);


			_RightArm._center.x = (_Center._x + 5450) - 100;
			_RightArm._center.y = (_Center._y + 250);

			_LeftHand._x = _LeftArm._x - 1000;
			_LeftHand._y = _LeftArm._y + 1000;

			_RightHand._x = _RightArm._x + 1000;
			_RightHand._y = _RightArm._y + 1000;

			_Bottom._x = _Center._x + 1600;
			_Bottom._y = _Center._y + 4500;

			_bossState = DEATH2;

		}

	}
	break;

	case DEATH2:
	{


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

	_Bottom._rectBody.update(Vector2(_Bottom._x + 50, _Bottom._y), Vector2(150, 100), pivot::CENTER);

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

	//

	if (_bossState == ICETHROWER)
	{
		_LeftHand._rectBody2.update(Vector2(_LeftHand._center.x + 50, _LeftHand._center.y + 410), Vector2(375, 350), pivot::CENTER);

		//_RightHand._rectBody2.update(Vector2(_RightHand._center.x + 100, _RightHand._center.y + 275), Vector2(275, 250), pivot::CENTER);
	}
	else if (_bossState == STONESHOWER)
	{
		_RightHand._rectBody2.update(Vector2(_RightHand._center.x, _RightHand._center.y + 275), Vector2(275, 500), pivot::CENTER);
	}

	else if (_bossState == FLAMETHROWER_READY2 || _bossState == FLAMETHROWER_READY3 || _bossState == FLAMETHROWER_READY4 || _bossState == FLAMETHROWER || _bossState == FLAMETHROWER_END || _bossState == FLAMETHROWER_END2)
	{
		_LeftHand._rectBody2.update(Vector2(_LeftHand._center.x + 150, _LeftHand._center.y + 310), Vector2(375, 350), pivot::CENTER);

		_RightHand._rectBody2.update(Vector2(_RightHand._center.x - 25, _RightHand._center.y + 275), Vector2(325, 500), pivot::CENTER);
	}

	else
	{
		_LeftHand._rectBody2.update(Vector2(_LeftHand._center.x - 135, _LeftHand._center.y + 300), Vector2(275, 500), pivot::CENTER);

		_RightHand._rectBody2.update(Vector2(_RightHand._center.x + 100, _RightHand._center.y + 275), Vector2(275, 500), pivot::CENTER);
	}

}

void boss::bossDraw()
{
	//바텀
	IMAGEMANAGER->findImage("보스바텀")->render(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left - 175, _Bottom._rectBody.top - 60)));

	if (_bossState == STUN || _bossState == STUN2 || _bossState == STUN3 && _stunCount < 350)
	{
		IMAGEMANAGER->findImage("보스바텀방어막3")->frameRender(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left + 75, _Bottom._rectBody.top + 60)),
			_bossShieldOneFrameX3, _bossShieldOneFrameY3);
	}

	else
	{
		IMAGEMANAGER->findImage("보스바텀방어막1")->frameRender(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left + 75, _Bottom._rectBody.top + 60)),
			_bossShieldOneFrameX, _bossShieldOneFrameY);

		IMAGEMANAGER->findImage("보스바텀방어막2")->frameRender(CAMERA->getRelativeVector2(Vector2(_Bottom._rectBody.left + 75, _Bottom._rectBody.top + 60)),
			_bossShieldOneFrameX2, _bossShieldOneFrameY2);
	}


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

	else if (_bossState == ICETHROWER || _bossState == STONESHOWER_READY2 || _bossState == STONESHOWER_READY3 || _bossState == ICEGUIDE)
	{
		IMAGEMANAGER->findImage("보스몸통우")->render(CAMERA->getRelativeVector2(Vector2((_Center._rectBody.left - 191) - 20, _Center._rectBody.top - 193)));
	}

	else if (_bossState == STONESHOWER || _bossState == STONESHOWER_END)
	{
		IMAGEMANAGER->findImage("보스몸통하")->render(CAMERA->getRelativeVector2(Vector2((_Center._rectBody.left - 191), (_Center._rectBody.top - 193) + 25)));
	}

	else if (_bossState == ICEGUIDE_READY2)
	{
		IMAGEMANAGER->findImage("보스몸통움직임2")->frameRender(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left + 277, _Center._rectBody.top + 145)),
			_centerMoveFrameX, _centerMoveFrameY);
	}

	else if (_bossState == STUN2 && _stunCount >= 75 || _bossState == STUN3 && _stunCount < 450)
	{
		IMAGEMANAGER->findImage("보스몸통하")->render(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left - 191, _Center._rectBody.top - 193)));
	}

	else if (_bossState == STUN3 && _stunCount >= 450)
	{
		IMAGEMANAGER->findImage("보스몸통")->render(CAMERA->getRelativeVector2(Vector2(_Center._rectBody.left - 191, _Center._rectBody.top - 193)));
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
	else if (_bossState == FLAMETHROWER_READY || _bossState == ICEGUIDE_READY)
	{
		IMAGEMANAGER->findImage("왼손움직임2")->setAngle(_LeftHand._realAngle);
		IMAGEMANAGER->findImage("왼손움직임2")->frameRender(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 45, _LeftHand._centerEnd.y + 220)),
			_bossLeftHandMoveFrameX, _bossLeftHandMoveFrameY);
	}
	else if (_bossState == FLAMETHROWER_READY2 || _bossState == FLAMETHROWER_READY3 || _bossState == FLAMETHROWER_READY4 || _bossState == FLAMETHROWER || _bossState == FLAMETHROWER_END || _bossState == FLAMETHROWER_END2)
	{
		IMAGEMANAGER->findImage("왼손움직임3")->setAngle(_LeftHand._realAngle);
		IMAGEMANAGER->findImage("왼손움직임3")->render(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 135, _LeftHand._centerEnd.y - 100)));
	}
	else if (_bossState == FLAMETHROWER_END3)
	{
		IMAGEMANAGER->findImage("왼손움직임1")->setAngle(_LeftHand._realAngle);
		IMAGEMANAGER->findImage("왼손움직임1")->frameRender(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 40, _LeftHand._centerEnd.y + 190)),
			_bossLeftHandMoveFrameX2, _bossLeftHandMoveFrameY2);
	}
	else if (_bossState == ICEGUIDE_READY2 || _bossState == ICEGUIDE)
	{
		IMAGEMANAGER->findImage("왼손공격2")->setAngle(_LeftHand._realAngle);
		IMAGEMANAGER->findImage("왼손공격2")->frameRender(CAMERA->getRelativeVector2(Vector2(_LeftHand._centerEnd.x - 45, _LeftHand._centerEnd.y + 220)),
			_bossLeftHandAttackFrameX2, _bossLeftHandAttackFrameY2);
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
	else if (_bossState == FLAMETHROWER_READY3 || _bossState == FLAMETHROWER_READY4 ||  _bossState == FLAMETHROWER)
	{
		IMAGEMANAGER->findImage("오른손공격2")->setAngle(_RightHand._realAngle);
		IMAGEMANAGER->findImage("오른손공격2")->frameRender(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x, _RightHand._centerEnd.y + 200)),
			_bossRightHandAttackFrameX2, _bossRightHandAttackFrameY2);
	}
	else
	{
		IMAGEMANAGER->findImage("오른손")->setAngle(_RightHand._realAngle);
		IMAGEMANAGER->findImage("오른손")->render(CAMERA->getRelativeVector2(Vector2(_RightHand._centerEnd.x - 198, _RightHand._centerEnd.y - 42)));
	}

	//먼지
	if (_bossState == STONESHOWER)
	{
		_stoneshower->dustDraw(_RightHand._centerEnd.x, _RightHand._centerEnd.y + 200);

	}

	//기모으기
	if (_bossState == FLAMETHROWER_READY4 && _chargeCount < 190)
	{
		_flamethrower->chargeDraw(_RightHand._centerEnd.x - 30, _RightHand._centerEnd.y + 255);
	}
	if (_bossState == FLAMETHROWER_READY4 && _chargeCount >= 190)
	{
		_flamethrower->chargeDraw2(_RightHand._centerEnd.x - 30, _RightHand._centerEnd.y + 255);
	}

	if (_bossState == DEATH)
	{
		for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
		{
			if (!_viEffect->_fireStart) continue;
			{

				IMAGEMANAGER->findImage("파괴")->frameRender(CAMERA->getRelativeVector2(Vector2(_viEffect->_x, _viEffect->_y)),
					_viEffect->_frameX, _deathFrameY);
			}
		}
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

	//
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_LeftHand._rectBody2));
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_RightHand._rectBody2));

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

void boss::protectFrame()
{
	//바텀 방어막 프레임

	_protectFrameCount++;

	_protectFrameCount2++;

	_bossShieldOneFrameY = 0;

	_bossShieldOneFrameY2 = 0;

	_bossShieldOneFrameY3 = 0;

	if (_bossState == STUN || _bossState == STUN2 || _bossState == STUN3 && _stunCount < 350)
	{
		_protectFrameCount3++;

		if (_protectFrameCount3 % 10 == 0)
		{
			if (_protectCurrentFrameX3 >= IMAGEMANAGER->findImage("보스바텀방어막3")->getMaxFrameX())
			{
				_protectCurrentFrameX3 = 0;
			}
			_bossShieldOneFrameX3 = _protectCurrentFrameX3;
			_protectCurrentFrameX3++;
			_protectFrameCount3 = 0;
		}
	}

	else
	{
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

		if (_protectFrameCount2 % 100 == 0)
		{
			if (_protectCurrentFrameX2 >= IMAGEMANAGER->findImage("보스바텀방어막2")->getMaxFrameX())
			{
				_protectCurrentFrameX2 = 0;
			}
			_bossShieldOneFrameX2 = _protectCurrentFrameX2;
			_protectCurrentFrameX2++;
			_protectFrameCount2 = 0;
		}
	}
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
		_LeftArm._angle += 0.01f / 40;
		_LeftHand._angle += 0.001f / 40;
		_RightArm._angle += 0.01f / 40;
		_RightHand._angle += 0.001f / 40;
		_LeftArm._center.x += 0.5f / 4;
		_LeftArm._center.y += 1.0f / 4;
		_RightArm._center.x -= 0.5f / 4;
		_RightArm._center.y -= 1.0f / 4;
		_Center._angle -= 0.01f;
	}

	
	if (_moveCount >= 17 && _moveCount < 48)
	{
		_LeftArm._angle -= 0.01f / 40;
		_LeftHand._angle -= 0.001f / 40;
		_RightArm._angle -= 0.01f / 40;
		_RightHand._angle -= 0.001f / 40;
		_LeftArm._center.x -= 0.5f / 4;
		_LeftArm._center.y -= 1.0f / 4;
		_RightArm._center.x += 0.5f / 4;
		_RightArm._center.y += 1.0f / 4;
		_Center._angle += 0.01f;

	}
	
	if (_moveCount >= 48 && _moveCount < 64)
	{
		_LeftArm._angle += 0.01f / 40;
		_LeftHand._angle += 0.001f / 40;
		_RightArm._angle += 0.01f / 40;
		_RightHand._angle += 0.001f / 40;
		_LeftArm._center.x += 0.5f / 4;
		_LeftArm._center.y += 1.0f / 4;
		_RightArm._center.x -= 0.5f / 4;
		_RightArm._center.y -= 1.0f / 4;
		_Center._angle -= 0.01f;
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
		_LeftArm._angle -= 0.01f / 40;
		_LeftHand._angle -= 0.001f / 40;
		_RightArm._angle -= 0.01f / 40;
		_RightHand._angle -= 0.001f / 40;
		_LeftArm._center.x -= 0.5f / 4;
		_LeftArm._center.y -= 1.0f / 4;
		_RightArm._center.x += 0.5f / 4;
		_RightArm._center.y += 1.0f / 4;
		_Center._angle += 0.01f;
	}


	if (_moveCount >= 17 && _moveCount < 48)
	{
		_LeftArm._angle += 0.01f / 40;
		_LeftHand._angle += 0.001f / 40;
		_RightArm._angle += 0.01f / 40;
		_RightHand._angle += 0.001f / 40;
		_LeftArm._center.x += 0.5f / 4;
		_LeftArm._center.y += 1.0f / 4;
		_RightArm._center.x -= 0.5f / 4;
		_RightArm._center.y -= 1.0f / 4;
		_Center._angle -= 0.01f;

	}

	if (_moveCount >= 48 && _moveCount < 64)
	{
		_LeftArm._angle -= 0.01f / 40;
		_LeftHand._angle -= 0.001f / 40;
		_RightArm._angle -= 0.01f / 40;
		_RightHand._angle -= 0.001f / 40;
		_LeftArm._center.x -= 0.5f / 4;
		_LeftArm._center.y -= 1.0f / 4;
		_RightArm._center.x += 0.5f / 4;
		_RightArm._center.y += 1.0f / 4;
		_Center._angle += 0.01f;
	}

	if (_moveCount >= 64)
	{
		_moveCount = 0;

	}
}

void boss::effectFire()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		if (_viEffect->_fireStart) continue;
		{
			_viEffect->_fireStart = true;

			_viEffect->_x = cosf(_viEffect->_angle) * _viEffect->_centerMeter + _viEffect->_center.x;
			_viEffect->_y = -sinf(_viEffect->_angle) * _viEffect->_centerMeter + _viEffect->_center.y;

			_viEffect->_rc.update(Vector2(_viEffect->_x, _viEffect->_y), Vector2(_viEffect->_size, _viEffect->_size), pivot::CENTER);

			break;
		}
	}

}

void boss::effectMove()
{

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->_angle += 10.01f;
		if (!_viEffect->_fireStart) continue;
		{
			
			_viEffect->_x += cosf(_viEffect->_angle);
			_viEffect->_y += -sinf(_viEffect->_angle);

			_viEffect->_rc.update(Vector2(_viEffect->_x, _viEffect->_y), Vector2(_viEffect->_size, _viEffect->_size), pivot::CENTER);

		}

		if (_effectDelay >= 400)
		{

			_viEffect->_fireStart = false;
		}
	}
}

void boss::effectFrame()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->_frameCount++;

		if (_viEffect->_fireStart)
		{
			_deathFrameY = 0;

			if (_viEffect->_frameCount % 3 == 0)
			{

				if (_viEffect->_currentFrameX >= IMAGEMANAGER->findImage("파괴")->getMaxFrameX())
				{
					_viEffect->_currentFrameX = 0;
				}

				_viEffect->_frameX = _viEffect->_currentFrameX;
				_viEffect->_currentFrameX++;
				_viEffect->_frameCount = 0;
			}
		}
	}


}

void boss::effectAngleMove()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->_centerEnd.x = cosf(_viEffect->_angle) * _viEffect->_centerMeter + _viEffect->_center.x;
		_viEffect->_centerEnd.y = -sinf(_viEffect->_angle) * _viEffect->_centerMeter + _viEffect->_center.y;
	}
}

void boss::effectDraw()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		if (!_viEffect->_fireStart) continue;
		{

			IMAGEMANAGER->findImage("파괴")->frameRender(CAMERA->getRelativeVector2(Vector2(_viEffect->_x, _viEffect->_y)),
				_viEffect->_frameX, _deathFrameY);
		}
	}
}

void boss::fireCollision()
{

	for (int i = 0; i < _icethrower->getIcethrowerVector().size(); i++)
	{

		if (WINSIZEY + 800 < _icethrower->getIcethrowerVector()[i]._rc.bottom)
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

	for (int i = 0; i < _flamethrower->getFlameVector().size(); i++)
	{

		if (WINSIZEY + 1600 < _flamethrower->getFlameVector()[i]._rc.bottom)
		{
			_flamethrower->removeFire(i);
			break;
		}

	}

}

void boss::bossInitialization()
{
	_Center._x = (WINSIZEX / 2 - 85);
	_Center._y = (WINSIZEY / 2 - 675);

	_Center._center.x = (WINSIZEX / 2 - 85);
	_Center._center.y = (WINSIZEY / 2 - 675);
	
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

void boss::bossInitialization2()
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
