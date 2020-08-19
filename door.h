#pragma once
#include "gameObject.h"

class door : public gameObject
{
	image* _image;
	floatRect _moveRect;
	int _type;
	string _nextSceneName;

public:
//	door(int type);
	void setType(int type) { _type = type; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

