#include "stdafx.h"
#include "sceneManager.h"
#include "scene.h"

sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

void sceneManager::init()
{
	_currentScene = NULL;
	//_tileBuffer = IMAGEMANAGER->addImage("tileBuffer", 2400, 2400);
	_tileImages[0] = IMAGEMANAGER->addFrameImage("terrain1 b", L"images/tile/terrain1.png", 16, 18);
	_tileImages[1] = IMAGEMANAGER->addFrameImage("terrain2 b", L"images/tile/terrain2.png", 16, 18);
	_tileImages[2] = IMAGEMANAGER->addFrameImage("terrain3 b", L"images/tile/terrain3.png", 16, 18);
	_objectImages[0] = IMAGEMANAGER->addFrameImage("object1 b", L"images/tile/object1.png", 16, 18);
	_objectImages[1] = IMAGEMANAGER->addFrameImage("object2 b", L"images/tile/object2.png", 16, 18);
	_objectImages[2] = IMAGEMANAGER->addFrameImage("object3 b", L"images/tile/object3.png", 16, 18);
}

void sceneManager::release()
{
	miScenes iter = _mScenes.begin();
	for (; iter != _mScenes.end(); )
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mScenes.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mScenes.clear();
}

void sceneManager::update()
{
	if (_currentScene != NULL) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene != NULL) _currentScene->render();
}

void sceneManager::addScene(wstring sceneName, scene * scene)
{
	if (scene == NULL) return;
	_mScenes.insert(make_pair(sceneName, scene));
}

void sceneManager::loadScene(wstring sceneName)
{
	miScenes iter = _mScenes.find(sceneName);

	if (iter == _mScenes.end()) return;
	else if (iter->second == _currentScene) return;

	_currentSceneName = sceneName;
	if (_currentScene != NULL)
		_currentScene->release();

	OBJECTMANAGER->removeObjectsWithoutPlayer();

	// for DEBUG
	if (sceneName.compare(L"maptool") == 0 || sceneName.compare(L"title") == 0 || sceneName.compare(L"boss") == 0)
	{
		OBJECTMANAGER->findObject(objectType::PLAYER, "player")->setIsActive(false);
	}

	_currentScene = iter->second;
	_currentScene->init();
}

scene * sceneManager::findScene(wstring sceneName)
{
	miScenes iter = _mScenes.find(sceneName);
	if (iter != _mScenes.end())
		return iter->second;
}

int sceneManager::getCurrentSceneMapXSize()
{
	return _currentScene->getTiles()[0].size();
}

int sceneManager::getCurrentSceneMapYSize()
{
	return _currentScene->getTiles().size();
}
