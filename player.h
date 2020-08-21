#pragma once
#include "gameObject.h"
#include "playerStateController.h"

class bullet;

enum class PLAYERDIRECTION : int
{
	TOP,
	LEFT_TOP,
	LEFT,
	LEFT_BOTTOM,
	BOTTOM,
	RIGHT_BOTTOM,
	RIGHT,
	RIGHT_TOP,
};

enum PLAYERSTATE : int
{
	IDLE,
	MOVE,
	JUMP,
	GUARD,
	DODGE,
	LONGATTACK,
	LONGATTACKIDLE,
	LONGATTACKMOVE,
	MOVESTOP,
	LEFT_ATTACK,
	RIGHT_ATTACK,
	RIGHT_FINALATTACK,
	LETHAL_CHARGE,
	LETHAL_ATTACK,
	BE_ATTACKED,
	END,
};

class player : public gameObject
{
private:
	image* _image;
	animation* _ani;
	floatRect _tile;		// center x, bottom 기준으로 현재 밟고 있는 tile rect

	floatRect rc1[12];
	floatRect rc2[12];
	floatRect _attackRC;

	playerStateController* _state;
	PLAYERDIRECTION _direction;
	bullet* _bullet;
	
	image* _attackImg;				//근거리 이펙트용
	animation* _attackAni[40];		//근거리 이펙트용
	float _attackAngle;			//근거리 이펙트용

	vector<playerState*>	_vState;

	POINT _backTile;
	POINT tileIndex;
	RECT rcCollision;
	int _nowOrder;
	int _backOrder;
	int _beginOrder;
	int _count;

	int _jumpCount;

	bool _iscombo;		//근거리 콤보 상태인지 체크
	int _combocount;	//근거리 콤보용
	int _combo;			//근거리 콤보용

	int _attackEffectCount;	//근거리 이펙트용
	int _attackCount;		//근거리 이펙트용
	
	bool _isEffect;
	int _fullCount;	//원거리공격 충전시간

	int _dodgeCount;	//닷지횟수
	int _dodgeCharge;	//닷지횟수 충전용
	
	int _lineCount;		//한번 클릭시 좁혀지는 양쪽 선

	int _pHp;		//플레이어 HP 
	int _pXp;		//플레이어 경험치 적을 죽였을때
	int _pSp;		//플레이어 SP 적을 때렸을때 차야됨 or 가만히있을때 참
	int _pSpcharge;	//SP 차징시간

	int _lethalCount;   // 필살기 횟수?
	int _lethalCharge;	// 필살기 충전시간
	bool _isLethal; // 필살기 체크용

	bool _beAttacked;	//충돌처리용 불값
	int _beAttackedCount;	//피격모션용 카운트

	float _jumpPower;
	float _gravity;
	bool _jumping;

	float _angle;
	float de;
	float d1;
	float d2;

	floatRect _tileRect;
	POINT next[6];

	int _attackPower;

public:
	player();
	virtual ~player();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void playerMove();
	void playerDodge();
	void playerJumpMove();
	void playerLongAttackMove();
	void playermeleeattackMove();
	void playerfinalattackMove();
	void move(const float& x, const float& y);
	void moveAngle(const float& cangle, const float& speed);
	void playerMeleeattack();
	void playerDodgeEffect();
	void playerLethalattack();

	void setImage(image* image) { _image = image; }
	void setImage(string imageName) { _image = IMAGEMANAGER->findImage(imageName); }
	void setAnimation(animation* ani) { _ani = ani; }
	void setDirection(PLAYERDIRECTION direction) { _direction = direction; }
	void setAttackRC(int a, int b) { _attackRC.update(Vector2(0, 0), Vector2(a, b), pivot::CENTER); }
	void setState(PLAYERSTATE state) { _state->setState(_vState[state]); }
	void setPlayerAttackRectRemove() { _attackRC.update(Vector2(0, 0), Vector2(0, 0), pivot::CENTER); }
	void setPlayerX(float x) { _position.x = x; }
	void setPlayerY(float y) { _position.y = y; }
	void setPlayerPlusX(float x) { _position.x += x; }
	void setPlayerPlusY(float y) { _position.y += y; }
	void setBeAttacked(bool beAttacked) { _beAttacked = beAttacked; }

	inline int getNowOrder() { return _nowOrder; }

	animation* getAnimation() { return _ani; }

	PLAYERDIRECTION getDirection() { return _direction; }

	bullet* getBullet() { return _bullet; }

	floatRect& getPlayerAttackRect() { return _attackRC; }

	int getPlayerAttackPower() { return _attackPower; }

	bool mouseCheck() { return (getDistance(_position.x, _position.y, _ptMouse.x /
		CAMERA->getZoomAmount() + CAMERA->getRect().left, _ptMouse.y /
		CAMERA->getZoomAmount() + CAMERA->getRect().top) < 150) ? true : false; }
	bool getBeAttacked() { return _beAttacked; }

	void setIdle();
};