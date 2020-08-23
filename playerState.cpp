#include "stdafx.h"
#include "playerState.h"
#include "player.h"
#include "enemy.h"
#include "iEvent.h"

// =========================== 플레이어 아이들 =========================== //
idleState::idleState(player * player)
{
	_player = player;

	int top[] = { 1 };
	_top = new animation;
	_top->init(1152, 768, 96, 96);
	_top->setPlayFrame(top, 1, 0);

	int ltop[] = { 70 };
	_left_top = new animation;
	_left_top->init(1152, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 1, 0);

	int left[] = { 82 };
	_left = new animation;
	_left->init(1152, 768, 96, 96);
	_left->setPlayFrame(left, 1, 0);

	int lbottom[] = { 94 };
	_left_bottom = new animation;
	_left_bottom->init(1152, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 1, 0);

	int bottom[] = { 49 };
	_bottom = new animation;
	_bottom->init(1152, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 1, 0);

	int rbottom[] = { 37 };
	_right_bottom = new animation;
	_right_bottom->init(1152, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 1, 0);

	int right[] = { 25 };
	_right = new animation;
	_right->init(1152, 768, 96, 96);
	_right->setPlayFrame(right, 1, 0);

	int rtop[] = { 13 };
	_right_top = new animation;
	_right_top->init(1152, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 1, 0);

}

idleState::~idleState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void idleState::enter()
{
	//cout << "idleState enter()" << endl;

	_player->setImage("p");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
}

void idleState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
	if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
}

void idleState::exit()
{
	//cout << "idleState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();
}

// =========================== 플레이어 무브 =========================== //
moveState::moveState(player * player)
{
	_player = player;

	int top[] = { 3, 4, 5, 6, 7, 8 };
	_top = new animation;
	_top->init(1152, 768, 96, 96);
	_top->setPlayFrame(top, 6, true);
	_top->setFPS(1);

	int ltop[] = { 68, 67, 66, 65, 64, 63 };
	_left_top = new animation;
	_left_top->init(1152, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 6, true);
	_left_top->setFPS(1);

	int left[] = { 80, 79, 78, 77, 76, 75 };
	_left = new animation;
	_left->init(1152, 768, 96, 96);
	_left->setPlayFrame(left, 6, true);
	_left->setFPS(1);

	int lbottom[] = { 92, 91, 90, 89, 88, 87 };
	_left_bottom = new animation;
	_left_bottom->init(1152, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 6, true);
	_left_bottom->setFPS(1);

	int bottom[] = { 51, 52, 53, 54, 55, 56 };
	_bottom = new animation;
	_bottom->init(1152, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 6, true);
	_bottom->setFPS(1);

	int rbottom[] = { 39, 40, 41, 42, 43, 44 };
	_right_bottom = new animation;
	_right_bottom->init(1152, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 6, true);
	_right_bottom->setFPS(1);

	int right[] = { 27, 28, 29, 30, 31, 32 };
	_right = new animation;
	_right->init(1152, 768, 96, 96);
	_right->setPlayFrame(right, 6, true);
	_right->setFPS(1);

	int rtop[] = { 15, 16, 17, 18, 19, 20 };
	_right_top = new animation;
	_right_top->init(1152, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 6, true);
	_right_top->setFPS(1);
}

moveState::~moveState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void moveState::enter()
{
//	cout << "moveState enter()" << endl;

	_player->setImage("p");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);

		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);

		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);

		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);

		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);

		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
}

void moveState::update()
{
	//cout << "moveState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	_player->playerMove();
	if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void moveState::exit()
{
	//cout << "moveState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();


}

// =========================== 플레이어 점프 =========================== //
jumpState::jumpState(player * player)
{
	_player = player;

	int top[] = { 0, 1 };
	_top = new animation;
	_top->init(192, 768, 96, 96);
	_top->setPlayFrame(top, 2, 0);
	_top->setFPS(1);


	int ltop[] = { 10, 11 };
	_left_top = new animation;
	_left_top->init(192, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 2, 0);
	_left_top->setFPS(1);

	int left[] = { 12, 13 };
	_left = new animation;
	_left->init(192, 768, 96, 96);
	_left->setPlayFrame(left, 2, 0);
	_left->setFPS(1);

	int lbottom[] = { 14, 15 };
	_left_bottom = new animation;
	_left_bottom->init(192, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 1, 0);
	_left_bottom->setFPS(1);

	int bottom[] = { 8, 9 };
	_bottom = new animation;
	_bottom->init(192, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 2, 0);
	_bottom->setFPS(1);

	int rbottom[] = { 6, 7 };
	_right_bottom = new animation;
	_right_bottom->init(192, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 2, 0);
	_right_bottom->setFPS(1);

	int right[] = { 4, 5 };
	_right = new animation;
	_right->init(192, 768, 96, 96);
	_right->setPlayFrame(right, 2, 0);
	_right->setFPS(1);

	int rtop[] = { 2, 3 };
	_right_top = new animation;
	_right_top->init(192, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 2, 0);
	_right_top->setFPS(1);
}

jumpState::~jumpState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void jumpState::enter()
{
	//cout << "jumpState enter()" << endl;
	_player->setImage("player jump");
	SOUNDMANAGER->play("pS jump", 0.1f);

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		_top->start();
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		_right_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		_right->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		_right_top->start();
		break;
	}
}

void jumpState::update()
{
	_player->playerJumpMove();
	//cout << "jumpState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);

		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);

		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);

		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);

		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);

		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);

		break;
	}
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
}

void jumpState::exit()
{
	//cout << "jumpState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();
	SOUNDMANAGER->stop("pS jump");
}

// =========================== 플레이어 가드 =========================== //
guardState::guardState(player * player)
{
	_player = player;

	int top[] = { 0,1,2 };
	_top = new animation;
	_top->init(288, 768, 96, 96);
	_top->setPlayFrame(top, 3, true);
	_top->setFPS(1);

	int rtop[] = { 3,4,5 };
	_right_top = new animation;
	_right_top->init(288, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 3, true);
	_right_top->setFPS(1);

	int right[] = { 6,7,8 };
	_right = new animation;
	_right->init(288, 768, 96, 96);
	_right->setPlayFrame(right, 3, true);
	_right->setFPS(1);

	int rbottom[] = { 9,10,11 };
	_right_bottom = new animation;
	_right_bottom->init(288, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 3, true);
	_right_bottom->setFPS(1);

	int bottom[] = { 12,13,14 };
	_bottom = new animation;
	_bottom->init(288, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 3, true);
	_bottom->setFPS(1);

	int ltop[] = { 15,16,17 };
	_left_top = new animation;
	_left_top->init(288, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 3, true);
	_left_top->setFPS(1);

	int left[] = { 18,19,20 };
	_left = new animation;
	_left->init(288, 768, 96, 96);
	_left->setPlayFrame(left, 3, true);
	_left->setFPS(1);

	int lbottom[] = { 21,22,23 };
	_left_bottom = new animation;
	_left_bottom->init(288, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 3, true);
	_left_bottom->setFPS(1);
}

guardState::~guardState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void guardState::enter()
{
//	cout << "guardState enter()" << endl;
	_player->setImage("player guard");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);

		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);

		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);

		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);

		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);

		break;
	}
	_player->getAnimation()->start();
}

void guardState::update()
{
	//cout << "guardState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	if (!_player->getAnimation()->isPlay())
	{
		_player->getAnimation()->start();
	}
}

void guardState::exit()
{
	//cout << "guardState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();
}

// =========================== 플레이어 회피 =========================== //
dodgeState::dodgeState(player * player)
{
	_player = player;

	int right[] = { 0,1,2,3,4,5,6,7,8 };
	_right = new animation;
	_right->init(711, 696, 79, 87);
	_right->setPlayFrame(right, 9, 0);
	_right->setFPS(1);

	int rtop[] = { 9,10,11,12,13,14,15,16,17 };
	_right_top = new animation;
	_right_top->init(711, 696, 79, 87);
	_right_top->setPlayFrame(rtop, 9, 0);
	_right_top->setFPS(1);

	int top[] = { 18,19,20,21,22,23,24,25,26 };
	_top = new animation;
	_top->init(711, 696, 79, 87);
	_top->setPlayFrame(top, 9, 0);
	_top->setFPS(1);

	int ltop[] = { 27,28,29,30,31,32,33,34,35 };
	_left_top = new animation;
	_left_top->init(711, 696, 79, 87);
	_left_top->setPlayFrame(ltop, 9, 0);
	_left_top->setFPS(1);

	int left[] = { 36,37,38,39,40,41,42,43,44 };
	_left = new animation;
	_left->init(711, 696, 79, 87);
	_left->setPlayFrame(left, 9, 0);
	_left->setFPS(1);

	int lbottom[] = { 45,46,47,48,49,50,51,52,53 };
	_left_bottom = new animation;
	_left_bottom->init(711, 696, 79, 87);
	_left_bottom->setPlayFrame(lbottom, 9, 0);
	_left_bottom->setFPS(1);

	int bottom[] = { 54,55,56,57,58,59,60,61,62 };
	_bottom = new animation;
	_bottom->init(711, 696, 79, 87);
	_bottom->setPlayFrame(bottom, 9, 0);
	_bottom->setFPS(1);

	int rbottom[] = { 63,64,65,66,67,68,69,70,71 };
	_right_bottom = new animation;
	_right_bottom->init(711, 696, 79, 87);
	_right_bottom->setPlayFrame(rbottom, 9, 0);
	_right_bottom->setFPS(1);
}

dodgeState::~dodgeState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void dodgeState::enter()
{
//	cout << "dodgeState enter()" << endl;
	_player->setImage("player dodge");
	SOUNDMANAGER->play("pS dodge", 0.5f);

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);

		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
}

void dodgeState::update()
{
	//cout << "dodgeState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	_player->playerDodge();
	if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 30);
}

void dodgeState::exit()
{
	//cout << "dodgeState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();
	SOUNDMANAGER->stop("pS dodge");
}

// =========================== 플레이어 원거리 공격 =========================== //
longAttackState::longAttackState(player * player)
{
	_player = player;

	int top[] = { 0,1,2,3,4,5,6,7,8 };
	_top = new animation;
	_top->init(1581, 720, 93, 90);
	_top->setPlayFrame(top, 9, 0);
	_top->setFPS(2);

	int rtop[] = { 17,18,19,20,21,22,23,24,25 };
	_right_top = new animation;
	_right_top->init(1581, 720, 93, 90);
	_right_top->setPlayFrame(rtop, 9, 0);
	_right_top->setFPS(2);

	int right[] = { 34,35,36,37,38,39,40,41,42 };
	_right = new animation;
	_right->init(1581, 720, 93, 90);
	_right->setPlayFrame(right, 9, 0);
	_right->setFPS(2);

	int rbottom[] = { 51,52,53,54,55,56,57,58,59 };
	_right_bottom = new animation;
	_right_bottom->init(1581, 720, 93, 90);
	_right_bottom->setPlayFrame(rbottom, 9, 0);
	_right_bottom->setFPS(2);

	int bottom[] = { 68,69,70,71,72,73,74,75,76 };
	_bottom = new animation;
	_bottom->init(1581, 720, 93, 90);
	_bottom->setPlayFrame(bottom, 9, 0);
	_bottom->setFPS(2);

	int lbottom[] = { 101,100,99,98,97,96,95,94,93 };
	_left_bottom = new animation;
	_left_bottom->init(1581, 720, 93, 90);
	_left_bottom->setPlayFrame(lbottom, 9, 0);
	_left_bottom->setFPS(2);

	int left[] = { 118,117,116,115,114,113,112,111,110 };
	_left = new animation;
	_left->init(1581, 720, 93, 90);
	_left->setPlayFrame(left, 9, 0);
	_left->setFPS(2);

	int ltop[] = { 135,134,133,132,131,130,129,128,127 };
	_left_top = new animation;
	_left_top->init(1581, 720, 93, 90);
	_left_top->setPlayFrame(ltop, 9, 0);
	_left_top->setFPS(2);
}

longAttackState::~longAttackState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_right_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_right);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_left_bottom);
}

void longAttackState::enter()
{
	float angle = getAngle(_player->getPosition().x, _player->getPosition().y,
		_ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left,
		_ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top);

	for (int i = 0; i < 8; i++)
	{
		float min = PI / 2 - PI / 8 + PI / 4 * i;
		float max = PI / 2 + PI / 8 + PI / 4 * i;

		if (min > PI2)
		{
			min -= PI2;
		}
		if (max > PI2)
		{
			max -= PI2;
		}

		if (angle > min && angle <= max && i != 6)
		{
			_player->setDirection((PLAYERDIRECTION)i);
		}
		else if (((angle <= PI2 && angle > min) || (angle >= 0 && angle <= max)) && i == 6)
		{
			_player->setDirection((PLAYERDIRECTION)i);
		}
	}

	//cout << "longAttackState enter()" << endl;
	_player->setImage("player longAttack");
	_count = 0;
	_isLongAttack = true;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
	{
		if (_isAttack == false)
		{
			int top[] = { 0,1,2,3,4,5,6,7,8 };
			_top->setPlayFrame(top, 9, false);
			_player->setAnimation(_top);
			_player->getAnimation()->start();
		}
	}
	break;
	case PLAYERDIRECTION::RIGHT_TOP:
	{
		if (_isAttack == false)
		{
			int rtop[] = { 17,18,19,20,21,22,23,24,25 };
			_right_top->setPlayFrame(rtop, 9, false);
			_player->setAnimation(_right_top);
			_player->getAnimation()->start();
		}
	}
	break;
	case PLAYERDIRECTION::RIGHT:
	{
		if (_isAttack == false)
		{
			int right[] = { 34,35,36,37,38,39,40,41,42 };
			_right->setPlayFrame(right, 9, false);
			_player->setAnimation(_right);
			_player->getAnimation()->start();
		}
	}
	break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
	{
		if (_isAttack == false)
		{
			int rbottom[] = { 51,52,53,54,55,56,57,58,59 };
			_right_bottom->setPlayFrame(rbottom, 9, false);
			_player->setAnimation(_right_bottom);
			_player->getAnimation()->start();
		}
	}
	break;
	case PLAYERDIRECTION::BOTTOM:
	{
		if (_isAttack == false)
		{
			int bottom[] = { 68,69,70,71,72,73,74,75,76 };
			_bottom->setPlayFrame(bottom, 9, false);
			_player->setAnimation(_bottom);
			_player->getAnimation()->start();
		}
	}
	break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
	{
		if (_isAttack == false)
		{
			int lbottom[] = { 101,100,99,98,97,96,95,94,93 };
			_left_bottom->setPlayFrame(lbottom, 9, false);
			_player->setAnimation(_left_bottom);
			_player->getAnimation()->start();
		}
	}
	break;
	case PLAYERDIRECTION::LEFT:
	{
		if (_isAttack == false)
		{
			int left[] = { 118,117,116,115,114,113,112,111,110 };
			_left->setPlayFrame(left, 9, false);
			_player->setAnimation(_left);
			_player->getAnimation()->start();
		}
	}
	break;
	case PLAYERDIRECTION::LEFT_TOP:
	{
		if (_isAttack == false)
		{
			int ltop[] = { 135,134,133,132,131,130,129,128,127 };
			_left_top->setPlayFrame(ltop, 9, false);
			_player->setAnimation(_left_top);
			_player->getAnimation()->start();
		}
	}
	break;
	}
}

void longAttackState::update()
{
	//cout << "longAttackState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		longAttack(_top, 10, true);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		longAttack(_right_top, 27, true);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		longAttack(_right, 44, true);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		longAttack(_right_bottom, 61, true);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		longAttack(_bottom, 78, true);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		longAttack(_left_bottom, 92, false);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		longAttack(_left, 109, false);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		longAttack(_left_top, 126, false);
		break;
	}
	_player->playerLongAttackMove();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
}

void longAttackState::exit()
{
	//cout << "longAttackState exit()" << endl;
	_top->stop();
	_left->stop();
	_right->stop();
	_bottom->stop();
	_left_top->stop();
	_right_top->stop();
	_left_bottom->stop();
	_right_bottom->stop();
	SOUNDMANAGER->stop("pS lattack");
}

void longAttackState::longAttack(animation* anim, int a, bool b)
{
	_count++;

	if (_player->getAnimation()->isPlay() == false && !_isAttack)
	{
		if (_count > 1)
		{
			_isAttack = true;
			_isLongAttack = false;
		}
	}
	if (_isAttack == true && _isLongAttack == true)
	{
		_isLeft = _isLeft == false ? true : false;

		if (_isLeft == true)
		{
			if (b == true)
			{
				anim->setPlayFrame(a, a + 3, false);
			}
			else
			{
				anim->setPlayFrame(a, a - 3, false);
			}
			_player->setAnimation(anim);
			_player->getAnimation()->start();
			_count = 0;
			_isLongAttack = false;
		}

		else if (_isLeft == false)
		{

			if (b == true)
			{
				anim->setPlayFrame(a + 4, a + 7, false);
			}
			else
			{
				anim->setPlayFrame(a - 4, a - 7, false);
			}

			_player->setAnimation(anim);
			_player->getAnimation()->start();
			_count = 0;
			_isLongAttack = false;
		}
	}
	if (_count > 30 && _player->getAnimation()->isPlay() == false)			// 원거리공격 텀?
	{
		_isAttack = false;
		_isLeft = false;
	}
}

// =========================== 플레이어 원거리 조준 무브 =========================== //
longAttackMoveState::longAttackMoveState(player * player)
{
	_player = player;

	int top[] = { 2,3,4,5,6 };
	_top = new animation;
	_top->init(672, 768, 96, 96);
	_top->setPlayFrame(top, 5, true);
	_top->setFPS(1);

	int rtop[] = { 9,10,11,12,13 };
	_right_top = new animation;
	_right_top->init(672, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 5, true);
	_right_top->setFPS(1);

	int right[] = { 16,17,18,19,20 };
	_right = new animation;
	_right->init(672, 768, 96, 96);
	_right->setPlayFrame(right, 5, true);
	_right->setFPS(1);

	int rbottom[] = { 23,24,25,26,27 };
	_right_bottom = new animation;
	_right_bottom->init(672, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 5, true);
	_right_bottom->setFPS(1);

	int bottom[] = { 30,31,32,33,34 };
	_bottom = new animation;
	_bottom->init(672, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 5, true);
	_bottom->setFPS(1);

	int ltop[] = { 39,38,37,36,35 };
	_left_top = new animation;
	_left_top->init(672, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 5, true);
	_left_top->setFPS(1);

	int left[] = { 46,45,44,43,42 };
	_left = new animation;
	_left->init(672, 768, 96, 96);
	_left->setPlayFrame(left, 5, true);
	_left->setFPS(1);

	int lbottom[] = { 53,52,51,50,49 };
	_left_bottom = new animation;
	_left_bottom->init(672, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 5, true);
	_left_bottom->setFPS(1);
}

longAttackMoveState::~longAttackMoveState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_right_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_right);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_left_bottom);
}

void longAttackMoveState::enter()
{
//	cout << "longAttackMoveState enter()" << endl;
	_player->setImage("player longAttackMove");
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
}

void longAttackMoveState::update()
{
	//cout << "longAttackMoveState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	_player->playerLongAttackMove();
	if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void longAttackMoveState::exit()
{
	//cout << "longAttackMoveState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();
}

// =========================== 플레이어 이동후 정지모션 =========================== //
movestopState::movestopState(player * player)
{
	_player = player;

	int top[] = { 9,10,11,1 };
	_top = new animation;
	_top->init(1152, 768, 96, 96);
	_top->setPlayFrame(top, 4, false);
	_top->setFPS(1);

	int rtop[] = { 21,22,23,13 };
	_right_top = new animation;
	_right_top->init(1152, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 4, false);
	_right_top->setFPS(1);

	int right[] = { 33,34,35,25 };
	_right = new animation;
	_right->init(1152, 768, 96, 96);
	_right->setPlayFrame(right, 4, false);
	_right->setFPS(1);

	int rbottom[] = { 45,46,47,37 };
	_right_bottom = new animation;
	_right_bottom->init(1152, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 4, false);
	_right_bottom->setFPS(1);

	int bottom[] = { 57,58,59,49 };
	_bottom = new animation;
	_bottom->init(1152, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 4, false);
	_bottom->setFPS(1);

	int ltop[] = { 62,61,60,70 };
	_left_top = new animation;
	_left_top->init(1152, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 4, false);
	_left_top->setFPS(1);

	int left[] = { 74,73,72,82 };
	_left = new animation;
	_left->init(1152, 768, 96, 96);
	_left->setPlayFrame(left, 4, false);
	_left->setFPS(1);

	int lbottom[] = { 86,85,84,94 };
	_left_bottom = new animation;
	_left_bottom->init(1152, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 4, false);
	_left_bottom->setFPS(1);
}

movestopState::~movestopState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void movestopState::enter()
{
	//cout << "movestopState enter()" << endl;
	_player->setImage("p");
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		_top->start();
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		_right_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		_right_top->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		_right->start();
		break;
	default:
		break;
	}
}

void movestopState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	//if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void movestopState::exit()
{
	//cout << "movestopState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_top->stop();
	_right->stop();
	_right_bottom->stop();
}

// =========================== 플레이어 근거리 오른손공격 =========================== //
rightattackState::rightattackState(player * player)
{
	_player = player;

	int top[] = { 16,24,32,0,8 };
	_top = new animation;
	_top->init(768, 672, 96, 96);
	_top->setPlayFrame(top, 5, false);
	_top->setFPS(2);

	int ltop[] = { 23,31,39,7,15 };
	_left_top = new animation;
	_left_top->init(768, 672, 96, 96);
	_left_top->setPlayFrame(ltop, 5, false);
	_left_top->setFPS(2);

	int left[] = { 22,30,38,6,14 };
	_left = new animation;
	_left->init(768, 672, 96, 96);
	_left->setPlayFrame(left, 5, false);
	_left->setFPS(2);

	int lbottom[] = { 21,29,37,5,13 };
	_left_bottom = new animation;
	_left_bottom->init(768, 672, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 5, false);
	_left_bottom->setFPS(2);

	int bottom[] = { 20,28,36,4,12 };
	_bottom = new animation;
	_bottom->init(768, 672, 96, 96);
	_bottom->setPlayFrame(bottom, 5, false);
	_bottom->setFPS(2);

	int rbottom[] = { 19,27,35,3,11 };
	_right_bottom = new animation;
	_right_bottom->init(768, 672, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 5, false);
	_right_bottom->setFPS(2);

	int right[] = { 18,26,34,2,10 };
	_right = new animation;
	_right->init(768, 672, 96, 96);
	_right->setPlayFrame(right, 5, false);
	_right->setFPS(2);

	int rtop[] = { 17,25,33,1,9 };
	_right_top = new animation;
	_right_top->init(768, 672, 96, 96);
	_right_top->setPlayFrame(rtop, 5, false);
	_right_top->setFPS(2);
}

rightattackState::~rightattackState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void rightattackState::enter()
{
	vector <gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);
	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);
		if (e->getEnemyCollision())
		{
			e->setEnemyCollision(false);
		}
	}

	//cout << "rightattackState enter()" << endl;
	_player->setImage("p_meleeattack_right");
	SOUNDMANAGER->play("pS mattack", 0.6f);

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		_top->start();
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		_right_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		_right_top->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		_right->start();
		break;
	default:
		break;
	}
}

void rightattackState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	_player->playermeleeattackMove();
	//if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void rightattackState::exit()
{
	//cout << "rightattackState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_top->stop();
	_right->stop();
	_right_bottom->stop();
	_player->setAttackRC(0, 0);
	SOUNDMANAGER->stop("pS mattack");
}

// =========================== 플레이어 근거리 왼손공격 =========================== //
leftattackState::leftattackState(player * player)
{
	_player = player;
	int top[] = { 23,31,39,7,15 };
	_top = new animation;
	_top->init(768, 672, 96, 96);
	_top->setPlayFrame(top, 5, false);
	_top->setFPS(2);

	int ltop[] = { 22,30,38,6,14 };
	_left_top = new animation;
	_left_top->init(768, 672, 96, 96);
	_left_top->setPlayFrame(ltop, 5, false);
	_left_top->setFPS(2);

	int left[] = { 21,29,37,5,13 };
	_left = new animation;
	_left->init(768, 672, 96, 96);
	_left->setPlayFrame(left, 5, false);
	_left->setFPS(2);

	int lbottom[] = { 20,28,36,4,12 };
	_left_bottom = new animation;
	_left_bottom->init(768, 672, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 5, false);
	_left_bottom->setFPS(2);

	int bottom[] = { 19,27,35,3,11 };
	_bottom = new animation;
	_bottom->init(768, 672, 96, 96);
	_bottom->setPlayFrame(bottom, 5, false);
	_bottom->setFPS(2);

	int rbottom[] = { 18,26,34,2,10 };
	_right_bottom = new animation;
	_right_bottom->init(768, 672, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 5, false);
	_right_bottom->setFPS(2);

	int right[] = { 17,25,33,1,9 };
	_right = new animation;
	_right->init(768, 672, 96, 96);
	_right->setPlayFrame(right, 5, false);
	_right->setFPS(2);

	int rtop[] = { 16,24,32,0,8 };
	_right_top = new animation;
	_right_top->init(768, 672, 96, 96);
	_right_top->setPlayFrame(rtop, 5, false);
	_right_top->setFPS(2);
}

leftattackState::~leftattackState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void leftattackState::enter()
{
	vector <gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);
	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);
		if (e->getEnemyCollision())
		{
			e->setEnemyCollision(false);
		}
	}
	SOUNDMANAGER->play("pS mattack", 0.6f);
	//cout << "leftattackState enter()" << endl;
	_player->setImage("p_meleeattack_left");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		_top->start();
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		_right_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		_right_top->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		_right->start();
		break;
	default:
		break;
	}
}

void leftattackState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	_player->playermeleeattackMove();
	//if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void leftattackState::exit()
{
//	cout << "leftattackState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_top->stop();
	_right->stop();
	_right_bottom->stop();
	_player->setAttackRC(0, 0);
	SOUNDMANAGER->stop("pS mattack");
}

// =========================== 플레이어 근거리 마지막공격 =========================== //
rightfinalattackState::rightfinalattackState(player * player)
{
	
	_player = player;

	int top[] = { 47,46,45,44,43,42,41,40,48,0,8 };
	_top = new animation;
	_top->init(768, 672, 96, 96);
	_top->setPlayFrame(top, 11, false);
	_top->setFPS(2);

	int ltop[] = { 46,45,44,43,42,41,40,47,55,7,15 };
	_left_top = new animation;
	_left_top->init(768, 672, 96, 96);
	_left_top->setPlayFrame(ltop, 11, false);
	_left_top->setFPS(2);

	int left[] = { 45,44,43,42,41,40,47,46,54,6,14 };
	_left = new animation;
	_left->init(768, 672, 96, 96);
	_left->setPlayFrame(left, 11, false);
	_left->setFPS(2);

	int lbottom[] = { 44,43,42,41,40,47,46,45,53,5,13 };
	_left_bottom = new animation;
	_left_bottom->init(768, 672, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 11, false);
	_left_bottom->setFPS(2);

	int bottom[] = { 43,42,41,40,47,46,45,44,52,4,12 };
	_bottom = new animation;
	_bottom->init(768, 672, 96, 96);
	_bottom->setPlayFrame(bottom, 11, false);
	_bottom->setFPS(2);

	int rbottom[] = { 42,41,40,47,46,45,44,43,51,3,11 };
	_right_bottom = new animation;
	_right_bottom->init(768, 672, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 11, false);
	_right_bottom->setFPS(2);

	int right[] = { 41,40,47,46,45,44,43,42,50,2,10 };
	_right = new animation;
	_right->init(768, 672, 96, 96);
	_right->setPlayFrame(right, 11, false);
	_right->setFPS(2);

	int rtop[] = { 40,47,46,45,44,43,42,41,49,1,9 };
	_right_top = new animation;
	_right_top->init(768, 672, 96, 96);
	_right_top->setPlayFrame(rtop, 11, false);
	_right_top->setFPS(2);
}


rightfinalattackState::~rightfinalattackState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void rightfinalattackState::enter()
{
	vector <gameObject*> temp = OBJECTMANAGER->getObjectList(objectType::ENEMY);
	for (int i = 0; i < temp.size(); i++)
	{
		enemy* e = dynamic_cast<enemy*>(temp[i]);
		if (e->getEnemyCollision())
		{
			e->setEnemyCollision(false);
		}
	}
	//cout << "rightfinalattackState enter()" << endl;
	SOUNDMANAGER->play("pS mattackf", 0.6f);
	_player->setImage("p_meleeattack_right");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		_top->start();
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		_right_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		_right_top->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		_right->start();
		break;
	default:
		break;
	}
}

void rightfinalattackState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	_player->playerfinalattackMove();
	//if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void rightfinalattackState::exit()
{
	//cout << "rightfinalattackState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_top->stop();
	_right->stop();
	_right_bottom->stop();
	_player->setAttackRC(0, 0);
	SOUNDMANAGER->stop("pS mattackf");
}

longAttackIdleState::longAttackIdleState(player * player)
{
	_player = player;

	int top[] = {0,1};
	_top = new animation;
	_top->init(672, 768, 96, 96);
	_top->setPlayFrame(top, 2, true);
	_top->setFPS(1);

	int rtop[] = { 7,8 };
	_right_top = new animation;
	_right_top->init(672, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 2, true);
	_right_top->setFPS(1);

	int right[] = { 14,15 };
	_right = new animation;
	_right->init(672, 768, 96, 96);
	_right->setPlayFrame(right, 2, true);
	_right->setFPS(1);

	int rbottom[] = { 21,22 };
	_right_bottom = new animation;
	_right_bottom->init(672, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 2, true);
	_right_bottom->setFPS(1);

	int bottom[] = { 28,29 };
	_bottom = new animation;
	_bottom->init(672, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 2, true);
	_bottom->setFPS(1);

	int ltop[] = { 41,40 };
	_left_top = new animation;
	_left_top->init(672, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 2, true);
	_left_top->setFPS(1);

	int left[] = { 48,47 };
	_left = new animation;
	_left->init(672, 768, 96, 96);
	_left->setPlayFrame(left, 2, true);
	_left->setFPS(1);

	int lbottom[] = { 55,54 };
	_left_bottom = new animation;
	_left_bottom->init(672, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 2, true);
	_left_bottom->setFPS(1);
}

longAttackIdleState::~longAttackIdleState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_right);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_left);
	SAFE_DELETE(_right_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_left_bottom);
}

void longAttackIdleState::enter()
{
	//cout << "longAttackIdleState enter()" << endl;

	_player->setImage("player longAttackMove");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);

		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);

		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);

		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);

		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);

		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
}

void longAttackIdleState::update()
{
	//cout << "longAttackIdleState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

}

void longAttackIdleState::exit()
{
	_top->stop();
	_right->stop();
	_bottom->stop();
	_left->stop();
	_right_top->stop();
	_left_top->stop();
	_right_bottom->stop();
	_left_bottom->stop();
}

lethalchargeState::lethalchargeState(player * player)
{
	_player = player;

	int top[] = { 0,1,2,3,4,5 };
	_top = new animation;
	_top->init(576, 768, 96, 96);
	_top->setPlayFrame(top, 6, false);
	_top->setFPS(1);

	int rtop[] = { 6,7,8,9,10,11 };
	_right_top = new animation;
	_right_top->init(576, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 6, false);
	_right_top->setFPS(1);

	int right[] = { 12,13,14,15,16,17 };
	_right = new animation;
	_right->init(576, 768, 96, 96);
	_right->setPlayFrame(right, 6, false);
	_right->setFPS(1);

	int rbottom[] = { 18,19,20,21,22,23 };
	_right_bottom = new animation;
	_right_bottom->init(576, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 6, false);
	_right_bottom->setFPS(1);

	int bottom[] = { 24,25,26,27,28,29 };
	_bottom = new animation;
	_bottom->init(576, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 6, false);
	_bottom->setFPS(1);

	int ltop[] = { 30,31,32,33,34,35 };
	_left_top = new animation;
	_left_top->init(576, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 6, false);
	_left_top->setFPS(1);

	int left[] = { 36,37,38,39,40,41 };
	_left = new animation;
	_left->init(576, 768, 96, 96);
	_left->setPlayFrame(left, 6, false);
	_left->setFPS(1);

	int lbottom[] = { 42,43,44,45,46,47 };
	_left_bottom = new animation;
	_left_bottom->init(576, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 6, false);
	_left_bottom->setFPS(1);
}

lethalchargeState::~lethalchargeState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void lethalchargeState::enter()
{
	_player->setImage("player charge");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	}
}

void lethalchargeState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void lethalchargeState::exit()
{
	_top->stop();
	_right->stop();
	_bottom->stop();
	_left->stop();
	_right_top->stop();
	_left_top->stop();
	_right_bottom->stop();
	_left_bottom->stop();
}

lethalattackState::lethalattackState(player * player)
{
	_player = player;

	int top[] = { 47,46,45,44,43,42,41,40,48,0,8,47,46,45,44,43,42,41,40,48,0,8 };
	_top = new animation;
	_top->init(768, 672, 96, 96);
	_top->setPlayFrame(top, 22, false);
	_top->setFPS(3);

	int ltop[] = { 46,45,44,43,42,41,40,47,55,7,15,46,45,44,43,42,41,40,47,55,7,15 };
	_left_top = new animation;
	_left_top->init(768, 672, 96, 96);
	_left_top->setPlayFrame(ltop, 22, false);
	_left_top->setFPS(3);

	int left[] = { 45,44,43,42,41,40,47,46,54,6,14,45,44,43,42,41,40,47,46,54,6,14 };
	_left = new animation;
	_left->init(768, 672, 96, 96);
	_left->setPlayFrame(left, 22, false);
	_left->setFPS(3);

	int lbottom[] = { 44,43,42,41,40,47,46,45,53,5,13,44,43,42,41,40,47,46,45,53,5,13 };
	_left_bottom = new animation;
	_left_bottom->init(768, 672, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 22, false);
	_left_bottom->setFPS(3);

	int bottom[] = { 43,42,41,40,47,46,45,44,52,4,12,43,42,41,40,47,46,45,44,52,4,12 };
	_bottom = new animation;
	_bottom->init(768, 672, 96, 96);
	_bottom->setPlayFrame(bottom, 22, false);
	_bottom->setFPS(3);

	int rbottom[] = { 42,41,40,47,46,45,44,43,51,3,11,42,41,40,47,46,45,44,43,51,3,11 };
	_right_bottom = new animation;
	_right_bottom->init(768, 672, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 22, false);
	_right_bottom->setFPS(3);

	int right[] = { 41,40,47,46,45,44,43,42,50,2,10,41,40,47,46,45,44,43,42,50,2,10 };
	_right = new animation;
	_right->init(768, 672, 96, 96);
	_right->setPlayFrame(right, 22, false);
	_right->setFPS(3);

	int rtop[] = { 40,47,46,45,44,43,42,41,49,1,9,40,47,46,45,44,43,42,41,49,1,9 };
	_right_top = new animation;
	_right_top->init(768, 672, 96, 96);
	_right_top->setPlayFrame(rtop, 22, false);
	_right_top->setFPS(3);
}

lethalattackState::~lethalattackState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void lethalattackState::enter()
{
	_player->setImage("p_meleeattack_right");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		_top->start();
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		_right_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		_right_top->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		_right->start();
		break;
	default:
		break;
	}
}

void lethalattackState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	default:
		break;
	}
	_player->playerLethalattackMove();
	//if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void lethalattackState::exit()
{
	_top->stop();
	_right->stop();
	_bottom->stop();
	_left->stop();
	_right_top->stop();
	_left_top->stop();
	_right_bottom->stop();
	_left_bottom->stop();
	_player->setAttackRC(0, 0);
}

beAttackedState::beAttackedState(player * player)
{
	_player = player;

	int top[] = { 0,1 };
	_top = new animation;
	_top->init(192, 768, 96, 96);
	_top->setPlayFrame(top, 2, false);
	_top->setFPS(1);

	int rtop[] = { 2,3 };
	_right_top = new animation;
	_right_top->init(192, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 2, false);
	_right_top->setFPS(1);

	int right[] = { 4,5 };
	_right = new animation;
	_right->init(192, 768, 96, 96);
	_right->setPlayFrame(right, 2, false);
	_right->setFPS(1);

	int rbottom[] = { 6,7 };
	_right_bottom = new animation;
	_right_bottom->init(192, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 2, false);
	_right_bottom->setFPS(1);

	int bottom[] = { 8,9 };
	_bottom = new animation;
	_bottom->init(192, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 2, false);
	_bottom->setFPS(1);

	int ltop[] = { 10,11 };
	_left_top = new animation;
	_left_top->init(192, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 2, false);
	_left_top->setFPS(1);

	int left[] = { 12,13 };
	_left = new animation;
	_left->init(192, 768, 96, 96);
	_left->setPlayFrame(left, 2, false);
	_left->setFPS(1);

	int lbottom[] = { 13,14 };
	_left_bottom = new animation;
	_left_bottom->init(192, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 2, false);
	_left_bottom->setFPS(1);
}

beAttackedState::~beAttackedState()
{
	SAFE_DELETE(_top);
	SAFE_DELETE(_left_top);
	SAFE_DELETE(_left);
	SAFE_DELETE(_left_bottom);
	SAFE_DELETE(_bottom);
	SAFE_DELETE(_right_bottom);
	SAFE_DELETE(_right);
	SAFE_DELETE(_right_top);
}

void beAttackedState::enter()
{
	_player->setImage("player beAttacked");

	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		_top->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		_right_top->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		_right->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		_right_bottom->start();
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	}

	if (_player->getPlayerHP() <= 0)
	{
		cout << "죽엇따" << endl;
		CAMERA->zoomStart(2.0f, 1.0f, false);
		iPlayerDead* move = new iPlayerDead();
		EVENTMANAGER->addEvent(move);
	}
}

void beAttackedState::update()
{
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	}
	//if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void beAttackedState::exit()
{
	_top->stop();
	_right->stop();
	_bottom->stop();
	_left->stop();
	_right_top->stop();
	_left_top->stop();
	_right_bottom->stop();
	_left_bottom->stop();
}
