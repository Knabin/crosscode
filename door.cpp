#include "stdafx.h"
#include "door.h"

HRESULT door::init()
{
	_image = IMAGEMANAGER->addFrameImage("door", L"images/tile/doorpreview.png", 3, 1);
	_rc.update(_position, _image->getFrameSize(), pivot::CENTER);
	_moveRect.update(_position + Vector2(0, 20), Vector2(50, 50), pivot::CENTER);

	switch (_type)
	{
	case 0:
		//_nextSceneName = ""
		break;
	case 1:
		break;
	case 2:
		break;
	}
	return S_OK;
}

void door::release()
{
}

void door::update()
{

	if (isCollision(_moveRect, OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getRect()))
	{
		// 여기서 갈 수 있다면 프레임 렌더! 문 열리게끔
	}
}

void door::render()
{
	if (_type == 1)
		_image->setAlpha(0.5f);
	_image->frameRender(CAMERA->getRelativeVector2(_position), _type, 0);
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_moveRect), D2D1::ColorF::Beige, 0);
}
