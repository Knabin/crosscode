#pragma once
class player
{
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

	void move(float angle, float speed);
};

