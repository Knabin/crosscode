#pragma once
#include "scene.h"
#include "townBlock.h"

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

