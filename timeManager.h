#pragma once
#include "timer.h"

class timeManager
{
public:
	static timeManager* getInstance()
	{
		static timeManager instance;
		return &instance;
	}
private:
	timeManager();
	~timeManager();

private:
	timer* _timer;

public:
	HRESULT init();
	void release();
	void update(float lockFPS = 0.0f);
	void render(HDC hdc);

	inline float getElapsedTime() const { return _timer->getElapsedTime(); }
	inline float getWorldTime() const { return _timer->getWorldTime(); }
};

