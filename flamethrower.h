#pragma once
#include "gameObject.h"

struct tagFlamethrower
{
	image* _image;

	floatRect _rc;

	float _x, _y;
	float _angle;
	float _speed;
	float _size;

	bool _fireStart;
};

class flamethrower : public gameObject
{
private:

	vector<tagFlamethrower>				_vFlamethrower;
	vector<tagFlamethrower>::iterator   _viFlamethrower;

	floatPoint _center;
	floatPoint _centerEnd;
	float _centerMeter;

	int _currentFrameX, _currentFrameY;
	int _frameCount;


public:

	flamethrower();
	~flamethrower();

	HRESULT init();
	void release();
	void update();
	void render();

	void angleUpdate();
	void fire();
	void move();



};

