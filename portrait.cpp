#include "stdafx.h"
#include "portrait.h"

portrait::portrait(int type)
{
	if (type == 0)
	{
		// pro
		_img = IMAGEMANAGER->addImage("pro", L"images/portrait/pro.png");
		_position = Vector2(200, 600);
	}
	else
	{
		// lea
		_img = IMAGEMANAGER->addImage("lea", L"images/portrait/lea.png");
		_position = Vector2(1500, 650);
	}
}

HRESULT portrait::init()
{
	return S_OK;
}

void portrait::render()
{
	_img->render(_position);
}
