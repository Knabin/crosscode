#pragma once
#include "gameObject.h"
#include "icethrower.h"
#include "mine.h"

enum bossState //���� �������� enum��
{
	//======================================������ ���̿�======================================//

	APPEARANCE = 0,

	//======================================�̵��� ���̿�======================================//

	STOP,
	MOVEUP,
	MOVEDOWN,

	//======================================������ ���̿�======================================//

	ICETHROWER_READY1,
	ICETHROWER_READY2,
	ICETHROWER,
	ICETHROWER_END,
	MINE_READY,
	MINE_READY2,
	MINE,
	MINE_END,
	MINE_END2
};
struct tagBossPart  //���� ������ ����ü
{
	image* _bossBodyImage;
	floatRect _rectBody;

	float _x, _y;
	float _speed;


	//������ �̹���ȸ���� �̹����� ����� �������� ȸ���ϰ� �ֽ��ϴ�. �׷���
	//������ ��Ʈ1���� ���� ���� �� �� �� �κп� �̹����� ���� ���ݴϴ�. 
	//������ �� ������ ��� �̹����� �ƴ� �� �� �κи� ȸ���� ��Ű��
	//�̹����� 360�� ���� �׸��鼭 �̵��մϴ�. ���ÿ�
	//�̶� �����ص� �� �ٸ� ���������� �̹��� ��� ������ ȸ�������ָ�~!

	float _angle;
	float _realAngle;	

	
	//��ġ Ȯ�ο뿡 �ʿ��� �� �׸���

	floatPoint _center;
	floatPoint _centerEnd;
	float _centerMeter;
};

class boss : public gameObject
{


private:

	icethrower* _icethrower;
	mine* _mine;

	image* image;
	bossState _bossState;		//���� ����

	tagBossPart _Center;		//����

	tagBossPart _LeftArm;		//����
	tagBossPart _RightArm;		//������

	tagBossPart _LeftHand;		//�޼�
	tagBossPart _RightHand;		//������

	tagBossPart _Bottom;		//����

	int _currentFrameX, _currentFrameY;
	int _frameCount;

	int _protectCurrentFrameX, _protectCurrentFrameY;
	int _protectFrameCount;

	int _moveCount;


	//�� ������
	int _bossShieldOneFrameX, _bossShieldOneFrameY;

	//�޼հ���1 ������
	int _bossLeftHandAttackFrameX, _bossLeftHandAttackFrameY;

	//��������� ������
	int _bossCenterMoveFrameX, _bossCenterMoveFrameY;

	//������ ������
	int _motionDelay;

	//������� ���� ������
	int _icethrowerDelay;

	int _mineAttackCount;


public:

	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();


	void bossState();		//���� ���� �������� 
	void bossMove();		//���� �ǽð� ������ 
	void bossDraw();		//���� ���� ���� �̹���

	void moveUp();
	void moveDown();

	void fireCollision();

};


