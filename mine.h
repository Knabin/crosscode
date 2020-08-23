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

	float _damage;

	bool _fireStart;

};

class mine : public gameObject
{
private:

	player* _player;

	//ÁÂÃø ¹ß»ç
	vector<tagMine>						_vMine;
	vector<tagMine>::iterator			_viMine;

	//¿ìÃø ¹ß»ç
	vector<tagMine>                     _vMine2;
	vector<tagMine>::iterator			_viMine2;

	float _centerMeter;
	float _angle;

	// ¹ß»ç ½Ã µå¶øµÇ´Â ÁÂÇ¥ ·£´ý ¼³Á¤
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

	bool _isCollision3;
	bool _isCollision4;
	bool _isCollision5;
	bool _isCollision6;

	float _colAngle3;
	float _colAngle4;
	float _colAngle5;
	float _colAngle6;


	bool _dropTrue1;
	bool _dropTrue2;
	bool _dropTrue3;
	bool _dropTrue4;
	bool _dropTrue5;
	bool _dropTrue6;



public:

	mine();
	~mine();

	HRESULT init(float centerX, float centerY);
	void release();
	void update();
	void render(float centerX, float centerY);

	void frameUpdate();   //Áö·Ú, Æø¹ß ÇÁ·¹ÀÓ
	void fire();			//Áö·Ú, ¹ß»ç
	void move();			//Áö·Ú ¹ß»ç ÈÄ ¿òÁ÷ÀÓ
	void explotion(float centerX, float centerY);		//Æø¹ß ÀÌÆåÆ®

	void collision(float angle);  //Áö·Ú Ãæµ¹
	void collision2(float angle);  //Áö·Ú Ãæµ¹2
	void collision3(float angle);  //Áö·Ú Ãæµ¹3
	void collision4(float angle);  //Áö·Ú Ãæµ¹4
	void collision5(float angle);  //Áö·Ú Ãæµ¹5
	void collision6(float angle);  //Áö·Ú Ãæµ¹6

	void mineRemove(int Num1);
	void mineRemove2(int Num2);



	vector<tagMine>& getMineVector() { return _vMine; }
	vector<tagMine>::iterator& getMineIterVector() { return _viMine; }

	vector<tagMine>& getMine2Vector() { return _vMine2; }
	vector<tagMine>::iterator& getMine2IterVector() { return _viMine2; }

	void setCollision(bool col) { _isCollision = col; }
	void setCollision2(bool col2) { _isCollision2 = col2; }
	void setCollision3(bool col3) { _isCollision3 = col3; }
	void setCollision4(bool col4) { _isCollision4 = col4; }
	void setCollision5(bool col5) { _isCollision5 = col5; }
	void setCollision6(bool col6) { _isCollision6 = col6; }

	bool getCollision() { return _isCollision; }


	bool getDropTrue1() { return _dropTrue1; }
	bool getDropTrue2() { return _dropTrue2; }
	bool getDropTrue3() { return _dropTrue3; }
	bool getDropTrue4() { return _dropTrue4; }
	bool getDropTrue5() { return _dropTrue5; }
	bool getDropTrue6() { return _dropTrue6; }

};

