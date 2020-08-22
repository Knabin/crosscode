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
	float _damage;

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

	vector<tagIceguide>				_vIceguide4;
	vector<tagIceguide>::iterator	_viIceguide4;

	vector<tagIceguide>				_vIceguide5;
	vector<tagIceguide>::iterator	_viIceguide5;


	floatPoint _center;
	float _centerMeter;
	floatPoint _centerEnd, _centerEnd2, _centerEnd3, _centerEnd4, _centerEnd5;
	float _angle, _angle2, _angle3, _angle4, _angle5;
	int _meterCount, _meterCount2, _meterCount3, _meterCount4, _meterCount5;

	int _iceFrameY;


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
	void frameUpdate();

	void removeFire1(int Num1);
	void removeFire2(int Num2);
	void removeFire3(int Num3);
	void removeFire4(int Num4);
	void removeFire5(int Num5);

	vector<tagIceguide>& getIceguideVector() { return _vIceguide; }
	vector<tagIceguide>::iterator& getIceguideIterVector() { return _viIceguide; }

	vector<tagIceguide>& getIceguideVector2() { return _vIceguide2; }
	vector<tagIceguide>::iterator& getIceguideIterVector2() { return _viIceguide2; }

	vector<tagIceguide>& getIceguideVector3() { return _vIceguide3; }
	vector<tagIceguide>::iterator& getIceguideIterVector3() { return _viIceguide3; }

	vector<tagIceguide>& getIceguideVector4() { return _vIceguide4; }
	vector<tagIceguide>::iterator& getIceguideIterVector4() { return _viIceguide4; }

	vector<tagIceguide>& getIceguideVector5() { return _vIceguide5; }
	vector<tagIceguide>::iterator& getIceguideIterVector5() { return _viIceguide5; }


};

