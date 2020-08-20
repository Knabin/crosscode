#include "stdafx.h"
#include "uiController.h"
#include "gameObject.h"

HRESULT uiController::init()
{
	_nm = new nomalUI;
	_nm->init();

	_tu = new tabUI;
	_tu->init();

	scene = SCENEMANAGER->getCurrentSceneName();

	
	return S_OK;
}

void uiController::release()
{
	// OBJECTMANAGER¿¡¼­ release()ÇÔ

	_nm->release();
	_tu->release();
}

void uiController::update()
{
	scene = SCENEMANAGER->getCurrentSceneName();
	_vUiObjects = OBJECTMANAGER->getObjectList(objectType::UI);

	for (int i = 0; i < _vUiObjects.size(); ++i)
	{
		if (_vUiObjects[i]->getIsActive())
		{
			_vUiObjects[i]->update();
		}
	}

	if (scene != "title" && scene != "maptool" && !EVENTMANAGER->isPlayingEvent())
	{
		_nm->update();
		_tu->update();
	}

}

void uiController::render()
{
	if (scene != "title" && scene != "maptool" && scene != "loading" && !EVENTMANAGER->isPlayingEvent())
	{
		_nm->render();
		_tu->render();
	}
	for (int i = 0; i < _vUiObjects.size(); ++i)
	{
		if (!_vUiObjects[i]->getIsActive()) continue;
		_vUiObjects[i]->render();
	}
	
}
