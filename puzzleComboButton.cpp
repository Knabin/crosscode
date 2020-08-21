#include "stdafx.h"
#include "puzzleComboButton.h"

puzzleComboButton::~puzzleComboButton()
{
}

HRESULT puzzleComboButton::init()
{
	_name = "puzzleComboButton";

	_image = IMAGEMANAGER->addFrameImage("puzzle2", L"images/object/button2.png", 14, 1);
	_rc.update(_position, Vector2(_image->getFrameSize().x, _image->getFrameSize().y), pivot::CENTER);
	
	return S_OK;
}

void puzzleComboButton::release()
{
}

void puzzleComboButton::update()
{
}

void puzzleComboButton::render()
{
	_image->setSize(Vector2(_image->getFrameSize()) * CAMERA->getZoomAmount());
	_image->frameRender(CAMERA->getRelativeVector2(_rc.getCenter()), 0, 0);
}
