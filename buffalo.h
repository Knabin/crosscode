#pragma once
#include "enemy.h"

class buffalo : public enemy
{
private:
	float _idleMoveSpeed;

public:
	buffalo() {};
	~buffalo() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animationControl();
	void animationAngleControl();
	void tileGet();
	void tileMove();
};

