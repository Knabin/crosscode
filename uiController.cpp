#include "stdafx.h"
#include "uiController.h"
#include "gameObject.h"
#include "vendor.h"

HRESULT uiController::init()
{
	_vVendor = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "vendor");
	
	_nm = new nomalUI;
	_nm->init();

	_tu = new tabUI;
	_tu->init();

	scene = SCENEMANAGER->getCurrentSceneName();

	_shop = new shop;
	_shop->init();
	return S_OK;
}

void uiController::release()
{
	// OBJECTMANAGER¿¡¼­ release()ÇÔ

	_nm->release();
	_tu->release();
	_shop->release();
}

void uiController::update()
{
	if (scene != SCENEMANAGER->getCurrentSceneName())
	{
		_vVendor = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "vendor");
	}

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
		_shop->update();
	}

	if (_vVendor.size() != NULL)
	{
		for (int i = 0; i < _vVendor.size(); ++i)
		{
			if (_vVendor[i]->getTrigger())
			{
				_shop->shopOn(i);
				_uiOn = true;
				break;
			}
			
		}
	}

	if (_uiOn && KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		for (int i = 0; i < _vVendor.size(); ++i)
		{
			_vVendor[i]->setTrigger(false);
		}

		_uiOn = false;
		_shop->setShopOn(false);
		
	}

}

void uiController::render()
{
	if (scene != "title" && scene != "maptool" && scene != "loading" && !EVENTMANAGER->isPlayingEvent())
	{
		_nm->render();
		_tu->render();
		_shop->render();
	}
	for (int i = 0; i < _vUiObjects.size(); ++i)
	{
		if (!_vUiObjects[i]->getIsActive()) continue;
		_vUiObjects[i]->render();
	}
	
	
}
