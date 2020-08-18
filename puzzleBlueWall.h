#pragma once
#include "gameObject.h"

class puzzleBlueWall : public gameObject
{
private:
	image* _image;
	int _type;

public:
	puzzleBlueWall(int type);
	~puzzleBlueWall();

	void setType(int type) { _type = type; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

