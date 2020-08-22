#pragma once

// scene manager는 모든 scene을 관리합니다.
// 전환될 화면은 scene을 상속받아 구현하고, SCENEMANAGER->addScene() 함수로 추가해 주면 됩니다.

class sceneManager
{
public:
	// 싱글톤으로 선언합니다.
	static sceneManager* getInstance()
	{
		static sceneManager instance;
		return &instance;
	}
private:
	// 싱글톤이기 때문에 생성 및 소멸을 private으로 막아 둡니다.
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

