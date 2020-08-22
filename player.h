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
	int _playerMaxHP;  //플레이어 최대HP
	int _pXp;		//플레이어 경험치 적을 죽였을때
	int _playerLevelUpXp; //레벨업까지 필요한 XP
	int _pSp;		//플레이어 SP 적을 때렸을때 차야됨 or 가만히있을때 참
	int _pSpcharge;	//SP 차징시간
	int _pLevel;

	int _pDef;		//플레이어 방어력
	float _pCrt;	//플레이어 크리티컬
	int _pfR;		//플레이어 불 저항력
	int _pIR;		//플레이어 얼음 저항력
	int _pER;		//플레이어 전기 저항력
	int _pPR;		//플레이어 파동 저항력

	int _lethalCount;   // 필살기 횟수?
	int _lethalCharge;	// 필살기 충전시간
	bool _isLethal; // 필살기 체크용

	bool _beAttacked;	//충돌처리용 불값
	bool _attackCollision;//에너미에게 공격당했을때 데미지를 중첩으로 먹는걸 방지하기 위한 값
	int _beAttackedCount;	//피격모션용 카운트

	float _jumpPower;
	float _gravity;
	bool _jumping;

	bool _attacking;

	float _angle;
	float de;
	float d1;
	float d2;

	floatRect _tileRect;
	POINT next[6];

	int _pAtk; //플레이어 본 공격력
	int _attackPower;	//에너미에게 가해지는 공격력

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
	void playerLethalattackMove();

	void damage(int damage)
	{
		int att = damage - _pDef;
		if (_state->getState() == _vState[PLAYERSTATE::DODGE])
		{
			SOUNDMANAGER->play("dodge", 0.3f);
			damage -= 10;
		}
		_pHp -= att < 0 ? 0 : att;
		if (_pHp <= 0) _pHp = 0;
	}

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
	void setAttackCollision(bool attackCollision) { _attackCollision = attackCollision; }
	

	
	bool isDashing() { return _state->getState() == _vState[PLAYERSTATE::DODGE]; }
	bool isLongAttacking() { return (_state->getState() == _vState[PLAYERSTATE::LONGATTACKIDLE] ||
		_state->getState() == _vState[PLAYERSTATE::LONGATTACKMOVE]);
	}
	inline int getNowOrder() { return _nowOrder; }

	inline bool getAttacking() {return _attacking;}
	void setAttacking(bool b) { _attacking = b; }

	animation* getAnimation() { return _ani; }

	PLAYERDIRECTION getDirection() { return _direction; }

	bullet* getBullet() { return _bullet; }

	floatRect& getPlayerAttackRect() { return _attackRC; }

	int getPlayerAttackPower() { return _attackPower; }
	void setPlayerAttackPower(int power) { _attackPower = power; }
	int getPlayerHP() { return _pHp; }
	void setPlayerHP(int hp) { _pHp = hp; }
	int getPlayerMaxHP() { return _playerMaxHP; }
	void setPlayerMaxHP(int mHp) { _playerMaxHP = mHp; }
	int getPlayerEXP() { return _pXp; }
	void setPlayerEXP(int exp) { _pXp = exp; }
	int getPlayerNextEXP() { return _playerLevelUpXp; }
	void setPlayerNextEXP(int Nexp) { _playerLevelUpXp = Nexp; }
	int getPlayerSP() { return _pSp; }
	void setPlayerSP(int sp) { _pSp = sp; }
	int getPlayerDef() { return _pDef; }
	void setPlayerDef(int def) { _pDef = def; }
	int getPlayerCri() { return _pCrt; }
	void setPlayerCri(int cri) { _pCrt = cri; }
	int getPlayerFR() { return _pfR; }
	void setPlayerFR(int fr) { _pfR = fr; }
	int getPlayerIR() { return _pIR; }
	void setPlayerIR(int ir) { _pIR = ir; }
	int getPlayerER() { return _pER; }
	void setPlayerER(int er) { _pER = er; }
	int getPlayerPR() { return _pPR; }
	void setPlayerPR(int pr) { _pPR = pr; }
	int getPlayerLEVEL() { return _pLevel; }
	void setPlayerLEVEL(int pl) { _pLevel = pl; }
	int getPlayerAtk() { return _pAtk;}
	void setPlayerAtk(int atk) { _pAtk = atk; }


	bool mouseCheck() { return (getDistance(_position.x, _position.y, _ptMouse.x /
		CAMERA->getZoomAmount() + CAMERA->getRect().left, _ptMouse.y /
		CAMERA->getZoomAmount() + CAMERA->getRect().top) < 150) ? true : false; }
	bool getBeAttacked() { return _beAttacked; }
	bool getAttackCollision() { return _attackCollision; }
	void setIdle();
};