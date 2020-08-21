#include "stdafx.h"
#include "foothold.h"

HRESULT foothold::init()
{
	_name = "foothold";
	_image = IMAGEMANAGER->addFrameImage("foothold", L"images/object/foothold.png", 3, 1);
	_isOn = true;
	_isStepOn = false;
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
		// ���� �������� �� �Ծ����� ������ �Դ� ó��
	}
	else
		_isStepOn = false;
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
