#pragma once
#include "enemy.h"

class buffalo : public enemy
{
private:
	image* _enemyAnimationImage;
	image* _attackImage;
	image* _hitImage;

	animation* _attackPrepareMotion_L;//공격준비 애니메이션
	animation* _attackPrepareMotion_R;//공격준비 애니메이션
	animation* _attackPrepareMotion_U_L;
	animation* _attackPrepareMotion_U_R;
	animation* _attackPrepareMotion_D_L;
	animation* _attackPrepareMotion_D_R;

	animation* _meleeAttackMotion_L;
	animation* _meleeAttackMotion_R;
	animation* _meleeAttackMotion_U_L;
	animation* _meleeAttackMotion_U_R;
	animation* _meleeAttackMotion_D_L;
	animation* _meleeAttackMotion_D_R;

	float _attackSpeed;
	float d;
	float an;

	bool _oneAnimation;//애니메이션을 한번만 실행시키기 위한 변수
	bool _wallCollision;//버팔로가 벽에 돌진공격으로 부딪혔는지 여부 확인용

public:
	buffalo() {};
	~buffalo() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animationDraw();
	void animationControl();
	void tileGet();
	void mapOutCollision();//에너미들이 맵밖으로 나가지 못하게 하기위한 함수
	bool tileMove();
};

