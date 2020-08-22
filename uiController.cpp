#include "stdafx.h"
#include "uiController.h"
#include "gameObject.h"
#include "vendor.h"
#include "loadUI.h"

HRESULT uiController::init()
{
	_vVendor = OBJECTMANAGER->findObjects(objectType::MAPOBJECT, "vendor");
	
	_nm = new nomalUI;
	_nm->init();

	_tu = new tabUI;
	_tu->init();

	scene = SCENEMANAGER->getCurrentSceneName();

	_inven = new inventory;
	_inven->init();
	OBJECTMANAGER->addObject(objectType::UI, _inven);

	_shop = new shop;
	_shop->init();

	_tu->setInventory(_inven);
	_shop->setInventory(_inven);

	loadUI* _lu = new loadUI;
	_lu->init();
	_lu->setTabUI(_tu);
	_lu->setInventory(_inven);

	return S_OK;
}

void uiController::release()
{
	// OBJECTMANAGER¿¡¼­ release()ÇÔ

	_nm->release();
	_tu->release();
	_shop->release();
	_inven->release();
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

	if (scene != L"title" && scene != L"maptool" && !EVENTMANAGER->isPlayingEvent())
	{
		_nm->update();
		if (!_uiOn)
		_tu->update();
		_shop->update();
		_inven->update();
	}

	if (_vVendor.size() != NULL)
	{
		for (int i = 0; i < _vVendor.size(); ++i)
		{
			if (_vVendor[i]->getTrigger())
			{
				_shop->shopOn(i);
				for (int j = 0; j < 3; ++j)
				{
					wstring tp = _shop->getItemType(j);
					int num = _shop->getItemNum(j);

					int counting = 0;

					for (int k = 0; k < _inven->getInven().size(); ++k)
					{
						if (_inven->getInven()[k].type == tp && _inven->getInven()[k].itemNum == num)
						{
							wstring numm = to_wstring(_inven->getInven()[k].count);
							_shop->setItemCount(j, numm);
							break;
						}
						counting++;
					}

					if (counting >= _inven->getInven().size())
					{
						_shop->setItemCount(j, L"0");
					}
				}
				_uiOn = true;
				break;
			}
			
		}
	}

	
	if (_uiOn && (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) || KEYMANAGER->isOnceKeyDown(VK_RBUTTON)))
	{
		for (int i = 0; i < _vVendor.size(); ++i)
		{
			_vVendor[i]->setTrigger(false);
		}

		_uiOn = false;
		_shop->setShopOn(false);
		
	}

	if (_tu->getOn())
	{
		_tu->setInven(_inven->getInven());
	}

}

void uiController::render()
{
	if (scene != L"title" && scene != L"maptool" && scene != L"loading" && !EVENTMANAGER->isPlayingEvent())
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
