#include "stdafx.h"
#include "puzzleTabButton.h"

puzzleTabButton::~puzzleTabButton()
{
}

HRESULT puzzleTabButton::init()
{
	_name = "puzzleTabButton";

	_frameX = _frameY = 0;

	_image = IMAGEMANAGER->addFrameImage("puzzle", L"images/object/button.png", 12, 3);
	_rc.update(_position, Vector2(_image->getFrameSize().x, _image->getFrameSize().y), pivot::CENTER);
	return S_OK;
}

void puzzleTabButton::release()
{
}

void puzzleTabButton::update()
{
}

void puzzleTabButton::render()
{
	_image->setSize(Vector2(_image->getFrameSize()) * CAMERA->getZoomAmount());
	_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), _frameX, _frameY);
}
