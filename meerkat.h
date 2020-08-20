#pragma once
#include "enemy.h"

class meerkat : public enemy
{
private:
	class bullets* _bullet;

	image* _meerkatMoveImage;//�̾�Ĺ ���� �̹���

	animation* _meerkatMoveMotion;//�̾�Ĺ�� �������� �� ���¿��� �����ϴ� �ִϸ��̼�
	animation* _meerkatTunnelDownMotion_L;//�̾�Ĺ�� �������� ���� �ִϸ��̼�
	animation* _meerkatTunnelDownMotion_R;
	animation* _meerkatTunnelUpMotion_L;//�̾�Ĺ�� ������ �ö󰡴� �ִϸ��̼�
	animation* _meerkatTunnelUpMotion_R;

	int _smallDistance;//ª�� �Ÿ��� ����
	int _bigDistance;//�հŸ��� ����
	int _reflectCount;//���� �ε��� Ƚ��
	int _meerkatSpeed;

	int _meerkatBallFrameX;
	int _meerkatBallFrameY;

	bool _isMove;//�÷��̾�� �Ÿ��� ����ﶧ �ݴ�������� �̵���Ű�� ���� �ʿ��� ����
	bool _isBigMove;//�÷��̾�� �̾�Ĺ�� �Ÿ��� �ʹ� �ְ�� �̾�Ĺ�� �÷��̾� ��ó�� �Ѿƿ��� �ϱ� ���� ����
	bool _reflect;//�̾�Ĺ�� ���� �ε����� ���� �ݴ������� �̵���Ű�� ���� �ʿ��� ����
	bool _oneAnimation;//�ִϸ��̼��� �ѹ��� �����Ű�� ���� ����

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animationControl();
	void tileGet();//Ÿ����ġ ��������
	void ballTileGet();//�̾�Ĺ�� ��Ÿ����ġ ��������
	void mapOutCollision();//���ʹ̵��� �ʹ����� ������ ���ϰ� �ϱ����� �Լ�
	bool ballTileMove();//��Ÿ�� ����
	bool tileMove();//���ʹ��� Ÿ�Ϲ���

	bullets* getBullets() { return _bullet; }
};

