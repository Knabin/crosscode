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
	//Ű�� �� �� ������
	bool isOnceKeyDown(int key);
	//Ű�� �����ٰ� ����
	bool isOnceKeyUp(int key);
	//Ű�� ��� ������ ������
	bool isStayKeyDown(int key);
	//Ű�� ��۵Ǹ�(?) ĸ���� �����ض�
	bool isToggleKey(int key);
};

