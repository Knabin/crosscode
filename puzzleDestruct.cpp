#include "stdafx.h"
#include "puzzleDestruct.h"

puzzleDestruct::~puzzleDestruct()
{
}

HRESULT puzzleDestruct::init()
{
	_image = IMAGEMANAGER->addImage("destruct", L"images/object/destruct.png");
	_rc.update(_position, _image->getSize(), pivot::CENTER);
	return S_OK;
}

void puzzleDestruct::release()
{
}

void puzzleDestruct::update()
{
}

void puzzleDestruct::render()
{
	D2DRENDERER->DrawRotationFillRectangle(
		CAMERA->getRelativeRect(_rc), D2D1::ColorF::AliceBlue, 0);
	_image->setSize(Vector2(_image->getSize()) * CAMERA->getZoomAmount());
	_image->render(CAMERA->getRelativeVector2(Vector2(_rc.left, _rc.top)));
}
