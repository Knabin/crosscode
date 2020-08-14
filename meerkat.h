#pragma once
#include "enemy.h"
class meerkat : public enemy
{
private:
	image* _meerkatMoveImage;//미어캣 무브 이미지

	animation* _meerkatMoveMotion;
	
	int _smallDistance;//짧은 거리값 기준
	int _bigDistance;//먼거리값 기준

	bool _isMove;//플레이어와 거리가 가까울때 반대방향으로 이동시키기 위해 필요한 변수

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animationControl();
	void animationAngleControl();
	void tileGet();//타일위치 가져오기
	bool tileMove();//에너미의 타일무브
};

