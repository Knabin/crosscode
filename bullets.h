#pragma once
#include "gameObject.h"

struct tagBullet
{
	image* image;
	floatRect rc;
	Vector2 position;
	Vector2 firePosition;
	float angle;
	float speed;
	int currentFrameX, currentFrameY;
	int count;
};

class bullets : public gameObject
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;

public:
	bullets() {};
	~bullets() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle, float speed);
	void move();
	void remove(int num);

	vector<tagBullet> getvEnemyBullet() { return _vBullet; }
	vector<tagBullet>::iterator getviEnemyBullet() { return _viBullet; }
};

