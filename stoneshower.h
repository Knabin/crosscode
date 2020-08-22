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

	void dustDraw(float centerX, float centerY); // ���� Render

	void frameUpdate();				//����, ���� ������ ������Ʈ
	void fire();					//���� �߻�
	void move();					//���� �߻� �� ������

	//boss Ŭ���� ������
	void dustTrue(int Num2);		//���� �̹��� On
	void dustFalse(int Num3);		//���� �̹��� Off

	void removeFire(int Num4);		//���� �߻� �� ����

	
	vector<tagStoneshower>& getStoneVector() { return _vStoneshower; }
	vector<tagStoneshower>::iterator& getStoneIterVector() { return _viStoneshower; }

	vector<tagStoneshower>& getDustVector() { return _vDust; }
	vector<tagStoneshower>::iterator& getDustIterVector() { return _viDust; }

};

