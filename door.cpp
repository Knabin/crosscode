#include "stdafx.h"
#include "door.h"

HRESULT door::init()
{
	_name = "door";
	_image = IMAGEMANAGER->addFrameImage("door", L"images/object/door.png", 4, 2);
	_rc.update(_position, _image->getFrameSize(), pivot::CENTER);
	_moveRect.update(_position + Vector2(0, 20), Vector2(50, 50), pivot::CENTER);

	_frameX = 0;
	_isOpen = false;
	_frameCount = 0;

	switch (_type)
	{
	case 0:
		//_nextSceneName = ""
		break;
	case 1:
		break;
	}
	return S_OK;
}

void door::release()
{
}

void door::update()
{
	_frameCount++;
	if (_isOpen)
	{
		// 여기서 갈 수 있다면 프레임 렌더! 문 열리게끔
		if (_frameCount % 5 == 0)
		{
			if (_frameX < _image->getMaxFrameX() - 1) ++_frameX;
			_frameCount = 0;
		}
	}
	else
	{
		if (_frameCount % 5 == 0)
		{
			if (_frameX != 0)
				--_frameX;
			_frameCount = 0;
		}
	}
}

void door::render()
{
	if (_type == 1) _image->setAlpha(0.5f);
	_image->frameRender(CAMERA->getRelativeVector2(_position), _frameX, _type);
	//D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_moveRect), D2D1::ColorF::Beige, 0);
}
