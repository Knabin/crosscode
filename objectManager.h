#pragma once
#include <unordered_map>

enum class objectType : int
{
	TileObject, Monster, Player, Item, UI, End,
};

class objectManager
{
public:
	objectManager* getInstance()
	{
		static objectManager instance;
		return &instance;
	}

private:
	objectManager();
	~objectManager();

private:
	unordered_map<objectType, vector<class gameObject*>> _mObjectContainer;
	typedef unordered_map<objectType, vector<class gameObject*>>::iterator objectContainerIter;

public:
	void release();
	void update();
	void render();

	void addObject(objectType type, class gameObject* newObject);
	void removeObject(objectType type, class gameObject* deleteObject);

	class gameObject* findObject(objectType type, string objectName);
	vector<class gameObject*> findObjects(objectType type, string objectName);
	vector<class gameObject*>& getObjectList(objectType type);
};

