#include "stdafx.h"
#include "dialogText.h"

dialogText::dialogText(wstring str, int type)
	: _str(str), _type(type)
{
}

HRESULT dialogText::init()
{
	if (_type % 2 == 0)
	{
		// ¿ÞÂÊ
		_img = IMAGEMANAGER->addImage("left d", L"images/UI/left-2.png");
		_rc = RectMakePivot(Vector2(300, 800), Vector2(500, 120), pivot::LEFTTOP);
	}
	else
	{
		_img = IMAGEMANAGER->addImage("right d", L"images/UI/right-2.png");
		_rc = RectMakePivot(Vector2(700, 800), Vector2(500, 120), pivot::LEFTTOP);
	}
	return S_OK;
}

void dialogText::release()
{
}

void dialogText::update()
{
	_textCount++;
	if (_textCount % 2 == 0)
	{
		if (_textIndex < _str.size())
		{
			_textIndex++;
			SOUNDMANAGER->play("dialog");
		}
		
	}
}

void dialogText::render()
{
	_img->render(_rc.getCenter());

	wstring temp = L"";
	for (int i = 0; i <= _textIndex; ++i)
	{
		temp += _str[i];
	}

	if (_type % 2 == 0)
		D2DRENDERER->RenderTextField(_rc.getCenter().x + 40, _rc.getCenter().y, temp, 30, _rc.getSize().x, _rc.getSize().y, D2DRenderer::DefaultBrush::White);
	else 
		D2DRENDERER->RenderTextField(_rc.getCenter().x + 20, _rc.getCenter().y, temp, 30, _rc.getSize().x, _rc.getSize().y, D2DRenderer::DefaultBrush::White);
	//D2DRENDERER->AddTextBoldFormat(_str, 30);
}
