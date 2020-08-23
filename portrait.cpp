#include "stdafx.h"
#include "portrait.h"

portrait::portrait(int type)
	: _type(type)
{
}

HRESULT portrait::init()
{
	setType(_type);
	return S_OK;
}

void portrait::update()
{
}

void portrait::render()
{
	_img->render(_position);
}

// ���α׷��� - 0: �Ϲ�, 2: �Ȱ�, 4: ȭ��, 6: ����, 8: ���
// ���� - 1: �Ϲ�, 3: �� ���, 5: ���, 7: ����, 9: �Ѥ�
void portrait::setType(int type)
{
	_type = type;
	switch (_type)
	{
	case 0:
		_img = IMAGEMANAGER->addImage("pro", L"images/portrait/pro.png");
		_position = Vector2(200, 600);
		break;
	case 1:
		_img = IMAGEMANAGER->addImage("lea", L"images/portrait/lea.png");
		_position = Vector2(1500, 650);
		break;
	case 2:
		_img = IMAGEMANAGER->addImage("pro2", L"images/portrait/pro2.png");
		_position = Vector2(200, 600);
		break;
	case 3:
		_img = IMAGEMANAGER->addImage("lea2", L"images/portrait/lea2.png");
		_position = Vector2(1500, 650);
		break;
	case 4:
		_img = IMAGEMANAGER->addImage("pro3", L"images/portrait/pro3.png");
		_position = Vector2(200, 600);
		break;
	case 5:
		_img = IMAGEMANAGER->addImage("lea3", L"images/portrait/lea3.png");
		_position = Vector2(1500, 650);
		break;
	case 6:
		_img = IMAGEMANAGER->addImage("pro4", L"images/portrait/pro4.png");
		_position = Vector2(200, 600);
		break;
	case 7:
		_img = IMAGEMANAGER->addImage("lea4", L"images/portrait/lea4.png");
		_position = Vector2(1500, 650);
		break;
	case 8:
		_img = IMAGEMANAGER->addImage("pro5", L"images/portrait/pro5.png");
		_position = Vector2(200, 600);
		break;
	case 9:
		_img = IMAGEMANAGER->addImage("lea5", L"images/portrait/lea5.png");
		_position = Vector2(1500, 650);
		break;
	}
}
