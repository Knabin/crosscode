#include "stdafx.h"
#include "mapObject.h"

mapObject::mapObject(int type, int frameX)
	: _type(type), _frameX(frameX)
{
}

HRESULT mapObject::init()
{
	IMAGEMANAGER->addFrameImage("tree", L"images/object/tree.png", 3, 1);
	IMAGEMANAGER->addFrameImage("grass", L"images/object/grass.png", 3, 1);
	IMAGEMANAGER->addFrameImage("roof", L"images/object/test.png", 1, 1);

	switch (_type)
	{
	case TREE:
		_image = IMAGEMANAGER->findImage("tree");
		
		break;
	case GRASS:
		_image = IMAGEMANAGER->findImage("grass");
		break;
	case ROOF:
		_image = IMAGEMANAGER->findImage("roof");
			break;
	}

	_rc.update(_position, Vector2(_image->getFrameSize().x, _image->getFrameSize().y), pivot::CENTER);
	return S_OK;
}

void mapObject::render()
{
	//D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_rc), D2D1::ColorF::BlanchedAlmond, 0);
	_image->setSize(Vector2(_image->getFrameSize()) * CAMERA->getZoomAmount());
	
	RECT temp;
	if (_type == ROOF && IntersectRect(&temp, &_rc.getRect(), &OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getRect().getRect()))
	{
		_image->setAlpha(0.3f);
	}
	_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), _frameX, 0);
}
