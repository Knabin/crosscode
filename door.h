#pragma once
#include "gameObject.h"

class door : public gameObject
{
	image* _image;
	floatRect _moveRect;
	int _type;
	int _frameX;
	int _frameCount;
	string _nextSceneName;

	bool _isOpen;

public:
//	door(int type);
	void setType(int type) { _type = type; }
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

