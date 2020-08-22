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
		
			_itemName1 = L"���ҵ�";
			_itemType[0] = L"��";
			_itemNum[0] = 1;
			
			_itemName2 = L"��";
			_itemType[1] = L"�ŷ�";
			_itemNum[1] = 2;
			
			_itemName3 = L"����ġ �ٴ�";
			_itemType[2] = L"�ŷ�";
			_itemNum[2] = 0;
			
			_itemNum1 = L"1";
			_itemNum2 = L"2";
			_itemNum3 = L"3";
			break;
		
		case 1:
		
			_itemName1 = L"���� ����";
			_itemType[0] = L"�Ӹ�";
			_itemNum[0] = 1;
			
			_itemName2 = L"����";
			_itemType[1] = L"�ŷ�";
			_itemNum[1] = 1;
			
			_itemName3 = L"����";
			_itemType[2] = L"�ŷ�";
			_itemNum[2] = 5;
			
			_itemNum1 = L"1";
			_itemNum2 = L"1";
			_itemNum3 = L"3";
			break;
		
		case 2:
		
			_itemName1 = L"�� �Ƹ�";
			_itemType[0] = L"����";
			_itemNum[0] = 1;
			
			_itemName2 = L"�� ��";
			_itemType[1] = L"�ŷ�";
			_itemNum[1] = 3;
			
			_itemName3 = L"�ΰ���";
			_itemType[2] = L"�ŷ�";
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

		D2DRENDERER->RenderText(1230 - 80, 295, _itemName1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
		D2DRENDERER->RenderText(1680 - 80, 295, _itemNum1, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
		D2DRENDERER->RenderText(1765 - 80, 295, _itemNum1M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");

		D2DRENDERER->RenderText(1230, 407, _itemName2, 35,D2DRenderer::DefaultBrush::White,DWRITE_TEXT_ALIGNMENT_LEADING,L"�������Bold");
		D2DRENDERER->RenderText(1680, 407, _itemNum2, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
		D2DRENDERER->RenderText(1765, 407, _itemNum2M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");

		D2DRENDERER->RenderText(1230, 475, _itemName3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
		D2DRENDERER->RenderText(1680, 475, _itemNum3, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
		D2DRENDERER->RenderText(1765, 475, _itemNum3M, 35, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");

		switch (_type)
		{
		case 0:
			IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1123, 320), 1, 0, 0.8f);
			{
				wstring Num = to_wstring(_it->getItemInfo(L"��", 1).price);
				D2DRENDERER->RenderText(1275 , 557, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");

				Num = to_wstring(_inven->getMoney() - _it->getItemInfo(L"��", 1).price);
				if (_inven->getMoney() < _it->getItemInfo(L"��", 1).price)
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				}
				else
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				}
				D2DRENDERER->RenderText(1325, 700, L"���ݷ� 15 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				D2DRENDERER->RenderText(1325, 750, L"ũ��Ƽ�� 10 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				floatRect rc;
				rc.update(Vector2(1455, 895), Vector2(200, 85), pivot::CENTER);

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc.getRect(), _ptMouse))
				{
					if (_inven->getMoney() >= _it->getItemInfo(L"��", 1).price
						&& _inven->getCount(L"�ŷ�",2) >= 2 && _inven->getCount(L"�ŷ�", 0) >= 3)
					{
						_inven->getItem(L"��", 1, 1, true);
						_inven->deleteItem(L"�ŷ�", 2);
						_inven->deleteItem(L"�ŷ�", 2);
						_inven->deleteItem(L"�ŷ�", 0);
						_inven->deleteItem(L"�ŷ�", 0);
						_inven->deleteItem(L"�ŷ�", 0);
					}
				}
			}
			break;
		case 1:
			IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1123, 320), 0, 0, 0.8f);
			{
				wstring Num = to_wstring(_it->getItemInfo(L"�Ӹ�", 1).price);
				D2DRENDERER->RenderText(1275, 557, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");

				Num = to_wstring(_inven->getMoney() - _it->getItemInfo(L"�Ӹ�", 1).price);
				if (_inven->getMoney() < _it->getItemInfo(L"�Ӹ�", 1).price)
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				}
				else
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				}

				D2DRENDERER->RenderText(1325, 700-30, L"ü�� 10 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				D2DRENDERER->RenderText(1325, 750-30, L"���� 10 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				D2DRENDERER->RenderText(1325, 800-30, L"�������׷� 10 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				floatRect rc;
				rc.update(Vector2(1455, 895), Vector2(200, 85), pivot::CENTER);

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc.getRect(), _ptMouse))
				{
					if (_inven->getMoney() >= _it->getItemInfo(L"�Ӹ�", 1).price
						&& _inven->getCount(L"�ŷ�", 1) >= 1 && _inven->getCount(L"�ŷ�", 5) >= 3)
					{
						_inven->getItem(L"�Ӹ�", 1, 1, true);
						_inven->deleteItem(L"�ŷ�", 1);
						_inven->deleteItem(L"�ŷ�", 5);
						_inven->deleteItem(L"�ŷ�", 5);
						_inven->deleteItem(L"�ŷ�", 5);
					}
				}
			}
			break;
		case 2:
			IMAGEMANAGER->findImage("weapon")->frameRender(Vector2(1123, 320), 2, 0, 0.8f);
			{
				wstring Num = to_wstring(_it->getItemInfo(L"����", 1).price);
				D2DRENDERER->RenderText(1275, 557, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");

				Num = to_wstring(_inven->getMoney() - _it->getItemInfo(L"����", 1).price);
				if (_inven->getMoney() < _it->getItemInfo(L"����", 1).price)
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				}
				else
				{
					D2DRENDERER->RenderText(1370, 595, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				}
				


				D2DRENDERER->RenderText(1325, 650, L"ü�� 10 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				D2DRENDERER->RenderText(1325, 685, L"���� 10 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				D2DRENDERER->RenderText(1325, 720, L"ũ��Ƽ�� 10 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				D2DRENDERER->RenderText(1325, 755 , L"�������׷� 5 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");
				D2DRENDERER->RenderText(1325, 790 , L"�ĵ����׷� 5 ����", 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"�������Bold");

				floatRect rc;
				rc.update(Vector2(1455, 895), Vector2(200, 85), pivot::CENTER);

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc.getRect(), _ptMouse))
				{
					if (_inven->getMoney() >= _it->getItemInfo(L"����", 1).price
						&& _inven->getCount(L"�ŷ�", 3) >= 1 && _inven->getCount(L"�ŷ�", 4) >= 2)
					{
						_inven->getItem(L"����", 1, 1, true);
						_inven->deleteItem(L"�ŷ�", 3);
						_inven->deleteItem(L"�ŷ�", 4);
						_inven->deleteItem(L"�ŷ�", 4);
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


