#include "stdafx.h"
#include "foothold.h"

HRESULT foothold::init()
{
	_name = "foothold";
	_image = IMAGEMANAGER->addFrameImage("foothold", L"images/object/foothold.png", 3, 1);
	_isOn = false;
	_isStepOn = false;
	_count = 0;

	return S_OK;
}

void foothold::release()
{
}

void foothold::update()
{
	if (isCollision(_rc, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getRect()))
	{
		_isStepOn = true;
		_count++;
		// 만약 아이템을 못 먹었으면 아이템 먹는 처리
	}
	else
	{
		_isStepOn = false;
		_count = 0;
	}
}

void foothold::render()
{
	if (_isOn)
	{
		if (_isStepOn)
			_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), 2, 0);
		else 
			_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), 1, 0);
	}
	else
		_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), 0, 0);
}
