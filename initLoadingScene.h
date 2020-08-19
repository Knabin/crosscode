#pragma once
#include "scene.h"
#define LOADINGMAX 2000

class initLoadingScene : public scene
{
	// 프로그레스바
private:
	floatRect _progressRc;
	int _currentCount;
	float _width;

	Vector2 _position;
	image* _progressBar;
	image* _progressBarBack;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

