#pragma once
#include <bitset>

#define KEYMAX 256

using namespace std;

class keyManager
{
public:
	static keyManager* getInstance()
	{
		static keyManager instance;
		return &instance;
	}
private:
	keyManager();
	~keyManager();

private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	HRESULT init();
	void release();
	//키를 한 번 누르면
	bool isOnceKeyDown(int key);
	//키를 눌렀다가 떼면
	bool isOnceKeyUp(int key);
	//키를 계속 누르고 있으면
	bool isStayKeyDown(int key);
	//키가 토글되면(?) 캡스롹 생각해라
	bool isToggleKey(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
};

