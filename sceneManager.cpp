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
	_tileBuffer = IMAGEMANAGER->addImage("tileBuffer", 2400, 2400);
	_tileImages[0] = IMAGEMANAGER->addFrameImage("terrain1 b", "images/tile1_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_tileImages[1] = IMAGEMANAGER->addFrameImage("terrain2 b", "images/tile2_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
	_tileImages[2] = IMAGEMANAGER->addFrameImage("terrain3 b", "images/tile3_big.bmp", 768, 864, 16, 18, true, RGB(255, 0, 255));
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

void sceneManager::addScene(string sceneName, scene * scene)
{
	if (scene == NULL) return;
	_mScenes.insert(make_pair(sceneName, scene));
}

void sceneManager::loadScene(string sceneName)
{
	miScenes iter = _mScenes.find(sceneName);

	if (iter == _mScenes.end()) return;
	else if (iter->second == _currentScene) return;

	if (_currentScene != NULL)
		_currentScene->release();

	OBJECTMANAGER->removeObjectsWithoutPlayer();

	_currentScene = iter->second;
	_currentScene->init();
}

scene * sceneManager::findScene(string sceneName)
{
	miScenes iter = _mScenes.find(sceneName);
	if (iter != _mScenes.end())
		return iter->second;
}
