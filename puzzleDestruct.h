#pragma once
#include "gameObject.h"

class puzzleDestruct : public gameObject
{
private:
	image* _image;

public:
	~puzzleDestruct();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

