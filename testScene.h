#pragma once
#include "scene.h"

class testScene : public scene
{
private:

public:
	virtual ~testScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

