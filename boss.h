#pragma once
#include "gameObject.h"
#include "icethrower.h"

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
	CENTER_ATTACK_READY,
	CENTER_ATTACK,
	CENTER_ATTACK_END,
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

	int _motionDelay;

	int _mineAttackCount;

	//�� ������
	int _bossShieldOneFrameX, _bossShieldOneFrameY;

	//�޼հ���1 ������
	int _bossLeftHandAttackFrameX, _bossLeftHandAttackFrameY;

	int _icethrowerDelay;


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

	void fireCollision();

};


