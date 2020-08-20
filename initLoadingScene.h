#pragma once
#include "scene.h"
#define LOADINGMAX 50

class initLoadingScene : public scene
{
	// 프로그레스바
private:
	floatRect _progressRc;
	int _currentCount;
	float _width;

	Vector2 _position;
	floatRect _progressBar;
	image* _progressBarBack;

	bool _isInit;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

