#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;
	int _y;

	image*		_effectImage;
	animation*	_effectAnimation;
	BOOL		_isRunning;
	float		_elapsedTime;
	float		_scale;
	float		_angle;
	float		_alpha;
public:
	effect();
	~effect();

	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime, float scale);
	virtual void release();
	virtual void update();
	virtual void render();

	void startEffect(int x, int y, float angle, float alpha);
	void startEffect(Vector2 pos, float angle, float alpha);

	virtual void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};

