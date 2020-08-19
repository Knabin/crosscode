#pragma once
#include "gameObject.h"

class puzzleOrangeWall : public gameObject
{
private:
	image* _image;
	int _type;
	int _frameX;
	int _count;

public:
	puzzleOrangeWall(int type);
	~puzzleOrangeWall();

	void setType(int type) { _type = type; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

