#pragma once
class eventManager
{
public:
	static eventManager* getInstance()
	{
		static eventManager instance;
		return &instance;
	}

private:
	eventManager();
	~eventManager();

public:
	queue<class iEvent*> _mEventQueue;

	void update();
	void addEvent(class iEvent* pEvent);
};

