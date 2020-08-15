#include "stdafx.h"
#include "door.h"

HRESULT door::init()
{
	_image = IMAGEMANAGER->addFrameImage("vendor", L"images/object/vendor.png", 3, 1);
	_rc.update(_position, _image->getFrameSize(), pivot::CENTER);
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
