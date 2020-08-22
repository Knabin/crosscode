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
	float _damage;
	
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

	int _angleCount;

	int _currentFrameX, _currentFrameY;
	int _frameCount;
	//int _collisionCurrentFrameX, _collisionCurrentFrameY;
	//int _collisionFrameCount;

	int _iceEffectFrameX, _iceEffectFrameY;		
	int _collisionFrameX, _collisionFrameY;


public:

	icethrower();
	~icethrower();

	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render();

	void angleUpdate();		//���� �� ������Ʈ
	void frameUpdate();		//���� ������ ������Ʈ
	void fire();			//���� �߻�
	void move();			//���� �߻� �� ������
	void removeFire(int Num1); //���� �߻� �� ����

	vector<tagIcethrower>& getIcethrowerVector() { return _vIcethrower; }
	vector<tagIcethrower>::iterator& getIcethrowerIterVector() { return _viIcethrower; }

};

