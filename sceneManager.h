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
	typedef map<string, class scene*>			mScenes;
	typedef map<string, class scene*>::iterator	miScenes;
private:
	mScenes		_mScenes;
	miScenes	_miScenes;
	class scene* _currentScene;
	string _currentSceneName;
	image* _tileBuffer;
	image* _tileImages[3];

public:
	void init();
	void release();
	void update();
	void render();

	image* getTileBuffer() { return _tileBuffer; }
	image* getTileImage(int pageNum) { return _tileImages[pageNum]; }

	void addScene(string sceneName, class scene* scene);
	void loadScene(string sceneName);
	scene* findScene(string sceneName);

	scene* getCurrentScene() { return _currentScene; }
	string getCurrentSceneName() { return _currentSceneName; }
};

