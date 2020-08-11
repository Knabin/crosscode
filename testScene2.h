#pragma once
#include "scene.h"

class testScene2 : public scene
{
private:

public:
	virtual ~testScene2() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

