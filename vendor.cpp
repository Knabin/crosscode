#include "stdafx.h"
#include "vendor.h"

HRESULT vendor::init()
{
	_image = IMAGEMANAGER->addFrameImage("vendor", L"images/object/vendor.png", 3, 1);
	_rc.update(_position, Vector2(_image->getFrameSize().x, _image->getFrameSize().y), pivot::CENTER);
	//_rc = RectMakePivot(floatPoint{ _x, _y }, floatPoint{ _image->getFrameWidth(), _image->getFrameHeight() }, pivot::CENTER);

	return S_OK;
}

void vendor::release()
{
}

void vendor::update()
{
}

void vendor::render()
{
	_image->setSize(Vector2(_image->getFrameSize()) * CAMERA->getZoomAmount());
	_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), _type, 0);
}
