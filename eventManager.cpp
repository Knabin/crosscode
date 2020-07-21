#include "stdafx.h"
#include "eventManager.h"
#include "iEvent.h"

eventManager::eventManager()
{
}

eventManager::~eventManager()
{
}

void eventManager::update()
{
	if (_mEventQueue.size() == 0)
		return;
	
	bool isEventEnd = _mEventQueue.front()->eventUpdate();
	if (isEventEnd)
	{
		SAFE_DELETE(_mEventQueue.front());
		_mEventQueue.pop();
		if (_mEventQueue.size() != 0)
		{
			_mEventQueue.front()->eventStart();
		}
	}
}

void eventManager::addEvent(iEvent * pEvent)
{
	if (_mEventQueue.size() == 0)
	{
		pEvent->eventStart();
	}

	_mEventQueue.push(pEvent);
}
