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
	float _damage;

	floatPoint _center;
	floatPoint _centerEnd;

	bool _fireStart;

};

class stoneshower : public gameObject
{
private:

	vector<tagStoneshower>				_vStoneshower;
	vector<tagStoneshower>::iterator	_viStoneshower;

	vector<tagStoneshower>				_vDust;
	vector<tagStoneshower>::iterator    _viDust;

	float _centerMeter;
	float _angle;

	int _currentFrameX, _currentFrameY;
	int _frameCount;

	int _dustFrameX, _dustFrameY;


public:

	stoneshower();
	~stoneshower();


	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render();

	void dustDraw(float centerX, float centerY); // 먼지 Render

	void frameUpdate();				//먼지, 바위 프레임 업데이트
	void fire();					//바위 발사
	void move();					//바위 발사 후 움직임

	//boss 클래스 참조용
	void dustTrue(int Num2);		//먼지 이미지 On
	void dustFalse(int Num3);		//먼지 이미지 Off

	void removeFire(int Num4);		//바위 발사 후 삭제

	
	vector<tagStoneshower>& getStoneVector() { return _vStoneshower; }
	vector<tagStoneshower>::iterator& getStoneIterVector() { return _viStoneshower; }

	vector<tagStoneshower>& getDustVector() { return _vDust; }
	vector<tagStoneshower>::iterator& getDustIterVector() { return _viDust; }

};

