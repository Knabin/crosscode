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
	END,
};

class player : public gameObject
{
private:
	image* _image;
	animation* _ani;
	floatRect _tile;		// center x, bottom 기준으로 현재 밟고 있는 tile rect

	playerStateController* _state;
	PLAYERDIRECTION _direction;
	

	vector<playerState*>	_vState;

	floatRect _attackRC;

	POINT tileIndex;
	RECT rcCollision;
	int _nowOrder;
	int _count;
	int _attackPower;

	float _jumpPower;
	float _gravity;

	bool _isAttack;

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

	void setImage(image* image) { _image = image; }
	void setImage(string imageName) { _image = IMAGEMANAGER->findImage(imageName); }
	void setAnimation(animation* ani) { _ani = ani; }
	void setPlayerAttackRectRemove() { _attackRC.set(0, 0, 0, 0); }
	void setPlayerX(float x) { _x = x; }
	void setPlayerY(float y) { _y = y; }

	animation* getAnimation() { return _ani; }

	PLAYERDIRECTION getDirection() { return _direction; }

	floatRect& getPlayerAttackRect() { return _attackRC; }

	int getPlayerAttackPower() { return _attackPower; }
};

