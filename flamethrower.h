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
	float _damage;

	int _frameX;
	int _frameCount;
	int _currentFrameX;

	bool _fireStart;
};

class flamethrower : public gameObject
{
private:

	//ȭ����� ����
	vector<tagFlamethrower>				_vFlamethrower;
	vector<tagFlamethrower>::iterator   _viFlamethrower;

	//ȭ���ѱ� ����Ʈ ����
	vector<tagFlamethrower>				_vFlameEffect;
	vector<tagFlamethrower>::iterator   _viFlameEffect;

	//ȭ����� �߻�
	floatPoint _center;			
	floatPoint _centerEnd;
	float _centerMeter;
	float _angle;


	//ȭ���ѱ� ����Ʈ �߻�
	floatPoint _centerEnd2;
	float _centerMeter2;
	float _angle2;

	//ȭ���߻� ����Ʈ
	int _flameFrameY;

	//ȭ���ѱ�����Ʈ 
	int _firePointFrameY;

	//��������Ʈ ī��Ʈ
	int _chargeCurrentFrameX, _chargeCurrentFrameY;
	int _chargeCurrentFrameX2, _chargeCurrentFrameY2;
	int _chargeFrameCount, _chargeFrameCount2;
	int _chargeFrameX, _chargeFrameY;
	int _chargeFrameX2, _chargeFrameY2;

	//�������� �ٲ��ִ� ī��Ʈ?
	int _angleCount;


public:

	flamethrower();
	~flamethrower();

	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render();

	void angleUpdate();
	void frameUpdate();
	void fire();
	void move();

	//��������Ʈ ����
	void chargeDraw(float centerX, float centerY);
	void chargeDraw2(float centerX, float centerY);

	void removeFire(int Num5);

	vector<tagFlamethrower>& getFlameVector() { return _vFlamethrower; }
	vector<tagFlamethrower>::iterator& getFlameIterVector() { return _viFlamethrower; }

	vector<tagFlamethrower>& getFlameEffectVector() { return _vFlameEffect; }
	vector<tagFlamethrower>::iterator& getFlameEffectIterVector() { return _viFlameEffect; }

};

