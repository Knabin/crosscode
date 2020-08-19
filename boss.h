#pragma once
#include "gameObject.h"
#include "icethrower.h"
#include "mine.h"
#include "stoneshower.h"
#include "flamethrower.h"

enum bossState //보스 상태패턴 enum문
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
	FLAMETHROWER_END3
};
struct tagBossPart  //보스 파츠별 구조체
{
	image* _bossBodyImage;
	floatRect _rectBody;

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

	icethrower* _icethrower;
	mine* _mine;
	stoneshower* _stoneshower;
	flamethrower* _flamethrower;

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

	//보스 방어막 프레임
	int _protectCurrentFrameX, _protectCurrentFrameY;
	int _protectFrameCount;
	int _bossShieldOneFrameX, _bossShieldOneFrameY;

	int _moveCount;  //움직이고 있을때의 카운트

	int _chargeCount; //충전할때의 카운트

	int _randomAttackCount;  // 어떤 공격을 할까나~~??


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

	void moveUp();
	void moveDown();

	void fireCollision();

	void bossInitialization();	//보스 stop후 위치 확인용

	
};


