#include "stdafx.h"
#include "objectManager.h"
#include "gameObject.h"

objectManager::objectManager()
{
	for (int i = 0; i < (int)objectType::End; ++i)
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
	objectContainerIter iter = _mObjectContainer.begin();
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
	objectContainerIter iter = _mObjectContainer.begin();
	for (; iter != _mObjectContainer.end(); ++iter)
	{
		vector<gameObject*>& objectList = iter->second;
		// UI는 uiController에서 상대 좌표 기준으로 render하기 때문에 하므로 continue 처리합니다.
		if (iter->first == objectType::UI) continue;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->getIsActive())
				objectList[i]->render();
		}
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
		if (iter->first == objectType::Player) continue;
		vector<gameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			objectList[i]->release();
			SAFE_DELETE(objectList[i]);
		}
		objectList.clear();
	}
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