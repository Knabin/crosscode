#include "stdafx.h"
#include "timeManager.h"

timeManager::timeManager()
	: _timer(NULL)
{
}

timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release()
{
	if (_timer != NULL) SAFE_DELETE(_timer);
}

void timeManager::update(float lockFPS)
{
	if (_timer != NULL)
	{
		_timer->tick(lockFPS);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);


#ifdef _DEBUG
	{
		sprintf_s(str, "framePerSecond(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));

	}
#else
	{
		sprintf_s(str, "framePerSecond(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}
