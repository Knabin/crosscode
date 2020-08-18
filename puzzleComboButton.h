#pragma once
#include "gameObject.h"
class puzzleComboButton : public gameObject
{
private:
	image* _image;

public:
	~puzzleComboButton();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

