#include "stdafx.h"
#include "puzzleOrangeWall.h"

puzzleOrangeWall::puzzleOrangeWall(int type)
	: _type(type)
{
}

puzzleOrangeWall::~puzzleOrangeWall()
{
}

HRESULT puzzleOrangeWall::init()
{
	_name = "puzzleOrangeWall";
	_frameX = 0;
	if (_type == 0)
	{
		_image = IMAGEMANAGER->addFrameImage("wall3", L"images/tile/wall3preview.png", 1, 1);
	}
	else
	{
		_image = IMAGEMANAGER->addFrameImage("wall4", L"images/object/wall_orange.png", 10, 1);
		_position.x -= 24;
	}
	_count = 0;
	_rc.update(_position, Vector2(_image->getFrameSize().x, _image->getFrameSize().y), pivot::CENTER);
	return S_OK;
}

void puzzleOrangeWall::release()
{
}

void puzzleOrangeWall::update()
{
	/*
	if (_type != 0)
	{
		_count++;

		if (_count > 5 && _frameX < _image->getMaxFrameX() - 1)
		{
			_frameX += 1;
			_count = 0;
		}
	}
	*/
}

void puzzleOrangeWall::render()
{
	//D2DRENDERER->DrawRotationFillRectangle(CAMERA->getRelativeRect(_rc), D2D1::ColorF::Azure, 0);
	_image->setSize(Vector2(_image->getFrameSize()) * CAMERA->getZoomAmount());
	_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), _frameX, 0);
}
