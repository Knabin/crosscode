#include "stdafx.h"
#include "puzzleBlueWall.h"

puzzleBlueWall::puzzleBlueWall(int type)
	: _type(type)
{
}

puzzleBlueWall::~puzzleBlueWall()
{
}

HRESULT puzzleBlueWall::init()
{
	_name = "puzzleBlueWall";

	_frameX = 0;

	if (_type == 0)
	{
		_image = IMAGEMANAGER->addFrameImage("wall1", L"images/tile/wallpreview.png", 1, 1);
	}
	else
	{
		_image = IMAGEMANAGER->addFrameImage("wall2", L"images/object/wall_blue.png", 8, 1);
	}
	_rc.update(Vector2(_position.x, _position.y + 50), Vector2(_image->getFrameSize().x, _image->getFrameSize().y), pivot::CENTER);
	return S_OK;
}

void puzzleBlueWall::release()
{
}

void puzzleBlueWall::update()
{
}

void puzzleBlueWall::render()
{
	//D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_rc), D2D1::ColorF::Azure, 0);
	_image->setSize(Vector2(_image->getFrameSize()) * CAMERA->getZoomAmount());
	_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _frameX, 0);
	//_image->render(CAMERA->getRelativeVector2(Vector2(_rc.left, _rc.top)));
}
