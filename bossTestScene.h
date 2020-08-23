#pragma once
#include "scene.h"
#include "boss.h"
#include "bossHPBar.h"


class bossTestScene : public scene
{
private:

	boss* _boss;
	gameObject* _cameraTarget;
	bossHPBar* _hpBar;
	int _hp;

public:
	virtual ~bossTestScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

