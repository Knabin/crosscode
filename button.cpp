#include "stdafx.h"
#include "button.h"

button::button()
{
}

button::~button()
{
}

HRESULT button::init(const char * imageName, float x, float y, int frameX, int frameY, int frameDownX, int frameDownY, function<void(void)> cbFunction)
{
	_callbackFunction = cbFunction;
	
	_direction = BUTTONDIRECTION::NONE;

	_x = x;
	_y = y;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	_frameUpPoint.x = frameX;
	_frameUpPoint.y = frameY;

	_frameDownPoint.x = frameDownX;
	_frameDownPoint.y = frameDownY;

	IMAGEMANAGER->addFrameImage("select", "images/title/select.bmp", 481, 660, 1, 10, true, RGB(255, 0, 255));

	_select = new animation;
	_select->init(IMAGEMANAGER->findImage("select")->getWidth(), IMAGEMANAGER->findImage("select")->getHeight(), IMAGEMANAGER->findImage("select")->getFrameWidth(), IMAGEMANAGER->findImage("select")->getFrameHeight());
	_select->setPlayFrame(0, 10, false, false);
	_select->setFPS(1);
	
	_selectOn = false;

	return S_OK;
}

void button::release()
{
}

void button::update()
{
	_select->frameUpdate(TIMEMANAGER->getElapsedTime() * 30);
	if (PtInRect(&_rc.getRect(), _ptMouse))
	{
		if (_imageName == "buttons")
		{
			if (!_selectOn)
				_select->start();
			_selectOn = true;
		}
		
		
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			_direction = BUTTONDIRECTION::DOWN;
		else if (_direction == BUTTONDIRECTION::DOWN && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION::UP;
			_callbackFunction();
		}

	}
	else
	{
		if (_imageName == "buttons")
		_selectOn = false;
		_direction = BUTTONDIRECTION::NONE;
	}
}

void button::render()
{
	switch (_direction)
	{
	case BUTTONDIRECTION::NONE:	case BUTTONDIRECTION::UP:
		_image->frameRender(getMemDC(), _rc.left, _rc.top,
			_frameUpPoint.x, _frameUpPoint.y);
		break;
	case BUTTONDIRECTION::DOWN:
		_image->frameRender(getMemDC(), _rc.left, _rc.top,
			_frameDownPoint.x, _frameDownPoint.y);
		break;
	}
}

void button::renderRelative(float x, float y)
{
	switch (_direction)
	{
	case BUTTONDIRECTION::NONE:	case BUTTONDIRECTION::UP:
		_image->frameRender(getMemDC(), _rc.left + x, _rc.top + y,
			_frameUpPoint.x, _frameUpPoint.y);
		break;
	case BUTTONDIRECTION::DOWN:
		_image->frameRender(getMemDC(), _rc.left + x, _rc.top + y,
			_frameDownPoint.x, _frameDownPoint.y);
		break;
	}

	if (PtInRect(&_rc.getRect(), _ptMouse) &&_imageName == "buttons")
	{
		IMAGEMANAGER->findImage("select")->aniRender(getMemDC(), _rc.left, _rc.top, _select);
	}
}
