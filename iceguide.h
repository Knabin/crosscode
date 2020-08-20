#pragma once
#include "gameObject.h"

struct tagIceguide
{
	image * _image;

	floatRect _rc;

	float _x, _y;
	float _angle;
	float _speed;
	float _size;

	int _frameX;
	int _frameCount;
	int _currentFrameX;

	bool _fireStart;
};

class iceguide : public gameObject
{
private:

	vector<tagIceguide>				_vIceguide;
	vector<tagIceguide>::iterator	_viIceguide;

	vector<tagIceguide>				_vIceguide2;
	vector<tagIceguide>::iterator	_viIceguide2;

	vector<tagIceguide>				_vIceguide3;
	vector<tagIceguide>::iterator	_viIceguide3;


	floatPoint _center;
	floatPoint _centerEnd;
	float _centerMeter;
	float _angle;
	float _angle2;


	int _meterCount;

public:

	iceguide();
	~iceguide();

	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render();

	void fire();
	void move();

	void angleUpdate();

	vector<tagIceguide>& getIceguideVector() { return _vIceguide; }
	vector<tagIceguide>::iterator& getIceguideIterVector() { return _viIceguide; }

	vector<tagIceguide>& getIceguideVector2() { return _vIceguide2; }
	vector<tagIceguide>::iterator& getIceguideIterVector2() { return _viIceguide2; }

	vector<tagIceguide>& getIceguideVector3() { return _vIceguide3; }
	vector<tagIceguide>::iterator& getIceguideIterVector3() { return _viIceguide3; }


};

