#pragma once
#include "gameObject.h"

// TODO: enemy 클래스 필요
class hedgehag : public gameObject
{
private:
	image* _image;
	animation* _test_ani;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

