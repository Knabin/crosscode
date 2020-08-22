#pragma once
#include "gameObject.h"
#include "player.h"

struct tagMine
{
	image * _image;

	floatRect _rc;

	float _x, _y;
	float _angle;
	float _speed;
	float _speed2;
	floatPoint _center;
	floatPoint _centerEnd;

	bool _fireStart;

};

class mine : public gameObject
{
private:

	player* _player;

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

	int _mineCurrentFrameX, _mineCurrentFrameY;
	int _mineFrameCount;

	int _mineFrameX, _mineFrameY;
	int _explosionFrameX, _explosionFrameY;

	bool _isCollision;
	int _colNum;
	float _colAngle;

	bool _isCollision2;
	int _colNum2;
	float _colAngle2;

public:

	mine();
	~mine();

	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render(float centerX, float centerY);

	void frameUpdate();   //지뢰, 폭발 프레임
	void fire();			//지뢰, 발사
	void move();			//지뢰 발사 후 움직임
	void explotion(float centerX, float centerY);		//폭발 이펙트

	void collision(int Num1, float angle);  //지뢰 충돌
	void collision2(int Num2, float angle);  //지뢰 충돌2

	void mineRemove(int Num1);
	void mineRemove2(int Num2);

	vector<tagMine>& getMineVector() { return _vMine; }
	vector<tagMine>::iterator& getMineIterVector() { return _viMine; }

	vector<tagMine>& getMine2Vector() { return _vMine2; }
	vector<tagMine>::iterator& getMine2IterVector() { return _viMine2; }

	void setCollision(bool col) { _isCollision = col; }

};

