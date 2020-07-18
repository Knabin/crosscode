#include "stdafx.h"
#include "timer.h"

#pragma comment(lib, "winmm.lib")

timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//Frame Lock을 걸어서 deltaTime 주기를 일정하게 잡아둔다
	//자체엔진이 유행하던 시절엔 프레임 스키핑 한다 표현함.
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < 1.0f / lockFPS)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;

	_FPSFrameCount++;

	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;


	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0.0f;
		_FPSTimeElapsed = 0.0f;
	}

}

unsigned long timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}
