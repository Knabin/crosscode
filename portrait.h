#pragma once
#include "gameObject.h"

class portrait : public gameObject
{
private:
	image* _img;

public:
	portrait(int type);
	HRESULT init();
	void render();
};

