#pragma once
#include "gameObject.h"

class puzzleBlueWall : public gameObject
{
private:
	image* _image;
	int _type;
	int _frameX;

public:
	puzzleBlueWall(int type);
	~puzzleBlueWall();

	image* getImage() { return _image; }

	int getFrameX() { return _frameX; }

	void setType(int type) { _type = type; }
	void setFrameX(int frameX) { _frameX = frameX; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

