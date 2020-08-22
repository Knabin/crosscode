#include "stdafx.h"
#include "shop.h"
#include "inventory.h"

HRESULT shop::init()
{
	IMAGEMANAGER->addImage("shopList", L"images/shop/shopList.png");
	_shopOn = false;

	_it = new item;
	_it->init();
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
		
			_itemName1 = L"ºö¼Òµå";
			_itemType[0] = L"ÆÈ";
			_itemNum[0] = 1;
			
			_itemName2 = L"»Ô";
			_itemType[1] = L"°Å·¡";
			_itemNum[1] = 2;
			
			_itemName3 = L"°í½¿µÍÄ¡ ¹Ù´Ã";
			_itemType[2] = L"°Å·¡";
			_itemNum[2] = 0;
			
			_itemNum1 = L"1";
			_itemNum2 = L"2";
			_itemNum3 = L"3";
			break;
		
		case 1:
		
			_itemName1 = L"°í¼º´É Çìµå¼Â";
			_itemType[0] = L"¸Ó¸®";
			_itemNum[0] = 1;
			
			_itemName2 = L"Çìµå¼Â";
			_itemType[1] = L"°Å·¡";
			_itemNum[1] = 1;
			
			_itemName3 = L"°¡Á×";
			_itemType[2] = L"°Å·¡";
			_itemNum[2] = 5;
			
			_itemNum1 = L"1";
			_itemNum2 = L"1";
			_itemNum3 = L"3";
			break;
		
		case 2:
		
			_itemName1 = L"º» ¾Æ¸Ó";
			_itemType[0] = L"¸öÅë";
			_itemNum[0] = 1;
			
			_itemName2 = L"¼Ò »À";
			_itemType[1] = L"°Å·¡";
			_itemNum[1] = 3;
			
			_itemName3 = L"µÎ°³°ñ";
			_itemType[2] = L"°Å·¡";
			_itemNum[2] = 4;
			
			_itemNum1 = L"1";
			_itemNum2 = L"1";
			_itemNum3 = L"2";
			
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

		D2DRENDERER->RenderText(1230 - 80, 295, _itemName1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
		D2DRENDERER->RenderText(1680 - 80, 295, _itemNum1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
		D2DRENDERER->RenderText(1765 - 80, 295, _itemNum1M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

		D2DRENDERER->RenderText(1230, 407, _itemName2, 35,D2DRenderer::DefaultBrush::White,DWRITE_TEXT_ALIGNMENT_LEADING,L"¸¼Àº°íµñBold");
		D2DRENDERER->RenderText(1680, 407, _itemNum2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
		D2DRENDERER->RenderText(1765, 407, _itemNum2M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

		D2DRENDERER->RenderText(1230, 475, _itemName3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
		D2DRENDERER->RenderText(1680, 475, _itemNum3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
		D2DRENDERER->RenderText(1765, 475, _itemNum3M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

		switch (_type)
		{
		case 0:
			IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1123, 320), 1, 0, 0.8f);
			{
				wstring Num = to_wstring(_it->getItemInfo(L"ÆÈ", 1).price);
				D2DRENDERER->RenderText(1275 , 557, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

				Num = to_wstring(_inven->getMoney() - _it->getItemInfo(L"ÆÈ", 1).price);
				if (_inven->getMoney() < _it->getItemInfo(L"ÆÈ", 1).price)
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				}
				else
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				}
				D2DRENDERER->RenderText(1325, 700, L"°ø°Ý·Â 15 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				D2DRENDERER->RenderText(1325, 750, L"Å©¸®Æ¼ÄÃ 10 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				floatRect rc;
				rc.update(Vector2(1455, 895), Vector2(200, 85), pivot::CENTER);

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc.getRect(), _ptMouse))
				{
					if (_inven->getMoney() >= _it->getItemInfo(L"ÆÈ", 1).price
						&& _inven->getCount(L"°Å·¡",2) >= 2 && _inven->getCount(L"°Å·¡", 0) >= 3)
					{
						_inven->getItem(L"ÆÈ", 1, 1, true);
						_inven->deleteItem(L"°Å·¡", 2);
						_inven->deleteItem(L"°Å·¡", 2);
						_inven->deleteItem(L"°Å·¡", 0);
						_inven->deleteItem(L"°Å·¡", 0);
						_inven->deleteItem(L"°Å·¡", 0);
					}
				}
			}
			break;
		case 1:
			IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1123, 320), 0, 0, 0.8f);
			{
				wstring Num = to_wstring(_it->getItemInfo(L"¸Ó¸®", 1).price);
				D2DRENDERER->RenderText(1275, 557, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

				Num = to_wstring(_inven->getMoney() - _it->getItemInfo(L"¸Ó¸®", 1).price);
				if (_inven->getMoney() < _it->getItemInfo(L"¸Ó¸®", 1).price)
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				}
				else
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				}

				D2DRENDERER->RenderText(1325, 700-30, L"Ã¼·Â 10 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				D2DRENDERER->RenderText(1325, 750-30, L"¹æ¾î·Â 10 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				D2DRENDERER->RenderText(1325, 800-30, L"¾óÀ½ÀúÇ×·Â 10 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				floatRect rc;
				rc.update(Vector2(1455, 895), Vector2(200, 85), pivot::CENTER);

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc.getRect(), _ptMouse))
				{
					if (_inven->getMoney() >= _it->getItemInfo(L"¸Ó¸®", 1).price
						&& _inven->getCount(L"°Å·¡", 1) >= 1 && _inven->getCount(L"°Å·¡", 5) >= 3)
					{
						_inven->getItem(L"¸Ó¸®", 1, 1, true);
						_inven->deleteItem(L"°Å·¡", 1);
						_inven->deleteItem(L"°Å·¡", 5);
						_inven->deleteItem(L"°Å·¡", 5);
						_inven->deleteItem(L"°Å·¡", 5);
					}
				}
			}
			break;
		case 2:
			IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1123, 320), 2, 0, 0.8f);
			{
				wstring Num = to_wstring(_it->getItemInfo(L"¸öÅë", 1).price);
				D2DRENDERER->RenderText(1275, 557, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

				Num = to_wstring(_inven->getMoney() - _it->getItemInfo(L"¸öÅë", 1).price);
				if (_inven->getMoney() < _it->getItemInfo(L"¸öÅë", 1).price)
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				}
				else
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				}
				


				D2DRENDERER->RenderText(1325, 650, L"Ã¼·Â 10 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				D2DRENDERER->RenderText(1325, 685, L"¹æ¾î·Â 10 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				D2DRENDERER->RenderText(1325, 720, L"Å©¸®Æ¼ÄÃ 10 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				D2DRENDERER->RenderText(1325, 755 , L"Àü±âÀúÇ×·Â 5 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");
				D2DRENDERER->RenderText(1325, 790 , L"ÆÄµ¿ÀúÇ×·Â 5 Áõ°¡", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"¸¼Àº°íµñBold");

				floatRect rc;
				rc.update(Vector2(1455, 895), Vector2(200, 85), pivot::CENTER);

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc.getRect(), _ptMouse))
				{
					if (_inven->getMoney() >= _it->getItemInfo(L"¸öÅë", 1).price
						&& _inven->getCount(L"°Å·¡", 3) >= 1 && _inven->getCount(L"°Å·¡", 4) >= 2)
					{
						_inven->getItem(L"¸öÅë", 1, 1, true);
						_inven->deleteItem(L"°Å·¡", 3);
						_inven->deleteItem(L"°Å·¡", 4);
						_inven->deleteItem(L"°Å·¡", 4);
					}
				}
			}
			break;
		}
		
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


