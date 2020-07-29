#pragma once
#include "singletonBase.h"
#include <bitset>
#include <list>

using namespace std;

class keyManager
{
public:
	keyManager* getInstance()
	{
		static keyManager instance;
		return &instance;
	}

private:
	keyManager();
	~keyManager();

private:
	list<int> _lKey;
	list<int>::iterator _liKey;

public:
	void release();
	//키를 한 번 누르면
	bool isOnceKeyDown(int key);
	//키를 눌렀다가 떼면
	bool isOnceKeyUp(int key);
	//키를 계속 누르고 있으면
	bool isStayKeyDown(int key);
	//키가 토글되면(?) 캡스롹 생각해라
	bool isToggleKey(int key);
};

