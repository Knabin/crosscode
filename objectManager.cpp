#include "stdafx.h"
#include "objectManager.h"
#include "gameObject.h"
#include "tile.h"
#include "player.h"

objectManager::objectManager()
{
	for (int i = 0; i < (int)objectType::END; ++i)
	{
		_mObjectContainer.insert(make_pair((objectType)i, vector<gameObject*>()));
	}
}

objectManager::~objectManager()
{
}

void objectManager::release()
{
	objectContainerIter iter = _mObjectContainer.begin();
	for (; iter != _mObjectContainer.end(); ++iter)
	{
		vector<gameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			objectList[i]->release();
			SAFE_DELETE(objectList[i]);
		}
	}
	_mObjectContainer.clear();
}

void objectManager::update()
{
	_vZOrderRender.clear();

	objectContainerIter iter = _mObjectContainer.begin();
	for (; iter != _mObjectContainer.end(); ++iter)
	{
		vector<gameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			// 해당 오브젝트만 보여지고 있는 경우에만 update 진행합니다.
			if (objectList[i]->getIsActive())
			{
				if (iter->first != objectType::UI)
					objectList[i]->update();
				if (iter->first != objectType::TILEOBJECT)
				{
					if (!objectList[i]->getIsAlive())
					{
						objectList[i]->release();
						SAFE_DELETE(objectList[i]);
						objectList.erase(objectList.begin() + i);
						i--;
					}
					else if(iter->first != objectType::UI)
					{
						_vZOrderRender.push_back(objectList[i]);
					}
				}
			}
			
		}
	}

	sortZorder(0, _vZOrderRender.size() - 1);
}

void objectManager::update(objectType type)
{
	objectContainerIter iter = _mObjectContainer.find(type);
	for (; iter != _mObjectContainer.end(); ++iter)
	{
		vector<gameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			// 해당 오브젝트만 보여지고 있는 경우에만 update 진행합니다.
			if (objectList[i]->getIsActive())
				objectList[i]->update();
		}
	}
}

void objectManager::render()
{
	for (int i = 0; i < _vZOrderRender.size(); ++i)
	{
		if (!_vZOrderRender[i]->getIsAlive()) continue;
		_vZOrderRender[i]->render();
	}

	vector<gameObject*>& objectList = _mObjectContainer.find(objectType::TILEOBJECT)->second;
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->getRect().right < CAMERA->getRect().left ||
			objectList[i]->getRect().left > CAMERA->getRect().right ||
			objectList[i]->getRect().top > CAMERA->getRect().bottom ||
			objectList[i]->getRect().bottom < CAMERA->getRect().top) continue;
		if (dynamic_cast<tile*>(objectList[i])->getOrderIndex() > 
			dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"))->getNowOrder() &&
				dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"))->getNowOrder() != 3 &&
			objectList[i]->getRect().bottom > OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y)
			objectList[i]->render();
	}
}

void objectManager::addObject(objectType type, gameObject * newObject)
{
	_mObjectContainer[type].push_back(newObject);
}

void objectManager::removeObject(objectType type, gameObject * deleteObject)
{
	vector<gameObject*> objectList = _mObjectContainer[type];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i] == deleteObject)
		{
			objectList[i]->release();
			SAFE_DELETE(objectList[i]);
			objectList.erase(objectList.begin() + i);
			return;
		}
	}
}

void objectManager::removeObjectsWithoutPlayer()
{
	objectContainerIter iter = _mObjectContainer.begin();
	for (; iter != _mObjectContainer.end(); ++iter)
	{
		//vector<gameObject*>& objectList = iter->second;
		vector<gameObject*>::iterator viter = iter->second.begin();
		if (iter->first == objectType::UI) continue;
		for (; viter != iter->second.end(); )
		{
			if ((*viter)->getName() != "player")
			{
				(*viter)->release();
				SAFE_DELETE(*viter);
				viter = iter->second.erase(viter);
			}
			else viter++;
		}
	}

	_vZOrderRender.clear();
}

gameObject * objectManager::findObject(objectType type, string objectName)
{
	vector<gameObject*>& objectList = _mObjectContainer[type];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->getName() == objectName)
		{
			return objectList[i];
		}
	}
	return nullptr;	// 못 찾음
}

vector<class gameObject*> objectManager::findObjects(objectType type, string objectName)
{
	vector<gameObject*> result;
	vector<gameObject*>& objectList = _mObjectContainer[type];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->getName() == objectName)
		{
			result.push_back(objectList[i]);
		}
	}
	return result;
}

vector<class gameObject*>& objectManager::getObjectList(objectType type)
{
	return _mObjectContainer[type];
}

void objectManager::sortZorder(int start, int end)
{
	if (start >= end) return;
	float pivot = _vZOrderRender[(start + end) / 2]->getRect().bottom;
	int left = start;
	int right = end;

	while (left <= right)
	{
		// left랑 pivot 비교해서 left가 작으면 ++
		while (_vZOrderRender[left]->getRect().bottom < pivot) ++left;
		// right랑 pivot 비교해서 right가 크면 --
		while (_vZOrderRender[right]->getRect().bottom > pivot) --right;

		// 두 개 스왑
		if (left <= right)
		{
			swap(_vZOrderRender[left], _vZOrderRender[right]);
			++left;
			--right;
		}
	}
	sortZorder(start, right);
	sortZorder(left, end);
}