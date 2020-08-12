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
	LONGATTACKLEFT,
	LONGATTACKRIGHT,
	END,
};

class player : public gameObject
{
private:
	image* _image;
	image* _imgShield;
	animation* _ani;
	animation* _aniShield;
	floatRect _tile;		// center x, bottom 기준으로 현재 밟고 있는 tile rect

	playerStateController* _state;
	PLAYERDIRECTION _direction;
	

	vector<playerState*>	_vState;

	POINT tileIndex;
	RECT rcCollision;
	int _nowOrder;

	float _jumpPower;
	float _gravity;


public:
	player();
	virtual ~player();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void playerMove();
	void move(const float& x, const float& y);
	void moveAngle(const float& cangle, const float& speed);
	void playerFire();

	void setImage(image* image) { _image = image; }
	void setImage(string imageName) { _image = IMAGEMANAGER->findImage(imageName); }
	void setAnimation(animation* ani) { _ani = ani; }

	animation* getAnimation() { return _ani; }

	PLAYERDIRECTION getDirection() { return _direction; }
};

