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
	if (_type == 0)
	{
		_image = IMAGEMANAGER->addImage("wall1", L"images/tile/wallpreview.png");
	}
	else
	{
		_image = IMAGEMANAGER->addImage("wall2", L"images/tile/wall2preview.png");
	}
	_rc.update(_position, Vector2(_image->getSize().x, _image->getSize().y), pivot::CENTER);
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
	D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_rc), D2D1::ColorF::Azure, 0);
	_image->setSize(Vector2(_image->getSize()) * CAMERA->getZoomAmount());
	_image->render(CAMERA->getRelativeVector2(Vector2(_rc.left, _rc.top)));
}
