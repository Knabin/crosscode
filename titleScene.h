#pragma once
#include "scene.h"
#include "button.h"

class titleScene : public scene
{
private:
	int _index;
	int _time;
	
	bool _loading;

	POINT _c1, _c2, _gr, _mn, _rl, _pl;	
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

