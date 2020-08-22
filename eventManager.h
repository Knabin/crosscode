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

	bool _firstEvent;		// 마을 첫 번째 이벤트
	bool _puzzleEvent;		// 퍼즐 맵 이벤트
	bool _secondEvent;		// 마을 두 번째 이벤트
	bool _bossFirstEvent;	// 보스 첫 번째 이벤트
	bool _bossSecondEvent;	// 보스 두 번째 이벤트

public:
	queue<class iEvent*> _mEventQueue;

	void update();
	void addEvent(class iEvent* pEvent);
	bool isPlayingEvent();

	void setFirstEvent(bool firstEvent) { _firstEvent = firstEvent; }
	bool getFirstEvent() { return _firstEvent; }

	void setPuzzleEvent(bool puzzleEvent) { _puzzleEvent = puzzleEvent; }
	bool getPuzzleEvent() { return _puzzleEvent; }

	void setSecondEvent(bool secondEvent) { _secondEvent = secondEvent; }
	bool getSecondEvent() { return _secondEvent; }

	void setBossFirstEvent(bool bossEvent) { _bossFirstEvent = bossEvent; }
	bool getBossFirstEvent() { return _bossFirstEvent; }

	void setBossSecondEvent(bool bossEvent) { _bossSecondEvent = bossEvent; }
	bool getBossSecondEvent() { return _bossSecondEvent; }
};

