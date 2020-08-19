#pragma once
#include "scene.h"

class townScene : public scene
{
private:

public:
	virtual ~townScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

