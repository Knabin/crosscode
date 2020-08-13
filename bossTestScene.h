#pragma once
#include "scene.h"
class bossTestScene : public scene
{
private:

public:
	virtual ~bossTestScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

