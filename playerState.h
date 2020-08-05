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

public:
	virtual ~playerState() {};

public:
	virtual void enter() {};
	virtual void update() {};
	virtual void exit() {};
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
	void enter() override;
	void update() override;
	void exit() override;
};

class jumpState : public playerState
{
public:
	jumpState(class player* player);

	void enter() override;
	void update() override;
	void exit() override;
};