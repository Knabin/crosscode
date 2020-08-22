#pragma once

// scene manager�� ��� scene�� �����մϴ�.
// ��ȯ�� ȭ���� scene�� ��ӹ޾� �����ϰ�, SCENEMANAGER->addScene() �Լ��� �߰��� �ָ� �˴ϴ�.

class sceneManager
{
public:
	// �̱������� �����մϴ�.
	static sceneManager* getInstance()
	{
		static sceneManager instance;
		return &instance;
	}
private:
	// �̱����̱� ������ ���� �� �Ҹ��� private���� ���� �Ӵϴ�.
	sceneManager();
	~sceneManager();

private:
	typedef map<wstring, class scene*>			mScenes;
	typedef map<wstring, class scene*>::iterator	miScenes;
private:
	mScenes		_mScenes;
	miScenes	_miScenes;
	class scene* _currentScene;
	wstring _currentSceneName;
	image* _tileBuffer;
	image* _tileImages[3];
	image* _objectImages[3];

public:
	void init();
	void release();
	void update();
	void render();

	image* getTileBuffer() { return _tileBuffer; }
	image* getTileImage(int pageNum) { return _tileImages[pageNum]; }
	image* getObjectImage(int pageNum) { return _objectImages[pageNum]; }

	void addScene(wstring sceneName, class scene* scene);
	void loadScene(wstring sceneName);
	scene* findScene(wstring sceneName);

	scene* getCurrentScene() { return _currentScene; }
	wstring getCurrentSceneName() { return _currentSceneName; }

	int getCurrentSceneMapXSize(); //{ return _currentScene->getTiles()[0].size(); }
	int getCurrentSceneMapYSize(); //{ return _currentScene->getTiles().size(); }
};

