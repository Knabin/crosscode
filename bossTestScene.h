#pragma once
#include "scene.h"
#include "boss.h"


class bossTestScene : public scene
{
private:

	boss* _boss;
	gameObject* _cameraTarget;
	floatRect _hpBar;
	int _hp;


public:
	virtual ~bossTestScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

