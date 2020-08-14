#pragma once
#include <unordered_map>

enum class objectType : int
{
	ENEMY, BOSS, PLAYER, MAPOBJECT, ITEM, TILEOBJECT, UI, END,
};

// object manager는 모든 gameObject를 관리합니다. 다시 말해 모든 gameObject들의 메모리를 쥐고 있습니다.
// 따라서 playGround에서 전방 선언을 남발하며 메모리를 연결해 줄 필요가 없어집니다.
// 단, 특정 클래스만 지니고 있는 특정 함수를 호출할 경우에는 형변환이 필요합니다. => dynamic_cast

class objectManager
{
public:
	// 싱글톤으로 선언합니다.
	static objectManager* getInstance()
	{
		static objectManager instance;
		return &instance;
	}

private:
	// 싱글톤이기 때문에 생성 및 소멸을 private으로 막아 둡니다.
	objectManager();
	~objectManager();

private:
	// key값(타입, enum)을 가지고 vector<gameObject*>를 관리하는 map
	unordered_map<objectType, vector<class gameObject*>> _mObjectContainer;
	typedef unordered_map<objectType, vector<class gameObject*>>::iterator objectContainerIter;

	vector<class gameObject*> _vZOrderRender;

public:
	void release();
	void update();
	void update(objectType type);
	void render();

	// 오브젝트를 추가합니다. (타입(objectType:: 치면 나옴), 객체)
	void addObject(objectType type, class gameObject* newObject);
	// 오브젝트를 제거합니다. (타입(objectType:: 치면 나옴), 객체)
	void removeObject(objectType type, class gameObject* deleteObject);
	// 플레이어를 제외한 모든 오브젝트를 제거합니다. Scene 전환 시 사용합니다.
	void removeObjectsWithoutPlayer();

	// 해당 이름의 오브젝트를 찾아서 반환합니다. (타입(objectType:: 치면 나옴), 객체 이름)
	class gameObject* findObject(objectType type, string objectName);
	// 해당 이름의 오브젝트들을 찾아서 벡터로 반환합니다. (타입(objectType:: 치면 나옴), 객체 이름)
	vector<class gameObject*> findObjects(objectType type, string objectName);
	// 해당 타입의 오브젝트들을 찾아서 벡터로 반환합니다. (타입(objectType:: 치면 나옴))
	vector<class gameObject*>& getObjectList(objectType type);

	void sortZorder(int start, int end);

	// 0: tile, 1: monster, 2: player, 3: item, 4: ui
	objectType intToObjType(int type) { return (objectType)type; }
};

