#pragma once
#include "enemy.h"

class buffalo : public enemy
{
private:
	image* _enemyAnimationImage;
	image* _attackImage;
	image* _hitImage;

	animation* _attackPrepareMotion_L;//�����غ� �ִϸ��̼�
	animation* _attackPrepareMotion_R;//�����غ� �ִϸ��̼�
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

	bool _oneAnimation;//�ִϸ��̼��� �ѹ��� �����Ű�� ���� ����
	bool _wallCollision;//���ȷΰ� ���� ������������ �ε������� ���� Ȯ�ο�

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
	void mapOutCollision();//���ʹ̵��� �ʹ����� ������ ���ϰ� �ϱ����� �Լ�
	bool tileMove();
};

