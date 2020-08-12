#pragma once
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

	bool _long;
	int _count;
public:
	virtual ~playerState() {};

public:
	virtual void enter() {};
	virtual void update() {};
	virtual void exit() {};

	//inline bool longAttack() { return _long; }
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

class defaltLongAttackState : public playerState
{
public:
	defaltLongAttackState(class player* player);
	~defaltLongAttackState();

	void enter() override;
	void update() override;
	void exit() override;
};
