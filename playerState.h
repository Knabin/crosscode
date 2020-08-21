#pragma once
#include "animation.h"

class playerState
{
protected:
	class player* _player;

	animation* _top;
	animation* _left_top;
	animation* _left;
	animation* _left_bottom;
	animation* _bottom;
	animation* _right_bottom;
	animation* _right;
	animation* _right_top;

	bool _isLongAttack;
	bool _isAttack;
	bool _isLeft;
	int _count;

	float _aMovespeed = 2.0f;

public:
	virtual ~playerState() {};

public:
	virtual void enter() {};
	virtual void update() {};
	virtual void exit() {};

	inline bool isAttack() { return _isAttack; }
	inline bool isLongAttack() { return _isLongAttack; }
	virtual void setLongAttack() { _isLongAttack = true; }
};

class idleState : public playerState
{
public:
	idleState(class player* player);
	~idleState();

	void enter() override;
	void update() override;
	void exit() override;
};

class moveState : public playerState
{
public:
	moveState(class player* player);
	~moveState();

	void enter() override;
	void update() override;
	void exit() override;
};

class jumpState : public playerState
{
public:
	jumpState(class player* player);
	~jumpState();

	void enter() override;
	void update() override;
	void exit() override;
};

class guardState : public playerState
{
public:
	guardState(class player* player);
	~guardState();

	void enter() override;
	void update() override;
	void exit() override;
};

class dodgeState : public playerState
{
public:
	dodgeState(class player* player);
	~dodgeState();

	void enter() override;
	void update() override;
	void exit() override;
};

class longAttackState : public playerState
{
public:
	longAttackState(class player* player);
	~longAttackState();

	void enter() override;
	void update() override;
	void exit() override;
	void longAttack(animation* anim, int a, bool b);
};

class longAttackIdleState : public playerState
{
public:
	longAttackIdleState(class player* player);
	~longAttackIdleState();

	void enter() override;
	void update() override;
	void exit() override;
};

class longAttackMoveState : public playerState
{
public:
	longAttackMoveState(class player* player);
	~longAttackMoveState();

	void enter() override;
	void update() override;
	void exit() override;
};

class movestopState : public playerState
{
public:
	movestopState(class player* player);
	~movestopState();

	void enter() override;
	void update() override;
	void exit() override;
};

class rightattackState : public playerState
{
public:
	rightattackState(class player* player);
	~rightattackState();

	void enter() override;
	void update() override;
	void exit() override;

};

class leftattackState : public playerState
{
public:
	leftattackState(class player* player);
	~leftattackState();

	void enter() override;
	void update() override;
	void exit() override;

};

class rightfinalattackState : public playerState
{
public:
	rightfinalattackState(class player* player);
	~rightfinalattackState();

	void enter() override;
	void update() override;
	void exit() override;
};

class lethalchargeState : public playerState
{
public:
	lethalchargeState(class player* player);
	~lethalchargeState();

	void enter() override;
	void update() override;
	void exit() override;

};

class lethalattackState : public playerState
{
public:
	lethalattackState(class player* player);
	~lethalattackState();

	void enter() override;
	void update() override;
	void exit() override;
};

class beAttackedState : public playerState
{
public:
	beAttackedState(class player* player);
	~beAttackedState();

	void enter() override;
	void update() override;
	void exit() override;
};