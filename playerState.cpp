#include "stdafx.h"
#include "playerState.h"

void idleState::enter()
{
	cout << "idleState enter()" << endl;
}

void idleState::update()
{
	cout << "idleState update()" << endl;
}

void idleState::exit()
{
	cout << "idleState exit()" << endl;
}

void moveState::enter()
{
	cout << "moveState enter()" << endl;
}

void moveState::update()
{
	cout << "moveState update()" << endl;
}

void moveState::exit()
{
	cout << "moveState exit()" << endl;
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
