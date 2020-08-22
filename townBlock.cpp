#include "stdafx.h"
#include "townBlock.h"
#include "player.h"

townBlock::~townBlock()
{
}

HRESULT townBlock::init()
{
	_img = IMAGEMANAGER->findImage("townblock");
	_isOpen = false;
	_rc = RectMakePivot(_position, _img->getSize() - Vector2(0, 100), pivot::CENTER);
	
	return S_OK;
}

void townBlock::release()
{
}

void townBlock::update()
{
	player* p = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	if (!_isOpen && isCollision(_rc, p->getRect()))
	{
		if (p->isDashing())
		{
			p->setPlayerPlusX(8.3f);
		}
		else
		{
			p->setPlayerPlusX(4.5f);
		}
	}

	if (EVENTMANAGER->getPuzzleEvent())
		_isOpen = true;
	
}

void townBlock::render()
{
	//D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_rc), D2D1::ColorF::DarkGoldenrod, 0);
	_img->frameRender(CAMERA->getRelativeVector2(_position), _isOpen, 0);
}
