#include "stdafx.h"
#include "uiController.h"
#include "gameObject.h"

HRESULT uiController::init()
{
	_nm = new nomalUI;
	_nm->init();
	return S_OK;
}

void uiController::release()
{
	// OBJECTMANAGER¿¡¼­ release()ÇÔ

	_nm->release();
}

void uiController::update()
{
	_vUiObjects = OBJECTMANAGER->getObjectList(objectType::UI);

	_nm->update();
}

void uiController::render()
{
	for (int i = 0; i < _vUiObjects.size(); ++i)
	{
		if (!_vUiObjects[i]->getIsActive()) continue;
		_vUiObjects[i]->renderRelative(CAMERA->getRect().left, CAMERA->getRect().top);
	}
	_nm->render();
}
