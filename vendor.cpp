#include "stdafx.h"
#include "vendor.h"
#include "player.h"

HRESULT vendor::init()
{
	_name = "vendor";
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	
	_image = IMAGEMANAGER->addFrameImage("vendor", L"images/object/vendor.png", 3, 1);
	_rc.update(_position, Vector2(_image->getFrameSize().x, _image->getFrameSize().y), pivot::CENTER);
	//_rc = RectMakePivot(floatPoint{ _x, _y }, floatPoint{ _image->getFrameWidth(), _image->getFrameHeight() }, pivot::CENTER);
	
	_iconNum = 0;
	_trigger = false;

	IMAGEMANAGER->addFrameImage("shopIcon", L"images/shop/shop_icon.png", 2, 1);

	return S_OK;
}

void vendor::release()
{

}

void vendor::update()
{
	POINT _ptUMouse;
	_ptUMouse.x = _ptMouse.x / CAMERA->getZoomAmount() + CAMERA->getRect().left;
	_ptUMouse.y = _ptMouse.y / CAMERA->getZoomAmount() + CAMERA->getRect().top;
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect().getRect(), &_rc.getRect()))
	{
		_iconNum = 0;
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_rc.getRect(), _ptUMouse))
		{
			_trigger = true;
			_player->setIdle();
		}
	}
	else
	{
		_iconNum = 1;
	}
}

void vendor::render()
{
	
	//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));
	_image->setSize(Vector2(_image->getFrameSize()) * CAMERA->getZoomAmount());
	_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), _type, 0);

	IMAGEMANAGER->findImage("shopIcon")->frameRender(Vector2(CAMERA->getRelativeVector2(_rc.getCenter()).x, CAMERA->getRelativeVector2(_rc.getCenter()).y - 60), _iconNum, 0);
}
