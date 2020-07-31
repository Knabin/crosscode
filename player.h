#pragma once
#include "gameObject.h"
#include "playerStateController.h"

enum class PLAYERDIRECTION : int
{
	LEFT,
	RIGHT
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

	playerStateController* _state;
	PLAYERDIRECTION _direction;
	
	vector<playerState*>	_vState;

public:
	player();
	virtual ~player();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void move(const float& x, const float& y);
	void moveAngle(const float& cangle, const float& speed);
};

