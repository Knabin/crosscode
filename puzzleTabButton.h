#pragma once
#include "gameObject.h"

class puzzleTabButton : public gameObject
{
private:
	image* _image;
	int _frameX, _frameY;

public:
	~puzzleTabButton();

	image* getImage() { return _image; }

	int getFrameX() { return _frameX; }

	void setFrameX(int frameX) { _frameX = frameX; }
	void setFrameY(int frameY) { _frameY = frameY; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

