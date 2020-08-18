#pragma once
#include "gameObject.h"
#include "playerStateController.h"

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
	END,
};

class player : public gameObject
{
private:
	image* _image;
	animation* _ani;
	floatRect _tile;		// center x, bottom 기준으로 현재 밟고 있는 tile rect

	floatRect rc1[10];
	floatRect rc2[10];
	float de;

	playerStateController* _state;
	PLAYERDIRECTION _direction;


	vector<playerState*>	_vState;

	POINT tileIndex;
	RECT rcCollision;
	int _nowOrder;
	int _count;

	bool _iscombo;
	bool _isEffect;
	int _combocount;
	int _combo;
	int _fullCount;	//원거리공격 충전시간

	int _dodgeCount;	//닷지횟수
	int _dodgeCharge;	//닷지횟수 충전용

	float _jumpPower;
	float _gravity;

	floatRect _tileRect;
	POINT next[3];

public:
	player();
	virtual ~player();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void playerMove();
	void playerDodge();
	void playerLongAttackMove();
	void playermeleeattackMove();
	void playerfinalattackMove();
	void move(const float& x, const float& y);
	void moveAngle(const float& cangle, const float& speed);
	void playerFire();
	void playerMeleeattack();

	void setImage(image* image) { _image = image; }
	void setImage(string imageName) { _image = IMAGEMANAGER->findImage(imageName); }
	void setAnimation(animation* ani) { _ani = ani; }
	void setDirection(PLAYERDIRECTION direction) { _direction = direction; }

	animation* getAnimation() { return _ani; }

	PLAYERDIRECTION getDirection() { return _direction; }
};