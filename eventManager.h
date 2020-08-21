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

	bool _firstEvent;

public:
	queue<class iEvent*> _mEventQueue;

	void update();
	void addEvent(class iEvent* pEvent);
	bool isPlayingEvent();

	void setFirstEvent(bool firstEvent) { _firstEvent = firstEvent; }
	bool getFirstEvent() { return _firstEvent; }
};

