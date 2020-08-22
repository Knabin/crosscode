#pragma once
#include "enemy.h"

class hedgehag : public enemy
{
private:
	float _attackSpeed;//�����߿� �����̴� ���ǵ�
	bool _effect;//���ݻ��¿��� ���ڸ��� ������ ������ ����Ʈ�� ������ ���� ����

	Vector2 _currentTileSave;
	tile* _currentTile;

	int _angleCount;
	int _jumpSoundCount;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void move();//���ʹ� ����
	void animationControl();//���ʹ� �ִϸ��̼� ��Ʈ��
	void animationAngleControl();//���ʹ̿� �÷��̾�� �ޱ۰��� ���� �ִϸ��̼�
	void tileGet();//Ÿ����ġ ��������
	void currentTileGet();//���� ���ʹ��� Ÿ����ġ
	void mapOutCollision();//���ʹ̵��� �ʹ����� ������ ���ϰ� �ϱ����� �Լ�
	bool tileMove();//���ʹ��� Ÿ�Ϲ���
};

