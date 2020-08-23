#pragma once
#include "gameObject.h"
#include "icethrower.h"
#include "mine.h"
#include "stoneshower.h"
#include "flamethrower.h"
#include "iceguide.h"

enum bossState //���� �������� enum��
{
	APPEARANCE_READY = 0,
	APPEARANCE,
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
	ICEGUIDE_END,
	STUN,
	STUN2,
	STUN3,
	STUN4,
	DEATH,
	DEATH2

};
struct tagEffect
{
	image* _image;

	floatRect _rc;

	float _x, _y;
	float _angle;
	float _speed;
	float _size;

	float _centerMeter;
	floatPoint _center;
	floatPoint _centerEnd;

	int _frameX;
	int _frameCount;
	int _currentFrameX;

	bool _fireStart;
};

struct tagBossPart  //���� ������ ����ü
{
	image* _bossBodyImage;
	floatRect _rectBody;

	floatRect _rectBody2;

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

	//�ı� ����Ʈ
	vector<tagEffect>				_vEffect;
	vector<tagEffect>::iterator	    _viEffect;

	//���� Ŭ����
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

	int _protectCurrentFrameX2, _protectCurrentFrameY2;
	int _protectFrameCount2;
	int _bossShieldOneFrameX2, _bossShieldOneFrameY2;

	int _protectCurrentFrameX3, _protectCurrentFrameY3;
	int _protectFrameCount3;
	int _bossShieldOneFrameX3, _bossShieldOneFrameY3;

	int _deathFrameY;

	int _moveCount;  //�����̰� �������� ī��Ʈ

	int _chargeCount; //�����Ҷ��� ī��Ʈ

	int _stopCount;  // ��� ���������� ī��Ʈ

	int _stunCount; //���� �ɷ����� ������ ī��Ʈ

	int _appearanceCount;

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

	//�ı� ����Ʈ ������
	int _effectDelay;

	int _stunDelay;

	bool _attack1, _attack2, _attack3, _attack4, _attack5;

	int _hp;
	int _bossMaxHp;

	bool _attackCollision;
	bool _stunTrue;

	floatRect _imagineWallRight;
	floatRect _imagineWallLeft;
	floatRect _imagineWallBottom;
	floatRect _imagineWallTop;


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
	void protectFrame();	//�� ������ ����

	void moveUp();
	void moveDown();

	void effectFire();
	void effectMove();
	void effectFrame();
	void effectAngleMove();
	void effectDraw();

	void fireCollision();

	void bossInitialization();	//���� stop�� ��ġ Ȯ�ο�
	void bossInitialization2();	//���� stop�� ��ġ Ȯ�ο�

	void hpManager();

	


	int getBossHp() { return _hp; }
	void setBossHp(int hp) { _hp = hp; }

	int getBossMaxHp() { return _bossMaxHp; }
	void setBossMaxHp(int Maxhp) { _bossMaxHp = Maxhp; }

	bool getBossCollision() { return _attackCollision;}
	void setBossCollision(bool attackCollision) { _attackCollision = attackCollision; }

	floatRect& getRightWall() { return _imagineWallRight; }
	floatRect& getLeftWall() { return _imagineWallLeft; }
	floatRect& getBottomWall() { return _imagineWallBottom; }
	floatRect& getTopWall() { return _imagineWallTop; }

	enum bossState getBossState() { return _bossState; }


							
///////////////////////////////////////////////////////////////
//��Ʈ ����
//
//
//
//
//		
	floatRect getRightHandRect() { return _RightHand._rectBody2; }
	floatRect getLeftHandRect() { return _LeftHand._rectBody2; }
	floatRect getBottomRect() { return _Bottom._rectBody; }

	
};





