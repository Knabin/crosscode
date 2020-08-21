#pragma once
#include "scene.h"
#include "boss.h"


class bossTestScene : public scene
{
private:

	boss* _boss;


public:
	virtual ~bossTestScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

