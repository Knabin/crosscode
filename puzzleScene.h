#pragma once
#include "scene.h"

class puzzleScene : public scene
{
private:

public:
	virtual ~puzzleScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

