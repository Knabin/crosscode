#pragma once
#include "scene.h"

class mountainScene : public scene
{
private:

public:
	virtual ~mountainScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};