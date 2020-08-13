#pragma once
#include "enemy.h"
class meerkat : public enemy
{
private:
	int _smallDistance;//ª�� �Ÿ��� ����
	int _bigDistance;//�հŸ��� ����

	bool _isMove;//�÷��̾�� �Ÿ��� ����ﶧ �ݴ�������� �̵���Ű�� ���� �ʿ��� ����

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animationControl();
	void animationAngleControl();
	void tileGet();//Ÿ����ġ ��������
	bool tileMove();//���ʹ��� Ÿ�Ϲ���
};

