#pragma once
#include "gameObject.h"
#include "icethrower.h"
#include "mine.h"
#include "stoneshower.h"
#include "flamethrower.h"
#include "iceguide.h"

enum bossState //보스 상태패턴 enum문
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

struct tagBossPart  //보스 파츠별 구조체
{
	image* _bossBodyImage;
	floatRect _rectBody;

	floatRect _rectBody2;

	float _x, _y;
	float _speed;


	//현재의 이미지회전은 이미지의 가운데를 중점으로 회전하고 있습니다. 그래서
	//가상의 렉트1개와 선을 생성 후 선 끝 부분에 이미지를 렌더 해줍니다. 
	//선언해 둔 각도값 대로 이미지가 아닌 선 끝 부분만 회전을 시키면
	//이미지가 360도 원을 그리면서 이동합니다. 동시에
	//이때 선언해둔 또 다른 각도값으로 이미지 가운데 중점을 회전시켜주면~!

	float _angle;
	float _realAngle;	

	
	//위치 확인용에 필요한 선 그리기

	floatPoint _center;
	floatPoint _centerEnd;
	float _centerMeter;

};

class boss : public gameObject
{


private:

	//파괴 이펙트
	vector<tagEffect>				_vEffect;
	vector<tagEffect>::iterator	    _viEffect;

	//참조 클래스
	icethrower* _icethrower;
	mine* _mine;
	stoneshower* _stoneshower;
	flamethrower* _flamethrower;
	iceguide* _iceguide;

	image* image;
	bossState _bossState;		//상태 패턴

	tagBossPart _Center;		//몸통

	tagBossPart _LeftArm;		//왼팔
	tagBossPart _RightArm;		//오른팔

	tagBossPart _LeftHand;		//왼손
	tagBossPart _RightHand;		//오른손


	tagBossPart _Bottom;		//바텀

	//보스 전신 프레임
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


	//보스 방어막 프레임
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

	int _moveCount;  //움직이고 있을때의 카운트

	int _chargeCount; //충전할때의 카운트

	int _stopCount;  // 잠시 멈춰있을때 카운트

	int _stunCount; //스턴 걸렸을때 딜레이 카운트

	int _appearanceCount;

	//움직임 딜레이
	int _motionDelay;

	//얼음방사 공격 딜레이
	int _icethrowerDelay;

	//지뢰 발사 딜레이
	int _mineAttackDelay;

	//바위 발사 딜레이
	int _stoneAttackDelay;

	//화염방사 공격 딜레이
	int _flamethrowerDelay;

	//뾰족얼음 공격 딜레이
	int _iceguideDelay;

	//파괴 이펙트 딜레이
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


	void bossState();		//보스 현재 상태패턴 
	void bossMove();		//보스 실시간 움직임 
	void bossDraw();		//보스 전신 렌더 이미지
	void protectFrame();	//방어막 프레임 관리

	void moveUp();
	void moveDown();

	void effectFire();
	void effectMove();
	void effectFrame();
	void effectAngleMove();
	void effectDraw();

	void fireCollision();

	void bossInitialization();	//보스 stop후 위치 확인용
	void bossInitialization2();	//보스 stop후 위치 확인용

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
//렉트 접근
//
//
//
//
//		
	floatRect getRightHandRect() { return _RightHand._rectBody2; }
	floatRect getLeftHandRect() { return _LeftHand._rectBody2; }
	floatRect getBottomRect() { return _Bottom._rectBody; }

	
};





