#pragma once
#include "gameObject.h"
#include "icethrower.h"
#include "mine.h"
#include "stoneshower.h"
#include "flamethrower.h"
#include "iceguide.h"

enum bossState //���� �������� enum��
{
	APPEARANCE = 0,
	STOP,
	ICETHROWER_READY,
	ICETHROWER_READY2,
	ICETHROWER,
	ICETHROWER_END,
	MINE_READY,
	MINE_READY2,
	MINE,
	MINE_END,
	MINE_END2,
	STONESHOWER_READY,
	STONESHOWER_READY2,
	STONESHOWER_READY3,
	STONESHOWER,
	STONESHOWER_END,
	FLAMETHROWER_READY,
	FLAMETHROWER_READY2,
	FLAMETHROWER_READY3,
	FLAMETHROWER_READY4,
	FLAMETHROWER,
	FLAMETHROWER_END,
	FLAMETHROWER_END2,
	FLAMETHROWER_END3,
	ICEGUIDE_READY,
	ICEGUIDE_READY2,
	ICEGUIDE,
	ICEGUIDE_END

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
	stoneshower* _stoneshower;
	flamethrower* _flamethrower;
	iceguide* _iceguide;

	image* image;
	bossState _bossState;		//���� ����

	tagBossPart _Center;		//����

	tagBossPart _LeftArm;		//����
	tagBossPart _RightArm;		//������

	tagBossPart _LeftHand;		//�޼�
	tagBossPart _RightHand;		//������


	tagBossPart _Bottom;		//����

	//���� ���� ������
	int _currentFrameX, _currentFrameY;
	int _frameCount;
	int _bossLeftHandAttackFrameX, _bossLeftHandAttackFrameY;
	int _bossCenterMoveFrameX, _bossCenterMoveFrameY;
	int _bossRightHandAttackFrameX, _bossRightHandAttackFrameY;
	int _bossRightHandAttackFrameX2, _bossRightHandAttackFrameY2;
	int _bossLeftHandMoveFrameX, _bossLeftHandMoveFrameY;
	int _bossLeftHandMoveFrameX2, _bossLeftHandMoveFrameY2;
	int _bossLeftHandAttackFrameX2, _bossLeftHandAttackFrameY2;

	int _centerMoveFrameX, _centerMoveFrameY;
	int _centerFrameCount;
	int _centerCurrentFrameX, _centerCurrentFrameY;

	//���� �� ������
	int _protectCurrentFrameX, _protectCurrentFrameY;
	int _protectFrameCount;
	int _bossShieldOneFrameX, _bossShieldOneFrameY;

	int _moveCount;  //�����̰� �������� ī��Ʈ

	int _chargeCount; //�����Ҷ��� ī��Ʈ

	int _stopCount;  // ��� ���������� ī��Ʈ


	//������ ������
	int _motionDelay;

	//������� ���� ������
	int _icethrowerDelay;

	//���� �߻� ������
	int _mineAttackDelay;

	//���� �߻� ������
	int _stoneAttackDelay;

	//ȭ����� ���� ������
	int _flamethrowerDelay;

	//�������� ���� ������
	int _iceguideDelay;


	bool _attack1, _attack2, _attack3, _attack4, _attack5;

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

	void bossInitialization();	//���� stop�� ��ġ Ȯ�ο�

	
};


