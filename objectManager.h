#pragma once
#include <unordered_map>

enum class objectType : int
{
	ENEMY, BOSS, PLAYER, MAPOBJECT, ITEM, TILEOBJECT, UI, END,
};

// object manager�� ��� gameObject�� �����մϴ�. �ٽ� ���� ��� gameObject���� �޸𸮸� ��� �ֽ��ϴ�.
// ���� playGround���� ���� ������ �����ϸ� �޸𸮸� ������ �� �ʿ䰡 �������ϴ�.
// ��, Ư�� Ŭ������ ���ϰ� �ִ� Ư�� �Լ��� ȣ���� ��쿡�� ����ȯ�� �ʿ��մϴ�. => dynamic_cast

class objectManager
{
public:
	// �̱������� �����մϴ�.
	static objectManager* getInstance()
	{
		static objectManager instance;
		return &instance;
	}

private:
	// �̱����̱� ������ ���� �� �Ҹ��� private���� ���� �Ӵϴ�.
	objectManager();
	~objectManager();

private:
	// key��(Ÿ��, enum)�� ������ vector<gameObject*>�� �����ϴ� map
	unordered_map<objectType, vector<class gameObject*>> _mObjectContainer;
	typedef unordered_map<objectType, vector<class gameObject*>>::iterator objectContainerIter;

	vector<class gameObject*> _vZOrderRender;

public:
	void release();
	void update();
	void update(objectType type);
	void render();

	// ������Ʈ�� �߰��մϴ�. (Ÿ��(objectType:: ġ�� ����), ��ü)
	void addObject(objectType type, class gameObject* newObject);
	// ������Ʈ�� �����մϴ�. (Ÿ��(objectType:: ġ�� ����), ��ü)
	void removeObject(objectType type, class gameObject* deleteObject);
	// �÷��̾ ������ ��� ������Ʈ�� �����մϴ�. Scene ��ȯ �� ����մϴ�.
	void removeObjectsWithoutPlayer();

	// �ش� �̸��� ������Ʈ�� ã�Ƽ� ��ȯ�մϴ�. (Ÿ��(objectType:: ġ�� ����), ��ü �̸�)
	class gameObject* findObject(objectType type, string objectName);
	// �ش� �̸��� ������Ʈ���� ã�Ƽ� ���ͷ� ��ȯ�մϴ�. (Ÿ��(objectType:: ġ�� ����), ��ü �̸�)
	vector<class gameObject*> findObjects(objectType type, string objectName);
	// �ش� Ÿ���� ������Ʈ���� ã�Ƽ� ���ͷ� ��ȯ�մϴ�. (Ÿ��(objectType:: ġ�� ����))
	vector<class gameObject*>& getObjectList(objectType type);

	void sortZorder(int start, int end);

	// 0: tile, 1: monster, 2: player, 3: item, 4: ui
	objectType intToObjType(int type) { return (objectType)type; }
};

