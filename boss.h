#pragma once
#include "gameObject.h"

enum bossState //보스 상태패턴 enum문
{
	APPEARANCE = 0,
	STOP,
	MOVEUP,
	MOVEDOWN,
	LEFTHAND_ATTACK_READY,
	LEFTHAND_ATTACK,
	LEFTHAND_ATTACK_END,
	CENTER_ATTACK_READY,
	CENTER_ATTACK,
	CENTER_ATTACK_END,
};
struct tagBossPart  //보스 파츠별 구조체
{
	image* _bossBodyImage;
	floatRect _rectBody;

	float _x, _y;
	float _angle;
	float _realAngle;	//실질적으로 이미지를 회전시켜주는 각도
	float _speed;

	floatPoint _center;
	floatPoint _centerEnd;
	float _centerMeter;
};

class boss : public gameObject
{


private:

	image* image;
	bossState _bossState;

	tagBossPart _Center;

	tagBossPart _LeftArm;
	tagBossPart _RightArm;

	tagBossPart _LeftHand;
	tagBossPart _RightHand;

	tagBossPart _Bottom;

	int _currentFrameX, _currentFrameY;
	int _frameCount;

	int _protectCurrentFrameX, _protectCurrentFrameY;
	int _protectFrameCount;

	int _appearanceCount;

	int _attackCount;
	int _attackEndCount;
	int _mineAttackCount;

	int _bossShieldOneFrameX;
	int _bossShieldOneFrameY;


	int _fireskill1Time;


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

};


