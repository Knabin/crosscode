#pragma once
#include "gameObject.h"

class puzzleTabButton : public gameObject
{
private:
	image* _image;
	int _frameY;

public:
	~puzzleTabButton();

	void setFrameY(int frameY) { _frameY = frameY; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

