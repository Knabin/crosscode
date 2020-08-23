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
	floatRect _tile;		// center x, bottom �������� ���� ��� �ִ� tile rect

	floatRect rc1[12];
	floatRect rc2[12];
	floatRect _attackRC;

	playerStateController* _state;
	PLAYERDIRECTION _direction;
	bullet* _bullet;
	
	image* _attackImg;				//�ٰŸ� ����Ʈ��
	animation* _attackAni[40];		//�ٰŸ� ����Ʈ��
	float _attackAngle;			//�ٰŸ� ����Ʈ��

	vector<playerState*>	_vState;

	POINT _backTile;
	POINT tileIndex;
	RECT rcCollision;
	int _nowOrder;
	int _backOrder;
	int _beginOrder;

	int _jumpCount;

	bool _iscombo;		//�ٰŸ� �޺� �������� üũ
	int _combocount;	//�ٰŸ� �޺���
	int _combo;			//�ٰŸ� �޺���

	int _attackEffectCount;	//�ٰŸ� ����Ʈ��
	int _attackCount;		//�ٰŸ� ����Ʈ��
	
	bool _isEffect;
	int _fullCount;	//���Ÿ����� �����ð�

	int _dodgeCount;	//����Ƚ��
	int _dodgeCharge;	//����Ƚ�� ������
	
	int _lineCount;		//�ѹ� Ŭ���� �������� ���� ��

	int _pHp;		//�÷��̾� HP 
	int _playerMaxHP;  //�÷��̾� �ִ�HP
	int _pXp;		//�÷��̾� ����ġ ���� �׿�����
	int _playerLevelUpXp; //���������� �ʿ��� XP
	int _pSp;		//�÷��̾� SP ���� �������� ���ߵ� or ������������ ��
	int _pSpcharge;	//SP ��¡�ð�
	int _pLevel;

	int _pDef;		//�÷��̾� ����
	float _pCrt;	//�÷��̾� ũ��Ƽ��
	int _pfR;		//�÷��̾� �� ���׷�
	int _pIR;		//�÷��̾� ���� ���׷�
	int _pER;		//�÷��̾� ���� ���׷�
	int _pPR;		//�÷��̾� �ĵ� ���׷�

	int _lethalCount;   // �ʻ�� Ƚ��?
	int _lethalCharge;	// �ʻ�� �����ð�
	bool _isLethal; // �ʻ�� üũ��

	bool _beAttacked;	//�浹ó���� �Ұ�
	bool _attackCollision;//���ʹ̿��� ���ݴ������� �������� ��ø���� �Դ°� �����ϱ� ���� ��
	int _beAttackedCount;	//�ǰݸ�ǿ� ī��Ʈ

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

	int _pAtk; //�÷��̾� �� ���ݷ�
	int _attackPower;	//���ʹ̿��� �������� ���ݷ�

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