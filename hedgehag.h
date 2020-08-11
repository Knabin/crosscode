#pragma once
#include "enemy.h"

class hedgehag : public enemy
{
private:
	float _attackSpeed;//�����߿� �����̴� ���ǵ�
	bool _effect;//���ݻ��¿��� ���ڸ��� ������ ������ ����Ʈ�� ������ ���� ����

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void move();//���ʹ� ����
	void animationControl();//���ʹ� �ִϸ��̼� ��Ʈ��
	void animationAngleControl();//���ʹ̿� �÷��̾�� �ޱ۰��� ���� �ִϸ��̼�
};

