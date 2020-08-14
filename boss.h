#pragma once
#include "gameObject.h"

class boss : public gameObject
{


private:



	image* image;





public:

	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();




};


