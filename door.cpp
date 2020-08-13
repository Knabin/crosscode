#include "stdafx.h"
#include "door.h"

HRESULT door::init()
{
	_image = IMAGEMANAGER->addFrameImage("vendor", "images/object/vendor.bmp", 720, 288, 3, 1, true, RGB(255, 0, 255));
	_rc.set(0, 0, _image->getFrameWidth(), _image->getFrameHeight());
	_rc.setCenter(_x, _y);
	return S_OK;
}

void door::release()
{
}

void door::update()
{
}

void door::render()
{
}
