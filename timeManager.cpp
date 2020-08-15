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

void timeManager::render()
{
	char str[256];
	string frameRate;

	//SetTextColor(hdc, RGB(255, 255, 255));
	//SetBkMode(hdc, TRANSPARENT);


#ifdef _DEBUG
	{
		sprintf_s(str, " %d FPS", _timer->getFrameRate());
		frameRate = str;
		wstring sstr;
		sstr.assign(frameRate.begin(), frameRate.end());

		D2DRENDERER->RenderTextField(0, 150, sstr, 20, 100, 20, D2DRenderer::DefaultBrush::Gray);

	}
#else
	{
		sprintf_s(str, "framePerSecond(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}
