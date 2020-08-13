#pragma once
#include "gameObject.h"

class door : public gameObject
{
	image* _image;
	int _type;

public:
	void setType(int type) { _type = type; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

