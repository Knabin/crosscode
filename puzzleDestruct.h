#pragma once
#include "gameObject.h"

class puzzleDestruct : public gameObject
{
private:
	image* _image;

	int _hp;
	int _count;
	int _frameX;

public:
	~puzzleDestruct();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	int getHP() { return _hp; }

	void setHP(int hp) { _hp -= hp; }
};

