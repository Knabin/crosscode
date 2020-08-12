#include "stdafx.h"
#include "objectManager.h"
#include "gameObject.h"

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
			// �ش� ������Ʈ�� �������� �ִ� ��쿡�� update �����մϴ�.
			if (objectList[i]->getIsActive())
			{
				objectList[i]->update();
				if(iter->first != objectType::UI && iter->first != objectType::TILEOBJECT)
					_vZOrderRender.push_back(objectList[i]);
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
			// �ش� ������Ʈ�� �������� �ִ� ��쿡�� update �����մϴ�.
			if (objectList[i]->getIsActive())
				objectList[i]->update();
		}
	}
}

void objectManager::render()
{
	/*
	objectContainerIter iter = _mObjectContainer.begin();
	for (; iter != _mObjectContainer.end(); ++iter)
	{
		vector<gameObject*>& objectList = iter->second;
		// UI�� uiController���� ��� ��ǥ �������� render�ϱ� ������ �ϹǷ� continue ó���մϴ�.
		if (iter->first == objectType::UI) continue;
		else if (iter->first == objectType::TILEOBJECT)
		{
			for (int i = 0; i < objectList.size(); ++i)
			{
				if (objectList[i]->getRect().bottom > OBJECTMANAGER->findObject(objectType::MAPOBJECT, "player")->getRect().bottom)
					objectList[i]->render();
			}
		}
		else
		{
			for (int i = 0; i < objectList.size(); ++i)
			{
				if (objectList[i]->getIsActive())
					objectList[i]->render();
			}
		}
	}*/
	for (int i = 0; i < _vZOrderRender.size(); ++i)
	{
		_vZOrderRender[i]->render();
	}

	vector<gameObject*>& objectList = _mObjectContainer.find(objectType::TILEOBJECT)->second;
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->getRect().bottom > OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getY())
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
	return nullptr;	// �� ã��
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
		// left�� pivot ���ؼ� left�� ������ ++
		while (_vZOrderRender[left]->getRect().bottom < pivot) ++left;
		// right�� pivot ���ؼ� right�� ũ�� --
		while (_vZOrderRender[right]->getRect().bottom > pivot) --right;

		// �� �� ����
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