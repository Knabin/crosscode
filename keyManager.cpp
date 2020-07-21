#include "stdafx.h"
#include "keyManager.h"

keyManager::keyManager()
{
}

keyManager::~keyManager()
{
}

void keyManager::release()
{
	_lKey.clear();
}

bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_liKey = find(_lKey.begin(), _lKey.end(), key);

		// 키가 이미 있다면 true 반환
		if (_liKey != _lKey.end())
		{
			return true;
		}
		else
		{
			_lKey.push_back(key);
			return true;
		}
	}
	else
	{
		_liKey = find(_lKey.begin(), _lKey.end(), key);

		if (_liKey != _lKey.end())
		{
			_lKey.erase(_liKey);
		}
	}

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_liKey = find(_lKey.begin(), _lKey.end(), key);

		// 찾지 못했다면 새로 추가
		if (_liKey == _lKey.end())
		{
			_lKey.push_back(key);
		}
	}
	else
	{
		_liKey = find(_lKey.begin(), _lKey.end(), key);

		if (_liKey != _lKey.end())
		{
			_lKey.erase(_liKey);
			return true;
		}
	}
	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}
