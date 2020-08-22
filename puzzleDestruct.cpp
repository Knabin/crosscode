#include "stdafx.h"
#include "puzzleDestruct.h"

puzzleDestruct::~puzzleDestruct()
{
}

HRESULT puzzleDestruct::init()
{
	_name = "puzzleDestruct";
	_count = 0;
	_hp = 50;
	_image = IMAGEMANAGER->addImage("destruct", L"images/object/destruct.png");
	IMAGEMANAGER->addFrameImage("destructExplosion", L"images/object/destructExplosion.png", 7, 1);
	EFFECTMANAGER->addEffect("destructExplosion", "destructExplosion", 1.0f, 0.5f, 5, 1.0f);
	_rc.update(_position, _image->getSize(), pivot::CENTER);
	return S_OK;
}

void puzzleDestruct::release()
{
}

void puzzleDestruct::update()
{
	if (_hp <= 0)
	{
		if (_count <= 50)
		{
			EFFECTMANAGER->play("destructExplosion", Vector2(CAMERA->getRelativeVector2(_rc.getCenter()).x + 50, CAMERA->getRelativeVector2(_rc.getCenter()).y + 50));//Æø¹ßÀÌÆåÆ®
			_count++;
		}

		_rc.update(Vector2(0, 0), Vector2(0, 0), pivot::CENTER);
	}
}

void puzzleDestruct::render()
{
	//D2DRENDERER->DrawRotationFillRectangle(
	//	CAMERA->getRelativeRect(_rc), D2D1::ColorF::AliceBlue, 0);
	_image->setSize(Vector2(_image->getSize()) * CAMERA->getZoomAmount());
	_image->render(CAMERA->getRelativeVector2(Vector2(_rc.left, _rc.top)));
}
