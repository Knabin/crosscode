#pragma once
#include "gameObject.h"

struct tagStoneshower
{
	image* _image;

	floatRect _rc;

	float _x, _y;
	float _angle;
	float _speed;
	float _size;

	bool _fireStart;

};

class stoneshower : public gameObject
{
private:

	vector<tagStoneshower>				_vStoneshower;
	vector<tagStoneshower>::iterator	_viStoneshower;

	vector<tagStoneshower>				_vDust;
	vector<tagStoneshower>::iterator    _viDust;


	int _currentFrameX, _currentFrameY;
	int _frameCount;

	int _dustFrameX, _dustFrameY;


public:

	stoneshower();
	~stoneshower();


	HRESULT init();
	void release();
	void update();
	void render(float centerX, float centerY);

	void dustDraw(float centerX, float centerY);

	void dustTrue(int Num2);		//먼지 이미지 On
	void dustFalse(int Num3);		//먼지 이미지 Off


	vector<tagStoneshower>& getDustVector() { return _vDust; }
	vector<tagStoneshower>::iterator& getDustIterVector() { return _viDust; }

};

