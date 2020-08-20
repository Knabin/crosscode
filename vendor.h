#pragma once
#include "gameObject.h"


class vendor : public gameObject
{
	class player* _player;

	
	int _iconNum;

	image* _image;
	int _type;

public:
	void setType(int type) { _type = type; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

