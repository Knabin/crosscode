#include "stdafx.h"
#include "vendor.h"

HRESULT vendor::init()
{
	_image = IMAGEMANAGER->addFrameImage("vendor", "images/object/vendor.bmp", 720, 288, 3, 1, true, RGB(255, 0, 255));
	_rc.set(0, 0, _image->getFrameWidth(), _image->getFrameHeight());
	_rc.setCenter(_x, _y);
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
	_rc.render(getMemDC());
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _type, 0);
}
