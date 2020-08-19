#pragma once
#include "gameObject.h"

struct tagPlayerBullet
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

class bullet : public gameObject
{
private:
	vector<tagPlayerBullet>			  _vPlayerBullet;
	vector<tagPlayerBullet>::iterator _viPlayerBullet;

	float _range;
	float _alpha;
	bool _isAlpha;

public:
	bullet() {};
	~bullet() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle, float speed);
	void nomalFire(float x, float y, float angle, float speed);
	void move();
	void remove(int arrNum);
	
	vector<tagPlayerBullet> getVPlayerBullet() { return _vPlayerBullet; }
	vector<tagPlayerBullet>::iterator getViPlayerBullet() { return _viPlayerBullet; }
};

