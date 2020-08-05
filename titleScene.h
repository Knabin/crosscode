#pragma once
#include "scene.h"
#include "button.h"

class titleScene : public scene
{
private:

public:
	virtual ~titleScene() override;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cbStart();
	void cbContinue();
	void cbMaptool();
	void cbOption();
	void cbExit();
};

