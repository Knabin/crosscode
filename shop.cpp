#include "stdafx.h"
#include "shop.h"
#include "inventory.h"

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
	if (_shopOn)
	{
		switch (_type)
		{
		case 0:
		
			_itemName1 = L"±‚∫ªƒÆ";
			_itemType[0] = L"∆»";
			_itemNum[0] = 0;
			
			_itemName2 = L"¿Á∑·";
			_itemType[1] = L"∞≈∑°";
			_itemNum[1] = 0;
			
			_itemName3 = L"¿Á∑·2";
			_itemType[2] = L"∞≈∑°";
			_itemNum[2] = 1;
			
			_itemNum1 = L"1";
			_itemNum2 = L"2";
			_itemNum3 = L"2";
			break;
		
		case 1:
		
			_itemName1 = L"øœº∫«∞2";
			_itemType[0] = L"º’";
			_itemNum[0] = 1;
			
			_itemName2 = L"¿Á∑·3";
			_itemType[1] = L"∞≈∑°";
			_itemNum[1] = 2;
			
			_itemName3 = L"¿Á∑·4";
			_itemType[2] = L"∞≈∑°";
			_itemNum[2] = 3;
			
			_itemNum1 = L"1";
			_itemNum2 = L"2";
			_itemNum3 = L"1";
			break;
		
		case 2:
		
			_itemName1 = L"øœº∫«∞3";
			_itemType[0] = L"º’";
			_itemNum[0] = 2;
			
			_itemName2 = L"¿Á∑·4";
			_itemType[1] = L"∞≈∑°";
			_itemNum[1] = 4;
			
			_itemName3 = L"¿Á∑·5";
			_itemType[2] = L"∞≈∑°";
			_itemNum[2] = 5;
			
			_itemNum1 = L"1";
			_itemNum2 = L"1";
			_itemNum3 = L"1";
			
			break;
		
		default:
			break;
		}

	}
}

void shop::render()
{
	if (_shopOn)
	{
		IMAGEMANAGER->findImage("shopList")->render(Vector2());

		D2DRENDERER->RenderText(1230 - 80, 295, _itemName1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		D2DRENDERER->RenderText(1680 - 80, 295, _itemNum1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		D2DRENDERER->RenderText(1765 - 80, 295, _itemNum1M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		D2DRENDERER->RenderText(1230, 407, _itemName2, 35,D2DRenderer::DefaultBrush::White,DWRITE_TEXT_ALIGNMENT_LEADING,L"∏º¿∫∞ÌµÒBold");
		D2DRENDERER->RenderText(1680, 407, _itemNum2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		D2DRENDERER->RenderText(1765, 407, _itemNum2M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

		D2DRENDERER->RenderText(1230, 475, _itemName3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		D2DRENDERER->RenderText(1680, 475, _itemNum3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
		D2DRENDERER->RenderText(1765, 475, _itemNum3M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");
	}
	

}

void shop::shopOn(int type)
{
	_shopOn = true;
	_type = type;
}

void shop::setItemCount(int i, wstring count)
{
	switch (i)
	{
	case 0:
		_itemNum1M = count;
		break;
	case 1:
		_itemNum2M = count;
		break;
	case 2:
		_itemNum3M = count;
		break;
	default:
		break;
	}
}


