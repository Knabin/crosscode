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

	//���� �߻�
	vector<tagMine>						_vMine;
	vector<tagMine>::iterator			_viMine;

	//���� �߻�
	vector<tagMine>                     _vMine2;
	vector<tagMine>::iterator			_viMine2;

	float _centerMeter;
	float _angle;

	// �߻� �� ����Ǵ� ��ǥ ���� ����
	float _randomDropX, _randomDropY, _randomDropX2, _randomDropY2, _randomDropX3, _randomDropY3, _randomDropX4, _randomDropY4, _randomDropX5, _randomDropY5, _randomDropX6, _randomDropY6;

	int _currentFrameX, _currentFrameY;
	int _frameCount;

	int _mineCurrentFrameX, _mineCurrentFrameY;
	int _mineFrameCount;

	int _mineFrameX, _mineFrameY;
	int _explosionFrameX, _explosionFrameY;

public:

	mine();
	~mine();

	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render(float centerX, float centerY);

	void frameUpdate();   //����, ���� ������
	void fire();			//����, �߻�
	void move();			//���� �߻� �� ������

	vector<tagMine>& getMineVector() { return _vMine; }
	vector<tagMine>::iterator& getMineIterVector() { return _viMine; }

	vector<tagMine>& getMine2Vector() { return _vMine2; }
	vector<tagMine>::iterator& getMine2IterVector() { return _viMine2; }
};

