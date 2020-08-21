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
	float de;

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
	int _count;

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
	int _pXp;		//�÷��̾� ����ġ ���� �׿�����
	int _pSp;		//�÷��̾� SP ���� �������� ���ߵ� or ������������ ��
	int _pSpcharge;	//SP ��¡�ð�

	int _lethalCount;   // �ʻ�� Ƚ��?
	int _lethalCharge;	// �ʻ�� �����ð�
	bool _isLethal; // �ʻ�� üũ��


	float _jumpPower;
	float _gravity;
	bool _jumping;

	float _angle;

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

	inline int getNowOrder() { return _nowOrder; }

	animation* getAnimation() { return _ani; }

	PLAYERDIRECTION getDirection() { return _direction; }

	bullet* getBullet() { return _bullet; }

	floatRect& getPlayerAttackRect() { return _attackRC; }

	int getPlayerAttackPower() { return _attackPower; }

	bool mouseCheck() { return (getDistance(_position.x, _position.y, _ptMouse.x /
		CAMERA->getZoomAmount() + CAMERA->getRect().left, _ptMouse.y /
		CAMERA->getZoomAmount() + CAMERA->getRect().top) < 150) ? true : false; }

	void setIdle();
};