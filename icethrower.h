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

	image* _attackImage[3];				// �߻� �� ������ ����� �ٸ� �̹����� �����ϱ� ����
	float  _attackSize[3];				// �߻� ���� ������ ������ �̹����� ����� ���߱� ����

	floatPoint _center;
	floatPoint _centerEnd;
	floatPoint _centerEnd2;
	float _centerMeter;
	float _centerMeter2;
	float _angle;						//���� �߻� �� ����
	float _angle2;						//���� �߻� �ѱ� ����Ʈ ����

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
