#include "stdafx.h"
#include "playerState.h"
#include "player.h"

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
	cout << "idleState enter()" << endl;

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
	cout << "idleState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();
}

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

void moveState::enter()
{
	cout << "moveState enter()" << endl;

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

void moveState::update()
{
	cout << "moveState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		//_player->move(0, -8.0f);
		break;
	case PLAYERDIRECTION::LEFT_TOP:
		_player->setAnimation(_left_top);
		//_player->moveAngle(PI * 0.75f, 8.0f);
		break;
	case PLAYERDIRECTION::LEFT:
		_player->setAnimation(_left);
		//_player->move(-8.0f, 0);
		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:
		_player->setAnimation(_left_bottom);
		//_player->moveAngle(PI * 1.25f, 8.0f);
		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		//_player->move(0, 8.0f);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_right_bottom);
		//_player->moveAngle(PI2 - PI * 0.25, 8.0f);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_right);
		//_player->move(8.0f, 0);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_right_top);
		//_player->moveAngle(PI * 0.25, 8.0f);
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
	cout << "moveState exit()" << endl;
	_top->stop();
	_left_top->stop();
	_left->stop();
	_left_bottom->stop();
	_bottom->stop();
	_right_bottom->stop();
	_right->stop();
	_right_top->stop();
}

jumpState::jumpState(player * player)
{
	_player = player;


	int top[] = { 0, 1 };
	_top = new animation;
	_top->init(192, 768, 96, 96);
	_top->setPlayFrame(top, 2, 0);

	int ltop[] = { 10, 11 };
	_left_top = new animation;
	_left_top->init(192, 768, 96, 96);
	_left_top->setPlayFrame(ltop, 2, 0);

	int left[] = { 12, 13 };
	_left = new animation;
	_left->init(192, 768, 96, 96);
	_left->setPlayFrame(left, 2, 0);

	int lbottom[] = { 14, 15 };
	_left_bottom = new animation;
	_left_bottom->init(192, 768, 96, 96);
	_left_bottom->setPlayFrame(lbottom, 1, 0);

	int bottom[] = { 8, 9 };
	_bottom = new animation;
	_bottom->init(192, 768, 96, 96);
	_bottom->setPlayFrame(bottom, 2, 0);

	int rbottom[] = { 6, 7 };
	_right_bottom = new animation;
	_right_bottom->init(192, 768, 96, 96);
	_right_bottom->setPlayFrame(rbottom, 2, 0);

	int right[] = { 4, 5 };
	_right = new animation;
	_right->init(192, 768, 96, 96);
	_right->setPlayFrame(right, 2, 0);

	int rtop[] = { 2, 3 };
	_right_top = new animation;
	_right_top->init(192, 768, 96, 96);
	_right_top->setPlayFrame(rtop, 2, 0);
}

void jumpState::enter()
{
	cout << "jumpState enter()" << endl;
	_player->setImage("player jump");

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
	cout << "jumpState update()" << endl;
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
}

void jumpState::exit()
{
	cout << "jumpState exit()" << endl;
}