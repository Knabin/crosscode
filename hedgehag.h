#pragma once
#include "enemy.h"

class hedgehag : public enemy
{
private:
	float _attackSpeed;//공격중에 움직이는 스피드
	bool _effect;//공격상태에서 제자리에 있을때 실행할 이펙트의 조건을 위한 변수
	POINT nextTileIndex;//현재 에너미 위치에서 근처에 장애물 위치를 파악할 타일


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void move();//에너미 무브
	void animationControl();//에너미 애니메이션 컨트롤
	void animationAngleControl();//에너미와 플레이어간에 앵글값에 따른 애니메이션
	void tileGet();//타일위치 가져오기
	bool tileMove();//에너미의 타일무브
};

