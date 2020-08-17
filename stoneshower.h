#pragma once
#include "gameObject.h"

class stoneshower : public gameObject
{
private:


public:


	stoneshower();
	~stoneshower();


	HRESULT init();
	void release();
	void update();
	void render();

	void dustDraw();

};

