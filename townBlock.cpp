#include "stdafx.h"
#include "townBlock.h"

townBlock::~townBlock()
{
}

HRESULT townBlock::init()
{
	_img = IMAGEMANAGER->findImage("townblock");
	_isOpen = false;
	_rc = RectMakePivot(_position, _img->getSize(), pivot::CENTER);

	return S_OK;
}

void townBlock::release()
{
}

void townBlock::update()
{
	if (!_isOpen)
	{
		if (isCollisionReaction(_rc, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getRect()))
		{

		}
	}
}

void townBlock::render()
{
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_rc), D2D1::ColorF::DarkGoldenrod, 0);
	_img->frameRender(CAMERA->getRelativeVector2(_position), _isOpen, 0);
}
