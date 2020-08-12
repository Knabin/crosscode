#include "stdafx.h"
#include "mapObject.h"

mapObject::mapObject(int type, int frameX)
	: _type(type), _frameX(frameX)
{
}

HRESULT mapObject::init()
{
	IMAGEMANAGER->addFrameImage("tree", "images/object/tree.bmp", 720, 288, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grass", "images/object/grass.bmp", 432, 96, 3, 1, true, RGB(255, 0, 255));

	switch (_type)
	{
	case TREE:
		_image = IMAGEMANAGER->findImage("tree");
		
		break;
	case GRASS:
		_image = IMAGEMANAGER->findImage("grass");
		break;
	}

	_rc.set(0, 0, _image->getFrameWidth(), _image->getFrameHeight());
	_rc.setCenter(_x, _y);
	return S_OK;
}

void mapObject::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0);
}
