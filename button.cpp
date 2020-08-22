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

	_position = Vector2(x, y);

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc.update(Vector2(x, y), Vector2(_image->getFrameSize()), pivot::CENTER);

	_width = _rc.GetWidth();
	_height = _rc.GetHeight();

	_frameUpPoint.x = frameX;
	_frameUpPoint.y = frameY;

	_frameDownPoint.x = frameDownX;
	_frameDownPoint.y = frameDownY;

	IMAGEMANAGER->addFrameImage("select", L"images/title/select.png", 1, 10);

	_select = new animation;
	_select->init(IMAGEMANAGER->findImage("select")->getSize().x, IMAGEMANAGER->findImage("select")->getSize().y, 
		IMAGEMANAGER->findImage("select")->getFrameSize().x, IMAGEMANAGER->findImage("select")->getFrameSize().y);
	_select->setPlayFrame(0, 9, false, false);
	_select->setFPS(1);
	
	_selectOn = false;
	_index = _time = 0;
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
			{
				_select->start();
				SOUNDMANAGER->play("button hover");
			}
			_selectOn = true;
		}
		
		
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION::DOWN;
		}
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
		_index = 0;
	}

	_time++;

	if (_time % 1 == 0)
	{
		if(_index < 9)
		_index++;
		_time = 0;
	}
}

void button::render()
{
	D2DRENDERER->DrawRotationFillRectangle(_rc, D2D1::ColorF::AliceBlue, 0);
	switch (_direction)
	{
	case BUTTONDIRECTION::NONE:	case BUTTONDIRECTION::UP:
		_image->frameRender(Vector2(_rc.getCenter()),
			_frameUpPoint.x, _frameUpPoint.y);
		break;
	case BUTTONDIRECTION::DOWN:
		_image->frameRender(Vector2(_rc.getCenter()),
			_frameDownPoint.x, _frameDownPoint.y);
		break;
	}

	if (PtInRect(&_rc.getRect(), _ptMouse) && _imageName == "buttons")
	{
		IMAGEMANAGER->findImage("select")->frameRender(Vector2(_rc.getCenter()), 0 , _index , 1.f);
	}
}

void button::renderRelative(float x, float y)
{
	switch (_direction)
	{
	case BUTTONDIRECTION::NONE:	case BUTTONDIRECTION::UP:
		_image->frameRender(Vector2(_rc.left + x, _rc.top + y),
			_frameUpPoint.x, _frameUpPoint.y);
		break;
	case BUTTONDIRECTION::DOWN:
		_image->frameRender(Vector2(_rc.left + x, _rc.top + y),
			_frameDownPoint.x, _frameDownPoint.y);
		break;
	}


}
