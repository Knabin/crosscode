#pragma once
class playerState
{
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
	void enter() override;
	void update() override;
	void exit() override;
};

class moveState : public playerState
{
public:
	void enter() override;
	void update() override;
	void exit() override;
};

class jumpState : public playerState
{
public:
	void enter() override;
	void update() override;
	void exit() override;
};