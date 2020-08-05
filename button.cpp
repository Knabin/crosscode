#include "stdafx.h"
#include "button.h"

button::button()
{
}

button::~button()
{
}

HRESULT button::init(const char * imageName, float x, float y, int frameX, int frameY, function<void(void)> cbFunction)
{
	_callbackFunction = cbFunction;
	
	_direction = BUTTONDIRECTION::NONE;

	_x = x;
	_y = y;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	_framePoint.x = frameX;
	_framePoint.y = frameY;

	return S_OK;
}

void button::release()
{
}

void button::update()
{
	if (PtInRect(&_rc.getRect(), _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			_direction = BUTTONDIRECTION::DOWN;
		else if (_direction == BUTTONDIRECTION::DOWN && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION::UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION::NONE;
}

void button::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _framePoint.x, _framePoint.y);
}

void button::renderRelative(float x, float y)
{
	_image->frameRender(getMemDC(), x + _rc.left, y + _rc.top, _framePoint.x, _framePoint.y);
}
