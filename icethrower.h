#pragma once
#include "gameObject.h"

struct tagIcethrower
{
	image* _image;

	floatRect _rc;

	float _x, _y;
	float _angle;
	float _speed;
	float _size;
	
	bool _fireStart;
};

class icethrower : public gameObject
{
private:

	vector<tagIcethrower>				_vIcethrower;
	vector<tagIcethrower>::iterator		_viIcethrower;

	image* _attackImage[3];				// 발사 시 제각각 사이즈가 다른 이미지를 구현하기 위해
	float  _attackSize[3];				// 발사 렌더 생성시 제각각 이미지의 사이즈에 맞추기 위해

	floatPoint _center;
	floatPoint _centerEnd;
	floatPoint _centerEnd2;
	float _centerMeter;
	float _centerMeter2;
	float _angle;						//얼음 발사 시 각도
	float _angle2;						//얼음 발사 총구 이펙트 각도

	int _currentFrameX, _currentFrameY;
	int _frameCount;

	int _iceEffectFrameX, _iceEffectFrameY;		

public:

	icethrower();
	~icethrower();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire();
	void move();
	void removeFire(int Num1);

	vector<tagIcethrower>& getIcethrowerVector() { return _vIcethrower; }
	vector<tagIcethrower>::iterator& getIcethrowerIterVector() { return _viIcethrower; }


};

