#include "stdafx.h"
#include "playerState.h"
#include "player.h"

idleState::idleState(player * player)
{
	_player = player;

	int top[] = { 1 };
	_top = new animation;
	_top->init(768, 912, 48, 48);
	_top->setPlayFrame(top, 1, 0);

	int ltop[] = { 17 };
	_left_top = new animation;
	_left_top->init(768, 912, 48, 48);
	_left_top->setPlayFrame(ltop, 1, 0);

	int left[] = { 33 };
	_left = new animation;
	_left->init(768, 912, 48, 48);
	_left->setPlayFrame(left, 1, 0);

	int lbottom[] = { 49 };
	_left_bottom = new animation;
	_left_bottom->init(768, 912, 48, 48);
	_left_bottom->setPlayFrame(lbottom, 1, 0);

	int bottom[] = { 65 };
	_bottom = new animation;
	_bottom->init(768, 912, 48, 48);
	_bottom->setPlayFrame(bottom, 1, 0);

	//int rbottom[] = {}
	//_right_bottom = new animation;
	//_right_bottom->init(1536, 1824, 16, 19);

	//_right = new animation;
	//_right->init(1536, 1824, 16, 19);

	//_right_top = new animation;
	//_right_top->init(1536, 1824, 16, 19);
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

		break;
	case PLAYERDIRECTION::LEFT:

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	default:
		break;
	}
}

void idleState::update()
{
	cout << "idleState update()" << endl;
	switch (_player->getDirection())
	{
	case PLAYERDIRECTION::TOP:
		_player->setAnimation(_top);
		break;
	case PLAYERDIRECTION::LEFT_TOP:

		break;
	case PLAYERDIRECTION::LEFT:

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_left_bottom);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_left);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_left_top);
		break;
	default:
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
	//_right_bottom->stop();
	//_right->stop();
	//_right_top->stop();
}

moveState::moveState(player * player)
{
	_player = player;

	int top[] = { 3, 4, 5, 6, 7, 8 };
	_top = new animation;
	_top->init(768, 912, 48, 48);
	_top->setPlayFrame(top, 6, true);
	_top->setFPS(1);

	int ltop[] = { 19, 20, 21, 22, 23, 24 };
	_left_top = new animation;
	_left_top->init(768, 912, 48, 48);
	_left_top->setPlayFrame(ltop, 6, true);
	_left_top->setFPS(1);

	int left[] = { 35, 36, 37, 38, 39, 40 };
	_left = new animation;
	_left->init(768, 912, 48, 48);
	_left->setPlayFrame(left, 6, true);
	_left->setFPS(1);

	int lbottom[] = { 51, 52, 53, 54, 55, 56 };
	_left_bottom = new animation;
	_left_bottom->init(768, 912, 48, 48);
	_left_bottom->setPlayFrame(lbottom, 6, true);
	_left_bottom->setFPS(1);

	int bottom[] = { 67, 68, 69, 70, 71, 72 };
	_bottom = new animation;
	_bottom->init(768, 912, 48, 48);
	_bottom->setPlayFrame(bottom, 6, true);
	_bottom->setFPS(1);
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

		break;
	case PLAYERDIRECTION::LEFT:

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_left_bottom->start();
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_left);
		_left->start();
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_left_top);
		_left_top->start();
		break;
	default:
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
		_player->move(0, -1);
		break;
	case PLAYERDIRECTION::LEFT_TOP:

		break;
	case PLAYERDIRECTION::LEFT:

		break;
	case PLAYERDIRECTION::LEFT_BOTTOM:

		break;
	case PLAYERDIRECTION::BOTTOM:
		_player->setAnimation(_bottom);
		_player->move(0, 1);
		break;
	case PLAYERDIRECTION::RIGHT_BOTTOM:
		_player->setAnimation(_left_bottom);
		_player->moveAngle(PI2 - PI * 0.25, 1);
		break;
	case PLAYERDIRECTION::RIGHT:
		_player->setAnimation(_left);
		_player->move(1, 0);
		break;
	case PLAYERDIRECTION::RIGHT_TOP:
		_player->setAnimation(_left_top);
		_player->moveAngle(PI * 0.25, 1);
		break;
	default:
		break;
	}
	if (!_player->getAnimation()->isPlay()) _player->getAnimation()->start();
	_player->getAnimation()->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void moveState::exit()
{
	cout << "moveState exit()" << endl;
}

jumpState::jumpState(player * player)
{
	_player = player;
}

void jumpState::enter()
{
	cout << "jumpState enter()" << endl;
}

void jumpState::update()
{
	cout << "jumpState update()" << endl;
}

void jumpState::exit()
{
	cout << "jumpState exit()" << endl;
}
