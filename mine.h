#pragma once
#include "gameObject.h"


struct tagMine
{
	image * _image;

	floatRect _rc;

	float _x, _y;
	float _angle;
	float _speed;
	floatPoint _center;
	floatPoint _centerEnd;

	bool _fireStart;

};

class mine : public gameObject
{
private:

	//좌측 발사
	vector<tagMine>						_vMine;
	vector<tagMine>::iterator			_viMine;

	//우측 발사
	vector<tagMine>                     _vMine2;
	vector<tagMine>::iterator			_viMine2;

	float _centerMeter;
	float _angle;

	// 발사 시 드랍되는 좌표 랜덤 설정
	float _randomDropX, _randomDropY, _randomDropX2, _randomDropY2, _randomDropX3, _randomDropY3, _randomDropX4, _randomDropY4, _randomDropX5, _randomDropY5, _randomDropX6, _randomDropY6;

	int _currentFrameX, _currentFrameY;
	int _frameCount;

	int _explosionFrameX, _explosionFrameY;

public:

	mine();
	~mine();

	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render(float centerX, float centerY);

	void fire();
	void move();


};

