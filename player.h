#pragma once
#include "gameObject.h"

class player : public gameObject
{
public:
	player();
	virtual ~player();

	void init() override;
	void release() override;
	void update() override;
	void render() override;

	void move(vector2 moveDirection, float speed);
	void move(float angle, float speed);
};

