#include "stdafx.h"
#include "shop.h"

HRESULT shop::init()
{
	IMAGEMANAGER->addImage("shopList", L"images/shop/shopList.png");
	_shopOn = false;
	return S_OK;
}

void shop::release()
{
}

void shop::update()
{
}

void shop::render()
{
	if (_shopOn)
	{
		switch (_type)
		{
		case 0:
		{
			char str[100];
			sprintf_s(str, "æ∆¿Ã≈€");
			string strr;
			strr = str;
			wstring sstr;
			sstr.assign(strr.begin(), strr.end());

			IMAGEMANAGER->findImage("shopList")->render(Vector2());
			D2DRENDERER->RenderText(500, 500, sstr, 50);
			break;
		}
		case 1:
		{
			char str[100];
			sprintf_s(str, "æ∆¿Ã≈€");
			string strr;
			strr = str;
			wstring sstr;
			sstr.assign(strr.begin(), strr.end());

			IMAGEMANAGER->findImage("shopList")->render(Vector2());
			D2DRENDERER->RenderText(500, 500, sstr, 50);
			break;
		}
		case 2:
		{
			
			wstring sstr = L"∫“≤…";
			

			IMAGEMANAGER->findImage("shopList")->render(Vector2());
			D2DRENDERER->RenderText(500, 500, sstr, 50,D2DRenderer::DefaultBrush::Black,DWRITE_TEXT_ALIGNMENT_LEADING,L"∏º¿∫∞ÌµÒBold");
				
			break;
		}
		default:
			break;
		}
		
	}
	

}

void shop::shopOn(int type)
{
	_shopOn = true;
	_type = type;
}